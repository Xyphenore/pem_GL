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
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <memory>
#include <vector>
#include <string_view>
#include <string>
#include <filesystem>
#include <iostream>

#include <glengine/shaderProgram.hpp>
#include <glengine/shader.hpp>
#include <glengine/utility.hpp>
#include <glengine/window.hpp>

#include <stbimage/stb_image.h>

#include <glengine/glfw/exception_factory.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>

// Préciser le dossier de la bibliothèque
#include "tp03-texture/config.hpp"

namespace xyf::clean_code {
    /// Charge GLAD en lui passant la fonction glfwGetProcAddress
    /// @throws initialisation_error Lancée si GLAD n’a pas été chargé.
    static void loadGLAD() {
        // Vérification du chargement de GLAD
        // On lui demande de charger la fonction permettant d’obtenir les adresses mémoire
        if ( 0 == ::gladLoadGLLoader( reinterpret_cast<GLADloadproc>(::glfwGetProcAddress) ) ) {
            throw std::runtime_error( "Impossible de charger GLAD" );
        }
    }
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

    using namespace gl_engine;

    try {
        const std::filesystem::path _shaders_directory{ _resources_directory / "shaders" };

        Dimension d;
        d.width = 800;
        d.height = 600;
        Window window(d, "OpenGL-Texture", Window_t::WINDOWED );
        window.becomeContext();

        cc::loadGLAD();

        AbstractShader vertex( Shader_t::VERTEX, Content(Path(_shaders_directory / "shader.vert") ) );
        AbstractShader fragment( Shader_t::FRAGMENT, Content( Path( _shaders_directory / "shader.frag") ) );

        ShaderProgram program;
        program.attachShader({vertex, fragment});

        // Tableau de sommets
        const std::vector<float> vertices = {
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // 0  0
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // 1  1
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // 2  2
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // 3  3

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f, // 0  4
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f, // 1  5
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f, // 2  6
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f, // 3  7

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // 0  8
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // 1  9
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // 2 10
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // 3 11

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // 0 12
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // 1 13
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // 2 14
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // 3 15

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // 0 16
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // 1 17
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // 2 18
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // 3 19

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // 0 20
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // 1 21
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // 2 22
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f  // 3 23
        };

        const std::vector<unsigned int> indices = {
                2,  1,  0, // 0 1 2
                0,  3,  2, // 2 3 0

                4,  5, 6,
                6,  7, 4,

                8,  9, 10,
                10, 11,  8,

                14, 13, 12,  // 12 13 14
                12, 15,  14, //14 15 12

                16, 17, 18,
                18, 19, 16,

                22, 21, 20, // 20 21 22
                20, 23, 22  // 22 23 20
        };

//        // Transformations
//        const auto translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f));
//
//        // Mise à l'échelle
//        const auto scale = glm::scale(translation, glm::vec3(0.5f, 0.5f, 0.5f));
//
//        // Sur l'axe x
//        const auto rotation_45 = glm::rotate(scale, glm::radians(45.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
//
//
//        // Camera
//        const auto posCamera = glm::vec3(0.0f, 0.0f, 3.0f);
//
//        // Objectif camera
//        const auto cibleCamera = glm::vec3(0.0f, 0.0f, 0.0f);
//
//        // Détermine vecteur vers le haut à l'origine de la caméra
//        const auto vecY = glm::vec3( 0.0f, 1.0f, 0.0f );
//
//        const auto view = glm::lookAt(posCamera, cibleCamera, vecY);
//
//
//        const auto world = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
//
//        // Récupérer les dimensions de la fenetre
//        const auto projection = glm::perspective(glm::radians(90.0f), 800.0f / 800.0f, 0.1f, 100.0f );


        // Création du programme de shaders
    using ID = unsigned int;

        // Création d’un VAO
        ID cube;
        glGenVertexArrays( 1, &cube );

        glBindVertexArray( cube );

        // On génère le VBO
        ID verticesBuffer;
        // Génère 1 buffer, dont l’id sera stocké dans verticesBuffer
        glGenBuffers( 1, &verticesBuffer );

        // Indique à OpenGL que le tampon généré est un ARRAY BUFFER ↔ tampon de sommets
        glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer );
        // Transfère les sommets dans le ARRAY BUFFER
        glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( GLfloat ), vertices.data(), GL_STATIC_DRAW );

        //std::cout << vertices.size() * sizeof(float);

        // Interprétation des valeurs contenues dans le buffer
        // 1er 0 <-> location = 0 (dans le vertex shader)
        // 3 ↔ nombre de valeurs contenues dans un sommet
        // 4ᵉ paramètre indique s’il faut normaliser les valeurs fournies
        constexpr auto numberCoordinates = 3;
        glVertexAttribPointer( 0, numberCoordinates, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ),
                               static_cast<void*>(0) );
        glEnableVertexAttribArray( 0 );

        glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ),
                               reinterpret_cast<void*>(3 * sizeof( GLfloat )) );
        glEnableVertexAttribArray( 3 );

        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ),
                               reinterpret_cast<void*>(5 * sizeof( GLfloat )) );
        glEnableVertexAttribArray( 2 );

        unsigned int EBO = 0;
        glGenBuffers(1, &EBO);

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( unsigned int ), indices.data(), GL_STATIC_DRAW );

        // Unbind les buffers useless
        glBindVertexArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );


        // Chargement de la texture
        unsigned int texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Chargement de l'image de texture
        int width = 0;
        int height = 0;
        int nbChannels = 0;
        auto data = stbi_load( std::filesystem::path(_resources_directory / "box/box2.jpg").string().c_str(), &width, &height, &nbChannels, 0);

        if ( data != nullptr ) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed loading texture\n";
        }

        stbi_image_free(data);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(program.get(), "textureFrag"), 0);


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

//        const auto uniformModel = glGetUniformLocation( idShaderProgram, "model");
//        const auto uniformWorld = glGetUniformLocation( idShaderProgram, "world" );
//        const auto uniformView = glGetUniformLocation( idShaderProgram, "view" );
//        const auto uniformProjection = glGetUniformLocation( idShaderProgram, "projection");

        // Boucle de rendu
        while ( 0 == ::glfwWindowShouldClose( window.get() ) ) {
            // Inputs
            xyf::processInput( window.get() );

            ::_update_fps_counter(window.get(), window.getTitle() );

//            // Calcul de la matrice rotation en fonction des secondes
//            const auto seconds = ::glfwGetTime();
//
//            const auto model = glm::rotate(rotation_45, static_cast<float>(glm::sin(seconds)), glm::vec3(0.0f,1.0f,0.0f));

//            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//            glUniformMatrix4fv( uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//            glUniformMatrix4fv( uniformWorld, 1, GL_FALSE, glm::value_ptr(world));
//            glUniformMatrix4fv( uniformView, 1, GL_FALSE, glm::value_ptr(view));

            // Rendu

            // Configuration de la couleur à mettre dans le tampon
            glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
            glEnable(GL_DEPTH_TEST);
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

            // DRAWING

            // Utilisation du programme de shaders
            program.use();


            // Dessin
            // Le type de primitive, l’index de départ de sommets, puis le nombre de sommets
            glBindVertexArray( cube );

//            const auto numberVertices = vertices.size() / 6;
//            glDrawArrays( GL_TRIANGLES, 0, numberVertices );
            const auto numberVertices = 6*2*3;
            glDrawElements( GL_TRIANGLES, numberVertices, GL_UNSIGNED_INT, GL_FALSE );

            glBindVertexArray( 0 );


            // Call events
            ::glfwPollEvents();
            ::glfwSwapBuffers( window.get() );
        }

        glDeleteBuffers( 1, &verticesBuffer );

        glDeleteVertexArrays( 1, &cube );
    }
    catch ( const glfw::Exception& e) {
        std::cout << e.what() << std::endl;
    }
    catch ( const std::exception& ) {
        ::glfwTerminate();
        throw;
    }

    std::hash<int> hasher;

    std::cout << "Size of 2void* : " << 2 * sizeof(void*) << '\n';
//    std::cout << "Size of Shader_t : " << sizeof(gl_engine::Shader::Type) << '\n';
//    std::cout << "Size of Shader : " << sizeof(gl_engine::Shader) << '\n';
//    std::cout << "Size of Content : " << sizeof(gl_engine::utility::Content) << '\n';
//    std::cout << "Size of Path : " << sizeof(gl_engine::utility::Path) << '\n';
//    std::cout << "Size of String : " << sizeof(std::string) << '\n';
//    std::cout << "Size of const char* : " << sizeof(const char*) << '\n';
//    std::cout << "Size of FS::Path : " << sizeof(std::filesystem::path) << '\n';
//    std::cout << "Size of ErrorCode : " << sizeof(gl_engine::glfw::ErrorCode) << '\n';
//    std::cout << "Size of Exception : " << sizeof(gl_engine::glfw::Exception) << '\n';
//    std::cout << "Size of Exception : " << sizeof(std::exception) << '\n';
//    std::cout << "Size of Window : " << sizeof(gl_engine::Window) << '\n';
//    std::cout << "Size of Hasher : " << hasher(15) << '\n';
//    std::cout << "Size of Title : " << sizeof(glfw::ListErrorCode::Title) << '\n';
//    std::cout << "Size of Creator : " << sizeof(glfw::ListErrorCode::CreateFunction) << '\n';
//    std::cout << "Size of ListErrorCode : " << sizeof(glfw::ListErrorCode) << '\n';
//    std::cout << "Size of Tuple : " << sizeof(glfw::ListErrorCode::Tuple) << '\n';
//    std::cout << "Size of Map : " << glfw::ListErrorCode::list_.size() * sizeof(glfw::ListErrorCode::list_.at(GLFW_NO_ERROR)) << '\n';
//    std::cout << "Size of Factory : " << sizeof(glfw::ExceptionFactory) << '\n';
//    std::cout << "Size of SourceType : " << sizeof(utility::Content::SOURCE_TYPE) << '\n';

    using namespace gl_engine::glfw;

    try {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        //throw InvalidEnum("Invalid Enum");

    }
    catch( InvalidEnum& ) {
        std::cout << "InvalidEnum" << std::endl;
        throw;
    }
    catch( Exception& ) {
        std::cout << "Exception" << std::endl;
        throw;
    }
    catch ( std::exception& ) {
        std::cout << "std" << std::endl;
        throw;
    }
    catch(...) {
        std::cout << "vide" << std::endl;
    }




    return 0;
}
