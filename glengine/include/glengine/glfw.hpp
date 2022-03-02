/*
 * PEM_GL - Copyright © 2022 DAVID Axel
 * Mail to:
 * axel.david@etu.univ-amu.fr
 *
 * PEM_GL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * PEM_GL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * PEX_GL - Copyright © 2022 DAVID Axel
 * Mail to:
 * axel.david@etu.univ-amu.fr
 *
 * PEX_GL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * PEX_GL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * Bidon_OpenGL - Copyright © 2022 DAVID Axel, GOI Suzy
 * Mail to:
 * axel.david@etu.univ-amu.fr
 * muriel.coet@etu.univ-amu.fr
 *
 * Bidon_OpenGL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Bidon_OpenGL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GLENGINE_GLFW_HPP
#define GLENGINE_GLFW_HPP

#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include <map>

#include <glengine/utility.hpp>
#include <glengine/window.hpp>

namespace gl_engine::glfw {
    // https://www.glfw.org/docs/3.1/group__window.html

    /**
         * @brief Exception lancée si une erreur de GLFW survient.
         */
    using glfw_exception = std::runtime_error;
    /**
     * @brief Fonction utilisée pour afficher les messages d'erreur de GLFW.
     * @throws gl_engine::App::glfw_exception Lancée si une erreur GLFW survient.
     * @exceptsafe BASE. TODO A déterminer
     */
    static constexpr GLFWerrorfun DEFAULT_ERROR_CALLBACK_FUNCTION = []
            ( const int errorCode, const char* const errorMessage ){
        throw glfw_exception("Erreur " + std::to_string(errorCode) + " : " + errorMessage );
    };

    void init() {
        static bool initialized = false;

//        const auto success = ::glfwInit();
//
//        if ( GLFW_FALSE == success ) {
//            const char* description = nullptr;
//            const auto code = ::glfwGetError( &description );
//
//            gl_engine::GLFWErrorCallback( code, description );
//        }
//
//        ::glfwSetErrorCallback( gl_engine::GLFWErrorCallback );
//
//        ::glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, GL_CONTEXT_VERSION_MAJOR );
//        ::glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, GL_CONTEXT_VERSION_MINOR );
//        ::glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
//
//        // Précise un anticrénelage de 4 couches d’échantillonnage
//        //::glfwWindowHint( GLFW_SAMPLES, 4 );
//
//#ifdef __APPLE__
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

        if ( !initialized ) {
            // ça part de là !
            // Définition de l'erreur callback
            ::glfwSetErrorCallback( DEFAULT_ERROR_CALLBACK_FUNCTION );

            if ( !static_cast<bool>( ::glfwInit() ) ) {
                // Lancer une exception
            }

            // Indique la spécification d’OpenGL utilisé
            ::glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
            ::glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
            ::glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

            // Précise un anticrénelage de 4 couches d’échantillonnage
            ::glfwWindowHint( GLFW_SAMPLES, 4 );

#ifdef __APPLE__
            ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        }

        initialized = true;
    }

    void terminate() {
        ::glfwTerminate();
    }

    // https://www.glfw.org/docs/3.1/group__context.html
    // Paramètre la fréquence de rendu verticale
    void swapInterval( int interval ) {
        ::glfwSwapInterval( interval );
    }

    bool extensionSupported( std::string extension ) {
        static std::map<std::string, bool> extensions;

        if ( const auto& findItems = extensions.find(extension);
                findItems != extensions.cend() ) {
            return findItems->second;
        }

        const bool found = ::glfwExtensionSupported(extension.c_str());

        extensions.emplace(std::move(extension), found);

        return found;
    }

    GLFWwindowposfun setWindowPosCallback( Window& window, GLFWwindowposfun cbfun ) {
        return ::glfwSetWindowPosCallback( window.get(), cbfun );
    }

    GLFWwindowrefreshfun setWindowRefreshCallback( Window& window, GLFWwindowrefreshfun cbfun ) {
        return ::glfwSetWindowRefreshCallback( window.get(), cbfun );
    }

    void setWindowShouldClose( Window& window, int value ) {
        ::glfwSetWindowShouldClose( window.get(), value );
    }

    void setWindowSize( Window& window, int width, int height ) {
        ::glfwSetWindowSize( window.get(), width, height );
    }

    void setWindowSize( Window& window, Dimension size ) {
        ::glfwSetWindowSize( window.get(), size.width, size.height );
    }

    GLFWwindowsizefun setWindowSizeCallback( Window& window, GLFWwindowsizefun cbfun ) {
        return ::glfwSetWindowSizeCallback( window.get(), cbfun );
    }

    void setWindowTitle( Window& window, const std::string& title ) {
        ::glfwSetWindowTitle( window.get(), title.c_str() );
    }

    // TODO Remplacer par une méthode dans la classe
    // TODO changer le type de retour de get() en const pointeur
    // TODO Ou supprimer la méthode get(), seulement faire une classe interface entre Window et GLFW
    // TODO de telle façon que seule la méthode get() soit disponible pour la classe statique GLFW
    void showWindow( const Window& window ) {
        ::glfwShowWindow( window.get() );
    }

    // TODO Rendre cette méthode non disponible à l'utilisateur hors de la classe
    void swapBuffers( Window& window ) {
        ::glfwSwapBuffers( window.get() );
    }

    void waitEvents() {
        ::glfwWaitEvents();
    }

    // TODO Créer des types target et hint
    void windowHint( int target, int hint ) {
        ::glfwWindowHint( target, hint );
    }

    // Retourne la valeur du drapeau, on peut donc convertir le type en booléen
    int windowShouldClose( const Window& window ) {
        return ::glfwWindowShouldClose( window.get() );
    }
}

#endif // GLENGINE_GLFW_HPP
