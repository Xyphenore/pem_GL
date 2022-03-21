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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>
#include <stdexcept>

#include <glengine/abstract_shader.hpp>
#include "glengine/utility.hpp"

namespace gl_engine::open_gl {
    Id createShader( const Shader_t type ) {
        return createShader(type.get() );
    }
}

// Constructors
gl_engine::AbstractShader::AbstractShader( const Shader_t type, Content source )
        : Shader() {
    // TODO Vérifier les erreurs opengl avant

    privateId_ = open_gl::createShader(type);
    // Vérifier que la création du shader est valide(aka le type)
    if ( 0 == privateId_ ) {
        GLint sizeLog = 0;
        glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );

        // TODO Vider glGetError

        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::CREATE_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " )
                    .append( source.type() ).append( " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    // Le shader a été alloué
    // Toutes exceptions lancées doivent supprimer le shader
    try {
        compile(std::move(source) );
    }
    catch ( ... ) {
        open_gl::deleteShader(privateId_);
        throw;
    }

    // TODO Vérifier les erreurs finales
}

gl_engine::AbstractShader::AbstractShader( const AbstractShader& other ) {
    // TODO Vérifier les erreurs opengl avant

    const auto type = other.getType();
    const auto source = other.getSource();

    privateId_ = open_gl::createShader(type);
    // Vérifier que la création du shader est valide(aka le type)
    if ( 0 == privateId_ ) {
        GLint sizeLog = 0;
        glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );

        // TODO Vider glGetError

        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::CREATE_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " )
                    .append( source.type() ).append( " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    // Le shader a été alloué
    // Toutes exceptions lancées doivent supprimer le shader
    try {
        open_gl::shaderSource( privateId_, source );

        GLint sizeLog = 0;
        glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );

        if ( sizeLog > 0 ) {
            //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
            std::string logMessage;
            logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
            glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

            std::string errorMessage( "ERROR::SOURCE_SHADER::TYPE : " );
            errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.type() ).append(
                    " : " ).append( logMessage );

            throw std::runtime_error( errorMessage );
        }

        // Compiler
        open_gl::compileShader(privateId_);

        // Vérifier les erreurs
        GLint success = GL_FALSE;
        glGetShaderiv( privateId_, GL_COMPILE_STATUS, &success );

        if ( GL_FALSE == static_cast<GLboolean>(success) ) {
            glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );
            //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
            std::string logMessage;
            logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
            glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

            std::string errorMessage( "ERROR::COMPILATION_SHADER::TYPE : " );
            errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.type() ).append(
                    " : " ).append( logMessage );

            throw std::runtime_error( errorMessage );
        }
    }
    catch ( ... ) {
        open_gl::deleteShader(privateId_);
        throw;
    }

    // TODO Vérifier les erreurs finales
}

gl_engine::AbstractShader::AbstractShader( AbstractShader&& other ) noexcept {
    // TODO Vérifier les erreurs opengl avant

    privateId_ = std::exchange(other.privateId_, 0);

    // TODO Vérifier les erreurs finales
}

gl_engine::AbstractShader& gl_engine::AbstractShader::operator=( const gl_engine::AbstractShader& other ) {
    // TODO Vérifier les erreurs opengl avant

    if ( &other != this ) {

        const auto source = other.getSource();

        if ( const auto type = other.getType();
                getType() != type ) {
            // TODO Erreur opengl
            open_gl::deleteShader( privateId_ );
            // TODO erreur delete

            privateId_ = open_gl::createShader( type );
            // Vérifier que la création du shader est valide(aka le type)
            if ( 0 == privateId_ ) {
                GLint sizeLog = 0;
                glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );

                // TODO Vider glGetError

                //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
                std::string logMessage;
                logMessage.resize( static_cast<size_t>(sizeLog), '\0' );
                glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

                std::string errorMessage( "ERROR::CREATE_SHADER::TYPE : " );
                errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.type() ).append(
                        " : " ).append( logMessage );

                throw std::runtime_error( errorMessage );
            }
        }

        try {
            open_gl::shaderSource( privateId_, source );

            GLint sizeLog = 0;
            glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );

            if ( sizeLog > 0 ) {
                //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
                std::string logMessage;
                logMessage.resize( static_cast<size_t>(sizeLog), '\0' );
                glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

                std::string errorMessage( "ERROR::SOURCE_SHADER::TYPE : " );
                errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.type() ).append(
                        " : " ).append( logMessage );

                throw std::runtime_error( errorMessage );
            }

            // Compiler
            open_gl::compileShader( privateId_ );

            // Vérifier les erreurs
            GLint success = GL_FALSE;
            glGetShaderiv( privateId_, GL_COMPILE_STATUS, &success );

            if ( GL_FALSE == static_cast<GLboolean>(success) ) {
                glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );
                //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
                std::string logMessage;
                logMessage.resize( static_cast<size_t>(sizeLog), '\0' );
                glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

                std::string errorMessage( "ERROR::COMPILATION_SHADER::TYPE : " );
                errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.type() ).append(
                        " : " ).append( logMessage );

                throw std::runtime_error( errorMessage );
            }
        }
        catch ( ... ) {
            open_gl::deleteShader( privateId_ );
            throw;
        }
        // TODO Vérifier les erreurs finales
    }

    return *this;
}

gl_engine::AbstractShader& gl_engine::AbstractShader::operator=( gl_engine::AbstractShader&& other ) noexcept {
    if ( &other != this ) {
        // TODO Vérifier erreur
        open_gl::deleteShader( privateId_ );
        // TODO Vérifier erreur après

        privateId_ = std::exchange( other.privateId_, 0 );
    }

    return *this;
}

// Destructor
gl_engine::AbstractShader::~AbstractShader() noexcept {
    // TODO les erreurs avant doivent juste être lancées
    open_gl::deleteShader(privateId_);
    // TODO Vérification des erreurs
    // TODO les erreurs doivent faire planter l'executions
}

// region Getters
gl_engine::Shader_t gl_engine::AbstractShader::type_() const {
    GLint type = GL_NONE;
    glGetShaderiv( privateId_, GL_SHADER_TYPE, &type );

    if ( GL_NONE == type ) {
        GLint sizeLog = 0;
        glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );

        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::GET_TYPE_SHADER::ID : " );
        errorMessage.append( std::to_string(privateId_) ).append( " : ").append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    return gl_engine::Shader_t(static_cast<GLenum>(type));
}

gl_engine::Content gl_engine::AbstractShader::source_() const {
    // Vérification avant exécution
    GLenum errorCode = GL_NO_ERROR;
    std::string errorMessage("ERREUR_INTERNE::AVANT_EXECUTION::getSource()::SHADER_ID : " + std::to_string(privateId_) + '\n' );
    while ( (errorCode = glGetError()) != GL_NO_ERROR ) {
        errorMessage.append("ERREUR " ).append( std::to_string(errorCode) ).append( " : " )
                    .append( gl_engine::utility::to_string(errorCode) + '\n');
    }

    // Récupération de la taille de la source
    GLint sourceLength = 0;
    glGetShaderiv( privateId_, GL_SHADER_SOURCE_LENGTH, &sourceLength );

    // Vérification des erreurs
    if ( const auto errorCode2 = glGetError(); errorCode2 != GL_NO_ERROR ) {
        throw std::runtime_error("Erreur glGetShaderiv : " + gl_engine::utility::to_string(errorCode2) );
    }

    if ( sourceLength <= 0 ) {
        GLint logSize = 0;
        glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &logSize );

        if ( logSize > 0 ) {
            const auto logMessage = std::make_unique<GLchar>(logSize);
            glGetShaderInfoLog( privateId_, logSize, nullptr, logMessage.get() );

            std::string errorMessage("INTERNAL_ERROR::SOURCE_SHADER::ID : " );
            errorMessage.append( std::to_string( privateId_ ) ).append(" : ").append(logMessage.get());

            throw std::runtime_error(errorMessage);
        }
    }

    // Récupération de la source
    std::string source;
    source.resize(sourceLength);
    glGetShaderSource( privateId_, sourceLength, nullptr, source.data() );

    GLint logSize = 0;
    glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &logSize );

    if ( logSize > 0 ) {
        const auto logMessage = std::make_unique<GLchar>(logSize);
        glGetShaderInfoLog( privateId_, logSize, nullptr, logMessage.get() );

        std::string errorMessage("INTERNAL_ERROR::SOURCE_SHADER::ID : " );
        errorMessage.append( std::to_string( privateId_ ) ).append(" : ").append(logMessage.get());

        throw std::runtime_error(errorMessage);
    }

    return Content(source);
}

// Private function
void gl_engine::AbstractShader::compile( const Content source ) const {
    open_gl::shaderSource( privateId_, source );

    GLint sizeLog = 0;
    glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );

    if ( sizeLog > 0 ) {
        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::SOURCE_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.type() ).append(
                " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }

    // Compiler
    open_gl::compileShader(privateId_);

    // Vérifier les erreurs
    GLint success = GL_FALSE;
    glGetShaderiv( privateId_, GL_COMPILE_STATUS, &success );

    if ( GL_FALSE == static_cast<GLboolean>(success) ) {
        glGetShaderiv( privateId_, GL_INFO_LOG_LENGTH, &sizeLog );
        //const auto logMessage = std::make_unique<char[]>( static_cast<size_t>(sizeLog) );
        std::string logMessage;
        logMessage.resize(static_cast<size_t>(sizeLog), '\0' );
        glGetShaderInfoLog( privateId_, sizeLog, nullptr, logMessage.data() );

        std::string errorMessage( "ERROR::COMPILATION_SHADER::TYPE : " );
        errorMessage.append( "TYPE"/*type*/ ).append( " , source : " ).append( source.type() ).append(
                " : " ).append( logMessage );

        throw std::runtime_error( errorMessage );
    }
}

void gl_engine::AbstractShader::checkCompileError() const {

}
// endregion
