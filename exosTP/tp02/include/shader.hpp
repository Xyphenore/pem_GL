#ifndef SHADER_HPP
#define SHADER_HPP

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>


class Shader {
public:
    Shader() = delete;

    /// Create a shader with a path to a shader
    Shader( GLenum type, std::filesystem::path shader );

    Shader( const Shader& ) = delete;

    Shader( Shader&& ) noexcept = default;

    Shader& operator=( const Shader& ) = delete;

    Shader& operator=( Shader&& ) noexcept = default;

    ~Shader() noexcept;


    [[nodiscard]] GLuint getID() const;

private:
    // Alias utilisée par toutes les exceptions lancées durant l’initialisation de l’application
    using initialisation_error = std::runtime_error;


    GLuint id_{};

    std::filesystem::path shaderPath_;


    void verifyType( GLenum type ) const;

    static void verifyPath( std::filesystem::path path ) ;

    static std::ostringstream getContentFromFile( std::filesystem::path path );

    void compileShader();

    static std::string getName( GLenum type );
};

inline GLuint Shader::getID() const {
    return id_;
}

inline Shader::~Shader() noexcept {
    glDeleteShader( id_ );
}

inline std::string Shader::getName( const GLenum type ) {
    std::string name;

    switch(type) {
        case GL_FRAGMENT_SHADER :
            name = "GL_FRAGMENT_SHADER";
            break;

        case GL_VERTEX_SHADER :
            name = "GL_VERTEX_SHADER";
            break;

        default :
            throw std::invalid_argument("The given type is unknown");
    }

    return name;
}

inline void Shader::verifyType( const GLenum type ) const {
    switch( type ) {
        case GL_VERTEX_SHADER : [[fallthrough]];
        case GL_FRAGMENT_SHADER : break;

        default :
            throw std::invalid_argument(std::string{ getName(type) + " is not a valid type"});
    }
}

inline void Shader::verifyPath( const std::filesystem::path path ) {
    if ( std::empty( path ) ) {
        throw std::invalid_argument( "Le chemin fourni est vide" );
    }

    if ( !std::filesystem::exists( path ) ) {
        throw std::invalid_argument( "Le fichier fourni n'existe pas : " + path.string() );
    }
}

inline std::ostringstream Shader::getContentFromFile( std::filesystem::path path ) {
    verifyPath(path);

    std::ifstream source( path );
    source.exceptions( std::ios::badbit | std::ios::failbit );

    if ( !source.is_open() ) {
        throw initialisation_error(
                "Impossible de lever cette exception, le flux ifstream n’a pas lancé d’exception avant" );
    }

    // Lien avec les sources du shader et compilation
    std::ostringstream iss;
    iss << source.rdbuf();

    return iss;
}

inline void Shader::compileShader() {
    glCompileShader( id_ );

    int success;
    // Vérification de la compilation du shader
    glGetShaderiv( id_, GL_COMPILE_STATUS, &success );

    if ( 0 == success ) {
        std::array<char, 512> infoLog;
        glGetShaderInfoLog( id_, infoLog.size(), nullptr, infoLog.data() );

        std::string errorMsg( "ERROR::SHADER::VERTEX::COMPILATION_FAILED : " );
        errorMsg.append( shaderPath_.filename().string() + " : " );
        errorMsg.append( infoLog.data() );


        throw std::runtime_error( errorMsg );
    }
}

inline Shader::Shader( const GLenum type, const std::filesystem::path shader )
: id_(), shaderPath_(shader) {
    verifyType(type);

    // Création du vertex shader
    // TODO Vérifier si l'allocation s'est bien passée
    id_ = glCreateShader( type );

    const auto content = getContentFromFile( shaderPath_ ).str();

    const auto* const content_c_str = content.c_str();
    glShaderSource( id_, 1, &content_c_str, nullptr );

    compileShader();
}


#endif //SHADER_HPP
