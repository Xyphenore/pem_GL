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

#ifndef GLENGINE_WINDOW_HPP
#define GLENGINE_WINDOW_HPP

#ifndef __cplusplus
#error Un compilateur C++ est nécessaire.
#endif

#if __cplusplus < 201703L
#error GL_Engine a été développée pour C++17. Veuillez supprimer cette condition est testé le code à vos risques et périls.
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <optional>
#include <memory>
#include <functional>

#include <glengine/glfw/glfw.hpp>
#include <glengine/utility.hpp>
#include <glengine/scene.hpp>

namespace gl_engine::glfw {
    class GLFW;
}

// region Code BON
/**
 * @brief Espace de noms contenant toutes les fonctions et objets nécessaires à la bibliothèque GL_Engine.
 *
 * @version 2.0
 * @since 0.1
 * @author Axel DAVID
 *
 * @see gl_engine::Window
 *
 * @note La bibliothèque GL_Engine n’a pas été développée pour être multi-threading. Elle est donc thread-unsafe.
 */
namespace gl_engine {

    /**
     * @brief Destructeur utilisé pour les pointeurs uniques contenants une poignée vers une GLFWwindow.
     *
     * @version 1.0
     * @since 0.1
     * @authors Axel DAVID
     * @authors ratchet freak
     *
     * @see [StackOverflow](https://stackoverflow.com/questions/35793672/use-unique-ptr-with-glfwwindow)
     * @see [ratchet freak](https://stackoverflow.com/users/731620/ratchet-freak)
     * @note L’idée pour contourner le problème vient du lien fourni, le code écrit viens de moi Axel DAVID.
     */
    class GLFWwindowDestroyer {
    public:
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
         * @see gl_engine::smartGLFWwindow
         * @see void gl_engine::glfw::GLFW::destroyWindow( GLFWwindow* window )
         * @see [GLFW-DestroyWindow](https://www.glfw.org/docs/3.3/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2)
         *
         * @note Cette fonction doit être appelée sur le thread principal.
         * @note L’exception gl_engine::glfw::Platform_Error est expliqué dans le lien fourni.
         */
        void operator()( GLFWwindow* const window ) const {
            interface::SmartDestroyWindow_GLFW::destroyWindow(window);
        }
    };

    /**
     * @brief Alias représentant un pointeur unique vers une GLFWwindow.
     *
     * @see [GLFWwindow](https://www.glfw.org/docs/3.3/window_guide.html)
     */
    using smartGLFWwindow = std::unique_ptr<GLFWwindow, GLFWwindowDestroyer>;
// endregion
    /**
     * @brief Fenêtre permettant le rendu d’une scène.
     *
     * La fenêtre initialise le contexte GLFW et le détruit, elle permet de faire le rendu d’une scène.\n
     * Cette classe doit avoir été instanciée sur le thread principal, sinon le comportement est indéfini.\n
     *
     * @version 2.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFWwindow](https://www.glfw.org/docs/3.3/window_guide.html)
     *
     * @note L’instanciation d’une fenêtre doit être effectuée sur le thread principal.
     * @note La bibliothèque gl_engine n’a pas été créée dans le but d’être multi-threading.
     *
     * Exemple de code:
     * @code
     *      using namespace gl_engine;
     * @endcode
     *
     * Création d’une fenêtre avec les paramètres 'title' et 'dimension' :
     * @code
     *      auto window = Window(title, dimension);
     * @endcode
     *
     * Demande de rendu de la fenêtre :
     * @code
     *      window.render();
     * @endcode
     */
    class Window {
    public:
        /**
         * @brief Le mode/type de fenêtre.
         */
        enum class Type {
            FULLSCREEN,
            WINDOWED,
        };

        using Window_t = Window::Type;

        /**
         * @brief Crée une fenêtre en mode fenêtré de dimension 800x600 pixels avec aucun titre et avec l’icône par défaut sur l’écran principal.
         * @post La dimension de la fenêtre est proche de 800x600 pixels.
         *
         * @throws TODO
         * @exceptsafe TODO
         *
         * @see [GLFW-Create_Window](https://www.glfw.org/docs/3.3/group__window.html#ga3555a418df92ad53f917597fe2f64aeb)
         *
         * @note Comme indiqué dans le lien précédent la dimension de la fenêtre créée n’est pas obligée d’être identique à la dimension demandée.
         */
        Window() = delete;

        /**
         * @overload Window( Dimension dimension, std::string title )
         *
         * @brief Crée une fenêtre dans le mode fournie, de dimension fournie avec le titre fourni et avec l’icône par défaut sur l'écran principal.
         * @param type Le type de fenêtre (plein écran ou fenêtré)
         *
         * @post Le type de fenêtre est identique au type fourni.
         *
         * @throws TODO
         * @exceptsafe TODO
         *
         * @see gl_engine::Window::Window_t
         */
        Window( Dimension dimension, std::string title, Window_t type );

        Window( const Window& other ) noexcept = delete;
        Window( Window&& other ) noexcept = default;

        Window& operator=( const Window& other ) noexcept = delete;
        Window& operator=( Window&& other ) noexcept {
            title_ = std::move(other.title_);
            scene_ = other.scene_;
            handle_ = std::move(other.handle_);
            resizeFunction_ = std::move(other.resizeFunction_);

            return *this;
        };

        /**
         * @brief Détruit la fenêtre, sa scène et son contexte.
         *
         * @exceptsafe NO-THROW.
         */
        ~Window() noexcept = default;

        /**
         * @brief Demande le rendu de la fenêtre.
         *
         * @see void gl_engine::Scene::render() const
         *
         * @note Cette fonction donnera un rendu noir si aucune scène n’a été liée à la fenêtre.
         */
        void render() const;

        void addScene( Scene scene );

        // TODO Peut être retourner la scene
        void removeScene() noexcept;


        std::string getTitle() const noexcept;

        void setTitle( std::string title );

        GLFWwindow* get() {
            return handle_.get();
        }

        void becomeContext();

    private:
        std::string title_{};

        std::optional<Scene> scene_{std::nullopt};

        smartGLFWwindow handle_{nullptr};

        std::function<void( GLFWwindow*, GLsizei, GLsizei )> resizeFunction_ = &Window::DEFAULT_FRAME_BUFFER_SIZE_CALLBACK;

        gl_engine::glfw::GLFW& glfw_ = gl_engine::interface::Window_GLFW::getInstance();

        /**
         * @brief Redéfinit la dimension de la fenêtre pointée par la poignée passée.
         *
         * @param window La poignée vers la fenêtre à redimensionner.
         *
         * @param width La nouvelle largeur.
         * @pre width doit être supérieur à 0 et inférieur à la largeur maximale de l'écran.
         * @throws TODO
         * @post La largeur du frame buffer est identique à width.
         *
         * @param height La nouvelle hauteur.
         * @pre height doit être supérieur à 0 et inférieur à la hauteur maximale de l'écran.
         * @throws TODO
         * @post La hauteur du frame buffer est identique à height.
         *
         * @throws TODO
         * @exceptsafe TODO
         *
         * @see [GLFW-SetFrameBufferCallback](https://www.glfw.org/docs/3.3/group__window.html#gab3fb7c3366577daef18c0023e2a8591f)
         */
        static void DEFAULT_FRAME_BUFFER_SIZE_CALLBACK( [[maybe_unused]]GLFWwindow* window, const GLsizei width, const GLsizei height ) {
            // TODO Vérifier window dif nullptr

            if ( width <= 0 ) {
                throw std::invalid_argument( "The given width is invalid." );
            }
            if ( height <= 0 ) {
                throw std::invalid_argument( "The given height is invalid." );
            }

            glViewport( 0, 0, width, height );
        }
    };

    /**
     * @brief Exportation dans gl_engine de Window::Type comme étant Window_t.
     */
    using Window_t = Window::Type;

    inline void Window::becomeContext() {
        glfw_.makeCurrentContext(handle_.get());
    }
}

#endif // GLENGINE_WINDOW_HPP
