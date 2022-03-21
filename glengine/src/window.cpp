/*
 * PEM_GL - Copyright © 2022-2022 DAVID Axel
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

#include <glengine/window.hpp>
#include <glengine/utility.hpp>
#include <stdexcept>

gl_engine::Window::Window( Dimension dimension, std::string title, Window_t type )
:   title_(std::move(title)) {
    // TODO Vérifier les paramètres

    GLFWmonitor* screen = nullptr;
    if ( type == Window_t::FULLSCREEN ) {
        screen = ::glfwGetPrimaryMonitor();
    }

    smartGLFWwindow window( ::glfwCreateWindow( dimension.width, dimension.height,
                                                title_.c_str(),screen, nullptr) );

    if ( nullptr == window ) {
        throw std::runtime_error( "Impossible d’allouer l’espace nécessaire pour créer la fenêtre" );
    }

    handle_ = std::move( window );
}

void gl_engine::Window::render() const {
    if (scene_.has_value()) {
        scene_->render();
    }
}

void gl_engine::Window::addScene( Scene scene ) {
    if ( !scene_.has_value() ) {
        scene_ = scene;
    }
    else {
        throw std::logic_error("erreur");
    }
}

void gl_engine::Window::removeScene() noexcept {
    scene_.reset();
}

std::string gl_engine::Window::getTitle() const noexcept {
    return title_;
}

void gl_engine::Window::setTitle( std::string title ) {
    title_ = title;

    glfwSetWindowTitle(handle_.get(),title_.c_str());
}
