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

#ifndef GLENGINE_ABSTRACT_SHADER_HPP
#define GLENGINE_ABSTRACT_SHADER_HPP

#include <glengine/utility.hpp>
#include <glengine/shader_interface.hpp>

namespace gl_engine {
    /**
    * @brief Classe abstraite représentant un shader OpenGL. Alloue et supprime le shader OpenGL, implémente l'interface gl_engine::Shader.
    *
    * @version 1.0
    * @since 0.1
    *
    * @see [Shader](https://www.khronos.org/opengl/wiki/Shader)
    */
    class AbstractShader : public Shader {
    public:
        /**
         * @brief Impossible de créer un shader sans spécifier un type
         *
         * @version 1.0
         * @since 0.1
         */
        AbstractShader() noexcept = delete;

    protected:
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
        explicit AbstractShader( Shader_t type, Content content );

        /**
        * @brief Construit un shader en copiant la source du shader passé en copie.
        * @param source Le shader copié.
        * @throws TODO Faire les exceptions
        * @exceptsafe FORT. Ne modifie pas les données en cas d'exception.
        */
        AbstractShader( const AbstractShader& other );

        /**
        * @brief Construit un shader en déplaçant le shader passé en paramètre.
        * @param source Le shader à déplacer.
        * @throws TODO Faire les exceptions
        * @exceptsafe FORT. Ne lance aucune exception.
        */
        AbstractShader( AbstractShader&& other ) noexcept;

        // Suppression du précédent shader avant l’affectation du nouveau
        AbstractShader& operator=( const AbstractShader& other );

        AbstractShader& operator=( AbstractShader&& other ) noexcept;

        /**
        * @brief Détruit le shader this.
        * @exceptsafe NO-THROW.
        */
        ~AbstractShader() noexcept;


    private:
        Id privateId_;

        /**
        * @brief Link et compile le shader avec le contenu fourni
        * @param source Le code source
        * @throws TODO exceptiosn
        * @exceptsafe TODO A déterminer
        */
        void compile( Content source ) const;

        /**
         * @brief Lance une exception en fonction de l’erreur de compilation du shader.
         *
         * @throws
         * @throws
         *
         * @exceptsafe FORT. Cette méthode ne modifie aucune donnée, c’est à la fonction appelante de faire le travail nécessaire.
         *
         * @version 1.0
         * @since 0.1
         */
        void checkCompileError() const;

        Id id_() const noexcept override {
            return privateId_;
        };

        Content source_() const override;

        Shader_t type_() const override;

    };
}

#endif // GLENGINE_ABSTRACT_SHADER_HPP
