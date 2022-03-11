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

#ifndef GLENGINE_SHADER_HPP
#define GLENGINE_SHADER_HPP

#include <GLFW/glfw3.h>

#include <glengine/utility.hpp>
#include <optional>

namespace gl_engine {
    // Nécessaire pour la déclaration d'amitié

    namespace interface {
        class Shader_Program;
    }

/**
 * @brief Classe concrète représentant un shader OpenGL. Alloue et supprime le shader OpenGL.
 *
 * @friend gl_engine::ShaderProgram
 *
 * @see [Shader](https://www.khronos.org/opengl/wiki/Shader)
 */
    class Shader {
    public:
        /**
         * @brief Type fort représentant le type d’un shader OpenGL 3.3
         * @see gl_engine::Shader::Shader( Type, Content );
         * @note Contient des types prédéfinis (VERTEX, FRAGMENT, GEOMETRY)
         */
        class Type {
        public:
            /// Shader pour les vertex
            static const Type VERTEX;
            /// Shader pour les fragments
            static const Type FRAGMENT;
            /// Shader pour la géométrie
            static const Type GEOMETRY;

            /**
             * @brief Construit un Shader::Type à partir d'un GLenum
             * @param type Le type du shader
             * @pre type doit être compris dans : {GL_VERTEX_SHADER,GL_FRAGMENT_SHADER,GL_GEOMETRY_SHADER}
             * @post Correspond à un type pris en charge et valide de Shader
             * @throw std::invalid_argument Lancée si le GLenum fourni n'est pas dans la liste des types pris en charge.
             * @exceptsafe FORT. Ne modifie aucune donnée.
             * @see [Shader Type](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml)
             */
            constexpr explicit Type( const GLenum type )
            : type_( type ) {
                if ( (type != GL_VERTEX_SHADER) && (type != GL_FRAGMENT_SHADER) && (type != GL_GEOMETRY_SHADER) ) {
                    throw std::invalid_argument( "Le type : " + gl_engine::utility::to_string( type ) +
                                                 " n’est pas un type de shader pris en charge." );
                }
            }

            /**
             * @brief Impossible de créer un Type sans spécifier le type
             */
            constexpr Type() = delete;


//            /**
//             * @brief Constructeur de copie par défaut
//             */
//            constexpr Type( const Type& ) = default;

//            /**
//             * @brief Constructeur de déplacement par défaut
//             * @exceptsafe FORT. Ne lance pas
//             */
//            constexpr Type( Type&& ) noexcept = default;

//            /**
//             * @brief Opérateur d'affectation de copie par défaut
//             * @return Retourne une référence vers l'objet this
//             */
//            constexpr Type& operator=( const Type& ) = default;

//            /**
//             * @brief Opérateur d'affectation par déplacement par défaut
//             * @return Retourne une référence vers l'objet this
//             * @exceptsafe FORT. Ne lance pas
//             */
//            constexpr Type& operator=( Type&& ) noexcept = default;

//            /**
//             * @brief Destructeur par défaut
//             * @exceptsafe FORT. Ne lance pas
//             */
//            ~Type() noexcept = default;


            /**
             * @brief Retourne le type en type GLenum de façon.
             * @post Retourne une valeur comprise dans : {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER}
             * @exceptsafe FORT. Ne lance pas.
             */
            [[nodiscard]] GLenum constexpr get() const noexcept {
                return type_;
            }

            static std::string to_string( GLenum type ) {
                switch (type) {
                    case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
                    case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
                    case GL_GEOMETRY_SHADER: return "GL_GEOMETRY_SHADER";
                    default: throw std::invalid_argument("Erreur type inconnu");
                }
            }

            /**
             * @brief Convertie un Shader_t en sa std::string correspondante
             * @param type Objet Shader::Type
             * @return Une chaine de caractère
             * @throws TODO
             * @exceptsafe TODO
             */
            static std::string to_string( Shader::Type type ) {
                return Shader::Type::to_string(type.type_);
            }

        private:
            GLenum type_{ GL_NONE };
        };

        using Shader_t = Shader::Type;


        /**
         * @brief Construit un shader du type passé en paramètre, avec la source contenue dans content.
         * @param type Le type du shader à créer.
         * @param content Le code source du shader.
         * @pre Toutes les erreurs OpenGL doivent être traitées.
         * @pre content doit être un code source de shader GLSL valide
         * @pre type doit être un type pris en charge
         * @throws std::runtime_error Lancée s'il n'est pas possible d'allouer le shader.
         * @throws std::runtime_error Lancée si une erreur est détectée durant l'ajout du code source du shader.
         * @throws std::runtime_error Lancée si une erreur est détectée durant la compilation du shader.
         * @exceptsafe BASE. // TODO OpenGL dans quel état
         * @see gl_engine::Shader::Type
         * @see gl_engine::utility::Content
         * @see gl_engine::utility::Path
         */
        explicit Shader( Shader_t type, Content content );


        /**
         * @brief Impossible de créer un shader sans spécifier un type
         */
        Shader() = delete;

        /**
         * @brief Construit un shader en copiant la source du shader passé en copie.
         * @param source Le shader copié.
         * @throws TODO Faire les exceptions
         * @exceptsafe FORT. Ne modifie pas les données en cas d'exception.
         */
        Shader( const Shader& other );

        /**
         * @brief Construit un shader en déplaçant le shader passé en paramètre.
         * @param source Le shader à déplacer.
         * @throws TODO Faire les exceptions
         * @exceptsafe FORT. Ne lance aucune exception.
         */
        Shader( Shader&& other ) noexcept;

        /**
         * @brief Détruit le shader this.
         * @exceptsafe FORT. Ne lance aucune exception.
         */
        ~Shader() noexcept;

        // Suppression du précédent shader avant l’affectation du nouveau
        Shader& operator=( const Shader& other );

        Shader& operator=( Shader&& other ) noexcept;

    private:
        // Nécessaire pour l'ajout d'un shader à un ShaderProgram
        friend class interface::Shader_Program;

        gl_engine::Id id_;

        /**
         * @brief Retourne l'identifiant du shader
         * @exceptsafe FORT. Ne lance aucune exception.
         */
        [[nodiscard]] gl_engine::Id getId() const noexcept;

        /**
         * @brief Link et compile le shader avec le contenu fourni
         * @param source Le code source
         * @throws TODO exceptiosn
         * @exceptsafe TODO A déterminer
         */
        void compile( Content source ) const;

        // TODO Refactoriser le code
        // void checkCompileError() const;

        /**
 * @brief Retourne une copie de la source du shader.
 * @return Shader::ShaderSource. Un pointeur propriétaire vers une copie de la source.
 * @throws std::bad_alloc Lancée s'il est impossible d'allouer l'espace nécessaire pour stocker le code source.
 * @exceptsafe FORT. Ne lance aucune exception.
 */
        [[nodiscard]] Content getSource() const;

        /**
         * @brief Retourne le type du shader
         * @return Retourne un Shader::Type
         * @throws TODO à faire
         * @exceptsafe TODO à déterminer
         */
        [[nodiscard]] Shader_t getType() const;

    };

    using Shader_t = Shader::Type;

    // Valeurs des constantes de types prédéfinis pour le type fort Shader::Type
    constexpr const Shader_t Shader_t::VERTEX{GL_VERTEX_SHADER};
    constexpr const Shader_t Shader_t::FRAGMENT{GL_FRAGMENT_SHADER};
    constexpr const Shader_t Shader_t::GEOMETRY{GL_GEOMETRY_SHADER};

    constexpr bool operator==( const Shader_t& t1, const Shader_t& t2 ) {
        return t1.get() == t2.get();
    }
    constexpr bool operator!=( const Shader_t& t1, const Shader_t& t2 ) {
        return !(t1 == t2);
    }

    // Nécessaire pour l'amitié
    class ShaderProgram;
}

/**
 * @brief Espace de noms contenant toutes les interfaces entre différents objets
 */
namespace gl_engine::interface {
    /**
     * @brief Classe d'interface entre le ShaderProgram et Shader, pour limiter les accès de ShaderProgram dans Shader
     */
    class Shader_Program {
    private:
        friend class gl_engine::ShaderProgram;

        /**
         * @brief Retourne l'identifiant du shader
         * @param shader Une référence constante vers un shader valide
         * @pre Shader doit être valide
         * @post L'identifiant retourné est valide durant la durée de vie du shader
         * @return L'identifiant du shader demandé
         * @exceptsafe FORT. Ne lance aucune exception.
         */
        [[nodiscard]] static gl_engine::Id getId( const Shader& shader ) noexcept {
            return shader.getId();
        }

        /**
         * @overload getId
         */
        [[nodiscard]] static gl_engine::Id getId( const std::optional<Shader>& shader ) noexcept {
            return getId(shader.value());
        }

        /**
        * @brief Retourne une copie de la source du shader.
        * @param shader Une référence constante vers un shader valide
        * @pre Shader doit être valide
        * @post La source retournée est identique au code source du shader
        * @return gl_engine::utility::Content. Un objet représentant le code source
        * @throws std::bad_alloc Lancée s'il est impossible d'allouer l'espace nécessaire pour stocker le code source.
        * @exceptsafe FORT. Ne modifie aucune donnée.
        */
        [[nodiscard]] static Content getSource( const Shader& shader ) {
            return shader.getSource();
        }

        /**
         * @overload getSource
         */
        [[nodiscard]] static Content getSource( const std::optional<Shader>& shader ) {
            return getSource(shader.value());
        }

        /**
         * @brief Retourne le type du shader
         * @param shader Une référence constante vers un shader valide
         * @pre Shader doit être valide
         * @post Le type retourné est identique au type du shade
         * @return Le type du shader
         * @throws TODO à faire
         * @exceptsafe TODO à déterminer
         */
        [[nodiscard]] static Shader_t getType( const Shader& shader ) {
            return shader.getType();
        }

        /**
         * @overload getType
         */
        [[nodiscard]] static Shader_t getType( const std::optional<Shader>& shader ) {
            return getType(shader.value());
        }
    };
}

/**
 * @brief Espace contiendra toutes les surcharges de fonctions OpenGL pour les objets GL_Engine
 */
namespace gl_engine::open_gl {
    /**
     * @brief Surcharge de la macro glCreateShader acceptant gl_engine::Shader_t
     * @param type Type du shader voulant être créée.
     * @overload
     */
    Id createShader( Shader_t type );
}

#endif // GLENGINE_SHADER_HPP
