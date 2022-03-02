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

#include <glengine/window.hpp>
#include <glengine/utility.hpp>
#include <iostream>

gl_engine::Window::Window( Settings settings )
:   dimensions_(settings.dim),
    title_(settings.title),
    monitor_(settings.monitor), shareWindows_(settings.shareWindow),
    resizeFunction_(settings.resizeFunction) {
    // TODO Vérifier les paramètres
    smartGLFWwindow window( ::glfwCreateWindow( dimensions_.width, dimensions_.height,
                                                title_.c_str(),monitor_, shareWindows_) );

    if ( window.get() == nullptr ) std::cout << "test" << '\n';

    if ( nullptr == window ) {
        throw std::runtime_error( "Impossible d’allouer l’espace nécessaire pour créer la fenêtre" );
    }

    window_ = std::move( window );
}

GLFWwindow* gl_engine::Window::get() const noexcept {
    return window_.get();
}

gl_engine::Dimension gl_engine::Window::getDimension() const {
    return dimensions_;
}

void gl_engine::Window::setDimension( Dimension newDimension ) {
    dimensions_ = std::move(newDimension);
}
