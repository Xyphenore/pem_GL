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

#include <glengine/glfw/glfw.hpp>

#include <string>
#include <unordered_map>

namespace gl_engine::glfw {
    GLFW::GLFW() {
        ::glfwSetErrorCallback( DEFAULT_ERROR_CALLBACK_FUNCTION );

        try {
            ::glfwInit();
        }
        catch ( const glfw::Exception& ) {
            // Remise dans l’état précédent l’appel du constructeur.
            ::glfwSetErrorCallback(nullptr);
            throw;
        }
    }

    GLFW::~GLFW() noexcept {
        ::glfwTerminate();
    }

    void GLFW::destroyWindow( GLFWwindow* window ) {
        ::glfwDestroyWindow(window);
    }

    // https://www.glfw.org/docs/3.1/group__window.html

    // region Interface gl_engine<=>glfw
//    void init() {
//        static bool initialized = false;
//
////        const auto success = ::glfwInit();
////
////        if ( GLFW_FALSE == success ) {
////            const char* description = nullptr;
////            const auto code = ::glfwGetError( &description );
////
////            gl_engine::GLFWErrorCallback( code, description );
////        }
////
////        ::glfwSetErrorCallback( gl_engine::GLFWErrorCallback );
////
////        ::glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, GL_CONTEXT_VERSION_MAJOR );
////        ::glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, GL_CONTEXT_VERSION_MINOR );
////        ::glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
////
////        // Précise un anticrénelage de 4 couches d’échantillonnage
////        //::glfwWindowHint( GLFW_SAMPLES, 4 );
////
////#ifdef __APPLE__
////        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
////#endif
//
//        if ( !initialized ) {
//            // ça part de là !
//            // Définition de l'erreur callback
//
//
//            if ( !static_cast<bool>(  ) ) {
//                // Lancer une exception
//            }
//
//            try {
//                // Indique la spécification d’OpenGL utilisé
//                ::glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
//                ::glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
//                ::glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
//
//                // Précise un anticrénelage de 4 couches d’échantillonnage
//                ::glfwWindowHint( GLFW_SAMPLES, 4 );
//
//#ifdef __APPLE__
//                ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//            }
//            catch ( const gl_engine::glfw::Exception& ) {
//                ::glfwTerminate();
//
//                throw;
//            }
//
//            initialized = true;
//        }
//
//
//    }

    bool extensionSupported( std::string extension ) {
        static std::unordered_map<std::string, bool> extensions;

        if ( const auto& findItems = extensions.find(extension);
                findItems != extensions.cend() ) {
            return findItems->second;
        }

        const bool found = ::glfwExtensionSupported(extension.c_str());

        extensions.emplace(std::move(extension), found);

        return found;
    }
    // endregion
}
