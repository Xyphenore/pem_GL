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
 * Bidon_OpenGL - Copyright © 2022-2022 DAVID Axel, GOI Suzy
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

#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <memory>
#include <stdexcept>

#include "glengine/shader.hpp"
#include "glengine/utility.hpp"

// Constructors
gl_engine::Shader::Shader( const Shader_t type, Content source ) {
    // TODO Vérifier les erreurs opengl avant

    id_ = open_gl::createShader(type);
    // Vérifier que la création du shader est valide(aka le type)
    if ( 0 == id_ ) {
        GLint sizeLog = 0;
        glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

        // TODO Vider glGetError

        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::CREATE_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " )
                    .append( source.getType() ).append( " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    // Le shader a été alloué
    // Toutes exceptions lancées doivent supprimer le shader
    try {
        compile(std::move(source) );
    }
    catch ( ... ) {
        open_gl::deleteShader(id_);
        throw;
    }

    // TODO Vérifier les erreurs finales
}

gl_engine::Shader::Shader( const gl_engine::Shader_t type, const std::filesystem::path source ) {
    // Vérifier que le path est good
    // Chemin valide
    if ( !std::filesystem::exists( source ) ) {
        throw std::invalid_argument( "Le chemin : '" + source.string() + "' n'existe pas." );
    }

    // TODO Inverser les deux opérations suivantes
    // Chemin vers un fichier ou un fifo
    // On accepte seulement les fichiers dits réguliers et les liens symboliques vers des fichiers réguliers
    if ( (!std::filesystem::is_regular_file( source )) && (!std::filesystem::is_symlink( source )) ) {
        throw std::invalid_argument(
                "Le chemin fourni : " + source.string() + " ne pointe pas vers un fichier régulier." );
    }

    const auto pathSRC = ( std::filesystem::is_symlink( source ) ? std::filesystem::read_symlink( source )
                                                                 : source );

    // TODO Peut être une vérification redondante
    // Le fichier ne doit pas être vide
    if ( std::filesystem::is_empty( pathSRC ) ) {
        throw std::invalid_argument( "La source du shader : " + pathSRC.string() + " est vide." );
    }

    // Lecture du contenu du fichier
    std::ifstream sourceFile( pathSRC );

    if ( !sourceFile.is_open() ) {
        throw std::ios_base::failure( "Impossible d’ouvrir le fichier à l’adresse : " + pathSRC.string() );
    }

    // Activation des exceptions pour les prochaines opérations
    sourceFile.exceptions( std::ios_base::failbit | std::ios_base::badbit );

    std::ostringstream buffer;
    try {
        buffer << sourceFile.rdbuf();
    }
    catch ( const std::ios_base::failure& exception ) {
        throw std::ios_base::failure( "Erreur interne durant la lecture du fichier : " + pathSRC.string(),
                                      exception.code() );
    }

    // Libération du fichier
    try {
        sourceFile.close();
    }
    catch ( const std::ios_base::failure& exception ) {
        throw std::ios_base::failure("Erreur interne durant la fermeture du fichier : " + pathSRC.string(),
                                     exception.code() );
    }






    // Associer la source au shader
    const auto sourceSTR = buffer.str();
    auto* const sourceCSTR = sourceSTR.c_str();

    id_ = open_gl::createShader(type);
    // Vérifier que la création du shader est valide(aka le type)
    if ( 0 == id_ ) {
        GLint sizeLog = 0;
        glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

        // TODO Vider glGetError

        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::CREATE_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " )
                    .append( source.string() ).append( " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    // Le shader a été alloué
    // Toutes exceptions lancées doivent supprimer le shader
    try {
        glShaderSource( id_, 1, &sourceCSTR, nullptr );

        GLint sizeLog = 0;
        glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

        if ( sizeLog > 0 ) {
            //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
            std::string logMessage;
            logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
            glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

            std::string errorMessage( "ERROR::SOURCE_SHADER::TYPE : " );
            errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.string() ).append(
                    " : " ).append( logMessage );

            throw std::runtime_error( errorMessage );
        }

        // Compiler
        glCompileShader( id_ );

        // Vérifier les erreurs
        GLint success = GL_FALSE;
        glGetShaderiv( id_, GL_COMPILE_STATUS, &success );

        if ( GL_FALSE == static_cast<GLboolean>(success) ) {
            glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );
            //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
            std::string logMessage;
            logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
            glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

            std::string errorMessage( "ERROR::COMPILATION_SHADER::TYPE : " );
            errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.string() ).append(
                    " : " ).append( logMessage );

            throw std::runtime_error( errorMessage );
        }
    }
    catch ( ... ) {
        glDeleteShader(id_);
        throw;
    }
}

gl_engine::Shader::Shader( const Shader& other ) {
    // TODO Vérifier les erreurs opengl avant

    const auto type = other.getType();
    const auto source = other.getSource();

    id_ = open_gl::createShader(type);
    // Vérifier que la création du shader est valide(aka le type)
    if ( 0 == id_ ) {
        GLint sizeLog = 0;
        glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

        // TODO Vider glGetError

        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::CREATE_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " )
                    .append( source.getType() ).append( " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    // Le shader a été alloué
    // Toutes exceptions lancées doivent supprimer le shader
    try {
        open_gl::shaderSource( id_, source );

        GLint sizeLog = 0;
        glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

        if ( sizeLog > 0 ) {
            //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
            std::string logMessage;
            logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
            glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

            std::string errorMessage( "ERROR::SOURCE_SHADER::TYPE : " );
            errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.getType() ).append(
                    " : " ).append( logMessage );

            throw std::runtime_error( errorMessage );
        }

        // Compiler
        open_gl::compileShader(id_);

        // Vérifier les erreurs
        GLint success = GL_FALSE;
        glGetShaderiv( id_, GL_COMPILE_STATUS, &success );

        if ( GL_FALSE == static_cast<GLboolean>(success) ) {
            glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );
            //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
            std::string logMessage;
            logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
            glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

            std::string errorMessage( "ERROR::COMPILATION_SHADER::TYPE : " );
            errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.getType() ).append(
                    " : " ).append( logMessage );

            throw std::runtime_error( errorMessage );
        }
    }
    catch ( ... ) {
        open_gl::deleteShader(id_);
        throw;
    }

    // TODO Vérifier les erreurs finales
}

gl_engine::Shader::Shader( Shader&& other ) noexcept {
    // TODO Vérifier les erreurs opengl avant

    id_ = std::exchange(other.id_, 0);

    // TODO Vérifier les erreurs finales
}

gl_engine::Shader& gl_engine::Shader::operator=( const gl_engine::Shader& other ) {
    // TODO Vérifier les erreurs opengl avant

    if ( &other != this ) {

        const auto source = other.getSource();

        if ( const auto type = other.getType();
                getType() != type ) {
            // TODO Erreur opengl
            open_gl::deleteShader( id_ );
            // TODO erreur delete

            id_ = open_gl::createShader( type );
            // Vérifier que la création du shader est valide(aka le type)
            if ( 0 == id_ ) {
                GLint sizeLog = 0;
                glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

                // TODO Vider glGetError

                //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
                std::string logMessage;
                logMessage.resize( static_cast<size_t>(sizeLog), '\0' );
                glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

                std::string errorMessage( "ERROR::CREATE_SHADER::TYPE : " );
                errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.getType() ).append(
                        " : " ).append( logMessage );

                throw std::runtime_error( errorMessage );
            }
        }

        try {
            open_gl::shaderSource( id_, source );

            GLint sizeLog = 0;
            glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

            if ( sizeLog > 0 ) {
                //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
                std::string logMessage;
                logMessage.resize( static_cast<size_t>(sizeLog), '\0' );
                glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

                std::string errorMessage( "ERROR::SOURCE_SHADER::TYPE : " );
                errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.getType() ).append(
                        " : " ).append( logMessage );

                throw std::runtime_error( errorMessage );
            }

            // Compiler
            open_gl::compileShader( id_ );

            // Vérifier les erreurs
            GLint success = GL_FALSE;
            glGetShaderiv( id_, GL_COMPILE_STATUS, &success );

            if ( GL_FALSE == static_cast<GLboolean>(success) ) {
                glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );
                //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
                std::string logMessage;
                logMessage.resize( static_cast<size_t>(sizeLog), '\0' );
                glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

                std::string errorMessage( "ERROR::COMPILATION_SHADER::TYPE : " );
                errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.getType() ).append(
                        " : " ).append( logMessage );

                throw std::runtime_error( errorMessage );
            }
        }
        catch ( ... ) {
            open_gl::deleteShader( id_ );
            throw;
        }
        // TODO Vérifier les erreurs finales
    }

    return *this;
}

gl_engine::Shader& gl_engine::Shader::operator=( gl_engine::Shader&& other ) noexcept {
    if ( &other != this ) {
        // TODO Vérifier erreur
        open_gl::deleteShader( id_ );
        // TODO Vérifier erreur après

        id_ = std::exchange( other.id_, 0 );
    }

    return *this;
}

// Destructor
gl_engine::Shader::~Shader() noexcept {
    // TODO les erreurs avant doivent juste être lancées
    open_gl::deleteShader(id_);
    // TODO Vérification des erreurs
    // TODO les erreurs doivent faire planter l'executions
}

// region Getters
gl_engine::Shader_t gl_engine::Shader::getType() const {
    GLint type = GL_NONE;
    glGetShaderiv( id_, GL_SHADER_TYPE, &type );

    if ( GL_NONE == type ) {
        GLint sizeLog = 0;
        glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::GET_TYPE_SHADER::ID : " );
        errorMessage.append( std::to_string(id_) ).append( " : ").append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    return gl_engine::Shader_t(static_cast<GLenum>(type));
}

gl_engine::Content gl_engine::Shader::getSource() const {
    // Vérification avant exécution
    GLenum errorCode = GL_NO_ERROR;
    std::string errorMessage("ERREUR_INTERNE::AVANT_EXECUTION::getSource()::SHADER_ID : " + std::to_string(id_) + '\n' );
    while ( (errorCode = glGetError()) != GL_NO_ERROR ) {
        errorMessage.append("ERREUR " ).append( std::to_string(errorCode) ).append( " : " )
        .append( gl_engine::utility::to_string(errorCode) + '\n');
    }

    // Récupération de la taille de la source
    GLint sourceLength = 0;
    glGetShaderiv( id_, GL_SHADER_SOURCE_LENGTH, &sourceLength );

    // Vérification des erreurs
    if ( const auto errorCode2 = glGetError(); errorCode2 != GL_NO_ERROR ) {
        throw std::runtime_error("Erreur glGetShaderiv : " + gl_engine::utility::to_string(errorCode2) );
    }

    if ( sourceLength <= 0 ) {
        GLint logSize = 0;
        glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &logSize );

        if ( logSize > 0 ) {
            const auto logMessage = std::make_unique<GLchar>(logSize);
            glGetShaderInfoLog( id_, logSize, nullptr, logMessage.get() );

            std::string errorMessage("INTERNAL_ERROR::SOURCE_SHADER::ID : " );
            errorMessage.append( std::to_string( id_ ) ).append(" : ").append(logMessage.get());

            throw std::runtime_error(errorMessage);
        }
    }

    // Récupération de la source
    const auto source = std::make_unique<GLchar>(sourceLength);
    glGetShaderSource( id_, sourceLength, nullptr, source.get() );

    GLint logSize = 0;
    glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &logSize );

    if ( logSize > 0 ) {
        const auto logMessage = std::make_unique<GLchar>(logSize);
        glGetShaderInfoLog( id_, logSize, nullptr, logMessage.get() );

        std::string errorMessage("INTERNAL_ERROR::SOURCE_SHADER::ID : " );
        errorMessage.append( std::to_string( id_ ) ).append(" : ").append(logMessage.get());

        throw std::runtime_error(errorMessage);
    }

    return Content(source.get());
}

// Private function
void gl_engine::Shader::compile( const Content source ) const {
    open_gl::shaderSource( id_, source );

    GLint sizeLog = 0;
    glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );

    if ( sizeLog > 0 ) {
        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::SOURCE_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.getType() ).append(
                " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    // Compiler
    open_gl::compileShader(id_);

    // Vérifier les erreurs
    GLint success = GL_FALSE;
    glGetShaderiv( id_, GL_COMPILE_STATUS, &success );

    if ( GL_FALSE == static_cast<GLboolean>(success) ) {
        glGetShaderiv( id_, GL_INFO_LOG_LENGTH, &sizeLog );
        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( id_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::COMPILATION_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.getType() ).append(
                " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }
}
// endregion






namespace gl_engine::open_gl {
    Id createShader( const Shader_t type ) {
        return createShader(type.get() );
    }
}

// endregion
