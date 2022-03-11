/*
 * PEM_GL - Copyright © 2022-2022 DAVID Axel
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

/*
 * Bidon_OpenGL - Copyright © 2022 DAVID Axel, GOI Suzy
 * Mail to:
 * axel.david@etu.univ-amu.fr
 * muriel.coet@etu.univ-amu.fr
 *
 * Bidon_OpenGL is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Bidon_OpenGL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GLENGINE_UTILITY_HPP
#define GLENGINE_UTILITY_HPP

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <type_traits>
#include <string>
#include <string_view>
#include <istream>
#include <filesystem>

// region Types
namespace gl_engine {
    /**
     * @brief Alias pour le type des identifiants générés par OpenGL
     */
    using Id = GLuint;

    using Size = GLsizei;

    using Length = GLint;
}
// endregion

namespace gl_engine::utility {
    // Déclaration de la class Path nécessaire pour la classe Content
    class Path;

    /**
     * @brief Type fort représentant le contenu, d’un flux d’entrée, d’un fichier ou d’une chaine de caractère.
     * @see gl_engine::Shader
     * @see gl_engine::utility::Path
     */
    class Content {
    public:
        /**
         * @brief Copie le contenu d’une std::string dans l’objet Content construit
         * @param source Le contenu
         * @pre La source ne doit pas être vide.
         * @throws std::invalid_argument Lancée si la std::string fournie est vide.
         * @post Le contenu de Content est identique à la std::string.
         * @throws std::bad_alloc Lancée si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit Content( std::string source );

        /**
         * @brief Copie le contenu d’une chaine de caractère const char* dans l’objet Content construit
         * @param source Le pointeur vers le contenu
         * @pre La source ne doit pas être vide.
         * @throws std::invalid_argument Lancée si la chaine de caractère fournie est vide.
         * @post Le contenu de Content est identique à la chaine de caractère.
         * @pre Le pointeur ne doit pas être nullptr
         * @throws std::logic_error Lancée si le pointeur est égale à nullptr.
         * @post Le pointeur fourni est toujours valide après cette fonction.
         * @throws std::bad_alloc Lancée si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit Content( const char* source );

        /**
         * @brief Copie le contenu d’une std::string_view dans l’objet Content construit
         * @param source La vue sur le contenu
         * @pre La source ne doit pas être vide.
         * @throws std::invalid_argument Lancée si la source fournie est vide.
         * @post Le contenu de Content est identique à la vue.
         * @throws std::bad_alloc Lancée si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit Content( std::string_view source );

        /**
         * @brief Copie le contenu du flux d’entrée dans l’objet Content construit
         * @param stream Le flux d’entrée vers le contenu
         * @pre Le stream doit être bien formé.
         * @throws std::ios_base::failure Lancée si une opération précédente cette méthode, a défini std::ios_base::badbit ou std::ios_base::failbit à 1.
         * @throws std::ios_base::failure Lancée si une erreur arrive durant la lecture du flux fourni.
         * @pre Le contenu du stream ne doit pas être vide.
         * @throws std::invalid_argument Lancée si le contenu du stream est vide.
         * @post Le contenu de Content est identique au contenu se trouvant dans stream.
         * @throws std::bad_alloc Lancée si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Seulement si c’est une mauvaise allocation arrive.
         * @exceptsafe BASE. Le flux est dans un état valide si std::ios_base::failbit est à 1.
         * @exceptsafe AUCUNE. Le flux est irrécupérable si std::ios_base::badbit est à 1.
         */
        explicit Content( std::istream& stream );

        /**
         * @brief Copie le contenu du fichier pointé par path dans l’objet Content construit
         * @param path Le chemin vers le code source
         * @pre L'objet Path doit contenir un chemin valide.
         * @throws std::ios_base::failure Lancée s’il est impossible d’ouvrir le fichier pointé par path.
         * @throws std::ios_base::failure Lancée si la fermeture du fichier échoue (le fichier est quand même libéré).
         * @throws std::ios_base::failure Lancée si une erreur arrive durant la lecture du fichier.
         * @pre Le code source ne doit pas être vide.
         * @throws std::invalid_argument Lancée si le contenu du fichier est vide.
         * @post Le contenu de Content est identique au contenu du fichier.
         * @throws std::bad_alloc Lancée si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         * @see gl_engine::utility::Path
         */
        explicit Content( Path path );

        /**
         * @brief Retourne une copie du contenu de l’objet Content sous forme de chaine de caractère std::string.
         * @return Une chaine de caractère.
         * @exceptsafe FORT. Ne lance aucune exception.
         */
        [[nodiscard]] std::string getContent() const noexcept;

        /**
         * @brief Retourne le type de la source. Dans le cas d’un path, cela retourne aussi le chemin du fichier contenant le code source.
         * @return Une chaine de caractère
         * @exceptsafe FORT. Ne lance aucune exception.
         */
        [[nodiscard]] std::string getType() const noexcept;

    private:
        // Dans le cas d’un besoin d’optimisation de taille utilisé, et que getContent est très peu utilisé
        // Ou bien la std::string est directement converti en const char* directement après l’appel
        // Stocker un const char*(propriétaire) et retourner un std::unique_ptr<char> serait une solution
        std::string content_;

        std::string sourceType_;

        /**
         * @brief Récupère le contenu du flux fourni
         * @param stream Flux d’entrée
         * @return Une chaine de caractère correspondant au contenu du flux
         * @pre Le stream fourni doit être bien formé.
         * @throws std::ios_base::failure Lancée si une opération précédente cette méthode, a défini std::ios_base::badbit ou std::ios_base::failbit à 1.
         * @throws std::ios_base::failure Lancée si une erreur arrive durant la lecture du flux fourni.
         * @post La chaine de caractère retournée contient le contenu du stream fourni.
         * @throws std::bad_alloc Lancée si la std::string n’arrive pas à être allouée.
         * @exceptsafe FORT. Seulement si c’est une mauvaise allocation de la string.
         * @exceptsafe BASE. Le flux est dans un état valide si std::ios_base::failbit est à 1.
         * @exceptsafe AUCUNE. Le flux est irrécupérable si std::ios_base::badbit est à 1.
         */
        static std::string getContentFrom( std::istream& stream );

        // TODO Peut être utiliser une fonction statique au lieu d'un constructeur pour l'initialisation
        /**
         * @brief Copie le contenu d’une std::string dans l’objet Content construit
         * @param source Le contenu
         * @param sourceType Le type de la source
         * @pre La source ne doit pas être vide.
         * @throws std::invalid_argument Lancée si la std::string fournie est vide.
         * @post Le contenu de Content est identique à la std::string.
         * @pre sourceType ne doit pas être vide
         * @throws std::logic_error Lancée si sourceType est vide.
         * @post Le type de la source est identique au type fourni.
         * @throws std::bad_alloc Lancée si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit Content( std::string source, std::string sourceType );
    };

    // TODO Vérifier les permissions de lecture des fichiers fournis
    /**
     * @brief Type fort représentant un chemin valide vers un fichier régulier.
     * @see gl_engine::utility::Content
     * @see gl_engine::Shader
     */
    class Path {
    public:
        /**
         * @brief Construit un objet Path à partir du chemin fourni dans la std::string.
         * @param path Le chemin vers un fichier régulier
         * @pre Le chemin fourni doit exister.
         * @throws std::invalid_argument Lancée si le chemin fourni n’existe pas.
         * @pre Le fichier contenant le code source doit être un fichier régulier
         * @throws std::invalid_argument Lancée si le fichier pointé par le path n’est pas régulier.
         * @post Le chemin contenu est un chemin valide vers un fichier régulier.
         * @throws std::bad_alloc Si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Aucune donnée modifiée
         */
        explicit Path( std::string path );

        /**
         * @brief Construit un objet Path à partir du chemin fourni dans la std::string_view.
         * @param path Le chemin vers un fichier régulier
         * @pre Le chemin fourni doit exister.
         * @throws std::invalid_argument Lancée si le chemin fourni n’existe pas.
         * @pre Le fichier contenant le code source doit être un fichier régulier
         * @throws std::invalid_argument Lancée si le fichier pointé par le path n’est pas régulier.
         * @post Le chemin contenu est un chemin valide vers un fichier régulier.
         * @throws std::bad_alloc Si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Aucune donnée modifiée
         */
        explicit Path( std::string_view path );

        /**
         * @brief Construit un objet Path à partir du chemin fourni dans la chaine de caractère const char*.
         * @param path Le chemin vers un fichier régulier
         * @pre Le chemin fourni doit exister.
         * @throws std::invalid_argument Lancée si le chemin fourni n’existe pas.
         * @pre Le fichier contenant le code source doit être un fichier régulier
         * @throws std::invalid_argument Lancée si le fichier pointé par le path n’est pas régulier.
         * @post Le chemin contenu est un chemin valide vers un fichier régulier.
         * @pre Le pointeur ne doit pas être null.
         * @throws std::logic_error Lancée si le pointeur fourni est égale à nullptr.
         * @post Le pointeur fourni est toujours valide après l’exécution de la méthode.
         * @throws std::bad_alloc Si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Aucune donnée modifiée
         */
        explicit Path( const char* path );

        /**
         * @brief Construit un objet Path à partir du chemin fourni dans le std::filesystem::path.
         * @param path Le chemin vers un fichier régulier
         * @pre Le chemin fourni doit exister.
         * @throws std::invalid_argument Lancée si le chemin fourni n’existe pas.
         * @pre Le fichier contenant le code source doit être un fichier régulier
         * @throws std::invalid_argument Lancée si le fichier pointé par le path n’est pas régulier.
         * @post Le chemin contenu est un chemin valide vers un fichier régulier.
         * @throws std::bad_alloc Si l’objet ne peut pas être alloué.
         * @exceptsafe FORT. Aucune donnée modifiée
         */
        explicit Path( std::filesystem::path path );

        /**
         * @brief Méthode amie de la classe gl_engine::utility::Content, pouvant accéder au contenu de Path
         */
        friend gl_engine::utility::Content::Content( Path path );

    private:
        // Dans le cas que seul la classe Content utilise Path, stocké un pointeur vers un const char*
        // peut être une optimisation de taille, si cela est nécessaire.
        // Car le constructeur de std::ifstream prenant un filesystem::path, sera appelé comme :
        // ifstream( path.string().c_str() )
        // Ainsi si un pointeur vers un const char est seulement nécessaire pourquoi ne pas le stocker directement.
        // https://en.cppreference.com/w/cpp/io/basic_ifstream/basic_ifstream
        std::filesystem::path path_;
    };




    /**
     * @brief Implémentation de la méthode std::to_underlying de C++23. Convertie une valeur d’une énumération en son type sous jasant.
     * @tparam Enum Type de l’énumération à convertir
     * @param value La valeur à convertir
     * @return La valeur convertie dans le type sous jasant.
     * @exceptsafe FORT. Ne lance aucune exception.
     * @cite https://en.cppreference.com/w/cpp/utility/to_underlying
     */
    template<class Enum>
    constexpr std::underlying_type_t<Enum> to_underlying( Enum value ) noexcept;

    /**
     * @brief Convertie la valeur d’une macro définis dans le fichier glad.h, en son nom.
     * @param macro La valeur de la macro dont on veut obtenir le nom
     * @return Retourne le nom de la macro sous forme de std::string.
     * @throws std::invalid_argument Lancée si la macro fournie n'est pas valide.
     * @exceptsafe FORT. Ne modifie aucune donnée.
     * @note Plusieurs macros ont la même valeur ainsi, la chaine de caractère retournée peut avoir plusieurs noms, exemple : "GL_ALL_ATTRIB_BITS/GL_CLIENT_ALL_ATTRIB_BITS".
     * @note Cette fonction ne gère que les macros définies dans le fichier glad.h, s’il y a un changement dans le système cette fonction peut ne pas fonctionner.
     */
    std::string to_string( GLenum macro );


}

// region Export
// Exportation des noms des utilities dans l’espace de nom gl_engine
namespace gl_engine {
    using Content = gl_engine::utility::Content;
    using Path = gl_engine::utility::Path;
}
// endregion

namespace gl_engine::open_gl {
    // region Shader
    /**
    * @brief Surcharge de la macro glCreateShader acceptant GLenum
    * @param type Type du shader voulant être créée.
    */
    Id createShader( GLenum type );

    /**
    * @brief Surcharge de la macro glShaderSource
    */
    void shaderSource( Id id, Size count, const GLchar** string, const Length* length );

    /**
    * @brief Surcharge de la macro glShaderSource prenant seulement l’id du shader et une seule std::string représentant le code source.
    * @param id Identifiant valide du shader
    * @param source Une std::string qui est une chaine de caractère du code source
    * @pre id doit être un identifiant valide pour un shader
    * @pre source doit contenir seulement un seul code source valide pour le shader
    */
    void shaderSource( Id id, std::string source );

    /**
    * @brief Surcharge de la macro glShaderSource prenant seulement l’id du shader et un code source contenus dans un type Content
    * @param id Identifiant valide du shader
    * @param source Un objet utility::Content qui est le code source
    * @pre id doit être un identifiant valide pour un shader
    * @pre source doit contenir seulement un seul code source valide pour le shader
    */
    void shaderSource( Id id, Content source );

    /**
    * @brief Surcharge de la macro glCompileShader
    * @param id Id du shader à compiler
    */
    void compileShader( Id id );

    /**
    * @brief Surcharge de la macro glDeleteShader
    * @param id Identifiant du shader à supprimer
    */
    void deleteShader( Id id );
    // endregion

    // region ShaderProgram
    // TODO Documenter cette zone
    /**
     * @brief Surcharge de la macro glCreateProgram
     * @return
     */
    Id createProgram();

    /**
     * @brief Surcharge de la macro glUseProgram
     * @param id
     */
    void useProgram( Id id );

    /**
     * @brief Surcharge de la macro glDeleteProgram
     * @param id_
     */
    void deleteProgram( Id id );

    /**
     * @brief Surchage de la macro glDetachShader
     * @param idProgram
     * @param idShader
     */
    void detachShader( Id idProgram, Id idShader );

    /**
     * @brief Surcharge de la macro glAttachShader
     * @param idProgram
     * @param idShader
     */
    void attachShader( Id idProgram, Id idShader );

    /**
     * @brief Surcharge de la macro glLinkProgram
     * @param id
     */
    void linkProgram( Id id );

    Id getUniformLocation( Id idProgram, std::string name );

    template <typename T>
    void setUniform( Id id, T value );
    //endregion

    class Uniform {
        // TODO Class pour les types d'Uniform
        // https://stackoverflow.com/questions/33690186/opengl-bool-uniform

    };
}

namespace gl_engine {
    using GLFWErrorCode = int;

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

        Dimension() = default;
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




#endif // GLENGINE_UTILITY_HPP
