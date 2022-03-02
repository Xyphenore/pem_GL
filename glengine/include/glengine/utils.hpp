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

#ifndef GLENGINE_UTILS_HPP
#define GLENGINE_UTILS_HPP

#include <GLFW/glfw3.h>

#include <stdexcept>

// TODO Factoriser le code avec le fichier utility
// Créer un fichier exception

namespace gl_engine {
    using GLFWErrorCode = int;

    // Exceptions
    using app_already_exists = std::logic_error;

    using appWindow_already_exists = std::logic_error;

    using GLFW_initialisation_failed = std::runtime_error;

    using GLFWException = std::runtime_error;

    using GLFWUnknownException = std::runtime_error;


    /**
     * @brief Retourne une chaine de caractère représentant le nom du code d'erreur GLFW passé.
     * @param code[in] Le code d'erreur voulant être convertit en chaine de caractère.
     * @return Une chaine de caractère.
     * @throws bidon::GLFWUnknownException Lancée si le code d'erreur est inconnu.
     * @throws std::bad_alloc Lancée si le conteneur interne ne peut pas être alloué.
     * @exceptsafe Forte. Ne modifie aucunes données.
     * @cite https://www.glfw.org/docs/3.3/group__errors.html#gad44162d78100ea5e87cdd38426b8c7a1
     */
    std::string getCodeName( GLFWErrorCode code );

    /**
     * @brief Fonctionne appelée à chaque erreur de GLFW. Cette fonction lance une exception pour chaque erreur.
     * @param code[in] Le code d'erreur GLFW.
     * @param description[in] La description du message d'erreur.
     * @throws std::bad_allox Lancée si l'allocation du message rate.
     * @throws bidon::GLFWException Lancée à chaque appel de la fonction.
     * @exceptsafe Forte. Ne modifie aucunes données.
     * @cite https://www.glfw.org/docs/3.3/intro_guide.html#error_handling
     */
    void GLFWErrorCallback( GLFWErrorCode code, const char* description );

    class Dimension {
    public:
        GLsizei width;
        GLsizei height;

        Dimension( const Dimension& ) = default;
        Dimension( Dimension&& ) noexcept = default;
        ~Dimension() noexcept = default;
        Dimension& operator=( const Dimension& ) = default;
        Dimension& operator=( Dimension&& ) noexcept = default;
    };

}

inline void gl_engine::GLFWErrorCallback( const gl_engine::GLFWErrorCode code, const char* const description ) {
    if ( GLFW_NO_ERROR != code ) {
        throw gl_engine::GLFWException( "Erreur GLFW : " + gl_engine::getCodeName( code ) + description );
    }
}


#endif //GLENGINE_UTILS_HPP
