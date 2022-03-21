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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <type_traits>
#include <utility>

#include <string>
#include <string_view>
#include <filesystem>

#include <istream>
#include <fstream>

#include <glengine/utility.hpp>

namespace gl_engine::open_gl {
    // region Shader
    Id createShader( const GLenum type ) {
        auto id = glCreateShader(type);
        return id;
    }


    void shaderSource( const Id id, const Size count, const GLchar** const string, const Length* const length ) {
        glShaderSource( id, count, string, length );
    }

    // TODO Passer une référence constante et une R-référence sera plus efficient
    void shaderSource( const Id id, const std::string source ) {
        auto* sourceContent = source.c_str();

        shaderSource( id, 1, &sourceContent, nullptr );
    }

    // TODO Passer une référence constante et une R-référence sera plus efficient
    void shaderSource( const Id id, const Content source ) {
        shaderSource( id, source.content() );
    }

    void compileShader( const Id id ) {
        glCompileShader( id );
    }

    void deleteShader( const Id id ) {
        glDeleteShader( id );
    }
    // endregion

    // region ShaderProgram
    Id createProgram() {
        return glCreateProgram();
    }

    void useProgram( const Id id ) {
        glUseProgram(id);
    }

    void deleteProgram( const Id id ) {
        glDeleteProgram(id);
    }

    void detachShader( const Id idProgram, const Id idShader ) {
        glDetachShader( idProgram, idShader );
    }

    void attachShader( const Id idProgram, const Id idShader ) {
        glAttachShader( idProgram, idShader );
    }

    void linkProgram( Id id ) {
        glLinkProgram(id);
    }

    GLint getUniformLocation( Id idProgram, std::string name ) {
        return glGetUniformLocation( idProgram, name.c_str() );
    }

    template <typename T>
    void setUniform( Id id, T value ) {
        const auto convertedId = static_cast<int>(id);

        if ( std::is_integral_v<T> ) {
            if ( std::is_signed_v<T> ) {
                const auto convertedValue = static_cast<int>(value);

                glUniform1iv( convertedId, 1, &convertedValue );
            }
            else {
                const auto convertedValue = static_cast<unsigned int>(value);

                glUniform1uiv( convertedId, 1, &convertedValue );
            }
        }
        else if ( std::is_floating_point_v<T> ) {
            const auto convertedValue = static_cast<float>(value);

            glUniform1fv(convertedId, 1, &convertedValue);
        }
        // Checker T est std::vector de type primitifs
        // Checker T est std::array de type primitifs
        // Checker T est std::initializer_list de type primitifs
//        else if ( std::is_same_v<T, std::vector<>> ) {
//
//        }
        else {
            // Error
        }
    }
    // endregion
}



namespace gl_engine::utility {
    Content::Content( std::string source, const SOURCE_TYPE& type )
    : content_( std::move(source) ), sourceType_( type.to_string() ) {
        if ( content_.empty() ) {
            throw EmptySource(sourceType_);
        }
    }

    Content::Content( std::string source )
    : Content( std::move(source), SOURCE_TYPE::STRING ) {}

    Content::Content( const char* const source )
    : Content( std::string{source}, SOURCE_TYPE::CONST_CHAR_PTR ) {}

    // TODO : Copie, donc un passage par référence const et R-référence sera plus efficient
    Content::Content( const std::string_view source )
    : Content( std::string{source}, SOURCE_TYPE::STRING_VIEW ) {}

    Content::Content( std::istream& stream )
    : Content( getContentFrom(stream), SOURCE_TYPE::STREAM ) {}

    Content::Content( const Path& path )
    : sourceType_( SOURCE_TYPE::FILE.to_string() + " : " + path.path_.string() ) {
        // TODO Note amélioration : On se trouve dans le cas où on utilise juste la variable path on ne la stocke pas
        // Ainsi un passage par référence constante
        // Et une surcharge par R-référence
        // Donnera normalement plus de performance
        // Il faut TESTER

        // Le fichier ne doit pas être vide
        // Peut être redondant de vérifier si le fichier est vide ou non.
        // Mais on peut éviter d’extraire et de construire un ifstream si le fichier est vide.
        // Mais il faut quand même vérifier que le contenu extrait n’est pas vide
        if ( std::filesystem::is_empty( path.path_ ) ) {
            throw EmptySource(sourceType_);
        }

        std::ifstream sourceFile(path.path_);

        if ( !sourceFile.is_open() ) {
            throw ErrorOpeningFile(path.path_.string());
        }

        try {
            content_ = getContentFrom( sourceFile );
        }
        catch ( const std::ios_base::failure& ) {
            throw ErrorReadingFile(path.path_.string());
        }

        if ( content_.empty() ) {
            throw EmptySource(sourceType_);
        }

        // Libération du fichier
        try {
            sourceFile.close();
        }
        catch ( const std::ios_base::failure& exception ) {
            throw ErrorClosingFile(path.path_.string());
        }
    }

    std::string Content::content() const noexcept {
        return content_;
    }

    std::string Content::getContentFrom( std::istream& stream ) {
        try {
            stream.exceptions( std::ios_base::failbit | std::ios_base::badbit );
        }
        catch ( const std::ios_base::failure& ) {
            throw ErrorOpeningStream("Flux venant de la fonction Content::getContentFrom");
        }

        std::ostringstream buffer;
        try {
            buffer << stream.rdbuf();
        }
        catch ( const std::ios_base::failure& ) {
            throw ErrorReadingStream("Flux venant de la fonction Content::getContentFrom");
        }

        return buffer.str();
    }

    std::string Content::type() const noexcept {
        return sourceType_;
    }



    Path::Path( std::filesystem::path path )
    : path_( std::move(path) ) {
        if ( !std::filesystem::exists( path_ ) ) {
            throw UnknownPath(path_.string());
        }

        // Dans le cas que path est un lien symbolique, on récupère le chemin vers le fichier pointé.
        if ( std::filesystem::is_symlink( path_ ) ) {
            path_ = std::filesystem::read_symlink( path_ );

            if ( !std::filesystem::exists( path_ ) ) {
                throw UnknownPath(path_.string());
            }
        }

        // On accepte seulement les fichiers dits réguliers
        if ( !std::filesystem::is_regular_file( path_ ) ) {
            throw NotRegularFile(path_.string());
        }
    }

    Path::Path( std::string path )
    : Path( std::filesystem::path{std::move(path) } ) {}

    Path::Path( const char* const path )
    : Path( std::string{path} ) {}

    // TODO : Copie, donc un passage par référence const et R-référence sera plus efficient
    Path::Path( const std::string_view path )
    : Path( std::string{path} ) {}


    Image::Image( const Path& path ) {
        // TODO Faire un objet File qui vérifie que le fichier à l'adresse fournie, n'est pas vide et que l'on a les autorisations suffisantes pour le lire.
        // class InputFile
        // TODO Fonction dans l'objet stbi image qui charge l'image et retourne un unique_ptr contenant les bytes de l'image.
        if ( std::filesystem::is_empty(path.path_) ) {
            throw EmptySource(path.path_.string());
        }

        data_ = smartSTBimage(stbi_load(path.path_.c_str(), &width_, &height_, &channels_, 0));

        // TODO Etre plus explicit sur l'erreur
        if ( data_ == nullptr ) {
            throw STBException("Erreur durant la lecture de l'image : " + path.path_.string() );
        }
    }

}
