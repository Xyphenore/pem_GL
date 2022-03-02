#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glad/glad.h>
#include <vector>

#include "shader.hpp"

class ShaderProgram {
public:
    ShaderProgram();

    ShaderProgram( const ShaderProgram& ) = delete;

    ShaderProgram( ShaderProgram&& ) noexcept = default;

    ShaderProgram& operator=( const ShaderProgram& ) = delete;

    ShaderProgram& operator=( ShaderProgram&& ) noexcept = default;

    ~ShaderProgram() noexcept;

    ShaderProgram( std::initializer_list<Shader> shaders );

    void use() const;

private:
    GLuint id_;

    std::vector<Shader> shaders_;
};

inline void ShaderProgram::use() const {
    glUseProgram( id_ );
}

inline ShaderProgram::~ShaderProgram() noexcept {
    glDeleteProgram(id_);
}

inline ShaderProgram::ShaderProgram()
: ShaderProgram({}) {}

inline ShaderProgram::ShaderProgram( const std::initializer_list<Shader> shaders )
: id_( glCreateProgram() ) {
    // TODO Vérifier si l'allocation du program a fonctionné

    for ( const auto& shader : shaders ) {
        glAttachShader( shader.getID(), id_ );
    }

    glLinkProgram( id_ );

    int success;
    // Vérification du lien des shaders au programme
    glGetProgramiv( id_, GL_LINK_STATUS, &success );

    if ( 0 == success ) {
        std::array<char, 512> infoLog;
        glGetProgramInfoLog( id_, infoLog.size(), nullptr, infoLog.data() );

        std::string errorMsg( "ERROR::SHADER::VERTEX::LINK_FAILED : " );
        errorMsg.append( infoLog.data() );

        throw std::runtime_error( errorMsg );
    }
}


#endif //SHADERPROGRAM_HPP
