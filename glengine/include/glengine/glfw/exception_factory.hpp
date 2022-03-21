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

#ifndef GLENGINE_GLFW_EXCEPTION_FACTORY_HPP
#define GLENGINE_GLFW_EXCEPTION_FACTORY_HPP

#ifndef __cplusplus
#error Un compilateur C++ est nécessaire.
#endif

#if __cplusplus < 201703L
#error GL_Engine a été développée pour C++17. Veuillez supprimer cette condition est testé le code à vos risques et périls.
#endif

#include <string>
#include <glengine/glfw/exception.hpp>


namespace gl_engine::glfw {
    /**
     * @brief Usine permettant de créer la bonne gl_engine::glfw::Exception en fonction du code d’erreur fourni.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::glfw::Exception
     * @see gl_engine::glfw::ErrorCode
     * @see [GLFW-Error_Code](https://www.glfw.org/docs/3.3/group__errors.html)
     */
    class ExceptionFactory final {
    public:
        // Note développeur : C’est la même usine de création pour les GLFW::Exception, il est donc impossible de l’instancier.

        ExceptionFactory() noexcept = delete;
        ExceptionFactory( const ExceptionFactory& ) noexcept = delete;
        ExceptionFactory( ExceptionFactory&& ) noexcept = delete;
        ExceptionFactory& operator=( const ExceptionFactory& ) noexcept = delete;
        ExceptionFactory& operator=( ExceptionFactory&& ) noexcept = delete;
        ~ExceptionFactory() noexcept = delete;

        /**
         * @brief Crée une exception en fonction du code d’erreur fourni, et da la raison d’erreur.
         * @param code Un objet gl_engine::glfw::ErrorCode.
         * @param reason Une chaine de caractère.
         * @return gl_engine::glfw::Exception
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::glfw::Exception
         * @see gl_engine::glfw::ErrorCode
         */
        static Exception* createException( ErrorCode code, std::string reason ) noexcept {
            return interface::Factory_ListErrorCode::getBuilder(code)(std::move(reason));
        }
    };
}

#endif // GLENGINE_GLFW_EXCEPTION_FACTORY_HPP
