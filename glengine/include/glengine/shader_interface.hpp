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

#ifndef GLENGINE_SHADER_INTERFACE_HPP
#define GLENGINE_SHADER_INTERFACE_HPP

#include <GLFW/glfw3.h>

#include <glengine/utility.hpp>
#include <glengine/exception.hpp>

#include <string>
#include <unordered_map>

namespace gl_engine {
    // Note développeur : Nécessaire pour la déclaration d’amitié

    // Note développeur : Dans le cas d’une amélioration du temps d’execution, il sera nécessaire de remplacer l’unordered map
    // Par un std::array d’une structure, qui lui peut être créé à la compilation.

    namespace interface {
        class Program_Shader;
    }

    /**
     * @brief Interface Shader. Elle contient seulement les méthodes permettant à gl_engine::ShaderProgram d'interagir avec.
     *
     * @version 2.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::ShaderProgram
     * @see gl_engine::AbstractShader
     * @see gl_engine::Shader::Type
     */
    class Shader {
    public:
        /**
         * @brief Type fort représentant le type d’un shader OpenGL 3.3
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see gl_engine::AbstractShader;
         * @note Contient des types prédéfinis (VERTEX, FRAGMENT, GEOMETRY)
         */
        class Type final {
        public:
            /// Shader pour les vertex
            static const Type VERTEX;
            /// Shader pour les fragments
            static const Type FRAGMENT;
            /// Shader pour la géométrie
            static const Type GEOMETRY;

            /**
             * @brief Construit un Shader::Type à partir d’un GLenum
             *
             * @param type Le type du shader
             * @pre type doit être compris dans : {GL_VERTEX_SHADER,GL_FRAGMENT_SHADER,GL_GEOMETRY_SHADER}
             * @post Correspond à un type pris en charge et valide de Shader
             * @throw gl_engine::Shader::Type::InvalidShaderType Lancée si le GLenum fourni n’est pas dans la liste des types pris en charge.
             * @exceptsafe FORT. Ne modifie aucune donnée.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see [Shader Type](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml)
             */
            constexpr explicit Type( const GLenum type )
            : type_( type ) {
                if ( !Type::supported( type ) ) {
                    throw InvalidShaderType( type );
                }
            }

            /**
             * @brief Impossible de créer un Type sans spécifier le type
             */
            constexpr Type() = delete;

            constexpr Type( const Type& ) noexcept = default;

            constexpr Type( Type&& ) noexcept = default;

            constexpr Type& operator=( const Type& ) noexcept = default;

            constexpr Type& operator=( Type&& ) noexcept = default;

            ~Type() noexcept = default;


            /**
             * @brief Retourne le type en type GLenum de façon.
             * @post Retourne une valeur comprise dans : {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER}
             * @exceptsafe FORT. Ne lance pas.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see [Shader Type](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml)
             */
            [[nodiscard]] GLenum constexpr get() const noexcept {
                return type_;
            }

            /**
             * @brief Convertit le gl_engine::Shader::Type en sa chaine de caractère.
             * @return Une chaine de caractère.
             *
             * @exceptsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            [[nodiscard]] std::string to_string() const noexcept;

            /**
             * @brief Convertie un Shader_t en sa std::string correspondante
             *
             * @param type Objet Shader::Type
             * @return Une chaine de caractère
             * @exceptsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            static std::string to_string( Shader::Type type ) noexcept;

        private:
            GLenum type_{ GL_NONE };

            /**
             * @brief Indique si le type fourni est supporté.
             * @param type Un type de Shader sous forme de GLenum.
             * @return Un booléen.
             *
             * @exceptsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            static bool supported( const GLenum type ) noexcept {
                return supportedTypes_.find( type ) != supportedTypes_.cend();
            }

            static inline const std::unordered_map<GLenum, std::string> supportedTypes_{
                { GL_VERTEX_SHADER,   "GL_VERTEX_SHADER" },
                { GL_FRAGMENT_SHADER, "GL_FRAGMENT_SHADER" },
                { GL_GEOMETRY_SHADER, "GL_GEOMETRY_SHADER" },
            };


            /**
             * @brief Exception lancée si le type de shader fourni n’est pas pris en charge.\n
             * @brief Le message d’erreur est près écrit.
             *
             * @version 1.0
             * @since 0.1
             * @author Axel DAVID
             *
             * @see gl_engine::Shader::Type
             * @see gl_engine::InvalidArgument
             */
            class InvalidShaderType final : public InvalidArgument {
            public:
                InvalidShaderType() noexcept = delete;

                explicit InvalidShaderType( const GLenum type ) noexcept
                : InvalidArgument( "Le type : " + gl_engine::utility::to_string( type ) +
                                   " n’est pas un type de shader pris en charge." ) {}

                InvalidShaderType( const InvalidShaderType& other ) noexcept = default;

                InvalidShaderType( InvalidShaderType&& other ) noexcept = default;

                InvalidShaderType& operator=( const InvalidShaderType& other ) noexcept = default;

                InvalidShaderType& operator=( InvalidShaderType&& other ) noexcept = default;

                ~InvalidShaderType() noexcept override = default;
            };
        };

        using Shader_t = Shader::Type;

    protected:
        Shader() noexcept = default;

        Shader( const Shader& ) noexcept = default;

        Shader( Shader&& ) noexcept = default;

        Shader& operator=( const Shader& ) noexcept = default;

        Shader& operator=( Shader&& ) noexcept = default;

        ~Shader() noexcept = default;

        /**
         * @brief Retourne l'identifiant du shader
         * @exceptsafe NO-THROW
         *
         * @version 1.0
         * @since 0.1
         */
        [[nodiscard]] gl_engine::Id getId() const noexcept {
            return id_();
        }

        /**
         * @brief Retourne une copie de la source du shader.
         * @return Shader::ShaderSource. Un pointeur propriétaire vers une copie de la source.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        [[nodiscard]] Content getSource() const noexcept {
            return source_();
        };

        /**
         * @brief Retourne le type du shader
         * @return Retourne un Shader::Type
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        [[nodiscard]] Shader_t getType() const noexcept {
            return type_();
        };

    private:
        friend class interface::Program_Shader;

        // Note développeur : Permet de changer la façon de stocker les informations.
        [[nodiscard]] virtual Id id_() const noexcept = 0;

        [[nodiscard]] virtual Content source_() const = 0;

        [[nodiscard]] virtual Shader_t type_() const = 0;

    };

    using Shader_t = Shader::Type;

    /**
     * @brief Convertie un gl_engine::Shader::Type en std::string.
     * @param type Le type à convertir.
     * @return Une chaine de caractère.
     *
     * @exceptsafe NO-THROW.
     *
     * @version 1.0
     * @since 0.1
     */
    inline std::string to_string( const Shader_t type ) noexcept {
        return type.to_string();
    }

    /**
     * @brief Converti un gl_engine::Shader::Type en entier.
     * @param type Le type à convertir.
     * @return Un GLenum.
     *
     * @exceptsafe NO-THROW.
     *
     * @version 1.0
     * @since 0.1
     */
    constexpr GLenum to_GLEnum( const Shader_t type ) noexcept {
        return type.get();
    }


    inline std::string Shader_t::to_string() const noexcept {
        const auto& it = supportedTypes_.find( type_ );
        if ( it == supportedTypes_.cend() ) {
            throw std::logic_error(
                    "Impossible que le type stocké dans la classe gl_engine::Shader::Type ne soit pas dans les types pris en charges."
                    " Le type a été modifié d’une façon inconnue" );
        }

        return it->second;
    }

    inline std::string Shader::Type::to_string( const Shader_t type ) noexcept {
        return type.to_string();
    }

    // Valeurs des constantes de types prédéfinis pour le type fort Shader::Type
    inline const Shader_t Shader_t::VERTEX{ GL_VERTEX_SHADER };
    inline const Shader_t Shader_t::FRAGMENT{ GL_FRAGMENT_SHADER };
    inline const Shader_t Shader_t::GEOMETRY{ GL_GEOMETRY_SHADER };

    constexpr bool operator==( const Shader_t& t1, const Shader_t& t2 ) noexcept {
        return t1.get() == t2.get();
    }

    constexpr bool operator!=( const Shader_t& t1, const Shader_t& t2 ) noexcept {
        return !( t1 == t2 );
    }



    // Nécessaire pour l’amitié

    class ShaderProgram;

    /**
     * @brief Espace de noms contenant toutes les interfaces entre différents objets
     */
    namespace interface {
        /**
         * @brief Interface entre le ShaderProgram et Shader, pour limiter les accès de ShaderProgram dans Shader.
         *
         * @version 2.0
         * @since 0.1
         *
         * @author Axel DAVID
         *
         * @see gl_engine::Shader
         * @see gl_engine::ShaderProgram
         */
        class Program_Shader {
        private:
            friend class gl_engine::ShaderProgram;

            /**
             * @brief Retourne l'identifiant du shader.
             *
             * @param shader Une référence constante vers un shader valide.
             * @pre Shader doit être valide.
             * @post L’identifiant retourné est valide durant la durée de vie du shader.
             * @return L’identifiant du shader demandé.
             *
             * @exceptsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            [[nodiscard]] static Id getId( const Shader& shader ) noexcept {
                return shader.getId();
            }

            /**
            * @brief Retourne une copie de la source du shader.
             *
            * @param shader Une référence constante vers un shader valide
            * @pre Shader doit être valide
            * @post La source retournée est identique au code source du shader
            * @return gl_engine::utility::Content. Un objet représentant le code source
             *
            * @exceptsafe NO-THROW.
             *
             * @version 1.1
             * @since 0.1
            */
            [[nodiscard]] static Content getSource( const Shader& shader ) noexcept {
                return shader.getSource();
            }

            /**
             * @brief Retourne le type du shader
             *
             * @param shader Une référence constante vers un shader valide
             * @pre Shader doit être valide
             * @post Le type retourné est identique au type du shade
             * @return Le type du shader
             *
             * @exceptsafe NO-THROW.
             *
             * @version 1.1
             * @since 0.1
             */
            [[nodiscard]] static Shader_t getType( const Shader& shader ) noexcept {
                return shader.getType();
            }
        };
    }
}

#endif // GLENGINE_SHADER_INTERFACE_HPP
