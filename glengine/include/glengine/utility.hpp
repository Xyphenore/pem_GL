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

#ifndef GLENGINE_UTILITY_HPP
#define GLENGINE_UTILITY_HPP

#include <GLFW/glfw3.h>

#include <stdexcept>
#include <type_traits>
#include <string>
#include <string_view>
#include <istream>
#include <filesystem>

#include <glengine/exception.hpp>


#include <stbimage/stb_image.h>


namespace gl_engine {
    /**
     * @brief Alias pour le type des identifiants générés par OpenGL
     */
    using Id = GLuint;

    using Size = GLsizei;

    using Length = GLint;
}

/**
 * @brief Espace de noms contenant tous les objets utilitaires.
 *
 * @version 1.0
 * @since 0.1
 * @author Axel DAVID
 */
namespace gl_engine::utility {
    /**
    * @brief Exception indiquant que la source fournie est vide.
    *
    * @version 1.0
    * @since 0.1
    * @author Axel DAVID
    *
    * @see gl_engine::utility::Content
    */
    class EmptySource final : public InvalidArgument {
    public:
        /**
         * @brief Crée l’exception à partir d’une std::string contenant le type de la source. Le message d’erreur a été prédéfini.
         * @param sourceType Le type de la source qui est vide.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::utility::Content
         */
        explicit EmptySource( const std::string& sourceType ) noexcept
        : InvalidArgument("Type de source : " + sourceType + '\n' + "La source est vide.") {}

        /**
         * @overload
         * @brief Surcharge permettant de créer une exception à partir d’un pointeur vers la chaine de caractère contenant le type de la source.
         * @param sourceType Le type de la source.
         */
        explicit EmptySource(const char* sourceType) noexcept
                : EmptySource(std::string(sourceType)) {}

        EmptySource() noexcept = delete;
        EmptySource( const EmptySource& other ) noexcept = default;
        EmptySource( EmptySource&& other ) noexcept = default;
        EmptySource& operator=( const EmptySource& other ) noexcept = default;
        EmptySource& operator=( EmptySource&& other ) noexcept = default;
        ~EmptySource() noexcept override = default;
    };

    /**
    * @brief Exception lancée s’il est impossible d’ouvrir un fichier.
    *
    * @version 1.0
    * @since 0.1
    * @author Axel DAVID
    *
    * @see gl_engine::utility::Path
    */
    class ErrorOpeningFile final : public IOException {
    public:
        /**
         * @brief Crée une exception d’ouverture de fichier avec l’adresse du fichier passée en paramètre.
         * @param fileUrl L’adresse du fichier ne pouvant pas être ouvert.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::utility::Path
         */
        explicit ErrorOpeningFile( const std::string& fileUrl ) noexcept
        : IOException("Erreur durant l’ouverture du fichier : " + fileUrl) {}

        /**
         * @overload
         * @brief Surcharge prenant l’adresse du fichier sous forme de pointeur vers chaine de caractère.
         * @param fileUrl Le pointeur vers la chaine de caractère.
         */
        explicit ErrorOpeningFile( const char* fileUrl ) noexcept
        : ErrorOpeningFile(std::string{fileUrl}) {}

        ErrorOpeningFile() noexcept = delete;
        ErrorOpeningFile( const ErrorOpeningFile& ) noexcept = default;
        ErrorOpeningFile( ErrorOpeningFile&& ) noexcept = default;
        ErrorOpeningFile& operator=( const ErrorOpeningFile& ) noexcept = default;
        ErrorOpeningFile& operator=( ErrorOpeningFile&& ) noexcept = default;
        ~ErrorOpeningFile() noexcept override = default;
    };

    /**
     * @brief Exception lancée si une erreur survient durant la lecture d’un fichier.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::utility::Path
     */
    class ErrorReadingFile final : public IOException {
    public:
        /**
         * @brief Crée une exception indiquant une erreur de lecture du fichier avec l’adresse du fichier passée en paramètre.
         * @param fileUrl L’adresse du fichier dont l’erreur de lecture est survenue.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::utility::Path
         */
        explicit ErrorReadingFile( const std::string& fileUrl ) noexcept
        : IOException("Erreur durant la lecture du contenu du fichier : " + fileUrl) {}

        /**
         * @overload
         * @brief Surcharge prenant l’adresse du fichier sous forme de pointeur vers chaine de caractère.
         * @param fileUrl Le pointeur vers la chaine de caractère.
         */
        explicit ErrorReadingFile( const char* fileUrl ) noexcept
        : ErrorReadingFile(std::string{fileUrl}) {}

        ErrorReadingFile() noexcept = delete;
        ErrorReadingFile( const ErrorReadingFile& ) noexcept = default;
        ErrorReadingFile( ErrorReadingFile&& ) noexcept = default;
        ErrorReadingFile& operator=( const ErrorReadingFile& ) noexcept = default;
        ErrorReadingFile& operator=( ErrorReadingFile&& ) noexcept = default;
        ~ErrorReadingFile() noexcept override = default;
    };

    /**
     * @brief Exception lancée si une erreur survient durant la fermeture d’un fichier.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::utility::Path
     */
    class ErrorClosingFile final : public IOException {
    public:
        /**
         * @brief Crée une exception indiquant une erreur durant la fermeture du fichier avec l’adresse du fichier passée en paramètre.
         * @param fileUrl L’adresse du fichier ne pouvant pas être ouvert.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::utility::Path
         */
        explicit ErrorClosingFile( const std::string& fileUrl ) noexcept
        : IOException("Erreur durant la fermeture du fichier : " + fileUrl) {}

        /**
         * @overload
         * @brief Surcharge prenant l’adresse du fichier sous forme de pointeur vers chaine de caractère.
         * @param fileUrl Le pointeur vers la chaine de caractère.
         */
        explicit ErrorClosingFile( const char* fileUrl ) noexcept
        : ErrorClosingFile(std::string{fileUrl}) {}

        ErrorClosingFile() noexcept = delete;
        ErrorClosingFile( const ErrorClosingFile& ) noexcept = default;
        ErrorClosingFile( ErrorClosingFile&& ) noexcept = default;
        ErrorClosingFile& operator=( const ErrorClosingFile& ) noexcept = default;
        ErrorClosingFile& operator=( ErrorClosingFile&& ) noexcept = default;
        ~ErrorClosingFile() noexcept override = default;
    };

    /**
     * @brief Exception lancée lorsqu’une erreur survient durant l’ouverture d’un flux.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     */
    class ErrorOpeningStream final : public IOException {
    public:
        /**
         * @brief Crée une exception d’ouverture de flux avec le nom du flux en paramètre.
         * @param fluxName L’e nom du flux.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         */
        explicit ErrorOpeningStream( const std::string& fluxName ) noexcept
        : IOException("Erreur durant l’ouverture du flux : " + fluxName) {}

        /**
         * @overload
         * @brief Surcharge prenant le nom du flux sous forme de pointeur vers chaine de caractère.
         * @param fluxName Le pointeur vers la chaine de caractère.
         */
        explicit ErrorOpeningStream( const char* fluxName ) noexcept
        : ErrorOpeningStream(std::string{fluxName}) {}

        ErrorOpeningStream() noexcept = delete;
        ErrorOpeningStream( const ErrorOpeningStream& ) noexcept = default;
        ErrorOpeningStream( ErrorOpeningStream&& ) noexcept = default;
        ErrorOpeningStream& operator=( const ErrorOpeningStream& ) noexcept = default;
        ErrorOpeningStream& operator=( ErrorOpeningStream&& ) noexcept = default;
        ~ErrorOpeningStream() noexcept override = default;
    };

    /**
     * @brief Exception lancée lorsqu’une erreur survient durant la lecture du flux.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     */
    class ErrorReadingStream final : public IOException {
    public:
        /**
         * @brief Crée une exception de lecture de flux, avec le nom du flux.
         * @param streamName Le nom du flux.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         */
        explicit ErrorReadingStream( const std::string& streamName ) noexcept
        : IOException("Erreur durant la lecture d'un flus : " + streamName) {}

        /**
         * @overload
         * @brief Surcharge prenant le nom du flux sous forme de pointeur vers chaine de caractère.
         * @param streamName Le pointeur vers la chaine de caractère.
         */
        explicit ErrorReadingStream( const char* streamName ) noexcept
        : ErrorReadingStream(std::string{streamName}) {}

        ErrorReadingStream() noexcept = delete;
        ErrorReadingStream( const ErrorReadingStream& ) noexcept = default;
        ErrorReadingStream( ErrorReadingStream&& ) noexcept = default;
        ErrorReadingStream& operator=( const ErrorReadingStream& ) noexcept = default;
        ErrorReadingStream& operator=( ErrorReadingStream&& ) noexcept = default;
        ~ErrorReadingStream() noexcept override = default;
    };

    /**
     * @brief Exception indiquant que le chemin passé est inconnu.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::utility::Path
     */
    class UnknownPath final : public InvalidArgument {
    public:
        /**
         * @brief Crée l’exception à partir d’une std::string contenant le chemin incriminé.
         * @param urlPath Le chemin incriminé.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::utility::Path
         */
        explicit UnknownPath( const std::string& urlPath ) noexcept
        : InvalidArgument("Le chemin : " + urlPath + " est inconnu.") {}

        /**
         * @overload
         * @brief Surcharge permettant de créer une exception à partir d’un pointeur vers la chaine de caractère contenant le type de la source.
         * @param urlPath Le chemin incriminé.
         */
        explicit UnknownPath(const char* urlPath) noexcept
        : UnknownPath(std::string(urlPath)) {}

        UnknownPath() noexcept = delete;
        UnknownPath( const UnknownPath& other ) noexcept = default;
        UnknownPath( UnknownPath&& other ) noexcept = default;
        UnknownPath& operator=( const UnknownPath& other ) noexcept = default;
        UnknownPath& operator=( UnknownPath&& other ) noexcept = default;
        ~UnknownPath() noexcept override = default;
    };

    /**
     * @brief Exception indiquant que le chemin passé pointe vers un fichier non régulier.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::utility::Path
     */
    class NotRegularFile final : public InvalidArgument {
    public:
        /**
         * @brief Crée l’exception à partir d’une std::string contenant le chemin incriminé.
         * @param urlPath Le chemin incriminé.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         *
         * @see gl_engine::utility::Path
         */
        explicit NotRegularFile( const std::string& urlPath ) noexcept
        : InvalidArgument("Le chemin : " + urlPath + " pointe vers un fichier non régulier.") {}

        /**
         * @overload
         * @brief Surcharge permettant de créer une exception à partir d’un pointeur vers la chaine de caractère contenant le type de la source.
         * @param urlPath Le chemin incriminé.
         */
        explicit NotRegularFile(const char* urlPath) noexcept
        : NotRegularFile(std::string(urlPath)) {}

        NotRegularFile() noexcept = delete;
        NotRegularFile( const NotRegularFile& other ) noexcept = default;
        NotRegularFile( NotRegularFile&& other ) noexcept = default;
        NotRegularFile& operator=( const NotRegularFile& other ) noexcept = default;
        NotRegularFile& operator=( NotRegularFile&& other ) noexcept = default;
        ~NotRegularFile() noexcept override = default;
    };


    /**
     * @brief Exception générique lancée si une erreur de la bibliothèque STB survient.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::utility::Image
     */
    class STBException final : public Exception {
    public:
        /**
         * @brief Crée une exception à partir de la raison fournie.
         * @param what_arg La raison sous forme de chaine de caractère.
         *
         * @exceptsafe NO-THROW.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         */
        STBException( const std::string& what_arg ) noexcept
        : Exception(what_arg) {}

        /**
         * @overload
         * @brief Surcharge prenant en paramètre la raison sous forme de pointeur vers chaine de caractère.
         * @param what_arg Le pointeur.
         */
        STBException( const char* what_arg ) noexcept
        : STBException(std::string{what_arg}) {}

        STBException() noexcept = delete;
        STBException( const STBException& other ) noexcept = default;
        STBException( STBException&& other ) noexcept = default;
        STBException& operator=( const STBException& other ) noexcept = default;
        STBException& operator=( STBException&& other ) noexcept = default;
        ~STBException() noexcept override = default;
    };



    // Amitié : Déclaration de la class Path nécessaire pour la classe Content.

    class Path;

    /**
     * @brief Type fort représentant le contenu, d’un flux d’entrée, d’un fichier ou d’une chaine de caractère.
     *
     * @version 1.0
     * @since 0.1
     * @author Axel DAVID
     *
     * @see gl_engine::Shader
     * @see gl_engine::utility::Path
     */
    class Content final {
    public:
        /**
         * @brief Copie le contenu d’une std::string dans l’objet Content construit
         *
         * @param source Le contenu
         * @pre La source ne doit pas être vide.
         * @throws gl_engine::utility::EmptySource Lancée si la std::string fournie est vide.
         * @post Le contenu de Content est identique à la std::string.
         *
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit Content( std::string source );

        /**
         * @brief Copie le contenu d’une chaine de caractère const char* dans l’objet Content construit.
         *
         * @param source Le pointeur vers le contenu
         * @pre La source ne doit pas être vide.
         * @throws gl_engine::utility::EmptySource Lancée si la chaine de caractère fournie est vide.
         * @post Le contenu de Content est identique à la chaine de caractère.
         *
         * @pre Le pointeur ne doit pas être nullptr
         * @throws std::logic_error Lancée si le pointeur est égale à nullptr.
         * @post Le pointeur fourni est toujours valide après cette fonction.
         *
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit Content( const char* source );

        /**
         * @brief Copie le contenu d’une std::string_view dans l’objet Content construit.
         *
         * @param source La vue sur le contenu
         * @pre La source ne doit pas être vide.
         * @throws gl_engine::utility::EmptySource Lancée si la source fournie est vide.
         * @post Le contenu de Content est identique à la vue.
         *
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit Content( std::string_view source );

        /**
         * @brief Copie le contenu du flux d’entrée dans l’objet Content construit.
         *
         * @param stream Le flux d’entrée vers le contenu
         * @pre Le stream doit être bien formé.
         * @throws std::ios_base::failure Lancée si une opération précédente cette méthode, a défini std::ios_base::badbit ou std::ios_base::failbit à 1.
         * @throws std::ios_base::failure Lancée si une erreur arrive durant la lecture du flux fourni.
         *
         * @pre Le contenu du stream ne doit pas être vide.
         * @throws gl_engine::utility::EmptySource Lancée si le contenu du stream est vide.
         * @post Le contenu de Content est identique au contenu se trouvant dans stream.
         *
         * @exceptsafe FORT. Seulement si c’est une mauvaise allocation arrive.
         * @exceptsafe BASE. Le flux est dans un état valide si std::ios_base::failbit est à 1.
         * @exceptsafe AUCUNE. Le flux est irrécupérable si std::ios_base::badbit est à 1.
         */
        explicit Content( std::istream& stream );

        /**
         * @brief Copie le contenu du fichier pointé par path dans l’objet Content construit.
         * @param path Le chemin vers le code source
         *
         * @pre Le code source ne doit pas être vide.
         * @throws gl_engine::utility::EmptySource Lancée si le contenu du fichier est vide.
         * @post Le contenu de Content est identique au contenu du fichier.
         *
         * @exceptsafe FORT. Ne modifie aucune donnée.
         *
         * @see gl_engine::utility::Path
         */
        explicit Content( const Path& path );

        /**
         * @brief Retourne une copie du contenu de l’objet Content sous forme de chaine de caractère std::string.
         * @return Une chaine de caractère.
         *
         * @exceptsafe NO-THROWS.
         *
         * @version 1.0
         * @since 0.1
         */
        [[nodiscard]] std::string content() const noexcept;

        /**
         * @brief Retourne le type de la source. Dans le cas d’un path, cela retourne aussi le chemin du fichier contenant le code source.
         * @return Une chaine de caractère
         *
         * @exceptsafe NO-THROWS.
         */
        [[nodiscard]] std::string type() const noexcept;


    private:
        // Dans le cas d’un besoin d’optimisation de taille utilisé, et que getContent est très peu utilisé
        // Ou bien la std::string est directement converti en const char* directement après l’appel
        // Stocker un const char*(propriétaire) et retourner un std::unique_ptr<char> serait une solution
        std::string content_;

        std::string sourceType_;

        /**
         * @brief Type fort représentant le type de la source pour le constructeur de gl_engine::utility::Content.
         *
         * @version 1.0
         * @since 0.1
         * @author Axel DAVID
         *
         * @see gl_engine::utility::Content
         */
        class SOURCE_TYPE final {
        public:
            /// Type indiquant que la source vient d’une std::string
            static const SOURCE_TYPE STRING;
            /// Type indiquant que la source vient d’un const char*
            static const SOURCE_TYPE CONST_CHAR_PTR;
            /// Type indiquant que la source vient d’une std::string_view
            static const SOURCE_TYPE STRING_VIEW;
            /// Type indiquant que la source vient d'un flux.
            static const SOURCE_TYPE STREAM;
            /// Type indiquant que la source vient du contenu d’un fichier.
            static const SOURCE_TYPE FILE;

            // Note développeur : Cette classe étant seulement composée de constantes prédéfinies
            // il est donc impossible de déplacer les constantes.

            /**
             * @brief Impossible de créer un gl_engine::utility::Content::SourceType sans argument.
             *
             * @version 1.0
             * @since 0.1
             */
            SOURCE_TYPE() noexcept = delete;

            SOURCE_TYPE( const SOURCE_TYPE& other ) noexcept = default;
            SOURCE_TYPE( SOURCE_TYPE&& ) noexcept = delete;

            SOURCE_TYPE& operator=( const SOURCE_TYPE& other ) noexcept = default;
            SOURCE_TYPE& operator=( SOURCE_TYPE&& other ) noexcept = delete;

            ~SOURCE_TYPE() noexcept = default;

            /**
             * @brief Convertit le gl_engine::utility::Content::SourceType en std::string
             * @return Une chaine de caractère représentant la constante.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::utility::Content
             */
            std::string to_string() const noexcept {
                return type_;
            }

            /**
             * @brief Surcharge statique permettant de convertir un gl_engine::utility::Content::SourceType en std::string.
             * @param type gl_engine::utility::Content::SourceType
             * @return Une chaine de caractère.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @see gl_engine::utility::Content
             */
            static std::string to_string( const SOURCE_TYPE type ) noexcept {
                return type.to_string();
            }

        private:
            std::string type_;

            /**
             * @brief Construit un gl_engine::utility::Content::SourceType à partir d’une std::string.
             * @param type Une chaine de caractère.
             *
             * @exceptsafe NO-THROWS.
             *
             * @version 1.0
             * @since 0.1
             *
             * @note Pour développeur : Actuellement cette classe ne contient que des constantes définies par le développeur.
             * Dans le futur, s’il est nécessaire de permettre à l’utilisateur de créer des constantes
             * Il faudra donc enlever le noexcept, est créé une std::unordered_map contenant tous les types acceptés.
             */
            explicit SOURCE_TYPE( std::string type ) noexcept
            : type_(std::move(type)) {}

            /**
             * @overload
             * @brief Surcharge du constructeur pour prendre en charge const char*.
             * @param type Le pointeur vers la chaine de caractère.
             */
            explicit SOURCE_TYPE( const char* type ) noexcept
            : SOURCE_TYPE( std::string( type ) ) {}

            /**
             * @overload
             * @brief Surcharge pour prendre en charge std::string_view.
             * @param type La vue vers la chaine de caractère.
             */
            explicit SOURCE_TYPE( std::string_view type ) noexcept
            : SOURCE_TYPE( std::string( type ) ) {}
        };


        /**
         * @brief Récupère le contenu du flux fourni.
         * @param stream Flux d’entrée
         * @return Une chaine de caractère correspondant au contenu du flux
         *
         * @pre Le stream fourni doit être bien formé.
         * @throws std::ios_base::failure Lancée si une opération précédente cette méthode, a défini std::ios_base::badbit ou std::ios_base::failbit à 1.
         * @throws std::ios_base::failure Lancée si une erreur arrive durant la lecture du flux fourni.
         * @post La chaine de caractère retournée contient le contenu du stream fourni.
         * @throws std::bad_alloc Lancée si la std::string n’arrive pas à être allouée.
         *
         * @exceptsafe FORT. Seulement si c’est une mauvaise allocation de la string.
         * @exceptsafe BASE. Le flux est dans un état valide si std::ios_base::failbit est à 1.
         * @exceptsafe AUCUNE. Le flux est irrécupérable si std::ios_base::badbit est à 1.
         */
        static std::string getContentFrom( std::istream& stream );

        /**
         * @brief Copie le contenu d’une std::string dans l’objet Content construit.
         * @param source Le contenu
         * @param sourceType gl_engine::utility::Content::SourceType
         *
         * @pre La source ne doit pas être vide.
         * @throws gl_engine::utility::EmptySource Lancée si la std::string fournie est vide.
         * @post Le contenu de Content est identique à la std::string.
         *
         * @exceptsafe FORT. Ne modifie aucune donnée.
         */
        explicit Content( std::string source, const SOURCE_TYPE& type );
    };

    inline const Content::SOURCE_TYPE Content::SOURCE_TYPE::STRING( "String" );
    inline const Content::SOURCE_TYPE Content::SOURCE_TYPE::CONST_CHAR_PTR( "Const char*" );
    inline const Content::SOURCE_TYPE Content::SOURCE_TYPE::STRING_VIEW( "String view" );
    inline const Content::SOURCE_TYPE Content::SOURCE_TYPE::STREAM( "Stream" );
    inline const Content::SOURCE_TYPE Content::SOURCE_TYPE::FILE( "File" );


    // TODO Vérifier les permissions de lecture des fichiers fournis
    /**
     * @brief Type fort représentant un chemin valide vers un fichier régulier.
     * @see gl_engine::utility::Content
     * @see gl_engine::Shader
     */
    class Path final {
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
        friend gl_engine::utility::Content::Content( const Path& path );

        friend class Image;

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
    constexpr inline std::underlying_type_t<Enum> to_underlying( Enum value ) noexcept {
        return static_cast<std::underlying_type_t<Enum>>(value);
    }

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


    class Image final {
    public:
        class STBimageDestroyer {
        public:
            /**
             * @brief Détruit la fenêtre pointée par la poignée fournie.
             *
             * @param [in]window La poignée vers la fenêtre à détruire.
             * @post La fenêtre et le contexte ont été détruit.
             *
             * @throws gl_engine::glfw::Not_Initialized Lancée si le contexte GLFW n’a pas été initialisé.
             * @throws gl_engine::glfw::Platform_Error Lancée si une erreur spécifique à la plateforme est survenue.
             * @exceptsafe AUCUNE. Si Not_Initialized est lancée alors le contexte GLFW n’a pas été initialisé, il suffit donc de l’initialiser.
             * @exceptsafe AUCUNE. Si Platform_Error est lancée alors l’objet GLFW est dans un état indéfini.
             *
             * @version 1.0
             * @since 0.1
             * @author Axel DAVID
             *
             * @see gl_engine::glfw::GLFW
             * @see gl_engine::smartGLFWwindow
             * @see void gl_engine::glfw::GLFW::destroyWindow( GLFWwindow* window )
             * @see [GLFW-DestroyWindow](https://www.glfw.org/docs/3.3/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2)
             *
             * @note Cette fonction doit être appelée sur le thread principal.
             * @note L’exception gl_engine::glfw::Platform_Error est expliqué dans le lien fourni.
             */
            void operator()( unsigned char* const data ) const {
                stbi_image_free(data);
            }
        };

        using smartSTBimage = std::unique_ptr<unsigned char, STBimageDestroyer>;

        Image() = delete;

        /**
         * @brief Charge une image sans correction de gamma
         * @param path Le chemin vers l'image à charger.
         */
        explicit Image(const Path& path);

        // TODO Permettre la copie du contenu de image dans une autre image

        Image(const Image&) noexcept = delete;
        Image( Image&& ) noexcept = default;
        Image& operator=( const Image& ) noexcept = delete;
        Image& operator=( Image&& ) noexcept = default;
        ~Image() noexcept = default;

    private:
        int width_ = 0;
        int height_ = 0;
        int channels_ = 0;

        /**
         * @brief Récupère le contenu de l’image.
         * @return Un pointeur non propriétaire vers le contenu.
         *
         * @exceptsafe NO-THROWS.
         */
        unsigned char* getData() const noexcept {
            return data_.get();
        }

        smartSTBimage data_{nullptr};
    };


    class Dimension final {
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

// Exportation des noms des utilities dans l’espace de nom gl_engine
namespace gl_engine {
    using Content = gl_engine::utility::Content;
    using Path = gl_engine::utility::Path;
    using Image = gl_engine::utility::Image;
    using Dimension = gl_engine::utility::Dimension;
}

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

    GLint getUniformLocation( Id idProgram, std::string name );

    template <typename T>
    void setUniform( Id id, T value );
    //endregion
}

#endif // GLENGINE_UTILITY_HPP
