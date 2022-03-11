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

/*
 * Test_OpenGL - Copyright © 2022 DAVID Axel
 * Mail to: axel.david@etu.univ-amu.fr.
 *
 * Test_OpenGL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Test_OpenGL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __GLENGINE_HPP__
#define __GLENGINE_HPP__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <iostream>
#include <stdexcept>

/**
 * \namespace GLEngine
 * @brief Espace de nom pour GLEngine
 *
 * blabla
 */
namespace GLEngine {
    static void GLClearError() {
        while ( glGetError() != GL_NO_ERROR ) {}
    }

    static bool GLLogCall( const char* function, const char* file, int line ) {
        GLenum error = GL_NO_ERROR;
        while ( (error = glGetError()) != GL_NO_ERROR ) {
            std::cout << "[OpenGL Error] (" << error << ") " << function << std::endl << file << " L" << line
                      << std::endl;
            return false;
        }
        return true;
    }
} // namespace GLEngine

#define ASSERT( x ) if ((!x)) throw std::runtime_error("a gl error occured");

#ifdef DEBUG
#define GLCALL(x) GLEngine::GLClearError();\
    x;\
    ASSERT(GLEngine::GLLogCall(#x, __FILE__, __LINE__));
#else
#define GLCALL( x ) x;
#endif


#endif // !
