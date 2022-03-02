#ifndef GLENGINE_UTILS_HPP
#define GLENGINE_UTILS_HPP

#include <GLFW/glfw3.h>

#include <stdexcept>

namespace bidon {
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

    struct Dimension {
        GLsizei width;
        GLsizei height;
    };

}

inline void bidon::GLFWErrorCallback( const bidon::GLFWErrorCode code, const char* const description ) {
    if ( GLFW_NO_ERROR != code ) {
        throw bidon::GLFWException( "Erreur GLFW : " + bidon::getCodeName( code ) + description );
    }
}


#endif //GLENGINE_UTILS_HPP
