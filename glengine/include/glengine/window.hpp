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

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>
#include <functional>

#include <memory>

#include <glengine/utils.hpp>

namespace gl_engine {
    class Window {
    public:
        struct Settings {
            const gl_engine::Dimension dim;
            const std::string title;
            GLFWmonitor* const monitor{ nullptr };
            GLFWwindow* const shareWindow{ nullptr };
            GLFWframebuffersizefun const resizeFunction{ nullptr };
        };

        /// Destructeur utilisé pour les uniques pointeurs contenant une GLFWwindow
        class GLFWwindowDestroyer {
        public:
            void operator()( GLFWwindow* const window ) const {
                ::glfwDestroyWindow( window );
            }
        };
        using smartGLFWwindow = std::unique_ptr<GLFWwindow, GLFWwindowDestroyer>;

        Window() = delete;

        Window( const Window& ) = delete;

        Window& operator=( const Window& ) = delete;


        Window( Window&& ) noexcept = default;

        Window& operator=( Window&& ) noexcept = default;

        ~Window() noexcept = default;

        explicit Window( Settings settings );

        // TODO Vérifier les dimensions
        void setDimension( Dimension newDimension );

        [[nodiscard]] GLFWwindow* get() const noexcept;

        Dimension getDimension() const;

    private:
        smartGLFWwindow window_;

        Dimension dimensions_;

        std::string title_;

        GLFWmonitor* monitor_ = nullptr;

        GLFWwindow* shareWindows_ = nullptr;

        std::function<void( GLFWwindow*, GLsizei, GLsizei )> resizeFunction_ = &Window::frameBufferSizeCallback;

        /// Fonction permettant de redimensionner la fenêtre
        static void frameBufferSizeCallback( [[maybe_unused]]GLFWwindow* window, const GLsizei width, const GLsizei height ) {
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




#endif //WINDOW_HPP
