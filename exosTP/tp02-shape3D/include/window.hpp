#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>
#include <functional>

#include "utils.hpp"

namespace bidon {
    class Window {
    public:
        struct Settings {
            const bidon::Dimension dim;
            const std::string title;
            GLFWmonitor* const monitor{ nullptr };
            GLFWmonitor* const shareWindow{ nullptr };
            GLFWframebuffersizefun const resizeFunction;
        };

        Window() = delete;

        Window( const Window& ) = delete;

        Window& operator=( const Window& ) = delete;


        Window( Window&& ) noexcept = default;

        Window& operator=( Window&& ) noexcept = default;

        ~Window() noexcept;

        Window( Settings settings );

        // TODO Vérifier les dimensions
        void setWidth(GLsizei width) {
            width_ = width;
        }

        void setHeight(GLsizei height) {
            height_ = height;
        }

    private:
        GLsizei width_;
        GLsizei height_;

        std::string title_;

        GLFWmonitor* monitor_;

        GLFWmonitor* shareWindows_;

        std::function<void( GLFWwindow*, GLsizei, GLsizei )> resizeFunction_ = &Window::frameBufferSizeCallback;

        /// Fonction permettant de redimensionner la fenêtre
        static void frameBufferSizeCallback( GLFWwindow* window, const GLsizei width, const GLsizei height ) {
            if ( width <= 0 ) {
                throw std::invalid_argument( "The given width is invalid." );
            }
            if ( height <= 0 ) {
                throw std::invalid_argument( "The given height is invalid." );
            }

            glViewport( 0, 0, width, height );
        }
    };
}

inline bidon::Window::~Window() noexcept {

}

inline bidon::Window::Window( const Settings settings )
: width_(settings.dim.width), height_(settings.dim.height), title_(settings.title),
monitor_(settings.monitor), shareWindows_(settings.shareWindow), resizeFunction_(settings.resizeFunction){
    // TODO Vérifier les paramètres
}


#endif //WINDOW_HPP
