/*
 * Test_OpenGL - Copyright © 2022 DAVID Axel
 * Mail to: axel.david@etu.univ-amu.fr.
 *
 * Test_OpenGL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Test_OpenGL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <memory>

#include <array>
#include <vector>
#include <string_view>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cmath>

// Préciser le dossier de la bibliothèque
#include "tp01/config.hpp"
#include "glengine/window.hpp"

#include <glengine/utility.hpp>
#include <glengine/shader.hpp>
#include <iostream>

#include <glengine/glfw/exception.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stbimage/stb_image.h>

namespace xyf::clean_code {
    using Width = int;
    using Height = int;
    using Coordinate = GLfloat;
    using ID = GLuint;
    using GrayShade = GLubyte;

    class WindowSettings {
    public:
        constexpr WindowSettings(
                const Width w, const Height h, const std::string_view title, GLFWmonitor* const monitor,
                GLFWwindow* const share, const GLFWframebuffersizefun callback )
                : w_( w ), h_( h ), title_( title.data() ), monitor_( monitor ), shareWindow_( share ),
                  callbackFunction_( callback ) {}

        constexpr WindowSettings(
                const Width w, const Height h, const std::string_view title, const GLFWframebuffersizefun callback )
                : WindowSettings( w, h, title, nullptr, nullptr, callback ) {}

        [[nodiscard]] Width getWidth() const {
            return w_;
        }

        [[nodiscard]] Height getHeight() const {
            return h_;
        }

        [[nodiscard]] std::string_view getTitle() const {
            return title_;
        }

        [[nodiscard]] GLFWmonitor* getMonitor() const {
            return monitor_;
        }

        [[nodiscard]] GLFWwindow* getShareWindow() const {
            return shareWindow_;
        }

        [[nodiscard]] GLFWframebuffersizefun getCallbackFunction() const {
            return callbackFunction_;
        }

    private :
        const Width w_;
        const Height h_;
        const std::string_view title_;

        GLFWmonitor* const monitor_ = nullptr;
        GLFWwindow* const shareWindow_ = nullptr;

        GLFWframebuffersizefun const callbackFunction_;
    };

    // SRC : https://stackoverflow.com/questions/35793672/use-unique-ptr-with-glfwwindow
    /// Destructeur utilisé pour les uniques pointeurs contenant une GLFWwindow
    class GLFWwindowDestroyer {
    public:
        void operator()( GLFWwindow* const window ) const {
            ::glfwDestroyWindow( window );
        }
    };

    using smartGLFWwindow = std::unique_ptr<GLFWwindow, GLFWwindowDestroyer>;

    // Alias utilisée par toutes les exceptions lancées durant l’initialisation de l’application
    using initialisation_error = std::runtime_error;

    /// Crée une fenêtre avec les paramètres passés
    /// @throws initialisation_error Lancée si la création de la fenêtre a échoué.
    /// @see OpenGL::glfwCreateWindow
    static smartGLFWwindow GLFWCreateWindow( const WindowSettings& settings ) {
        smartGLFWwindow window(
                ::glfwCreateWindow( settings.getWidth(), settings.getHeight(), settings.getTitle().data(),
                                    settings.getMonitor(), settings.getShareWindow() ) );

        if ( nullptr == window ) {
            throw initialisation_error( "Impossible d’allouer l’espace nécessaire pour créer la fenêtre" );
        }

        return window;
    }

    /// Charge GLAD en lui passant la fonction glfwGetProcAddress
    /// @throws initialisation_error Lancée si GLAD n’a pas été chargé.
    static void loadGLAD() {
        // Vérification du chargement de GLAD
        // On lui demande de charger la fonction permettant d’obtenir les adresses mémoire
        if ( 0 == ::gladLoadGLLoader( reinterpret_cast<GLADloadproc>(::glfwGetProcAddress) ) ) {
            throw initialisation_error( "Impossible de charger GLAD" );
        }
    }

    static smartGLFWwindow createWindow( const WindowSettings& settings ) {
        auto window = GLFWCreateWindow( settings );

        ::glfwMakeContextCurrent( window.get() );

        // Vérification du chargement de GLAD
        loadGLAD();

        // Définition de la fenêtre de rendu
        // (0,0) <-> coin bas gauche
        glViewport( 0, 0, settings.getWidth(), settings.getHeight() );

        // Note de développement : Mettre en place les fonctions callback avant le démarrage du rendu.
        // Spécification de la fonction de redimensionnement.
        ::glfwSetFramebufferSizeCallback( window.get(), settings.getCallbackFunction() );

        return window;
    }


    //Creating a shader from a file.
    static ID GLCreateShader( const GLenum type, const std::filesystem::path pathSource ) {
        if ( std::empty( pathSource ) ) {
            throw std::invalid_argument( "Le chemin fourni est vide" );
        }

        if ( !std::filesystem::exists( pathSource ) ) {
            throw std::invalid_argument( "Le fichier fourni n'existe pas : " + pathSource.string() );
        }

        std::ifstream source( pathSource );
        source.exceptions( std::ios::badbit | std::ios::failbit );

        if ( !source.is_open() ) {
            throw initialisation_error(
                    "Impossible de lever cette exception, le flux ifstream n’a pas lancé d’exception avant" );
        }


        // Création du vertex shader
        const auto idShader = glCreateShader( type );

        // Lien avec les sources du shader et compilation
        std::stringstream iss;
        iss << source.rdbuf();

        const auto str = iss.str();
        const auto* const c_str = str.c_str();
        glShaderSource( idShader, 1, &c_str, nullptr );
        glCompileShader( idShader );

        int success;
        // Vérification de la compilation du shader
        glGetShaderiv( idShader, GL_COMPILE_STATUS, &success );

        if ( 0 == success ) {
            GLint logSize = 0;
            glGetShaderiv( idShader, GL_INFO_LOG_LENGTH, &logSize );

            //auto infoLog = std::make_unique<char>(logSize);
            auto infoLog = std::make_unique<char[]>(logSize);
            glGetShaderInfoLog( idShader, logSize, nullptr, infoLog.get() );

            std::string errorMsg( "ERROR::SHADER::VERTEX::COMPILATION_FAILED : " );
            errorMsg.append( pathSource.filename().string() + " : " );
            errorMsg.append( std::string{infoLog.get()} );

            glDeleteShader(idShader);

            throw std::runtime_error( errorMsg );
        }

        return idShader;
    }

    static ID GLCreateProgram( const std::initializer_list<ID> idsShader ) {
        // Création du programme de shaders
        const auto idShaderProgram = glCreateProgram();

        for ( const auto id: idsShader ) {
            glAttachShader( idShaderProgram, id );
        }

        glLinkProgram( idShaderProgram );

        int success;
        // Vérification du lien des shaders au programme
        glGetProgramiv( idShaderProgram, GL_LINK_STATUS, &success );

        if ( 0 == success ) {
            std::array<char, 512> infoLog;
            glGetProgramInfoLog( idShaderProgram, infoLog.size(), nullptr, infoLog.data() );

            std::string errorMsg( "ERROR::SHADER::VERTEX::LINK_FAILED : " );
            errorMsg.append( infoLog.data() );

            throw std::runtime_error( errorMsg );
        }

        return idShaderProgram;
    }
}

namespace xyf {
    namespace cc = clean_code;

    static void frameBufferSizeCallback(
            [[maybe_unused]] GLFWwindow* const window, const cc::Width width, const cc::Height height ) {
        glViewport( 0, 0, width, height );
    }

    static void processInput( GLFWwindow* const window ) {
        if ( GLFW_PRESS == ::glfwGetKey( window, GLFW_KEY_ESCAPE ) ) {
            ::glfwSetWindowShouldClose( window, true );
        }
    }
}

// Permet d’afficher le nombre de fps dans le titre de la fenêtre
// src : https://antongerdelan.net/opengl/glcontext2.html
void _update_fps_counter( GLFWwindow* window, const std::string title ) {
    static auto previous_seconds = glfwGetTime();
    static auto frame_count = 0;
    const auto current_seconds = glfwGetTime();
    const auto elapsed_seconds = current_seconds - previous_seconds;
    if (elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        const auto fps = frame_count / elapsed_seconds;
        char tmp[128];
        sprintf(tmp, " @ fps: %.2f", fps);

        const auto newTitle{title + tmp};
        glfwSetWindowTitle(window, newTitle.c_str() );
        frame_count = 0;
    }
    frame_count++;
}

int main() {
    namespace cc = xyf::clean_code;

    // ça part de là !
    ::glfwInit();

    // Indique la spécification d’OpenGL utilisé
    ::glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    ::glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    ::glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    // Précise un anticrénelage de 4 couches d’échantillonnage
    ::glfwWindowHint( GLFW_SAMPLES, 4 );

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Création de la fenêtre
    constexpr cc::WindowSettings settings( 800, 800, "Fenêtre de test", xyf::frameBufferSizeCallback );

    const std::filesystem::path _shaders_directory{ _resources_directory / "shaders" };

//    std::vector<cc::Coordinate> vertices;
//
//    const auto nbPts = 6;
//
//    // Angle en degré
//    const auto angle = 45;
//    const auto rayon = 1;
//    for ( auto i = 0; i < nbPts; ++i ) {
//        vertices.push_back(rayon * std::cos(angle * i) );
//        vertices.push_back(rayon * std::sin(angle * i) );
//    }

    // Tableau de sommets
    constexpr std::array<cc::Coordinate, 12> vertices{ 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f,
                                                       0.5f, 0.0f };

    constexpr std::array<cc::GrayShade, 12> color{ 43, 250, 250, 255, 0, 255, 255, 255, 0, 0, 0, 0 };

    constexpr std::array<cc::ID, 6> id = { 0, 1, 3, 1, 2, 3 };


    try {
        const auto window = cc::createWindow( settings );

        // Création du vertex shader
        const auto idVertexShader = cc::GLCreateShader( GL_VERTEX_SHADER, _shaders_directory / "shader.vert" );

        // Création du fragment shader
        const auto idFragmentShader = cc::GLCreateShader( GL_FRAGMENT_SHADER, _shaders_directory / "shader.frag" );

        // Création du programme de shaders
        const auto idShaderProgram = cc::GLCreateProgram( { idVertexShader, idFragmentShader } );





        const auto idShader = glCreateShader( GL_VERTEX_SHADER );

        // Lien avec les sources du shader et compilation
        std::string src("#version 330 core\n"
                        "\n"
                        "layout (location = 0) in vec3 aPos;\n"
                        "layout (location = 1) in vec3 Color;\n"
                        "\n"
                        "out vec4 VertexColor;\n"
                        "\n"
                        "void main() {\n"
                        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                        "\n"
                        "    VertexColor = vec4(Color, 1.0f);\n"
                        "}");

        std::string src3{"test" + src + "test"};
        std::string_view source{src3};
        source.remove_prefix(4);
        source.remove_suffix(4);
        auto ptr = source.data();
        GLint size = source.size();
        glShaderSource( idShader, 1, &ptr, &size );
        glCompileShader( idShader );

        int success;
        // Vérification de la compilation du shader
        glGetShaderiv( idShader, GL_COMPILE_STATUS, &success );

        if ( 0 == success ) {
            GLint logSize = 0;
            glGetShaderiv( idShader, GL_INFO_LOG_LENGTH, &logSize );

            //auto infoLog = std::make_unique<char>(logSize);
            auto infoLog = std::make_unique<char[]>(logSize);
            glGetShaderInfoLog( idShader, logSize, nullptr, infoLog.get() );

            std::string errorMsg( "ERROR::SHADER::VERTEX::COMPILATION_FAILED : " );
            errorMsg.append( "test : " ).append( std::string{infoLog.get()} );

            glDeleteShader(idShader);

            throw std::runtime_error( errorMsg );
        }







        // Suppression des objets shaders
        glDeleteShader( idVertexShader );
        glDeleteShader( idFragmentShader );

        // Création d’un VAO
        cc::ID idVAO;
        glGenVertexArrays( 1, &idVAO );

        glBindVertexArray( idVAO );

        // On génère le EBO
        cc::ID idEBO;
        glGenBuffers( 1, &idEBO );

        // Injection des indices dans le buffer EBO
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idEBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, id.size() * sizeof( unsigned int ), id.data(), GL_STATIC_DRAW );

        // On génère le VBO
        cc::ID idVBO;
        // Génère 1 buffer, dont l’id sera stocké dans idVBO
        glGenBuffers( 1, &idVBO );

        // Indique à OpenGL que le tampon généré est un ARRAY BUFFER ↔ tampon de sommets
        glBindBuffer( GL_ARRAY_BUFFER, idVBO );
        // Transfère les sommets dans le ARRAY BUFFER
        glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( cc::Coordinate ), vertices.data(), GL_STATIC_DRAW );

        // Interprétation des valeurs contenues dans le buffer
        // 1er 0 <-> location = 0 (dans le vertex shader)
        // 3 ↔ nombre de valeurs contenues dans un sommet
        // 4ᵉ paramètre indique s’il faut normaliser les valeurs fournies
        constexpr auto numberCoordinates = 3;
        glVertexAttribPointer( 0, numberCoordinates, GL_FLOAT, GL_FALSE, numberCoordinates * sizeof( cc::Coordinate ),
                               static_cast<void*>(0) );
        glEnableVertexAttribArray( 0 );

        // On génère le VBO
        cc::ID idVBO2;
        // Génère 1 buffer, dont l’id sera stocké dans idVBO
        glGenBuffers( 1, &idVBO2 );

        // Indique à OpenGL que le tampon généré est un ARRAY BUFFER ↔ tampon de sommets
        glBindBuffer( GL_ARRAY_BUFFER, idVBO2 );
        // Transfère les sommets dans le ARRAY BUFFER
        glBufferData( GL_ARRAY_BUFFER, color.size() * sizeof( unsigned int ), color.data(), GL_STATIC_DRAW );

        glVertexAttribPointer( 1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 3 * sizeof( unsigned char ), static_cast<void*>(0) );
        glEnableVertexAttribArray( 1 );

        // Unbind les buffers useless
        glBindVertexArray( 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );



        // Suppression de la face arrière de la forme

        // Activation de la fonction permettant de supprimer les faces non visibles
        glEnable(GL_CULL_FACE);

        // Indique que l’on coupe la face arrière
        glCullFace(GL_BACK);

        // Définition de la face avant comme étant la suite de sommet dans l’ordre horaire
        // Ordre antihoraire <=> GL_CCW
        glFrontFace(GL_CW);


        // Indique à OpenGL de dessiner les polygones en mode filaire
        // 1er ↔ Applique le second paramètre à l’avant et l’arrière des polygones
        // 2ᵉ ↔ On dessine des lignes (G_FILL <=> remplir les polygones)
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        // Boucle de rendu
        while ( 0 == ::glfwWindowShouldClose( window.get() ) ) {
            // Inputs
            xyf::processInput( window.get() );

            ::_update_fps_counter(window.get(), std::string{settings.getTitle()} );

            // Rendu

            // Configuration de la couleur à mettre dans le tampon
            glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            // DRAWING

            // Utilisation du programme de shaders
            glUseProgram( idShaderProgram );


            // Dessin
            // Le type de primitive, l’index de départ de sommets, puis le nombre de sommets
            glBindVertexArray( idVAO );

//            constexpr auto numberVertices = 3;
//            glDrawArrays( GL_TRIANGLES, 0, numberVertices );
            //glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idEBO );

            glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

            glBindVertexArray( 0 );


            // Call events
            ::glfwPollEvents();
            ::glfwSwapBuffers( window.get() );
        }

        glDeleteBuffers( 1, &idVBO );
        glDeleteBuffers( 1, &idVBO2 );
        glDeleteBuffers( 1, &idEBO );

        glDeleteVertexArrays( 1, &idVAO );
        glDeleteProgram( idShaderProgram );

        GLint error = GL_NO_ERROR;
        while ( glGetError() != GL_NO_ERROR ) {}
        auto shader = glCreateShader(GL_VERTEX_SHADER);
        while ( (error = glGetError()) != GL_NO_ERROR ) {
            std::cout << error << '\n';
        }
        glDeleteShader(shader);
        while ( (error = glGetError()) != GL_NO_ERROR ) {
            std::cout << error << '\n';
        }
        glDeleteShader(shader);
        while ( (error = glGetError()) != GL_NO_ERROR ) {
            std::cout << error << '\n';
        }
    }
    catch ( const std::exception& ) {
        ::glfwTerminate();
        throw;
    }

    ::glfwTerminate();

    std::hash<int> hasher;

    std::cout << "Size of 2void* : " << 2 * sizeof(void*) << '\n';
    std::cout << "Size of Shader_t : " << sizeof(gl_engine::AbstractShader::Type) << '\n';
    std::cout << "Size of Shader : " << sizeof(gl_engine::AbstractShader) << '\n';
    std::cout << "Size of Content : " << sizeof(gl_engine::utility::Content) << '\n';
    std::cout << "Size of Path : " << sizeof(gl_engine::utility::Path) << '\n';
    std::cout << "Size of String : " << sizeof(std::string) << '\n';
    std::cout << "Size of const char* : " << sizeof(const char*) << '\n';
    std::cout << "Size of FS::Path : " << sizeof(std::filesystem::path) << '\n';
    std::cout << "Size of ErrorCode : " << sizeof(gl_engine::glfw::ErrorCode) << '\n';
    std::cout << "Size of Exception : " << sizeof(gl_engine::glfw::Exception) << '\n';
    std::cout << "Size of Exception : " << sizeof(std::exception) << '\n';
    std::cout << "Size of Window : " << sizeof(gl_engine::Window) << '\n';
    std::cout << "Size of Error : " << hasher(15) << '\n';
    std::cout << "Size of Pair : " << sizeof(std::pair<int, std::string>) << '\n';

    stbi_image_free(NULL);


    //gl_engine::Shader test( gl_engine::Shader_t::VERTEX, gl_engine::utility::Content(gl_engine::utility::Path("patate")));



    return 0;
}
