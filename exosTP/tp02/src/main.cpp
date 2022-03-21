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


#include <vector>
#include <string_view>
#include <string>
#include <filesystem>

#include <glengine/app.hpp>
#include <glengine/shaderProgram.hpp>
#include <glengine/shader.hpp>

// Préciser le dossier de la bibliothèque
#include "tp02/config.hpp"



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
}

namespace xyf {
    namespace cc = clean_code;

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

    const std::filesystem::path shaders_directory{ _resources_directory / "shaders" };

    using namespace gl_engine;

    const Window::Settings settings{
            Dimension{800, 800},
            "Test OpenGL TP 2"
    };

    const auto app = App::createApp();
    app->addWindow(std::make_unique<Window>(settings));

    const auto vertexShader = AbstractShader( Shader_t::VERTEX, Content( Path( shaders_directory / "shader.vert" ) ) );
    const auto fragmentShader = AbstractShader( Shader_t::FRAGMENT, Content( Path( shaders_directory / "shader.frag" ) ) );
    auto program = ShaderProgram();
    program.attachShader({vertexShader, fragmentShader});


    // Tableau de sommets
    std::vector<float> vertices = {
            // position            // colors
            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

            0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f
    };

    try {
        // Création d’un VAO
        cc::ID cube;
        glGenVertexArrays( 1, &cube );

        glBindVertexArray( cube );

        // On génère le VBO
        cc::ID verticesBuffer;
        // Génère 1 buffer, dont l’id sera stocké dans verticesBuffer
        glGenBuffers( 1, &verticesBuffer );

        // Indique à OpenGL que le tampon généré est un ARRAY BUFFER ↔ tampon de sommets
        glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer );
        // Transfère les sommets dans le ARRAY BUFFER
        glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( GLfloat ), vertices.data(), GL_STATIC_DRAW );

        // Interprétation des valeurs contenues dans le buffer
        // 1er 0 <-> location = 0 (dans le vertex shader)
        // 3 ↔ nombre de valeurs contenues dans un sommet
        // 4ᵉ paramètre indique s’il faut normaliser les valeurs fournies
        constexpr auto numberCoordinates = 3;
        glVertexAttribPointer( 0, numberCoordinates, GL_FLOAT, GL_FALSE, 2 * numberCoordinates * sizeof( GLfloat ),
                               static_cast<void*>(0) );
        glEnableVertexAttribArray( 0 );

        glVertexAttribPointer( 1, numberCoordinates, GL_FLOAT, GL_FALSE, 2 * numberCoordinates * sizeof( GLfloat ),
                               reinterpret_cast<void*>(numberCoordinates * sizeof( GLfloat )) );
        glEnableVertexAttribArray( 1 );

        // Unbind les buffers useless
        glBindVertexArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );



        // Suppression de la face arrière de la forme

//        // Activation de la fonction permettant de supprimer les faces non visibles
//        glEnable(GL_CULL_FACE);
//
//        // Indique que l’on coupe la face arrière
//        glCullFace(GL_BACK);
//
//        // Définition de la face avant comme étant la suite de sommet dans l’ordre horaire
//        // Ordre antihoraire <=> GL_CCW
//        glFrontFace(GL_CW);


        // Indique à OpenGL de dessiner les polygones en mode filaire
        // 1er ↔ Applique le second paramètre à l’avant et l’arrière des polygones
        // 2ᵉ ↔ On dessine des lignes (G_FILL <=> remplir les polygones)
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        // Boucle de rendu
        auto windowPtr = app->getWindow()->get();
        while ( false == ::glfwWindowShouldClose( windowPtr ) ) {
            // Inputs
            xyf::processInput( windowPtr );

            ::_update_fps_counter(windowPtr, std::string{settings.title} );

            // Rendu

            // Configuration de la couleur à mettre dans le tampon
            glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            // DRAWING

            // Utilisation du programme de shaders
            program.use();


            // Dessin
            // Le type de primitive, l’index de départ de sommets, puis le nombre de sommets
            glBindVertexArray( cube );

            constexpr auto numberVertices = 12*3;
            glDrawArrays( GL_TRIANGLES, 0, numberVertices );

            glBindVertexArray( 0 );


            // Call events
            ::glfwPollEvents();
            ::glfwSwapBuffers( windowPtr );
        }

        glDeleteBuffers( 1, &verticesBuffer );

        glDeleteVertexArrays( 1, &cube );
    }
    catch ( const std::exception& ) {
        ::glfwTerminate();
        throw;
    }


    ::glfwTerminate();
    return 0;
}
