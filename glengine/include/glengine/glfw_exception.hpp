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

#ifndef GLENGINE_GLFW_EXCEPTION_HPP
#define GLENGINE_GLFW_EXCEPTION_HPP

#if __cplusplus < 201103L
#error La version minimum prise en charge est C++11
#endif

#include <GLFW/glfw3.h>

#include <exception>
#include <stdexcept>
#include <string>
#include <unordered_set>

/**
 * @brief Espace de noms gl_engine::glfw contient tous les objets concernant et en relation avec la bibliothèque GLFW
 */
namespace gl_engine::glfw {
    // Déclaration de la classe pour ErrorCode
    class exception;

    // region Alias
    // Alias plus explicite sur la raison de l’exception
    using no_error = glfw::exception;

    using not_initialized = glfw::exception;

    using no_current_context = glfw::exception;

    using invalid_enum = glfw::exception;

    using invalid_value = glfw::exception;

    using out_of_memory = glfw::exception;

    using api_unavailable = glfw::exception;

    using version_unavailable = glfw::exception;

    using platform_error = glfw::exception;

    using format_unavailable = glfw::exception;

    using no_window_context = glfw::exception;
    // endregion

    // region Code Erreur
    /**
     * @brief Objet représentant un code d’erreur de GLFW qui est valide.
     */
    class ErrorCode {
    public:
        // https://www.glfw.org/docs/3.3/group__errors.html#gafa30deee5db4d69c4c93d116ed87dbf4
        /// Code d’erreur représentant aucune erreur.
        static const ErrorCode NO_ERROR;
        /// Code d’erreur indiquant que GLFW n’est pas initialisée.
        static const ErrorCode NOT_INITIALIZED;
        /// Code d’erreur indiquant qu’aucun contexte n’est actuellement existant sur le thread actuel.
        static const ErrorCode NO_CURRENT_CONTEXT;
        /// Code d’erreur indiquant qu’une valeur fournie à une fonction GLFW est une valeur d’énumération non valide.
        static const ErrorCode INVALID_ENUM;
        /// Code d’erreur indiquant qu’une valeur fournie à une fonction GLFW est une valeur non valide.
        static const ErrorCode INVALID_VALUE;
        /// Code d’erreur indiquant qu’un manque de mémoire est apparue durant l’exécution d’une fonction GLFW.
        static const ErrorCode OUT_OF_MEMORY;
        /// Code d’erreur indiquant que l’API demandée n’est pas disponible sur le système actuel.
        static const ErrorCode API_UNAVAILABLE;
        /// Code d’erreur indiquant que la version demandée de l’API demandée n’est pas disponible sur le système actuel.
        static const ErrorCode VERSION_UNAVAILABLE;
        /// Code d’erreur indiquant une erreur spécifique à la plateforme s’est produite.
        static const ErrorCode PLATFORM_ERROR;
        /// Code d’erreur indiquant :
        /// - lors de la création d’une fenêtre que le format de pixel demandé n’est pas disponible
        /// - lors de l’interrogation du presse-papier, le contenu du presse-papier n’a pas pu être converti au format demandé.
        static const ErrorCode FORMAT_UNAVAILABLE;
        /// Code d’erreur indiquant qu’une fenêtre n’ayant pas de contexte a été transmît à une fonction GLFW demandant une fenêtre avec contexte.
        static const ErrorCode NO_WINDOW_CONTEXT;

        /**
         * @brief Impossible de créer un code d’erreur sans fournir un code.
         */
        constexpr ErrorCode() noexcept = delete;

        /**
         * @brief Construit un code d’erreur à partir d’un entier.
         * @brief La liste des entiers correspondants à un code d’erreur sont définis : https://www.glfw.org/docs/3.3/group__errors.html
         * @param code Un code d'erreur
         * @throws std::invalid_argument Lancée si l’argument code passé ne représente pas un code d’erreur de GLFW.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit ErrorCode( const int code )
        : code_(code) {
            static const std::unordered_set<int> errorCodes {
                GLFW_NO_ERROR, GLFW_NOT_INITIALIZED, GLFW_NO_CURRENT_CONTEXT, GLFW_INVALID_ENUM, GLFW_INVALID_VALUE,
                GLFW_OUT_OF_MEMORY, GLFW_API_UNAVAILABLE, GLFW_VERSION_UNAVAILABLE, GLFW_PLATFORM_ERROR,
                GLFW_FORMAT_UNAVAILABLE, GLFW_NO_WINDOW_CONTEXT
            };

            if ( errorCodes.find(code) == errorCodes.cend() ) {
                throw std::invalid_argument("Le code erreur : " + std::to_string(code) + " n'est pas pris en charge.\n"
                                             "Les seuls codes d’erreurs pris en charge sont définis par GLFW3.3.6 :\n"
                                             "https://www.glfw.org/docs/3.3/group__errors.html");
            }
        };

        constexpr ErrorCode( const ErrorCode& ) noexcept = default;
        constexpr ErrorCode( ErrorCode&& ) noexcept = default;

        constexpr ErrorCode& operator=( const ErrorCode& ) noexcept = default;
        constexpr ErrorCode& operator=( ErrorCode&& ) noexcept = default;

    private:
        int code_ = GLFW_NO_ERROR;

        /**
         * @brief Retourne un entier représentant le code d’erreur
         * @exceptsafe FORT. Ne lance aucune exception.
         */
        [[nodiscard]] int constexpr code() const noexcept {
            return code_;
        };

        friend class glfw::exception;
    };

    // region Définition
    // Définition des codes d’erreurs que GLFW lance
    // https://www.glfw.org/docs/3.3/group__errors.html
    inline const ErrorCode ErrorCode::NO_ERROR(GLFW_NO_ERROR);
    inline const ErrorCode ErrorCode::NOT_INITIALIZED(GLFW_NOT_INITIALIZED);
    inline const ErrorCode ErrorCode::NO_CURRENT_CONTEXT(GLFW_NO_CURRENT_CONTEXT);
    inline const ErrorCode ErrorCode::INVALID_ENUM(GLFW_INVALID_ENUM);
    inline const ErrorCode ErrorCode::INVALID_VALUE(GLFW_INVALID_VALUE);
    inline const ErrorCode ErrorCode::OUT_OF_MEMORY(GLFW_OUT_OF_MEMORY);
    inline const ErrorCode ErrorCode::API_UNAVAILABLE(GLFW_API_UNAVAILABLE);
    inline const ErrorCode ErrorCode::VERSION_UNAVAILABLE( GLFW_VERSION_UNAVAILABLE );
    inline const ErrorCode ErrorCode::PLATFORM_ERROR(GLFW_PLATFORM_ERROR);
    inline const ErrorCode ErrorCode::FORMAT_UNAVAILABLE(GLFW_FORMAT_UNAVAILABLE);
    inline const ErrorCode ErrorCode::NO_WINDOW_CONTEXT(GLFW_NO_WINDOW_CONTEXT);
    // endregion
    // endregion

    // region Exception
    /**
     * @brief Exception lancée quand une erreur survient avec GLFW
     */
    class exception : public std::exception {
    public:
        /**
         * @brief Construit l’exception avec un code d’erreur de GLFW valide et un message d’erreur
         * @param code
         * @param message Il est conseiller de ne pas mettre un message d’erreur vide.
         * @exceptsafe FORT. Ne lance aucune exception
         */
        exception( ErrorCode code, std::string message ) noexcept;

        exception( const exception& ) noexcept = default;
        exception( exception&& ) noexcept = default;
        exception& operator=( const exception& ) noexcept = default;
        exception& operator=( exception&& ) noexcept = default;

        ~exception() noexcept override = default;

        [[nodiscard]] const char* what() const noexcept override;
        [[nodiscard]] int code() const noexcept;

    private:
        int code_;
        std::string message_;
    };

    // region Constructeur
    exception::exception( const ErrorCode code, std::string message ) noexcept
    : std::exception(), code_(code.code()), message_(std::move(message)) {}
    // endregion

    // region Getter
    inline const char* exception::what() const noexcept {
        return message_.c_str();
    }

    inline int exception::code() const noexcept {
        return code_;
    }
    // endregion

    // endregion
}

#endif // GLENGINE_GLFW_EXCEPTION_HPP
