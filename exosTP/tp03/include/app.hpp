#ifndef APP_HPP
#define APP_HPP

#include <GLFW/glfw3.h>

#include <memory>

#include "tp02-shape3D/config.hpp"
#include "utils.hpp"

// TODO Déplacer les définitions dans le cpp pour les longues fontions.
// TODO Finir de documenter l'interface
// TODO Finir de documenter le code développeur
namespace bidon {
    class Window;

    /**
     * @brief Cette classe est l'application permettant le rendu d'une scène.
     */
    class App {
    public:
        /**
         * @brief Crée l’application sans fenêtres.
         * @throw bidon::app_already_exists Lancée si l'application existe déjà.
         * @exceptsafe Forte. Aucune modification effectuée.
         */
        static std::unique_ptr<App> createApp();

        /**
         * @brief Crée l'application avec la fenêtre fournie. Si l'application existe déjà, un
         * @param window[in] La fenêtre de rendu.
         * @throw bidon::app_already_exists Lancée si l'application existe déjà.
         * @exceptsafe Forte. Aucune modification effectuée.
         */
        static std::unique_ptr<App> createApp( std::unique_ptr<Window> window );

        /**
         * @brief Supprime l'application créée
         * @expectsafe Ne lance pas
         */
        ~App() noexcept;

        /**
         * @brief Retourne un pointeur non propriétaire vers la fenêtre de rendu
         * @return Window* Un pointeur vers la fenêtre de rendu
         * @exceptsafe Ne lance pas
         */
        [[nodiscard]] Window* getWindow() const;

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
    };
}

// Public interface
inline std::unique_ptr<bidon::App> bidon::App::createApp() {
    return App::createApp( nullptr );
}

inline void bidon::App::deleteWindow() {
    window_.reset();
}


#endif //APP_HPP
