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

#ifndef APP_HPP
#define APP_HPP

#include <GLFW/glfw3.h>

#include <memory>

#include <glengine/utils.hpp>
#include <glengine/window.hpp>

// TODO Déplacer les définitions dans le cpp pour les longues fontions.
// TODO Finir de documenter l'interface
// TODO Finir de documenter le code développeur
namespace gl_engine {

    /**
     * @brief Cette classe est l'application permettant le rendu d'une scène.
     */
    class App {
    public:
        /**
         * @brief Retourne une référence vers l'instance de l'application.
         * @brief Crée l'application si elle n'existe pas.
         * @return App&
         * @throws TODO A déterminer
         * @exceptsafe TODO A déterminer
         */
        static App& getInstance();

        /**
         * @brief Supprime l'application créée
         * @expectsafe Ne lance pas
         */
        ~App() noexcept;

        /**
         * @brief Retourne un pointeur non propriétaire vers la fenêtre de rendu
         * @return Window* Un pointeur vers la fenêtre de rendu
         * @return nullptr si aucune fenêtre n'est liée.
         * @exceptsafe Ne lance pas
         */
        [[nodiscard]] Window* getWindow() const noexcept;

        /**
         * @brief Supprime la fenêtre de rendu actuellement contenue dans l'application
         * @exceptsafe Ne lance pas
         */
        void deleteWindow();

        /**
         * @brief Ajoute la fenêtre fournie, en tant que fenêtre de rendu de l'application
         * @param window[in] La nouvelle fenêtre de rendu
         * @throws bidon::appWindow_already_exists Lancée si l'application a déjà une fenêtre de rendu.
         * @exceptsafe Forte. Aucune modification effectuée.
         */
        void addWindow( std::unique_ptr<Window> window );


        // Opérations supprimées
        App( const App& ) = delete;

        App& operator=( const App& ) = delete;

        App& operator=( App&& ) noexcept = delete;

    protected:
        /**
         * @brief Construit l'application sans fenêtre
         */
        App();

        /**
         * @brief Construit l'application en déplaçant l'application fournie
         * @param application[in] L'application à déplacer
         * @exceptsafe Ne lance pas.
         */
        App( App&& ) noexcept = default;

        /**
         * @brief Crée l'application avec la fenêtre fournie. Si l'application existe déjà, un
         * @param window[in] La fenêtre de rendu
         */
        explicit App( std::unique_ptr<Window> window );

    private:
        static inline bool appExists = false;

        std::unique_ptr<Window> window_;


        /**
         * @brief Exception lancée si une erreur de GLFW survient.
         */
        using glfw_exception = std::runtime_error;
        /**
         * @brief Fonction utilisée pour afficher les messages d'erreur de GLFW.
         * @throws gl_engine::App::glfw_exception Lancée si une erreur GLFW survient.
         * @exceptsafe BASE. TODO A déterminer
         */
        static constexpr GLFWerrorfun DEFAULT_ERROR_CALLBACK_FUNCTION = []
                ( const int errorCode, const char* const errorMessage ){
            throw glfw_exception("Erreur " + std::to_string(errorCode) + " : " + errorMessage );
        };
    };
}


#endif //APP_HPP
