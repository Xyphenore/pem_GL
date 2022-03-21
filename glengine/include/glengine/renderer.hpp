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

#ifndef GLENGINE_RENDERER_HPP
#define GLENGINE_RENDERER_HPP

#include <optional>
#include <glengine/exception.hpp>
#include <glengine/shaderProgram.hpp>

namespace gl_engine {
    class Renderer {
    public:
        /**
         * @brief Construit une méthode de rendu sans aucune gl_engine::ShaderProgram.
         */
        Renderer() noexcept = default;
        explicit Renderer( ShaderProgram program );
        explicit Renderer( ShaderProgram program, std::function<void()> renderer );

        /**
         * @brief Ajout un gl_engine::ShaderProgram.
         * @param program Le program de rendu.
         *
         * @throws gl_engine::Renderer::ProgramAlreadyPresent Lancée si un shader program est déjà attaché au renderer.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         *
         * @version 1.0
         * @since 0.1
         */
        void addProgram( ShaderProgram program );

        /**
         * @brief Supprime et retourne le shader program contenu dans l’objet renderer.
         * @return Le gl_engine::ShaderProgram contenu dans l'objet renderer.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        std::optional<ShaderProgram> removeProgram() noexcept;

        /**
         * @brief Interverti le gl_engine::ShaderProgram contenu dans le renderer avec celui fourni.
         * @param program Le nouveau gl_engine::ShaderProgram.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        void swapProgram( ShaderProgram& program ) noexcept;

        /**
         * @brief Ajoute une méthode de rendu.
         * @param renderer
         */
        void addMethod( std::function<void()> renderer );

    private:
        std::optional<ShaderProgram> program_{std::nullopt};

        std::function<void()> renderer_{};

        /**
         * @brief Exception lancée s’il y a déjà un shader program attaché au renderer.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         */
        class ProgramAlreadyPresent final : public LogicError {
        public:
            /**
             * @brief Construit l’exception avec la raison fournie.
             * @param what_arg La raison de l’exception.
             *
             * @exceptsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            explicit ProgramAlreadyPresent( const std::string& what_arg ) noexcept
            : LogicError(what_arg) {}

            /**
             * @overload
             * @brief Surcharge du constructeur prenant un pointeur vers une chaine de caractère.
             * @param what_arg Le pointeur.
             */
            explicit ProgramAlreadyPresent( const char* what_arg ) noexcept
            : ProgramAlreadyPresent(std::string{what_arg}) {}

            ProgramAlreadyPresent( const ProgramAlreadyPresent& ) noexcept = default;
            ProgramAlreadyPresent( ProgramAlreadyPresent&& ) noexcept = default;
            ProgramAlreadyPresent& operator=( const ProgramAlreadyPresent& ) noexcept = default;
            ProgramAlreadyPresent& operator=( ProgramAlreadyPresent&& ) noexcept = default;
            ~ProgramAlreadyPresent() noexcept override = default;
        };
    };

    Renderer::Renderer( ShaderProgram program, std::function<void()> renderer )
    : program_(std::move(program)), renderer_(std::move(renderer)) {}

    Renderer::Renderer( ShaderProgram program )
    : Renderer(std::move(program), nullptr ) {}

    inline void Renderer::addProgram( ShaderProgram program ) {
        if ( program_.has_value() ) {
            throw ProgramAlreadyPresent("L’objet de rendu a déjà un shader programme attaché.\n"
                                        "Veuillez le supprimer et réessayer.");
        }

        program_ = program;
    }
    inline std::optional<ShaderProgram> Renderer::removeProgram() noexcept {
        auto returnValue = program_;

        program_.reset();

        return returnValue;
    }
    inline void Renderer::swapProgram( ShaderProgram& program ) noexcept {
        std::swap(program, program_.value());
    }

    inline void Renderer::addMethod( std::function<void()> renderer ) {
        renderer_ = std::move(renderer);
    }

}

#endif // GLENGINE_RENDERER_HPP
