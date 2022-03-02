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

#ifndef GLENGINE_SHADERPROGRAM_HPP
#define GLENGINE_SHADERPROGRAM_HPP

#include <GLFW/glfw3.h>

#include <glengine/utility.hpp>
#include <glengine/shader.hpp>

#include <optional>

namespace gl_engine {
    class ShaderProgram {
    public:
        /**
         * @brief Génère un shader program(inutilisable) sans shader.
         */
        ShaderProgram();

        ~ShaderProgram() noexcept;


        /**
         * @brief Utiliser le programme
         */
        void use() const;

        /**
         * @brief Attache un shader au programme et le recompile
         * @param shader
         */
        void attachShader( Shader shader );
        void attachShader( std::initializer_list<Shader> shaders );

        /**
         * @brief Détache tous les shaders
         */
        void detachShader();
        void detachShader( Shader_t type );

        template <typename T>
        void setUniform( std::string name, T value );

    private:
        gl_engine::Id id_ = open_gl::createProgram();

        bool compiled_ = false;

        std::optional<Shader> vertex_ = std::nullopt;
        std::optional<Shader> fragment_ = std::nullopt;
        std::optional<Shader> geometry_ = std::nullopt;


        void compile();
    };
}

#endif // GLENGINE_SHADERPROGRAM_HPP
