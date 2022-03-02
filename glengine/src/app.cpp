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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glengine/config.hpp>
#include <glengine/glfw.hpp>
#include <glengine/app.hpp>
#include <glengine/window.hpp>

#include <memory>

namespace gl_engine {

// region Public interface
    App& App::getInstance() {
        static App app;
        return app;
    }

    App::~App() noexcept {
        glfw::terminate();
    }


    Window* App::getWindow() const noexcept {
        return window_.get();
    }

    void App::addWindow( std::unique_ptr<Window> window ) {
        if ( window_ != nullptr ) {
            throw appWindow_already_exists( "L'application a déjà une fenêtre de rendu."
                                                       " S'il vous plait supprimer l'ancienne "
                                                       "fenêtre de rendu avec la méthode App::deleteWindow(), puis réitérer." );
        }

        window_ = std::move( window );
    }

    void App::deleteWindow() {
        window_.reset();
    }
// endregion

// region Protected interface
    App::App() {
        glfw::init();
    }
// endregion

}
