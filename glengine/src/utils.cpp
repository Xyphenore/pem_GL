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

#include <unordered_map>

#include <GLFW/glfw3.h>

#include <glengine/utility.hpp>

std::string gl_engine::getCodeName( const gl_engine::GLFWErrorCode code ) {
    // SRC : https://www.glfw.org/docs/3.3/group__errors.html#gad44162d78100ea5e87cdd38426b8c7a1
    static const std::unordered_map<gl_engine::GLFWErrorCode, const std::string> glfwErrorCode( {
       { GLFW_NO_ERROR,            "GLFW_NO_ERROR" },
       { GLFW_NOT_INITIALIZED,     "GLFW_NOT_INITIALIZED" },
       { GLFW_NO_CURRENT_CONTEXT,  "GLFW_NO_CURRENT_CONTEXT" },
       { GLFW_INVALID_ENUM,        "GLFW_INVALID_ENUM" },
       { GLFW_INVALID_VALUE,       "GLFW_INVALID_VALUE" },
       { GLFW_OUT_OF_MEMORY,       "GLFW_OUT_OF_MEMORY" },
       { GLFW_API_UNAVAILABLE,     "GLFW_API_UNAVAILABLE" },
       { GLFW_VERSION_UNAVAILABLE, "GLFW_VERSION_UNAVAILABLE" },
       { GLFW_PLATFORM_ERROR,      "GLFW_PLATFORM_ERROR" },
       { GLFW_FORMAT_UNAVAILABLE,  "GLFW_FORMAT_UNAVAILABLE" },
       { GLFW_NO_WINDOW_CONTEXT,   "GLFW_NO_WINDOW_CONTEXT" }
   } );

    const auto itStr = glfwErrorCode.find(code);

    if ( itStr == glfwErrorCode.cend() ) {
        throw gl_engine::GLFWUnknownException("Le code d'erreur passé est inconnu");
    }

    return itStr->second;
}
