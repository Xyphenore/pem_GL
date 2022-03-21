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

#ifndef GLENGINE_SHADERPROGRAM_HPP
#define GLENGINE_SHADERPROGRAM_HPP

#include <GLFW/glfw3.h>

#include <glengine/utility.hpp>
#include <glengine/shader.hpp>

#include <optional>
#include <unordered_map>

#include <glm/glm.hpp>

namespace gl_engine {
    class ShaderProgram {
    public:
        /**
         * @brief Génère un shader program(inutilisable) sans shader.
         */
        ShaderProgram();

        ShaderProgram( const ShaderProgram& other ) noexcept = default;
        ShaderProgram( ShaderProgram&& ) noexcept = default;
        ShaderProgram& operator=( const ShaderProgram& other ) noexcept = default;
        ShaderProgram& operator=( ShaderProgram&& ) noexcept = default;

        ~ShaderProgram() noexcept;

        explicit ShaderProgram( VertexShader shader );
        explicit ShaderProgram( FragmentShader shader );
        explicit ShaderProgram( GeometryShader shader );
        explicit ShaderProgram( VertexShader vertex, FragmentShader fragment );
        explicit ShaderProgram( VertexShader vertex, FragmentShader fragment, GeometryShader geometry );



        /**
         * @brief Utiliser le programme.
         */
        void use() const;

        /**
         * @brief Attache un shader au programme et le recompile
         * @param shader
         */
        void attachShader( VertexShader shader );
        void attachShader( FragmentShader shader );
        void attachShader( GeometryShader shader );
        void attachShader( VertexShader vertex, FragmentShader fragment, GeometryShader geometry );

        /**
         * @brief Détache tous les shaders
         */
        void detachShader();
        /**
         * @brief Détache le shader dont le type est fourni.
         * @param type Le type du shader a détacher.
         *
         * @note Ne fait rien si aucun shader n'est attaché pour le type fourni.
         */
        void detachShader( Shader_t type );

        void setUniform( std::string name, int value );
        void setUniform( std::string name, float value );
        void setUniform( std::string name, bool value );
        void setUniform( std::string name, double value );
        void setUniform( std::string name, unsigned int value );


        void setUniform( std::string name, glm::vec2 value );
        void setUniform( std::string name, glm::vec3 value );
        void setUniform( std::string name, glm::vec4 value );


        void setUniform( std::string name, glm::ivec2 value );
        void setUniform( std::string name, glm::ivec3 value );
        void setUniform( std::string name, glm::ivec4 value );


        void setUniform( std::string name, glm::uvec2 value );
        void setUniform( std::string name, glm::uvec3 value );
        void setUniform( std::string name, glm::uvec4 value );


        void setUniform( std::string name, glm::bvec2 value );
        void setUniform( std::string name, glm::bvec3 value );
        void setUniform( std::string name, glm::bvec4 value );


        void setUniform( std::string name, glm::dvec2 value );
        void setUniform( std::string name, glm::dvec3 value );
        void setUniform( std::string name, glm::dvec4 value );


        /**
         * @brief Indique si la matrice doit être transposée.
         *
         * @version 1.0
         * @since 0.1
         */
        enum class TRANSPOSE : bool {
            YES = true,
            NO = false,
        };

        void setUniform( std::string name, glm::mat2 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::mat2x3 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::mat2x4 value, TRANSPOSE transpose );

        void setUniform( std::string name, glm::mat3 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::mat3x2 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::mat3x4 value, TRANSPOSE transpose );

        void setUniform( std::string name, glm::mat4 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::mat4x2 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::mat4x3 value, TRANSPOSE transpose );


        void setUniform( std::string name, glm::dmat2 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::dmat2x3 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::dmat2x4 value, TRANSPOSE transpose );

        void setUniform( std::string name, glm::dmat3 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::dmat3x2 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::dmat3x4 value, TRANSPOSE transpose );

        void setUniform( std::string name, glm::dmat4 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::dmat4x2 value, TRANSPOSE transpose );
        void setUniform( std::string name, glm::dmat4x3 value, TRANSPOSE transpose );


    private:
        Id id_ = open_gl::createProgram();

        bool compiled_ = false;

        std::optional<VertexShader> vertex_ = std::nullopt;
        std::optional<FragmentShader> fragment_ = std::nullopt;
        std::optional<GeometryShader> geometry_ = std::nullopt;


        void compile();

        /**
         * @brief Cache des positions des uniforms pour le programme.
         *
         * @version 1.0
         * @since 0.1
         */
        std::unordered_map<std::string, GLint> uniformLocation_;

        /**
         * @brief Récupère la localisation de l’uniforme dont le nom est passé en paramètre.
         * @param name Le nom de l’uniforme.
         * @pre Name ne doit pas contenir d’espace blanc.
         * @return Retourne la localisation, un entier.
         *
         * @throws gl_engine::ShaderProgram::ProgramNotCompiled Lancée si le programme n’est pas compilé.
         * @throws gl_engine::ShaderProgram::UniformNotFound Lancée si aucun uniforme n'est trouvé pour le nom fourni.
         */
        GLint getUniformLocation( std::string name );

        void setUniformFloat( std::string name, const float* value, size_t size );
        void setUniformInt( std::string name, const int* value, size_t size );
        void setUniformUnsigned( std::string name, const unsigned int* value, size_t size );

        void setUniformFloatMatrix( std::string name, const float* value, size_t sizeX, size_t sizeY, bool transpose );

        /**
         * @brief Exception lancée si l’utilisateur souhaite utiliser un gl_engine::ShaderProgram alors qu’il n’est pas compilé.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see gl_engine::ShaderProgram
         */
        class ProgramNotCompiled final : public LogicError {
        public:
            ProgramNotCompiled() noexcept = delete;

            /**
             * @brief Construit l’exception avec la raison de l’erreur.
             * @param what_arg La raison de l’erreur sous forme de chaine de caractère.
             *
             * @excetpsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            explicit ProgramNotCompiled( const std::string& what_arg ) noexcept
            : LogicError(what_arg) {}

            /**
             * @overload
             * @brief Surcharge du constructeur prenant en la raison sous forme de pointeur vers une chaine de caractère.
             * @param what_arg Le pointeur.
             */
            explicit ProgramNotCompiled( const char* what_arg ) noexcept
            : ProgramNotCompiled(std::string{what_arg}) {}

            ProgramNotCompiled( const ProgramNotCompiled& ) noexcept = default;
            ProgramNotCompiled( ProgramNotCompiled&& ) noexcept = default;
            ProgramNotCompiled& operator=( const ProgramNotCompiled& ) noexcept = default;
            ProgramNotCompiled& operator=( ProgramNotCompiled&& ) noexcept = default;
            ~ProgramNotCompiled() noexcept override = default;
        };

        /**
         * @brief Exception lancée lorsque l’on attache un gl_engine::VertexShader au gl_engine::ShaderProgram alors qu’il en a déjà un.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         */
        class VertexShaderAlreadyPresent final : public LogicError {
        public:
            VertexShaderAlreadyPresent() noexcept = delete;

            /**
             * @brief Construit l’exception avec la raison de l’erreur.
             * @param what_arg La raison de l’erreur sous forme de chaine de caractère.
             *
             * @excetpsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            explicit VertexShaderAlreadyPresent( const std::string& what_arg ) noexcept
            : LogicError(what_arg) {}

            /**
             * @overload
             * @brief Surcharge du constructeur prenant en la raison sous forme de pointeur vers une chaine de caractère.
             * @param what_arg Le pointeur.
             */
            explicit VertexShaderAlreadyPresent( const char* what_arg ) noexcept
            : VertexShaderAlreadyPresent(std::string{what_arg}) {}

            VertexShaderAlreadyPresent( const VertexShaderAlreadyPresent& ) noexcept = default;
            VertexShaderAlreadyPresent( VertexShaderAlreadyPresent&& ) noexcept = default;
            VertexShaderAlreadyPresent& operator=( const VertexShaderAlreadyPresent& ) noexcept = default;
            VertexShaderAlreadyPresent& operator=( VertexShaderAlreadyPresent&& ) noexcept = default;
            ~VertexShaderAlreadyPresent() noexcept override = default;
        };

        /**
         * @brief Exception lancée lorsque l’on attache un gl_engine::FragmentShader au gl_engine::ShaderProgram alors qu’il en a déjà un.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         */
        class FragmentShaderAlreadyPresent final : public LogicError {
        public:
            FragmentShaderAlreadyPresent() noexcept = delete;

            /**
             * @brief Construit l’exception avec la raison de l’erreur.
             * @param what_arg La raison de l’erreur sous forme de chaine de caractère.
             *
             * @excetpsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            explicit FragmentShaderAlreadyPresent( const std::string& what_arg ) noexcept
            : LogicError(what_arg) {}

            /**
             * @overload
             * @brief Surcharge du constructeur prenant en la raison sous forme de pointeur vers une chaine de caractère.
             * @param what_arg Le pointeur.
             */
            explicit FragmentShaderAlreadyPresent( const char* what_arg ) noexcept
            : FragmentShaderAlreadyPresent(std::string{what_arg}) {}

            FragmentShaderAlreadyPresent( const FragmentShaderAlreadyPresent& ) noexcept = default;
            FragmentShaderAlreadyPresent( FragmentShaderAlreadyPresent&& ) noexcept = default;
            FragmentShaderAlreadyPresent& operator=( const FragmentShaderAlreadyPresent& ) noexcept = default;
            FragmentShaderAlreadyPresent& operator=( FragmentShaderAlreadyPresent&& ) noexcept = default;
            ~FragmentShaderAlreadyPresent() noexcept override = default;
        };

        /**
         * @brief Exception lancée lorsque l’on attache un gl_engine::GeometryShader au gl_engine::ShaderProgram alors qu’il en a déjà un.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         */
        class GeometryShaderAlreadyPresent final : public LogicError {
        public:
            GeometryShaderAlreadyPresent() noexcept = delete;

            /**
             * @brief Construit l’exception avec la raison de l’erreur.
             * @param what_arg La raison de l’erreur sous forme de chaine de caractère.
             *
             * @excetpsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            explicit GeometryShaderAlreadyPresent( const std::string& what_arg ) noexcept
            : LogicError(what_arg) {}

            /**
             * @overload
             * @brief Surcharge du constructeur prenant en la raison sous forme de pointeur vers une chaine de caractère.
             * @param what_arg Le pointeur.
             */
            explicit GeometryShaderAlreadyPresent( const char* what_arg ) noexcept
            : GeometryShaderAlreadyPresent(std::string{what_arg}) {}

            GeometryShaderAlreadyPresent( const GeometryShaderAlreadyPresent& ) noexcept = default;
            GeometryShaderAlreadyPresent( GeometryShaderAlreadyPresent&& ) noexcept = default;
            GeometryShaderAlreadyPresent& operator=( const GeometryShaderAlreadyPresent& ) noexcept = default;
            GeometryShaderAlreadyPresent& operator=( GeometryShaderAlreadyPresent&& ) noexcept = default;
            ~GeometryShaderAlreadyPresent() noexcept override = default;
        };

        /**
         * @brief Exception lancée si la localisation d’un uniforme n’a pas été trouvé.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         */
        class UniformNotFound final : public RuntimeError {
        public:
            UniformNotFound() noexcept = delete;

            /**
             * @brief Construit une exception avec un message préfixé ainsi que le nom de l’uniforme non trouvé.
             * @param name Le nom de l’uniforme.
             *
             * @exceptsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            explicit UniformNotFound( const std::string& name ) noexcept
            : RuntimeError("L'uniforme : " + name + " n'a pas été trouvé.") {}

            /**
             * @overload
             * @brief Surcharge du constructeur qui prend le nom de l’uniforme sous forme de pointeur vers une chaine de caractère.
             * @param name Le pointeur vers la chaine de caractère.
             */
            explicit UniformNotFound( const char* name ) noexcept
            : UniformNotFound(std::string{name}) {}

            UniformNotFound( const UniformNotFound& ) noexcept = default;
            UniformNotFound( UniformNotFound&& ) noexcept = default;
            UniformNotFound& operator=( const UniformNotFound& ) noexcept = default;
            UniformNotFound& operator=( UniformNotFound&& ) noexcept = default;
            ~UniformNotFound() noexcept = default;
        };

        /**
         * @brief Exception lancée si on essaie de compiler un gl_engine::ShaderProgram sans gl_engine::VertexShader
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         */
        class MissingVertexShader : public LogicError {
        public:
            MissingVertexShader() noexcept
            : LogicError("Impossible de compier, il manque le vertex shader.") {}

            MissingVertexShader( const MissingVertexShader& ) noexcept = default;
            MissingVertexShader( MissingVertexShader&& ) noexcept = default;
            MissingVertexShader& operator=( const MissingVertexShader& ) noexcept = default;
            MissingVertexShader& operator=( MissingVertexShader&& ) noexcept = default;
            ~MissingVertexShader() noexcept override = default;
        };

        /**
         * @brief Exception lancée si on essaie de compiler un gl_engine::ShaderProgram sans gl_engine::FragmentShader.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         */
        class MissingFragmentShader : public LogicError {
        public:
            MissingFragmentShader() noexcept
            : LogicError("Impossible de compier, il manque le fragment shader.") {}

            MissingFragmentShader( const MissingFragmentShader& ) noexcept = default;
            MissingFragmentShader( MissingFragmentShader&& ) noexcept = default;
            MissingFragmentShader& operator=( const MissingFragmentShader& ) noexcept = default;
            MissingFragmentShader& operator=( MissingFragmentShader&& ) noexcept = default;
            ~MissingFragmentShader() noexcept override = default;
        };
    };
}

#endif // GLENGINE_SHADERPROGRAM_HPP
