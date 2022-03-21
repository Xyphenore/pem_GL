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

#ifndef SCENE_HPP
#define SCENE_HPP

#include <optional>

#include <glengine/exception.hpp>
#include <glengine/object.hpp>
#include <glengine/renderer.hpp>

namespace gl_engine {
    /**
     * @brief Classe représentant une scène contenant des objects
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     */
    class Scene {
    public:
        /**
         * @brief Construit une scène sans object.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::Object
         */
        Scene() noexcept = default;

        /**
         * @brief Construit une scène avec aucuns objets et le gl_engine::Renderer fourni.
         * @param renderer L’objet qui fait le rendu.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        explicit Scene( Renderer renderer ) noexcept;

        /**
         * @brief Construit une scène avec le vecteur contenant les objects fourni.
         * @param objects Un tableau d’objets.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        explicit Scene( std::vector<Object> objects ) noexcept;

        /**
         * @brief Construit une scène avec le tableau d’objets fourni ainsi qu’avec la méthode de rendu.
         * @param objects Le tableau d’objets.
         * @param renderer La méthode de rendu.
         */
        explicit Scene( std::vector<Object> objects, Renderer renderer ) noexcept;

        /**
         * @brief Demande le rendu de la scène.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        void render() const noexcept;

        /**
         * @brief Ajoute un objet à la scène.
         * @param object L'objet a ajouter.
         */
        void add( Object object );

        /**
         * @brief Supprime l’objet fourni en paramètre.
         * @param object L'objet à supprimer.
         *
         * @exceptsafe NO-THROW.
         *
         * @note Ne fait rien si l’objet n’est pas présent.
         */
        void remove( Object object ) noexcept;

        /**
         * @brief Supprime tous les objets de la scène.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        void clear() noexcept;

        /**
         * @brief Ajoute l’objet de rendu gl_engine::Renderer à la scène, pour pouvoir la rendre.
         * @param renderer La function de rendu.
         *
         * @throw gl_engine::Scene::RendererAlreadyPresent Lancée si la méthode de rendu existe déjà.
         *
         * @exceptsafe FORT. Ne modifie aucune donnée.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see std::optional<Renderer> gl_engine::Scene::removeRenderer() noexcept
         */
        void addRenderer( Renderer renderer );

        /**
         * @brief Supprime et retourne l’objet de rendu.
         * @return Retourne l’objet de rendu s’il a été ajouté précédemment.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         */
        std::optional<Renderer> removeRenderer() noexcept;

    private:
        std::vector<Object> objects_{};

        std::optional<Renderer> renderer_{std::nullopt};

        /**
         * @brief Exception lancée si la fonction de rendu existe déjà dans la scène actuelle.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see gl_engine::Scene
         * @see gl_engine::Renderer
         */
        class RendererAlreadyPresent final : public LogicError {
        public:
            /**
             * @brief Construit une exception avec la raison de l’erreur fournie.
             * @param what_arg La raison de l’exception.
             *
             * @exceptsafe NO-THROW.
             *
             * @version 1.0
             * @since 0.1
             */
            explicit RendererAlreadyPresent( const std::string& what_arg ) noexcept
            : LogicError(what_arg) {}

            /**
             * @overload
             * @brief Surcharge du constructeur en passant la raison sous forme de pointeur vers une chaine de caractère.
             * @param what_arg Le pointeur.
             */
            explicit RendererAlreadyPresent( const char* what_arg ) noexcept
            : RendererAlreadyPresent( std::string{what_arg} ) {}

            RendererAlreadyPresent() noexcept = delete;
            RendererAlreadyPresent( const RendererAlreadyPresent& ) noexcept = default;
            RendererAlreadyPresent( RendererAlreadyPresent&& ) noexcept = default;
            RendererAlreadyPresent& operator=( const RendererAlreadyPresent& ) noexcept = default;
            RendererAlreadyPresent& operator=( RendererAlreadyPresent&& ) noexcept = default;
            ~RendererAlreadyPresent() noexcept override = default;
        };
    };

    Scene::Scene( Renderer renderer ) noexcept
    : renderer_(renderer) {}

    Scene::Scene( std::vector<Object> objects ) noexcept
    : objects_(std::move(objects)) {}

    Scene::Scene( std::vector<Object> objects, Renderer renderer ) noexcept
    : objects_(std::move(objects)), renderer_(renderer) {}


    inline void Scene::add( Object object ) {
        objects_.push_back(std::move(object));
    }
    inline void Scene::remove( Object object ) noexcept {

    }
    inline void Scene::clear() noexcept {
        objects_.clear();
    }

    inline void Scene::addRenderer( Renderer renderer ) {
        if ( renderer_.has_value() ) {
            throw RendererAlreadyPresent("La méthode de rendu est déjà existante dans la scène.\n"
                                         "Veuillez la supprimer en appelant la méthode removeRenderer().\n"
                                         "Puis ajouter la nouvelle méthode de rendu.\n");
        }

        renderer_ = renderer;
    }
    inline std::optional<Renderer>  Scene::removeRenderer() noexcept {
        auto returnValue = renderer_;

        renderer_.reset();

        return returnValue;
    }
}

#endif //SCENE_HPP
