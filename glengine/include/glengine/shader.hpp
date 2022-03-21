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

#ifndef SHADER_HPP
#define SHADER_HPP

#include <glengine/utility.hpp>
#include <glengine/abstract_shader.hpp>

namespace gl_engine {
    /**
     * @brief Classe représentant un Vertex Shader d'OpenGL.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::Abstract_Shader
     */
    class VertexShader final : public AbstractShader {
    public:
        VertexShader() noexcept = delete;

        /**
         * @brief Construit un Vertex Shader à partir de la source Content.
         * @param content Le code source du shader.
         *
         * @throws
         *
         * @exceptsafe
         *
         * @version 1.0
         * @since 0.1
         */
        explicit VertexShader( Content content )
        : AbstractShader(Shader_t::VERTEX, std::move(content)) {}

        VertexShader( const VertexShader& other ) = default;
        VertexShader( VertexShader&& ) noexcept = default;
        VertexShader& operator=( const VertexShader& ) = default;
        VertexShader& operator=( VertexShader&& ) noexcept = default;
        ~VertexShader() noexcept = default;
    };

    /**
     * @brief Classe représentant un Fragment Shader d'OpenGL.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::Abstract_Shader
     */
    class FragmentShader final : public AbstractShader {
    public:
        FragmentShader() noexcept = delete;

        /**
         * @brief Construit un Fragment Shader à partir de la source Content.
         * @param content Le code source du shader.
         *
         * @throws
         *
         * @exceptsafe
         *
         * @version 1.0
         * @since 0.1
         */
        explicit FragmentShader( Content content )
        : AbstractShader(Shader_t::FRAGMENT, std::move(content)) {}

        FragmentShader( const FragmentShader& ) = default;
        FragmentShader( FragmentShader&& ) noexcept = default;
        FragmentShader& operator=( const FragmentShader& ) = default;
        FragmentShader& operator=( FragmentShader&& ) noexcept = default;
        ~FragmentShader() noexcept = default;
    };

    /**
     * @brief Classe représentant un Geometry Shader d'OpenGL.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::Abstract_Shader
     */
    class GeometryShader final : public AbstractShader {
    public:
        GeometryShader() noexcept = delete;

        /**
         * @brief Construit un Geometry Shader à partir de la source Content.
         * @param content Le code source du shader.
         *
         * @throws
         *
         * @exceptsafe
         *
         * @version 1.0
         * @since 0.1
         */
        explicit GeometryShader( Content content )
        : AbstractShader(Shader_t::GEOMETRY, std::move(content)) {}

        GeometryShader( const GeometryShader& ) = default;
        GeometryShader( GeometryShader&& ) noexcept = default;
        GeometryShader& operator=( const GeometryShader& ) = default;
        GeometryShader& operator=( GeometryShader&& ) noexcept = default;
        ~GeometryShader() noexcept = default;
    };



//    // TODO Déplacer dans l'objet OpenGL
//    /**
//     * @brief Espace contiendra toutes les surcharges de fonctions OpenGL pour les objets GL_Engine.
//     */
//    namespace open_gl {
//        /**
//         * @brief Surcharge de la macro glCreateShader acceptant gl_engine::Shader_t
//         * @param type Type du shader voulant être créée.
//         * @overload
//         */
//        Id createShader( Shader_t type );
//    }
}

#endif //SHADER_HPP
