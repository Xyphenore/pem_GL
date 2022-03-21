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

#ifndef __cplusplus
#error Un compilateur C++ est nécessaire.
#endif

#if __cplusplus < 201703L
#error GL_Engine a été développée pour C++17. Veuillez supprimer cette condition est testé le code à vos risques et périls.
#endif


#include <GLFW/glfw3.h>

#include <exception>
#include <string>
#include <stdexcept>
#include <unordered_map>


// Note développeur : Ce fichier est très long, car les classes sont interdépendantes.
// Il est donc impossible de les séparer dans des fichiers à part sans créer un problème d'inclusion en boucle.
// Note développeur : Nécessaire pour l’amitié entre classes.

namespace gl_engine::glfw {
    class ErrorCode;
    class ExceptionFactory;

    /**
     * @brief Espace de noms contenant les interfaces entre les objets de gl_engine::glfw
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::glfw::interface::Exception_ErrorCode
     * @see gl_engine::glfw::interface::Window_GLFW
     * @see gl_engine::glfw::interface::SmartDestroyWindow_GLFW
     */
    namespace interface {
        class ErrorCode_ListErrorCode;
        class Factory_ListErrorCode;
        class Exception_ErrorCode;
        class Hash_ErrorCode;
        class Interface_FactoryListErrorCode_ErrorCode;
    }
}

namespace gl_engine::glfw {
    using Code_t = int;

    // TODO Refactoring utiliser une interface puis une class abstraite pour que le code soit meilleur.
    // Voir le graph sur LucidChart

    /**
     * @brief Exception lancée quand une erreur survient avec GLFW.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::glfw::ErrorCode
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     *
     * @note Pour les développeurs qu’ils veulent étendre cette classe, il est nécessaire de créer une méthode statique
     * Exception create(std:string reason) qui crée une Exception en fournissant la reason au constructeur de la classe étendant.
     */
    class Exception : public std::exception {
    public:
        /**
         * @brief Impossible de créer une exception sans un code d’erreur et sans raison.
         *
         * @version 1.0
         * @since 0.1
         */
        Exception() noexcept = delete;

        Exception( const Exception& ) noexcept = default;

        Exception( Exception&& ) noexcept = default;

        Exception& operator=( const Exception& ) noexcept = default;

        Exception& operator=( Exception&& ) noexcept = default;

        ~Exception() noexcept override = default;

        /**
         * @brief Retourne un pointeur vers le message d’erreur
         * @exceptsafe FORT. Ne lance aucune exception
         *
         * @version 1.0
         * @since 0.1
         *
         * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
         */
        [[nodiscard]] const char* what() const noexcept override;

        /**
         * @brief Retourne la raison du message d’erreur.
         * @exceptsafe FORT. Ne lance aucune exception.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
         */
        [[nodiscard]] const char* reason() const noexcept;

        /**
         * @brief Retourne le code d’erreur sous forme d’entier.
         * @exceptsafe FORT. Ne lance aucune exception
         *
         * @version 1.0
         * @since 0.1
         *
         * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
         */
        [[nodiscard]] int code() const noexcept;

    protected:
        /**
         * @brief Construit l’exception avec un code d’erreur de GLFW valide et un message d’erreur.
         * @param [in]code Un objet gl_engine::glfw::ErrorCode.
         * @param [in]reason Il est conseiller de mettre la raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ErrorCode
         */
        Exception( ErrorCode code, std::string reason ) noexcept;

    private:
        int code_;
        std::string reason_;
        std::string message_;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_NO_ERROR est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     *
     * @note Cette exception est seulement présente pour ne pas créer d’erreur si ce code d’erreur apparaît.
     * Mais cela n’a pas de logique que GLFW lance un code d’erreur NO_ERROR.
     * Il serra plus nécessaire de tester en profondeur les codes d’erreurs et les exceptions pouvant être lancés par GLFW.
     */
    class NoError final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        NoError() noexcept = delete;

        /**
         * @brief Crée une exception NoError avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit NoError( std::string reason ) noexcept;

        NoError( const NoError& ) noexcept = default;

        NoError( NoError&& ) noexcept = default;

        NoError& operator=( const NoError& ) noexcept = default;

        NoError& operator=( NoError&& ) noexcept = default;

        ~NoError() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_NOT_INITIALIZED est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class NotInitialized final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        NotInitialized() noexcept = delete;

        /**
         * @brief Crée une exception NotInitialized avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit NotInitialized( std::string reason ) noexcept;

        NotInitialized( const NotInitialized& ) noexcept = default;

        NotInitialized( NotInitialized&& ) noexcept = default;

        NotInitialized& operator=( const NotInitialized& ) noexcept = default;

        NotInitialized& operator=( NotInitialized&& ) noexcept = default;

        ~NotInitialized() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_NO_CURRENT_CONTEXT est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class NoCurrentContext final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        NoCurrentContext() noexcept = delete;

        /**
         * @brief Crée une exception NoCurrentContext avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit NoCurrentContext( std::string reason ) noexcept;

        NoCurrentContext( const NoCurrentContext& ) noexcept = default;

        NoCurrentContext( NoCurrentContext&& ) noexcept = default;

        NoCurrentContext& operator=( const NoCurrentContext& ) noexcept = default;

        NoCurrentContext& operator=( NoCurrentContext&& ) noexcept = default;

        ~NoCurrentContext() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_INVALID_ENUM est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class InvalidEnum final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        InvalidEnum() noexcept = delete;

        /**
         * @brief Crée une exception InvalidEnum avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit InvalidEnum( std::string reason ) noexcept;

        InvalidEnum( const InvalidEnum& ) noexcept = default;

        InvalidEnum( InvalidEnum&& ) noexcept = default;

        InvalidEnum& operator=( const InvalidEnum& ) noexcept = default;

        InvalidEnum& operator=( InvalidEnum&& ) noexcept = default;

        ~InvalidEnum() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_INVALID_VALUE est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class InvalidValue final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        InvalidValue() noexcept = delete;

        /**
         * @brief Crée une exception InvalidValue avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit InvalidValue( std::string reason ) noexcept;

        InvalidValue( const InvalidValue& ) noexcept = default;

        InvalidValue( InvalidValue&& ) noexcept = default;

        InvalidValue& operator=( const InvalidValue& ) noexcept = default;

        InvalidValue& operator=( InvalidValue&& ) noexcept = default;

        ~InvalidValue() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_OUT_OF_MEMORY est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class OutOfMemory final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        OutOfMemory() noexcept = delete;

        /**
         * @brief Crée une exception OutOfMemory avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit OutOfMemory( std::string reason ) noexcept;

        OutOfMemory( const OutOfMemory& ) noexcept = default;

        OutOfMemory( OutOfMemory&& ) noexcept = default;

        OutOfMemory& operator=( const OutOfMemory& ) noexcept = default;

        OutOfMemory& operator=( OutOfMemory&& ) noexcept = default;

        ~OutOfMemory() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_API_UNAVAILABLE est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class ApiUnavailable final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        ApiUnavailable() noexcept = delete;

        /**
         * @brief Crée une exception ApiUnavailable avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit ApiUnavailable( std::string reason ) noexcept;

        ApiUnavailable( const ApiUnavailable& ) noexcept = default;

        ApiUnavailable( ApiUnavailable&& ) noexcept = default;

        ApiUnavailable& operator=( const ApiUnavailable& ) noexcept = default;

        ApiUnavailable& operator=( ApiUnavailable&& ) noexcept = default;

        ~ApiUnavailable() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_VERSION_UNAVAILABLE est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class VersionUnavailable final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        VersionUnavailable() noexcept = delete;

        /**
         * @brief Crée une exception VersionUnavailable avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit VersionUnavailable( std::string reason ) noexcept;

        VersionUnavailable( const VersionUnavailable& ) noexcept = default;

        VersionUnavailable( VersionUnavailable&& ) noexcept = default;

        VersionUnavailable& operator=( const VersionUnavailable& ) noexcept = default;

        VersionUnavailable& operator=( VersionUnavailable&& ) noexcept = default;

        ~VersionUnavailable() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_FORMAT_UNAVAILABLE est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class FormatUnavailable final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        FormatUnavailable() noexcept = delete;

        /**
         * @brief Crée une exception FormatUnavailable avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit FormatUnavailable( std::string reason ) noexcept;

        FormatUnavailable( const FormatUnavailable& ) noexcept = default;

        FormatUnavailable( FormatUnavailable&& ) noexcept = default;

        FormatUnavailable& operator=( const FormatUnavailable& ) noexcept = default;

        FormatUnavailable& operator=( FormatUnavailable&& ) noexcept = default;

        ~FormatUnavailable() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_NO_WINDOW_CONTEXT est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class NoWindowContext final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        NoWindowContext() noexcept = delete;

        /**
         * @brief Crée une exception NoWindowContext avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit NoWindowContext( std::string reason ) noexcept;

        NoWindowContext( const NoWindowContext& ) noexcept = default;

        NoWindowContext( NoWindowContext&& ) noexcept = default;

        NoWindowContext& operator=( const NoWindowContext& ) noexcept = default;

        NoWindowContext& operator=( NoWindowContext&& ) noexcept = default;

        ~NoWindowContext() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Exception lancée si le code d’erreur GLFW_PLATFORM_ERROR est lancé.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class PlatformError final : public Exception {
    public:
        /**
         * @brief Impossible de créer une exception sans préciser d’argument.
         *
         * @version 1.0
         * @since 0.1
         */
        PlatformError() noexcept = delete;

        /**
         * @brief Crée une exception NoError avec la raison fournie.
         * @param [in]reason La raison de l’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         */
        explicit PlatformError( std::string reason ) noexcept;

        PlatformError( const PlatformError& ) noexcept = default;

        PlatformError( PlatformError&& ) noexcept = default;

        PlatformError& operator=( const PlatformError& ) noexcept = default;

        PlatformError& operator=( PlatformError&& ) noexcept = default;

        ~PlatformError() noexcept override = default;

        /**
         * @brief Crée une gl_engine::glfw::Exception.
         * @param [in]reason La raison de l’erreur.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::ExceptionFactory
         * @see gl_engine::glfw::Exception
         *
         * @note Cette méthode est nécessaire pour la factory.
         */
        static Exception* create( std::string reason ) noexcept;
    };


    /**
     * @brief Liste de toutes les static factories permettant de créer les exceptions de GLFW.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::glfw::Exception
     * @see gl_engine::glfw::ErrorCode
     */
    class ListErrorCode final {
    public :
        // Note développeur : Impossible d’instancier un objet ListErrorCode, toutes les fonctions sont statiques.
        // Car c’est la même liste pour tout le code.

        ListErrorCode() noexcept = delete;

        ListErrorCode( const ListErrorCode& ) noexcept = delete;

        ListErrorCode( ListErrorCode&& ) noexcept = delete;

        ListErrorCode& operator=( const ListErrorCode& ) noexcept = delete;

        ListErrorCode& operator=( ListErrorCode&& ) noexcept = delete;

        ~ListErrorCode() noexcept = delete;

    private:
        /**
         * @brief Classe représentant une structure composée d’un titre et d’une fonction de création d’exception.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see gl_engine::glfw::ListErrorCode
         * @see gl_engine::glfw::ErrorCode
         * @see gl_engine::glfw::Exception
         */
        class Tuple final {
        public:
            /**
             * @brief Objet représentant une fonction qui crée une exception.
             *
             * @version 1.0
             * @since 0.1
             * @author Axel DAVID
             *
             * @see gl_engine::glfw::Exception
             */
            class CreateFunction final {
            public:
                using Creator_ptr = Exception* ( * )( std::string );

                /**
                 * @brief Impossible de créer une fonction de création d’exception sans argument.
                 *
                 * @version 1.0
                 * @since 0.1
                 *
                 * @see gl_engine::glfw::Exception
                 */
                CreateFunction() noexcept = delete;

                /**
                 * @brief Crée une fonction de création d’exception à partir du pointeur fourni.
                 * @param [in]creator Le pointeur vers la fonction de création d’exception.
                 *
                 * @throws gl_engine::glfw::ListErrorCode::Tuple::CreateFunction::InvalidCreateFunction Lancée si le pointeur est null.
                 * @exceptsafe FORT. Ne modifie aucune donnée.
                 *
                 * @version 1.0
                 * @since 0.1
                 *
                 * @see gl_engine::glfw::Exception
                 */
                explicit CreateFunction( Creator_ptr creator )
                        : creator_( creator ) {
                    if ( creator_ == nullptr ) {
                        throw InvalidCreateFunction();
                    }
                }

                CreateFunction( const CreateFunction& ) noexcept = default;

                CreateFunction( CreateFunction&& ) noexcept = default;

                CreateFunction& operator=( const CreateFunction& ) noexcept = default;

                CreateFunction& operator=( CreateFunction&& ) noexcept = default;

                ~CreateFunction() noexcept = default;

                /**
                 * @brief Retourne le pointeur vers la fonction de création de l’exception.
                 *
                 * @exceptsafe NO-THROWS.
                 *
                 * @version 1.0
                 * @since 0.1
                 *
                 * @see gl_engine::glfw::Exception
                 */
                [[nodiscard]] Creator_ptr to_function() const noexcept {
                    return creator_;
                }

            private:
                Creator_ptr creator_;

                /**
                 * @brief Exception lancée si le pointeur fourni au constructeur gl_engine::glfw::ListErrorCode::Tuple::CreateFunction est null.
                 *
                 * @version 1.0
                 * @since 0.1
                 * @author Axel DAVID
                 *
                 * @see gl_engine::glfw::ListErrorCode::Tuple::CreateFunction
                 * @see gl_engine::glfw::Exception
                 */
                class InvalidCreateFunction final
                        : public std::invalid_argument {
                public:
                    /**
                     * @brief Constructeur par défaut avec un message préfixé.
                     *
                     * @exceptsafe NO-THROWS.
                     */
                    InvalidCreateFunction() noexcept
                            : std::invalid_argument(
                            "Le pointeur vers la fonction de création d’exception est null." ) {}

                    InvalidCreateFunction( const InvalidCreateFunction& ) noexcept = default;

                    InvalidCreateFunction( InvalidCreateFunction&& ) noexcept = default;

                    InvalidCreateFunction& operator=( const InvalidCreateFunction& ) noexcept = default;

                    InvalidCreateFunction& operator=( InvalidCreateFunction&& ) noexcept = default;

                    ~InvalidCreateFunction() noexcept override = default;
                };
            };

            using Creator_ptr = CreateFunction::Creator_ptr;

            /**
             * @brief Objet représentant le titre de l’exception.
             *
             * @version 1.0
             * @since 0.1
             * @author Axel DAVID
             *
             * @see gl_engine::glfw::Exception
             */
            class Title final {
            public:
                /**
                 * @brief Impossible de créer un titre sans passé d’argument.
                 *
                 * @version 1.0
                 * @since 0.1
                 *
                 * @see gl_engine::glfw::Exception
                 */
                Title() noexcept = delete;

                /**
                 * @brief Construit un titre à partir de la std::string fournie.
                 * @param title La std::string représentant le titre.
                 *
                 * @throws gl_engine::glfw::ListErrorCode::Tuple::Title::InvalidTitle Lancée si l’argument est vide.
                 * @exceptsafe FORT. Ne modifie pas de donnée.
                 *
                 * @version 1.0
                 * @since 0.1
                 *
                 * @see gl_engine::glfw::Exception
                 */
                explicit Title( std::string title )
                        : title_( std::move( title ) ) {
                    if ( title_.empty() ) {
                        throw InvalidTitle();
                    }
                }

                /**
                 * @overload
                 * @brief Surcharge du constructeur pour prendre un const char*.
                 * @param title Le pointeur vers la chaine de caractères.
                 */
                explicit Title( const char* title )
                        : Title( std::string( title ) ) {}

                /**
                 * @overload
                 * @brief Surcharge du constructeur pour prendre une std::string_view.
                 * @param title La vue vers le titre.
                 */
                explicit Title( std::string_view title )
                        : Title( std::string( title ) ) {}

                Title( const Title& ) noexcept = default;

                Title( Title&& ) noexcept = default;

                Title& operator=( const Title& ) noexcept = default;

                Title& operator=( Title&& ) noexcept = default;

                ~Title() noexcept = default;

                /**
                 * @brief Retourne le titre sous forme de std::string.
                 * @return Le titre de l’exception.
                 *
                 * @exceptsafe NO-THROWS.
                 *
                 * @version 1.0
                 * @since 0.1
                 *
                 * @see gl_engine::glfw::Exception
                 */
                [[nodiscard]] std::string to_string() const noexcept {
                    return title_;
                }

            private:
                std::string title_;

                /**
                 * @brief Exception lancée par le constructeur de gl_engine::glfw::ListErrorCode::Tuple::Title si le titre passé est null.
                 *
                 * @version 1.0
                 * @since 0.1
                 * @author Axel DAVID
                 *
                 * @see gl_engine::glfw::ListErrorCode::Tuple::Title
                 * @see gl_engine::glfw::Exception
                 */
                class InvalidTitle final
                        : public std::invalid_argument {
                public:
                    /**
                     * @brief Crée l’exception avec un message prédéfini.
                     *
                     * @exceptsafe NO-THROWS.
                     *
                     * @version 1.0
                     * @since 0.1
                     *
                     * @see gl_engine::glfw::Exception
                     */
                    InvalidTitle() noexcept
                            : std::invalid_argument(
                            "Le titre de l’exception fourni est vide, veuillez fourni un titre non vide." ) {};

                    InvalidTitle( const InvalidTitle& ) noexcept = default;

                    InvalidTitle( InvalidTitle&& ) noexcept = default;

                    InvalidTitle& operator=( const InvalidTitle& ) noexcept = default;

                    InvalidTitle& operator=( InvalidTitle&& ) noexcept = default;

                    ~InvalidTitle() noexcept override = default;
                };
            };

            /**
             * @brief Impossible de créer un Tuple sans spécifier d’argument.
             *
             * @version 1.0
             * @since 0.1
             */
            Tuple() noexcept = delete;

            /**
             * @brief Construit un Tuple à partir d’un Title et d’une CreateFunction.
             * @param title Le titre de l’exception à stocker.
             * @param creator La fonction de création pour cette exception.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ListErrorCode::Tuple::Title
             * @see gl_engine::glfw::ListErrorCode::Tuple::CreateFunction
             * @see gl_engine::glfw::Exception
             */
            explicit Tuple( Title title, CreateFunction creator ) noexcept
                    : title_( std::move( title ) ), creator_( creator ) {}

            Tuple( const Tuple& other ) noexcept = default;

            Tuple( Tuple&& other ) noexcept = default;

            Tuple& operator=( const Tuple& other ) noexcept = default;

            Tuple& operator=( Tuple&& other ) noexcept = default;

            ~Tuple() noexcept = default;

            /**
             * @brief Récupère le titre de l’exception sous forme de std::string.
             * @return Une std::string.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ListErrorCode::Tuple::Title
             * @see gl_engine::glfw::Exception
             */
            [[nodiscard]] std::string title() const noexcept {
                return title_.to_string();
            }

            /**
             * @brief Retourne un pointeur vers la fonction de création d’exception.
             * @return Un pointeur vers la fonction de création.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ListErrorCode::Tuple::CreateFunction
             * @see gl_engine::glfw::Exception
             */
            [[nodiscard]] Creator_ptr creator() const noexcept {
                return creator_.to_function();
            }

        private:
            Title title_;
            CreateFunction creator_;
        };


        using Title = Tuple::Title;
        using CreateFunction = Tuple::CreateFunction;


        /**
         * @brief Liste de toutes les static factories permettant de créer les exceptions de GLFW, ainsi que des représentations des codes d’erreurs sous forme de string.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         * @see gl_engine::glfw::ErrorCode
         */
        static const inline std::unordered_map<Code_t, Tuple> list_{
            { GLFW_NO_ERROR, Tuple{Title( "GLFW_NO_ERROR" ), CreateFunction(&NoError::create)} },
            { GLFW_NOT_INITIALIZED, Tuple{Title( "GLFW_NOT_INITIALIZED" ), CreateFunction(&NotInitialized::create)} },
            { GLFW_NO_CURRENT_CONTEXT, Tuple{Title( "GLFW_NO_CURRENT_CONTEXT" ), CreateFunction(&NoCurrentContext::create)} },
            { GLFW_INVALID_ENUM, Tuple{Title( "GLFW_INVALID_ENUM" ), CreateFunction(&InvalidEnum::create)} },
            { GLFW_INVALID_VALUE, Tuple{Title( "GLFW_INVALID_VALUE" ), CreateFunction(&InvalidValue::create)} },
            { GLFW_OUT_OF_MEMORY, Tuple{Title( "GLFW_OUT_OF_MEMORY" ), CreateFunction(&OutOfMemory::create)} },
            { GLFW_API_UNAVAILABLE, Tuple{Title( "GLFW_API_UNAVAILABLE" ), CreateFunction(&ApiUnavailable::create)} },
            { GLFW_VERSION_UNAVAILABLE, Tuple{Title( "GLFW_VERSION_UNAVAILABLE" ), CreateFunction(&VersionUnavailable::create)} },
            { GLFW_PLATFORM_ERROR, Tuple{Title( "GLFW_PLATFORM_ERROR" ), CreateFunction(&PlatformError::create)} },
            { GLFW_FORMAT_UNAVAILABLE, Tuple{Title( "GLFW_FORMAT_UNAVAILABLE" ), CreateFunction(&FormatUnavailable::create)} },
            { GLFW_NO_WINDOW_CONTEXT, Tuple{Title( "GLFW_NO_WINDOW_CONTEXT" ), CreateFunction(&NoWindowContext::create)} }
            };


        /**
         * @brief Recherche si le code d’erreur fourni est présent dans la liste des codes d’erreurs pris en charge.
         * @param code Le code d’erreur.
         * @return Retourne une copie de l’itérateur contenant le code d’erreur, ainsi que sa représentation sous forme de string et l’adresse du constructeur.
         *
         * @version 1.0
         * @since 0.1
         *
         * @note Sachant que les code d’erreurs sont déterminés à partir de la bibliothèque GLFW et surtout à la compilation.\n
         * @note Il est impossible que cette fonction retourne un pointeur égale à cend().\n
         * @note Car les constantes définies dans la classe gl_engine::glfw::ErrorCode, sont définies d’après cette liste.\n
         * @note De plus toute création de code d’erreur gl_engine::glfw::ErrorCode à partir d’un entier, vérifie que l’entier est présent dans cette liste.
         */
        static auto find( Code_t code ) noexcept {
            return list_.find( code );
        }

        /**
         * @brief Détermine si le code d’erreur fourni est un code d’erreur de GLFW.
         * @param [in]code Le code d’erreur.
         * @return Un booléen indiquant si le code est présent dans la liste.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
         */
        static bool contains( Code_t code ) noexcept {
            return find( code ) != list_.cend();
        }


        // Note développeur : Interfaces communiquant avec la liste
        friend class gl_engine::glfw::interface::ErrorCode_ListErrorCode;

        friend class gl_engine::glfw::interface::Factory_ListErrorCode;
    };


    namespace interface {
        /**
         * @brief Interface entre gl_engine::glfw::ErrorCode et gl_engine::glfw::ListErrorCode.\n
         * @brief Elle permet de limiter l'accès de la classe gl_engine::glfw::ListErrorCode à la classe gl_engine::glfw::ErrorCode.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see gl_engine::glfw::ErrorCode
         * @see  gl_engine::glfw::ListErrorCode
         */
        class ErrorCode_ListErrorCode final {
        public :
            // Note développeur : C’est la même interface pour tout le code, il est donc impossible d’instancier une interface.

            ErrorCode_ListErrorCode() noexcept = delete;

            ErrorCode_ListErrorCode( const ErrorCode_ListErrorCode& ) noexcept = delete;

            ErrorCode_ListErrorCode& operator=( const ErrorCode_ListErrorCode& ) noexcept = delete;

            ErrorCode_ListErrorCode( ErrorCode_ListErrorCode&& ) noexcept = delete;

            ErrorCode_ListErrorCode& operator=( ErrorCode_ListErrorCode&& ) noexcept = delete;

            ~ErrorCode_ListErrorCode() noexcept = delete;

        private:
            /**
             * @brief Vérifie si le code d’erreur fourni est un code d’erreur de GLFW.
             * @param [in]code Le code d’erreur.
             * @return Retourne un booléen indiquant si le code fourni est un code GLFW.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             */
            static bool contains( Code_t code ) noexcept {
                return ListErrorCode::contains( code );
            }

            /**
             * @brief Recherche si le code fourni est compris dans la liste de code d’erreur pris en charge.
             * @param [in]code Le code d’erreur.
             * @return Un itérateur contenant :\n
             * - le code d’erreur sous forme d’entier.\n
             * - la représentation sous forme de std::string\n
             * - un pointeur vers la fonction construisant l’exception.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::Exception
             */
            static auto find( Code_t code ) noexcept {
                return ListErrorCode::find( code );
            }

            friend glfw::ErrorCode;
        };
    }


    /**
     * @brief Objet représentant un code d’erreur de GLFW.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     * @see gl_engine::glfw::Exception
     */
    class ErrorCode final {
    public:
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
        /// Code d’erreur indiquant :\n
        /// - lors de la création d’une fenêtre que le format de pixel demandé n’est pas disponible.\n
        /// - lors de l’interrogation du presse-papier, le contenu du presse-papier n’a pas pu être converti au format demandé.
        static const ErrorCode FORMAT_UNAVAILABLE;
        /// Code d’erreur indiquant qu’une fenêtre n’ayant pas de contexte a été transmît à une fonction GLFW demandant une fenêtre avec contexte.
        static const ErrorCode NO_WINDOW_CONTEXT;


        /**
         * @brief Impossible de créer un code d’erreur sans fournir un code.
         *
         * @version 1.0
         * @since 0.1
         */
        ErrorCode() noexcept = delete;

        /**
         * @brief Construit un code d’erreur à partir d’un entier.\n
         *
         * @param [in]code Un code d'erreur.
         * @throws gl_engine::glfw::ErrorCode::InvalidErrorCode Lancée si le code passé ne représente pas un code d’erreur de GLFW.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
         */
        constexpr explicit ErrorCode( Code_t code )
                : code_( code ) {
            if ( !interface::ErrorCode_ListErrorCode::contains( code ) ) {
                throw InvalidErrorCode( code );
            }
        };

        constexpr ErrorCode( const ErrorCode& ) noexcept = default;

        constexpr ErrorCode( ErrorCode&& ) noexcept = default;

        constexpr ErrorCode& operator=( const ErrorCode& ) noexcept = default;

        constexpr ErrorCode& operator=( ErrorCode&& ) noexcept = default;

        /**
         * @brief Récupère le nom du code d’erreur.
         * @return Une chaine de caractères correspondant au code d’erreur.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
         * @see gl_engine::glfw::ListErrorCode
         */
        [[nodiscard]] std::string to_string() const noexcept;

        /**
         * @overload std::string gl_engine::glfw::ErrorCode::to_string()
         *
         * @brief Convertit un objet ErrorCode en sa chaine de caractère.
         *
         * @param [in]code Un objet gl_engine::glfw::ErrorCode.
         * @return La chaine de caractère correspondant au code d’erreur.
         *
         * @see std::string gl_engine::glfw::ErrorCode::to_string()
         */
        static std::string to_string( ErrorCode code ) noexcept;

    private:
        Code_t code_ = GLFW_NO_ERROR;

        /**
         * @brief Retourne un entier représentant le code d’erreur
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         */
        [[nodiscard]] Code_t constexpr code() const noexcept {
            return code_;
        };


        /**
         * @brief Exception lancée si le code d’erreur fourni lors de la création d’un objet gl_engine::glfw::ErrorCode est invalide.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
         */
        class InvalidErrorCode final
                : public std::invalid_argument {
        public:
            /**
             * @brief Impossible de créer une exception sans préciser le code d’erreur.
             *
             * @version 1.0
             * @since 0.1
             */
            InvalidErrorCode() noexcept = delete;

            /**
             * @brief Crée une exception avec le code fourni.
             * @param [in]code Code d’erreur GLFW.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ErrorCode
             */
            explicit InvalidErrorCode( Code_t code ) noexcept;

            InvalidErrorCode( const InvalidErrorCode& other ) noexcept = default;

            InvalidErrorCode( InvalidErrorCode&& other ) noexcept = default;

            InvalidErrorCode& operator=( const InvalidErrorCode& other ) noexcept = default;

            InvalidErrorCode& operator=( InvalidErrorCode&& other ) noexcept = default;

            ~InvalidErrorCode() noexcept override = default;
        };


        friend class interface::Exception_ErrorCode;

        friend class interface::Hash_ErrorCode;

        friend class interface::Interface_FactoryListErrorCode_ErrorCode;

        friend bool operator==( const ErrorCode&, const ErrorCode& ) noexcept;
    };


    // Définition des codes d’erreurs que GLFW lance
    // Si une exception est lancée durant la création des constantes, c’est une erreur de logique
    // Car les macros sont définies par GLFW
    // https://www.glfw.org/docs/3.3/group__errors.html

    inline const ErrorCode ErrorCode::NO_ERROR( GLFW_NO_ERROR );
    inline const ErrorCode ErrorCode::NOT_INITIALIZED( GLFW_NOT_INITIALIZED );
    inline const ErrorCode ErrorCode::NO_CURRENT_CONTEXT( GLFW_NO_CURRENT_CONTEXT );
    inline const ErrorCode ErrorCode::INVALID_ENUM( GLFW_INVALID_ENUM );
    inline const ErrorCode ErrorCode::INVALID_VALUE( GLFW_INVALID_VALUE );
    inline const ErrorCode ErrorCode::OUT_OF_MEMORY( GLFW_OUT_OF_MEMORY );
    inline const ErrorCode ErrorCode::API_UNAVAILABLE( GLFW_API_UNAVAILABLE );
    inline const ErrorCode ErrorCode::VERSION_UNAVAILABLE( GLFW_VERSION_UNAVAILABLE );
    inline const ErrorCode ErrorCode::PLATFORM_ERROR( GLFW_PLATFORM_ERROR );
    inline const ErrorCode ErrorCode::FORMAT_UNAVAILABLE( GLFW_FORMAT_UNAVAILABLE );
    inline const ErrorCode ErrorCode::NO_WINDOW_CONTEXT( GLFW_NO_WINDOW_CONTEXT );

    inline bool operator==( const ErrorCode& code1, const ErrorCode& code2 ) noexcept {
        return code1.code() == code2.code();
    }

    inline bool operator!=( const ErrorCode& code1, const ErrorCode& code2 ) noexcept {
        return !operator==( code1, code2 );
    }

    inline std::string ErrorCode::to_string() const noexcept {
        return interface::ErrorCode_ListErrorCode::find( code_ )->second.title();
    }

    inline std::string ErrorCode::to_string( ErrorCode code ) noexcept {
        return code.to_string();
    }

    inline ErrorCode::InvalidErrorCode::InvalidErrorCode( Code_t code ) noexcept
    : std::invalid_argument( "Le code erreur : " + std::to_string( code ) + " n'est pas pris en charge.\n"
                                "Les seuls codes d’erreurs pris en charge sont définis par GLFW3.3.6 :\n"
                                "https://www.glfw.org/docs/3.3/group__errors.html" ) {}


    namespace interface {
        /**
         * @brief Interface entre l'interface gl_engine::glfw::interface::Factory_ListErrorCode et l'objet gl_engine::glfw::ErrorCode.
         * Permettant à l’interface gl_engine::glfw::interface::Factory_ListErrorCode de récupérer le code en entier d’un gl_engine::glfw::ErrorCode.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @note Cette interface permet de limiter l'accès de l'interface gl_engine::glfw::interface::Factory_ListErrorCode
         * dans l'objet gl_engine::glfw::ErrorCode.
         *
         * @see gl_engine::glfw::ErrorCode
         * @see gl_engine::glfw::ExceptionFactory
         */
        class Interface_FactoryListErrorCode_ErrorCode final {
        public:
            // Note développeur : Cette interface est identique pour tout le programme, il est donc impossible de l’instancier.

            using I_FLEC_EC = Interface_FactoryListErrorCode_ErrorCode;

            Interface_FactoryListErrorCode_ErrorCode() noexcept = delete;

            Interface_FactoryListErrorCode_ErrorCode( const I_FLEC_EC& ) noexcept = delete;

            Interface_FactoryListErrorCode_ErrorCode( I_FLEC_EC&& ) noexcept = delete;

            I_FLEC_EC& operator=( const I_FLEC_EC& ) noexcept = delete;

            I_FLEC_EC& operator=( I_FLEC_EC&& ) noexcept = delete;

            ~Interface_FactoryListErrorCode_ErrorCode() noexcept = delete;

        private:
            /**
             * @brief Retourne le code d’erreur sous forme d’un entier.
             * @param code Objet gl_engine::glfw::ErrorCode.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ErrorCode
             */
            static Code_t code( ErrorCode code ) noexcept {
                return code.code();
            }

            friend Factory_ListErrorCode;
        };

        /**
         * @brief Interface entre gl_engine::glfw::ExceptionFactory et gl_engine::glfw::ErrorCode.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @note Elle permet de limiter l'accès de gl_engine::glfw::ExceptionFactory dans gl_engine::glfw::ErrorCode.
         */
        class Factory_ListErrorCode final {
        public:
            // Note développeur : Cette interface est identique dans tout le code, il est donc impossible de l’instancier.

            Factory_ListErrorCode() noexcept = delete;

            Factory_ListErrorCode( const Factory_ListErrorCode& ) noexcept = delete;

            Factory_ListErrorCode& operator=( const Factory_ListErrorCode& ) noexcept = delete;

            Factory_ListErrorCode( Factory_ListErrorCode&& ) noexcept = delete;

            Factory_ListErrorCode& operator=( Factory_ListErrorCode&& ) noexcept = delete;

            ~Factory_ListErrorCode() noexcept = delete;

        private:
            /**
             * @brief Recherche le code d’erreur dans la liste des codes d’erreurs pris en charge.
             * @param code Objet gl_engine::glfw::ErrorCode.
             * @return Un itérateur contenant :\n
             * - le code d’erreur sous forme d’entier.\n
             * - la représentation sous forme de std::string\n
             * - un pointeur vers la fonction construisant l’exception.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ErrorCode
             * @see gl_engine::glfw::ExceptionFactory
             */
            static auto find( ErrorCode code ) noexcept {
                return ListErrorCode::find( Interface_FactoryListErrorCode_ErrorCode::code( code ) );
            }

            /**
             * @brief Vérifie si le code d’erreur se trouve dans la liste des codes d’erreurs pris en charge.
             * @param code Objet gl_engine::glfw::ErrorCode.
             * @return Un booléen indiquant la présence ou non du code d’erreur.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ErrorCode
             * @see gl_engine::glfw::ExceptionFactory
             */
            static bool contains( ErrorCode code ) noexcept {
                return ListErrorCode::contains( interface::Interface_FactoryListErrorCode_ErrorCode::code( code ) );
            }

            /**
             * @brief Récupère la fonction de construction pour le code d’erreur fourni.
             * @param code Objet gl_engine::glfw::ErrorCode
             * @return Un pointeur vers la fonction de construction de l’exception pour ce code d’erreur.
             *
             * @exceptsafe NO-THROWS.
             *
             * @see gl_engine::glfw::ErrorCode
             * @see gl_engine::glfw::ExceptionFactory
             */
            static auto getBuilder( ErrorCode code ) noexcept {
                return find( code )->second.creator();
            }

            friend glfw::ExceptionFactory;
        };

        /**
     * @brief Interface limitée entre l’objet gl_engine::glfw::Exception et gl_engine::glfw::ErrorCode.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::glfw::Exception
     * @see gl_engine::glfw::ErrorCode
     */
        class Exception_ErrorCode final {
        public:
            //Note développeur : Cette interface est identique dans tout le code, il est donc impossible de l’instancier.

            Exception_ErrorCode() noexcept = delete;
            Exception_ErrorCode(const Exception_ErrorCode&) noexcept = delete;
            Exception_ErrorCode(Exception_ErrorCode&&) noexcept = delete;
            Exception_ErrorCode& operator=(const Exception_ErrorCode&) noexcept = delete;
            Exception_ErrorCode& operator=(Exception_ErrorCode&&) noexcept = delete;
            ~Exception_ErrorCode() noexcept = delete;

        private:
            /**
             * @brief Retourne le code d’erreur en entier d’un Objet gl_engine::glfw::ErrorCode
             * @param [in]code Objet ErrorCode.
             * @return Code d’erreur comme un entier
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ErrorCode
             */
            [[nodiscard]]
            static constexpr Code_t code(glfw::ErrorCode code) noexcept {
                return code.code();
            }

            friend class gl_engine::glfw::Exception;
        };

        /**
         * @brief Interface entre std::hash et gl_engine::glfw::ErrorCode.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see std::hash
         * @see gl_engine::glfw::ErrorCode
         */
        class Hash_ErrorCode final {
        public:
            // Note développeur : Cette interface est identique dans tout le code, il est donc impossible de l’instancier.

            Hash_ErrorCode() noexcept = delete;
            Hash_ErrorCode(const Hash_ErrorCode &) noexcept = delete;
            Hash_ErrorCode(Hash_ErrorCode &&) noexcept = delete;
            Hash_ErrorCode &operator=(const Hash_ErrorCode &) noexcept = delete;
            Hash_ErrorCode &operator=(Hash_ErrorCode &&) noexcept = delete;
            ~Hash_ErrorCode() noexcept = delete;

        private:
            /**
             * @brief Retourne le code d’erreur en entier d’un Objet gl_engine::glfw::ErrorCode
             * @param [in]code Objet ErrorCode.
             * @return Code d’erreur comme un entier
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::glfw::ErrorCode
             */
            [[nodiscard]]
            static constexpr Code_t code(glfw::ErrorCode code) noexcept {
                return code.code();
            }

            friend class std::hash<gl_engine::glfw::ErrorCode>;
        };
    }


    inline Exception::Exception( const ErrorCode code, std::string reason ) noexcept
    : std::exception(), code_(interface::Exception_ErrorCode::code(code)), reason_(std::move(reason)),
      message_( "Erreur " + std::to_string(code_) + " : " + code.to_string() + " : " + reason_) {}

    inline const char* Exception::what() const noexcept {
        return message_.c_str();
    }

    inline const char* Exception::reason() const noexcept {
        return reason_.c_str();
    }

    inline int Exception::code() const noexcept {
        return code_;
    }


    inline NoError::NoError( std::string reason ) noexcept
    : Exception(ErrorCode::NO_ERROR, std::move(reason)) {}

    inline Exception* NoError::create( std::string reason ) noexcept {
        return new NoError(std::move(reason));
    }


    inline NotInitialized::NotInitialized( std::string reason ) noexcept
    : Exception(ErrorCode::NOT_INITIALIZED, std::move(reason)) {}

    inline Exception* NotInitialized::create( std::string reason ) noexcept {
        return new NotInitialized(std::move(reason));
    }


    inline NoCurrentContext::NoCurrentContext( std::string reason ) noexcept
    : Exception( ErrorCode::NO_CURRENT_CONTEXT, std::move(reason) ) {}

    inline Exception* NoCurrentContext::create( std::string reason ) noexcept {
        return new NoCurrentContext(std::move(reason));
    }


    inline InvalidEnum::InvalidEnum( std::string reason ) noexcept
    : Exception( ErrorCode::INVALID_ENUM, std::move(reason) ) {}

    inline Exception* InvalidEnum::create( std::string reason ) noexcept {
        return new InvalidEnum(std::move(reason));
    }


    inline InvalidValue::InvalidValue( std::string reason ) noexcept
    : Exception(ErrorCode::INVALID_VALUE, std::move(reason) ) {}

    inline Exception* InvalidValue::create( std::string reason ) noexcept {
        return new InvalidValue(std::move(reason));
    }


    inline OutOfMemory::OutOfMemory( std::string reason ) noexcept
    : Exception(ErrorCode::OUT_OF_MEMORY, std::move(reason)) {}

    inline Exception* OutOfMemory::create( std::string reason ) noexcept {
        return new OutOfMemory(std::move(reason));
    }


    inline ApiUnavailable::ApiUnavailable( std::string reason ) noexcept
    : Exception(ErrorCode::API_UNAVAILABLE, std::move(reason)) {}

    inline Exception* ApiUnavailable::create( std::string reason ) noexcept {
        return new ApiUnavailable(std::move(reason));
    }


    inline VersionUnavailable::VersionUnavailable( std::string reason ) noexcept
    : Exception(ErrorCode::VERSION_UNAVAILABLE, std::move(reason)) {}

    inline Exception* VersionUnavailable::create( std::string reason ) noexcept {
        return new VersionUnavailable(std::move(reason));
    }


    inline FormatUnavailable::FormatUnavailable( std::string reason ) noexcept
    : Exception(ErrorCode::FORMAT_UNAVAILABLE, std::move(reason)) {}

    inline Exception* FormatUnavailable::create( std::string reason ) noexcept {
        return new FormatUnavailable(std::move(reason));
    }


    inline PlatformError::PlatformError( std::string reason ) noexcept
    : Exception(ErrorCode::PLATFORM_ERROR, std::move(reason)) {}

    inline Exception* PlatformError::create( std::string reason ) noexcept {
        return new PlatformError(std::move(reason));
    }


    inline NoWindowContext::NoWindowContext( std::string reason ) noexcept
    : Exception(ErrorCode::NO_WINDOW_CONTEXT, std::move(reason)) {}

    inline Exception* NoWindowContext::create( std::string reason ) noexcept {
        return new NoWindowContext(std::move(reason));
    }

}


namespace gl_engine::utility {
    /**
     * @brief Convertie un gl_engine::glfw::ErrorCode en std::string.
     * @param [in]code Le code d’erreur.
     * @return std::string
     *
     * @exceptsafe NO-THROWS.
     *
     * @version 1.0
     * @since 0.1
     *
     * @see gl_engine::glfw::ErrorCode
     */
    inline std::string to_string( gl_engine::glfw::ErrorCode code ) noexcept {
        return code.to_string();
    }
}


namespace std {
    /**
     * @brief Surcharge de la fonction hash pour le type gl_engine::glfw::ErrorCode
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see [cppreference-hash](https://en.cppreference.com/w/cpp/utility/hash/operator())
     * @see [cppreference-extending_std](https://en.cppreference.com/w/cpp/language/extending_std)
     */
    template <>
    struct hash<gl_engine::glfw::ErrorCode> {
        size_t operator()(const gl_engine::glfw::ErrorCode& code ) const {
            std::hash<int> hasher;
            return hasher(gl_engine::glfw::interface::Hash_ErrorCode::code(code));
        }
    };
}



#endif // GLENGINE_GLFW_EXCEPTION_HPP
