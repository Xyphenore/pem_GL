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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <type_traits>
#include <utility>

#include <string>
#include <string_view>
#include <filesystem>

#include <istream>
#include <fstream>

#include <vector>
#include <array>
#include <initializer_list>

#include <stdexcept>

#include <glengine/utility.hpp>

template<class Enum>
constexpr std::underlying_type_t<Enum> gl_engine::utility::to_underlying( const Enum value ) noexcept {
    return static_cast<std::underlying_type_t<Enum>>(value);
}




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
        shaderSource( id, source.getContent() );
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

    Id getUniformLocation( Id idProgram, std::string name ) {
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
    // region Content
    Content::Content( std::string source, std::string sourceType )
    : content_( std::move(source) ), sourceType_( std::move(sourceType) ) {
        if ( content_.empty() ) {
            throw std::invalid_argument("La source est vide");
        }

        if ( sourceType_.empty() ) {
            throw std::logic_error("Le type de la source est vide");
        }
    }

    Content::Content( std::string source )
    : Content( std::move(source), "String" ){}

    Content::Content( const char* const source )
    : Content( std::string{source}, "const char*" ) {}

    // TODO : Copie, donc un passage par référence const et R-référence sera plus efficient
    Content::Content( const std::string_view source )
    : Content( std::string{source }, "String_view" ) {}

    Content::Content( std::istream& stream )
    : Content( getContentFrom( stream ), "Input stream" ) {}

    Content::Content( const Path path )
    : sourceType_( "Path : " + path.path_.string() ) {
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
            throw std::invalid_argument( "Le fichier : " + path.path_.string() + " est vide." );
        }

        std::ifstream sourceFile(path.path_);

        if ( !sourceFile.is_open() ) {
            throw std::ios_base::failure( "Impossible d’ouvrir le fichier : " + path.path_.string() );
        }

        try {
            content_ = getContentFrom( sourceFile );
        }
        catch ( const std::ios_base::failure& ) {
            throw std::ios_base::failure( "Erreur interne durant la lecture du flux du fichier : "
                                          + path.path_.string() );
        }

        if ( content_.empty() ) {
            throw std::invalid_argument("La source est vide");
        }

        // Libération du fichier
        try {
            sourceFile.close();
        }
        catch ( const std::ios_base::failure& exception ) {
            throw std::ios_base::failure("Erreur interne durant la fermeture du fichier : " + path.path_.string(),
                                         exception.code() );
        }
    }

    std::string Content::getContent() const noexcept {
        return content_;
    }

    std::string Content::getContentFrom( std::istream& stream ) {
        // Activation des exceptions pour les prochaines opérations
        stream.exceptions( std::ios_base::failbit | std::ios_base::badbit );

        std::ostringstream buffer;
        try {
            buffer << stream.rdbuf();
        }
        catch ( const std::ios_base::failure& ) {
            throw std::ios_base::failure( "Erreur interne durant la lecture du flux" );
        }

        return buffer.str();
    }

    std::string Content::getType() const noexcept {
        return sourceType_;
    }
    // endregion

    // region Path
    Path::Path( std::filesystem::path path )
    : path_( std::move(path) ) {
        if ( !std::filesystem::exists( path_ ) ) {
            throw std::invalid_argument( "Le chemin : '" + path_.string() + "' n'existe pas." );
        }

        // Dans le cas que path est un lien symbolique, on récupère le chemin vers le fichier pointé.
        if ( std::filesystem::is_symlink( path_ ) ) {
            path_ = std::filesystem::read_symlink( path_ );
        }

        // On accepte seulement les fichiers dits réguliers
        if ( !std::filesystem::is_regular_file( path_ ) ) {
            throw std::invalid_argument(
                    "Le chemin fourni : " + path_.string() + " ne pointe pas vers un fichier régulier." );
        }
    }

    Path::Path( std::string path )
    : Path( std::filesystem::path{std::move(path) } ) {}

    Path::Path( const char* const path )
    : Path( std::string{path} ) {}

    // TODO : Copie, donc un passage par référence const et R-référence sera plus efficient
    Path::Path( const std::string_view path )
    : Path( std::string{path} ) {}
    // endregion
}
