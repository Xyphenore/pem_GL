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

#ifndef GLENGINE_GLFW_GLFW_HPP
#define GLENGINE_GLFW_GLFW_HPP

#ifndef __cplusplus
#error Un compilateur C++ est nécessaire.
#endif

#if __cplusplus < 201703L
#error GL_Engine a été développée pour C++17. Veuillez supprimer cette condition est testé le code à vos risques et périls.
#endif

#include <GLFW/glfw3.h>

#include <string>

#include <glengine/utility.hpp>
//#include <glengine/window.hpp>

#include <glengine/glfw/exception_factory.hpp>

// TODO Compléter les fonctions manquantes

// region Classes Amies
namespace gl_engine::interface {
    // Note développeur : Nécessaire pour l’amitié
    class Window_GLFW;
    class SmartDestroyWindow_GLFW;
}
// endregion

/**
 * @brief Espace de noms gl_engine::glfw contient tous les objets concernant et en relation avec la bibliothèque GLFW
 */
namespace gl_engine::glfw {
    class GLFW {
    public:
        void setWindowHint() = delete;

        /**
         * @brief Détruit la fenêtre et le contexte pointés par la poignée fournie.
         *
         * @param [in]window La poignée vers la fenêtre.
         * @post La fenêtre pointée est détruite, ainsi que son contexte.
         *
         * @throws gl_engine::glfw::Not_Initialized Lancée si le contexte GLFW n’a pas été initialisé.
         * @throws gl_engine::glfw::Platform_Error Lancée si une erreur spécifique à la plateforme est survenue.
         *
         * @exceptsafe AUCUNE. Si Not_Initialized est lancée, alors le contexte GLFW n’a pas été initialisé, il suffit donc de l’initialiser.
         * @exceptsafe AUCUNE. Si Platform_Error est lancée, alors l'objet GLFW est dans un état indéfini.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see [GLFW-Error_Code-Platform_Error](https://www.glfw.org/docs/3.3/group__errors.html#gad44162d78100ea5e87cdd38426b8c7a1)
         *
         * @note L’exception gl_engine::glfw::Platform_Error est expliqué dans le lien fourni.
         */
        void destroyWindow( GLFWwindow* window );

        void makeCurrentContext( GLFWwindow* window );

    private:
        GLFW();
        ~GLFW() noexcept;

        /**
         * @brief Retourne une référence vers l’instance de GLFW, ou la crée.
         * @throws TODO
         * @exceptsafe TODO
         *
         * @version 1.0
         * @since 0.1
         *
         * @see [GLFW](https://www.glfw.org/docs/3.3/intro_guide.html)
         */
        static GLFW& getInstance() {
            static gl_engine::glfw::GLFW glfw;
            return glfw;
        }

        friend gl_engine::interface::Window_GLFW;
        friend gl_engine::interface::SmartDestroyWindow_GLFW;
    };



    // https://www.glfw.org/docs/3.1/group__window.html

    /**
     * @brief Fonction utilisée pour afficher les messages d'erreur de GLFW.
     * @throws gl_engine::App::glfw_exception Lancée si une erreur GLFW survient.
     * @note Si cette fonction appel std::terminate à cause de l'objet ErrorCode.
     * @note Alors il y a une erreur entre les codes renvoyés par GLFW et la représentation de ces codes dans la classe
     * @note gl_engine::glfw::glfw_exception, c’est une erreur de conception
     */
    static constexpr GLFWerrorfun DEFAULT_ERROR_CALLBACK_FUNCTION = []
            ( const int errorCode, const char* const errorMessage ) {
        throw *glfw::ExceptionFactory::createException( ErrorCode(errorCode), errorMessage );
    };

//    // region Interface gl_engine<=>glfw
//
//
//    // https://www.glfw.org/docs/3.1/group__context.html
//    // Paramètre la fréquence de rendu verticale
//    void swapInterval( int interval ) {
//        ::glfwSwapInterval( interval );
//    }
//
//    bool extensionSupported( std::string extension );
//
//    GLFWwindowposfun setWindowPosCallback( gl_engine::Window& window, GLFWwindowposfun cbfun ) {
//        return ::glfwSetWindowPosCallback( window.get(), cbfun );
//    }
//
//    GLFWwindowrefreshfun setWindowRefreshCallback( gl_engine::Window& window, GLFWwindowrefreshfun cbfun ) {
//        return ::glfwSetWindowRefreshCallback( window.get(), cbfun );
//    }
//
//    void setWindowShouldClose( gl_engine::Window& window, int value ) {
//        ::glfwSetWindowShouldClose( window.get(), value );
//    }
//
//    void setWindowSize( gl_engine::Window& window, int width, int height ) {
//        ::glfwSetWindowSize( window.get(), width, height );
//    }
//
//    void setWindowSize( gl_engine::Window& window, Dimension size ) {
//        ::glfwSetWindowSize( window.get(), size.width, size.height );
//    }
//
//    GLFWwindowsizefun setWindowSizeCallback( gl_engine::Window& window, GLFWwindowsizefun cbfun ) {
//        return ::glfwSetWindowSizeCallback( window.get(), cbfun );
//    }
//
//    void setWindowTitle( gl_engine::Window& window, const std::string& title ) {
//        ::glfwSetWindowTitle( window.get(), title.c_str() );
//    }
//
//    // TODO Remplacer par une méthode dans la classe
//    // TODO changer le type de retour de get() en const pointeur
//    // TODO Ou supprimer la méthode get(), seulement faire une classe interface entre Window et GLFW
//    // TODO de telle façon que seule la méthode get() soit disponible pour la classe statique GLFW
//    void showWindow( const gl_engine::Window& window ) {
//        ::glfwShowWindow( window.get() );
//    }
//
//    // TODO Rendre cette méthode non disponible à l'utilisateur hors de la classe
//    void swapBuffers( gl_engine::Window& window ) {
//        ::glfwSwapBuffers( window.get() );
//    }
//
//    void waitEvents() {
//        ::glfwWaitEvents();
//    }
//
//    // TODO Créer des types target et hint
//    void windowHint( int target, int hint ) {
//        ::glfwWindowHint( target, hint );
//    }
//
//    // Retourne la valeur du drapeau, on peut donc convertir le type en booléen
//    int windowShouldClose( const gl_engine::Window& window ) {
//        return ::glfwWindowShouldClose( window.get() );
//    }
    // endregion

    inline void GLFW::makeCurrentContext( GLFWwindow* window ) {
        ::glfwMakeContextCurrent(window);
    }
}


namespace gl_engine {
    class Window;
    class GLFWwindowDestroyer;
}

namespace gl_engine::interface {
    /**
     * @brief Interface entre l’objet gl_engine::glfw::GLFW et gl_engine::Window.\n
     * @brief Elle permet l’instanciation de l’objet gl_engine::glfw::GLFW.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::Window
     * @see gl_engine::glfw::GLFW
     */
    class Window_GLFW final {
        /*
         * Note développeur :
         * Cette classe existe pour empêcher l’accès aux données privées de gl_engine::glfw::GLFW par l'objet gl_engine::Window.
         * Et pour avoir une seule instance de l’objet gl_engine::glfw::GLFW
         */
    private:
        /**
         * @brief Retourne l’instance de l’objet gl_engine::glfw::GLFW, ou le crée s’il est inexistant.
         *
         * @return Retourne l’instance de GLFW.
         *
         * @post La même instance est retournée.
         * @post L’instance de l’objet GLFW est dans un état valide.
         *
         * @throws std::bad_alloc Lancée si la mémoire est insuffisante pour allouer l’objet gl_engine::glfw::GLFW.
         * @throws gl_engine::glfw::Platform_Error Lancée si une erreur survient durant l’initialisation de l’objet GLFW.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see gl_engine::glfw::GLFW
         * @see [GLFW-Error_Code-Platform_Error](https://www.glfw.org/docs/3.3/group__errors.html#gad44162d78100ea5e87cdd38426b8c7a1)
         * @see [GLFW-Init](https://www.glfw.org/docs/3.3/group__init.html#ga317aac130a235ab08c6db0834907d85e)
         *
         * @note Cette fonction doit être appelée sur le thread principal.
         */
        static auto& getInstance() {
            return gl_engine::glfw::GLFW::getInstance();
        }

        friend class gl_engine::Window;
    };

    /**
     * @brief Interface entre l’objet gl_engine::glfw::GLFW et gl_engine::GLFWwindowDestroyer.\n
     * @brief Elle permet de détruire une fenêtre GLFW et son contexte.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::GLFWwindowDestroyer
     * @see gl_engine::glfw::GLFW
     */
    class SmartDestroyWindow_GLFW final {
        /*
         * Note développeur :
         * Cette classe existe pour limiter l’accès à l’objet gl_engine::glfw::GLFW par l'objet gl_engine::GLFWwindowDestroyer.
         * Pour seulement lui permettre de détruire une fenêtre GLFW pointée par le pointeur contenu
         * dans un gl_engine::smartGLFWwindow.
         */
    private:
        /**
         * @brief Détruit la fenêtre pointée par la poignée fournie.
         *
         * @param [in]window La poignée vers la fenêtre à détruire.
         * @post La fenêtre et le contexte ont été détruit.
         *
         * @throws gl_engine::glfw::Not_Initialized Lancée si le contexte GLFW n’a pas été initialisé.
         * @throws gl_engine::glfw::Platform_Error Lancée si une erreur spécifique à la plateforme est survenue.
         * @exceptsafe AUCUNE. Si Not_Initialized est lancée alors le contexte GLFW n’a pas été initialisé, il suffit donc de l’initialiser.
         * @exceptsafe AUCUNE. Si Platform_Error est lancée alors l’objet GLFW est dans un état indéfini.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see gl_engine::glfw::GLFW
         * @see gl_engine::GLFWwindowDestroyer
         * @see gl_engine::smartGLFWwindow
         * @see void gl_engine::glfw::GLFW::destroyWindow( GLFWwindow* window )
         * @see [GLFW-DestroyWindow](https://www.glfw.org/docs/3.3/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2)
         *
         * @note Cette fonction doit être appelée sur le thread principal.
         * @note L’exception gl_engine::glfw::Platform_Error est expliqué dans le lien fourni.
         */
        static void destroyWindow( GLFWwindow* const window ) {
            gl_engine::glfw::GLFW::getInstance().destroyWindow(window);
        }

        friend class gl_engine::GLFWwindowDestroyer;
    };
}

#endif // GLENGINE_GLFW_GLFW_HPP
