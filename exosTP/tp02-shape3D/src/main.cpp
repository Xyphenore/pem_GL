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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <memory>
#include <vector>
#include <string_view>
#include <string>
#include <filesystem>
#include <iostream>

// Préciser le dossier de la bibliothèque
#include "tp02-shape3D/config.hpp"

#include "shader.hpp"
#include "shaderProgram.hpp"
#include "window.hpp"
#include "app.hpp"

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

    try {
        const std::filesystem::path _shaders_directory{ _resources_directory / "shaders" };


        const auto app = bidon::App::createApp();

        // Création de la fenêtre
        constexpr cc::WindowSettings settings( 800, 800, "Fenêtre de test", xyf::frameBufferSizeCallback );

        auto window = cc::createWindow( settings );

        app->addWindow(/*Window*/nullptr);

        const Shader vertexShader(GL_VERTEX_SHADER, _shaders_directory / "shader.vert");

        const Shader fragmentShader(GL_FRAGMENT_SHADER, _shaders_directory / "shader.frag");

        // Création du programme de shaders
        const auto idShaderProgram = cc::GLCreateProgram( { vertexShader.getID(), fragmentShader.getID() } );




        // Tableau de sommets
        const std::vector<float> cubeVertices = {
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

        // Mise à l'échelle
        const auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));

        // Sur l'axe x
        const auto rotation_45 = glm::rotate(scale, glm::radians(45.0f), glm::vec3(-1.0f, 1.0f, 0.0f));

        // Transformations
        const auto translation = glm::translate(rotation_45, glm::vec3(0.5f, -0.5f, 0.0f));


        // Camera
        const auto posCamera = glm::vec3(0.0f, 0.0f, 3.0f);

        // Objectif camera
        const auto cibleCamera = glm::vec3(0.0f, 0.0f, 0.0f);

        // Détermine vecteur vers le haut à l'origine de la caméra
        const auto vecY = glm::vec3( 0.0f, 1.0f, 0.0f );

        const auto view = glm::lookAt(posCamera, cibleCamera, vecY);


        const auto cubeWorld = glm::translate( glm::mat4( 1.0f ), glm::vec3( 0.0f, 0.0f, -5.0f ) );

        // Récupérer les dimensions de la fenetre
        const auto projection = glm::perspective(glm::radians(90.0f), 800.0f / 800.0f, 0.1f, 100.0f );





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
        glBufferData( GL_ARRAY_BUFFER, cubeVertices.size() * sizeof( GLfloat ), cubeVertices.data(), GL_STATIC_DRAW );

        // Interprétation des valeurs contenues dans le buffer
        // 1er 0 <-> location = 0 (dans le vertex shader)
        // 3 ↔ nombre de valeurs contenues dans un sommet
        // 4ᵉ paramètre indique s’il faut normaliser les valeurs fournies
        constexpr auto numberCoordinates = 3;
        glVertexAttribPointer( 0, numberCoordinates, GL_FLOAT, GL_FALSE, 2 * numberCoordinates * sizeof( GLfloat ),
                               reinterpret_cast<void*>(0) );
        glEnableVertexAttribArray( 0 );

        glVertexAttribPointer( 1, numberCoordinates, GL_FLOAT, GL_FALSE, 2 * numberCoordinates * sizeof( GLfloat ),
                               reinterpret_cast<void*>(numberCoordinates * sizeof( GLfloat )) );
        glEnableVertexAttribArray( 1 );

//        // Unbind les buffers useless
//        glBindVertexArray( 0 );
//        glBindBuffer( GL_ARRAY_BUFFER, 0 );


        const std::vector<GLfloat> lightCubeVertices = {
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,

                -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,

                -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,

                0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,

                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,

                -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
        };

        const auto lightModel = glm::mat4(1.0f);

        GLuint lightCube;
        glGenVertexArrays(1, & lightCube);

        glBindVertexArray(lightCube);

        GLuint lightCoordonates;
        glGenBuffers(1, &lightCoordonates );

        glBindBuffer(GL_ARRAY_BUFFER, lightCoordonates);
        glBufferData(GL_ARRAY_BUFFER, lightCubeVertices.size() * sizeof(GLfloat), lightCubeVertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, numberCoordinates, GL_FLOAT, GL_FALSE, 2 * numberCoordinates * sizeof(GLfloat),
                              reinterpret_cast<void*>(0) );
        glEnableVertexAttribArray(0);

        GLuint lightColors;
        glGenBuffers(1, &lightColors);

        glBindBuffer(GL_ARRAY_BUFFER, lightColors);
        glBufferData(GL_ARRAY_BUFFER, lightCubeVertices.size() * sizeof(GLfloat), lightCubeVertices.data(), GL_STATIC_DRAW );

        glVertexAttribPointer(1, numberCoordinates, GL_FLOAT, GL_FALSE, 2 * numberCoordinates * sizeof(GLfloat),
                              reinterpret_cast<void*>(numberCoordinates * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        const auto lightWorld = glm::mat4(1.0f);



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

        const auto uniformModel = glGetUniformLocation( idShaderProgram, "model");
        const auto uniformWorld = glGetUniformLocation( idShaderProgram, "cubeWorld" );
        const auto uniformView = glGetUniformLocation( idShaderProgram, "view" );
        const auto uniformProjection = glGetUniformLocation( idShaderProgram, "projection");


        const auto uniformLightColor = glGetUniformLocation(idShaderProgram, "lightColor");
        const auto lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

        glUseProgram(idShaderProgram);

        glUniform3fv( uniformLightColor, 1, glm::value_ptr(lightColor) );

        // Boucle de rendu
        while ( 0 == ::glfwWindowShouldClose( window.get() ) ) {
            // Inputs
            xyf::processInput( window.get() );

            ::_update_fps_counter(window.get(), std::string{settings.getTitle()} );

            // Calcul de la matrice rotation en fonction des secondes
            const auto seconds = ::glfwGetTime();


            glUniformMatrix4fv( uniformView, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv( uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

            // Rendu

            // Configuration de la couleur à mettre dans le tampon
            glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
            glEnable(GL_DEPTH_TEST);
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

            // DRAWING

            // Utilisation du programme de shaders
            glUseProgram( idShaderProgram );


            // Dessin
            // Le type de primitive, l’index de départ de sommets, puis le nombre de sommets
            glBindVertexArray( cube );

            const auto model = glm::rotate(translation, static_cast<float>(glm::sin(seconds)), glm::vec3(0.0f,1.0f,0.0f));
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv( uniformWorld, 1, GL_FALSE, glm::value_ptr( cubeWorld ) );


            const auto numberVertices = cubeVertices.size() / 6;
            glDrawArrays( GL_TRIANGLES, 0, numberVertices );



            glBindVertexArray(lightCube);

            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(lightModel));
            glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, glm::value_ptr(lightWorld));
            glDrawArrays( GL_TRIANGLES, 0, numberVertices);

            glBindVertexArray( 0 );


            // Call events
            ::glfwPollEvents();
            ::glfwSwapBuffers( window.get() );
        }

        glDeleteBuffers( 1, &verticesBuffer );

        glDeleteVertexArrays( 1, &cube );
        glDeleteProgram( idShaderProgram );
    }
    catch ( const std::exception& ) {
        ::glfwTerminate();
        throw;
    }

    return 0;
}
