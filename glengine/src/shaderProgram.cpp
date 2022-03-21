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

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glengine/utility.hpp>

#include <glengine/shaderProgram.hpp>
#include <glengine/shader.hpp>




namespace gl_engine {

// Constructor
    ShaderProgram::ShaderProgram() {
        // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml
        // TODO Vérifier GL
        // Vérifier création prgm
    }

    ShaderProgram::ShaderProgram( VertexShader vertex, FragmentShader fragment, GeometryShader geometry )
    : vertex_(std::move(vertex)), fragment_(std::move(fragment)), geometry_(std::move(geometry)) {
        compile();
    }

    ShaderProgram::ShaderProgram( VertexShader vertex )
    : vertex_(std::move(vertex)) {}

    ShaderProgram::ShaderProgram( FragmentShader fragment )
    : fragment_(std::move(fragment)) {}

    ShaderProgram::ShaderProgram( GeometryShader geometry )
    : geometry_(std::move(geometry)) {}

    ShaderProgram::ShaderProgram( VertexShader vertex, FragmentShader fragment )
    : vertex_(std::move(vertex)), fragment_(std::move(fragment)) {
        compile();
    }


// Destructor
    ShaderProgram::~ShaderProgram() noexcept {
        // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
        // TODO Vérifier erreur GL
        open_gl::deleteProgram( id_ );
        // TODO Vérifier erreur GL
    }

// Utilities
    void ShaderProgram::use() const {
        if ( !compiled_ ) {
            throw ProgramNotCompiled( "Impossible d’utiliser un programme non compilé" );
        }

        // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUseProgram.xhtml

        // TODO Vérifier erreur GL
        open_gl::useProgram( id_ );
        // TODO Vérifier erreur GL
    }

    void ShaderProgram::attachShader( VertexShader shader ) {
        if ( vertex_.has_value() ) {
            throw VertexShaderAlreadyPresent("Le programme a déjà un vertex shader attaché.\n"
                                             "Veuillez le détacher avec la méthode detachShader(Shader_t::VERTEX)");
        }

        compiled_ = false;

        vertex_ = std::move(shader);

        open_gl::attachShader(id_, interface::Program_Shader::getId(vertex_.value()) );

        if ( fragment_.has_value() ) {
            compile();
        }
    }
    void ShaderProgram::attachShader( FragmentShader shader ) {
        if ( fragment_.has_value() ) {
            throw FragmentShaderAlreadyPresent("Le programme a déjà un fragment shader attaché.\n"
                                               "Veuillez le détacher avec la méthode detachShader(Shader_t::FRAGMENT)");
        }

        compiled_ = false;

        fragment_ = std::move(shader);

        open_gl::attachShader(id_, interface::Program_Shader::getId(fragment_.value()) );

        if ( vertex_.has_value() ) {
            compile();
        }
    }
    void ShaderProgram::attachShader( GeometryShader shader ) {
        if ( geometry_.has_value() ) {
            throw GeometryShaderAlreadyPresent("Le programme a déjà un geometry shader attaché.\n"
                                               "Veuillez le détacher avec la méthode detachShader(Shader_t::GEOMETRY)");
        }

        compiled_ = false;

        geometry_ = std::move(shader);

        open_gl::attachShader(id_, interface::Program_Shader::getId(geometry_.value()) );

        if ( vertex_.has_value() && fragment_.has_value() ) {
            compile();
        }
    }
    void ShaderProgram::attachShader( VertexShader vertex, FragmentShader fragment, GeometryShader geometry ) {
        if ( vertex_.has_value() ) {
            throw VertexShaderAlreadyPresent("Le programme a déjà un vertex shader attaché.\n"
                                             "Veuillez le détacher avec la méthode detachShader(Shader_t::VERTEX)");
        }
        if ( fragment_.has_value() ) {
            throw FragmentShaderAlreadyPresent("Le programme a déjà un fragment shader attaché.\n"
                                               "Veuillez le détacher avec la méthode detachShader(Shader_t::FRAGMENT)");
        }
        if ( geometry_.has_value() ) {
            throw GeometryShaderAlreadyPresent("Le programme a déjà un geometry shader attaché.\n"
                                               "Veuillez le détacher avec la méthode detachShader(Shader_t::GEOMETRY)");
        }

        compiled_ = false;

        vertex_ = std::move(vertex);
        open_gl::attachShader(id_, interface::Program_Shader::getId(vertex_.value()) );

        fragment_ = std::move(fragment);
        open_gl::attachShader(id_, interface::Program_Shader::getId(fragment_.value()) );

        geometry_ = std::move(geometry);
        open_gl::attachShader(id_, interface::Program_Shader::getId(geometry_.value()) );

        compile();
    }

    void ShaderProgram::detachShader() {
        // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDetachShader.xhtml
        // TODO Vérifier GL

        compiled_ = false;

        if ( vertex_.has_value() ) {
            open_gl::detachShader(id_, interface::Program_Shader::getId(vertex_.value()));
        }

        if ( fragment_.has_value() ) {
            open_gl::detachShader(id_, interface::Program_Shader::getId(fragment_.value()));
        }

        if ( geometry_.has_value() ) {
            open_gl::detachShader(id_, interface::Program_Shader::getId(geometry_.value()));
        }

        // Vérifier erreurs finales

        uniformLocation_.clear();
    }

    void ShaderProgram::detachShader( Shader_t type) {
        // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDetachShader.xhtml
        // TODO Vérifier GL

        if ( type == Shader_t::VERTEX ) {
            if ( vertex_.has_value() ) {
                compiled_ = false;

                open_gl::detachShader(id_, interface::Program_Shader::getId(vertex_.value()));

                vertex_.reset();
            }
        }
        else if ( type == Shader_t::FRAGMENT ) {
            if ( fragment_.has_value() ) {
                compiled_ = false;

                open_gl::detachShader(id_, interface::Program_Shader::getId(fragment_.value()));

                fragment_.reset();
            }
        }
        else if ( type == Shader_t::GEOMETRY ) {
            if ( geometry_.has_value() ) {
                compiled_ = false;

                open_gl::detachShader(id_, interface::Program_Shader::getId(geometry_.value()));

                geometry_.reset();

                if ( vertex_.has_value() && fragment_.has_value() ) {
                    compile();
                }
            }
        }
        else {
            throw LogicError("Il est impossible d’avoir un type différent de VERTEX,FRAGMENT,GEOMETRY.");
        }

        // Vérifier erreurs finales

        uniformLocation_.clear();
    }

    void gl_engine::ShaderProgram::compile() {
        // TODO Déterminer comment gérer un programme non compilé en cas d'exception
        // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml

        if (!compiled_) {
            if ( !vertex_.has_value() ) {
                throw MissingVertexShader();
            }

            if ( !fragment_.has_value() ) {
                throw MissingFragmentShader();
            }

            open_gl::linkProgram( id_ );

            // TODO Checker les erreurs

            compiled_ = true;
        }

        uniformLocation_.clear();
    }


    GLint ShaderProgram::getUniformLocation( std::string name ) {
        if ( !compiled_ ) {
            throw ProgramNotCompiled("Pour récupérer la localisation des uniformes d’un programme, il est nécessaire que le programme soit compilé.");
        }

        // TODO Vérifier que name ne contienne pas d'espace blanc.

        const auto& location = uniformLocation_.find(name);

        if ( location != uniformLocation_.cend() ) {
            return location->second;
        }

        // TODO Vérifier les erreurs GL
        const auto computedLocation = open_gl::getUniformLocation(id_, name);
        // TODO Vérifier les erreurs GL

        if ( computedLocation < 0 ) {
            throw UniformNotFound(name);
        }

        uniformLocation_.emplace(std::move(name), computedLocation);

        return computedLocation;
    }


    void ShaderProgram::setUniformFloat( std::string name, const float* value, size_t size ) {
        if ( !compiled_ ) {
            throw ProgramNotCompiled("Le programme doit être compilé pour pouvoir modifier la valeur d’un uniforme.");
        }

        const auto location = getUniformLocation(name);

        switch ( size ) {
            case 1:
                glUniform1fv(location, 1, value);
                break;
            case 2:
                glUniform2fv(location, 1, value);
                break;
            case 3:
                glUniform3fv(location, 1, value);
                break;
            case 4:
                glUniform4fv(location, 1, value);
                break;
            default:
                throw std::invalid_argument("La taille fournie doit être comprise entre 1 et 4");
        }
    }

    void ShaderProgram::setUniform( std::string name, glm::vec2 value ) {
        setUniformFloat( std::move(name), glm::value_ptr(value) , 2);
    }
    void ShaderProgram::setUniform( std::string name, glm::vec3 value ) {
        setUniformFloat( std::move(name), glm::value_ptr(value) , 3);
    }
    void ShaderProgram::setUniform( std::string name, glm::vec4 value ) {
        setUniformFloat( std::move(name), glm::value_ptr(value) , 4);
    }


    void ShaderProgram::setUniformInt( std::string name, const int* value, size_t size) {
        if ( !compiled_ ) {
            throw ProgramNotCompiled("Le programme doit être compilé pour pouvoir modifier la valeur d’un uniforme.");
        }

        const auto location = getUniformLocation(name);

        switch ( size ) {
            case 1:
                glUniform1iv(location, 1, value);
                break;
            case 2:
                glUniform2iv(location, 1, value);
                break;
            case 3:
                glUniform3iv(location, 1, value);
                break;
            case 4:
                glUniform4iv(location, 1, value);
                break;
            default:
                throw std::invalid_argument("La taille fournie doit être comprise entre 1 et 4");
        }
    }

    void ShaderProgram::setUniform( std::string name, glm::ivec2 value ) {
        setUniformInt( std::move(name), glm::value_ptr(value), 2);
    }
    void ShaderProgram::setUniform( std::string name, glm::ivec3 value ) {
        setUniformInt( std::move(name), glm::value_ptr(value), 3);
    }
    void ShaderProgram::setUniform( std::string name, glm::ivec4 value ) {
        setUniformInt( std::move(name), glm::value_ptr(value), 4);
    }


    void ShaderProgram::setUniformUnsigned( std::string name, const unsigned int* value, size_t size) {
        if ( !compiled_ ) {
            throw ProgramNotCompiled("Le programme doit être compilé pour pouvoir modifier la valeur d’un uniforme.");
        }

        const auto location = getUniformLocation(name);

        switch ( size ) {
            case 1:
                glUniform1uiv(location, 1, value);
                break;
            case 2:
                glUniform2uiv(location, 1, value);
                break;
            case 3:
                glUniform3uiv(location, 1, value);
                break;
            case 4:
                glUniform4uiv(location, 1, value);
                break;
            default:
                throw std::invalid_argument("La taille fournie doit être comprise entre 1 et 4");
        }
    }

    void ShaderProgram::setUniform( std::string name, glm::uvec2 value ) {
        setUniformUnsigned(std::move(name), glm::value_ptr(value), 2);
    }
    void ShaderProgram::setUniform( std::string name, glm::uvec3 value ) {
        setUniformUnsigned(std::move(name), glm::value_ptr(value), 3);
    }
    void ShaderProgram::setUniform( std::string name, glm::uvec4 value ) {
        setUniformUnsigned(std::move(name), glm::value_ptr(value), 4);
    }


    void ShaderProgram::setUniform( std::string name, glm::dvec2 value ) {
        const auto convertedValue = static_cast<glm::vec2>(value);
        setUniformFloat(std::move(name), glm::value_ptr(convertedValue), 2);
    }
    void ShaderProgram::setUniform( std::string name, glm::dvec3 value ) {
        const auto convertedValue = static_cast<glm::vec3>(value);
        setUniformFloat(std::move(name), glm::value_ptr(convertedValue), 3);
    }
    void ShaderProgram::setUniform( std::string name, glm::dvec4 value ) {
        const auto convertedValue = static_cast<glm::vec4>(value);
        setUniformFloat(std::move(name), glm::value_ptr(convertedValue), 4);
    }


    void ShaderProgram::setUniform( std::string name, glm::bvec2 value ) {
        const auto convertedValue = static_cast<glm::ivec2>(value);
        setUniformInt(std::move(name), glm::value_ptr(convertedValue), 2);
    }
    void ShaderProgram::setUniform( std::string name, glm::bvec3 value ) {
        const auto convertedValue = static_cast<glm::ivec3>(value);
        setUniformInt(std::move(name), glm::value_ptr(convertedValue), 3);
    }
    void ShaderProgram::setUniform( std::string name, glm::bvec4 value ) {
        const auto convertedValue = static_cast<glm::ivec4>(value);
        setUniformInt(std::move(name), glm::value_ptr(convertedValue), 4);
    }


    void ShaderProgram::setUniform( std::string name, int value ) {
        setUniformInt(std::move(name), &value, 1 );
    }
    void ShaderProgram::setUniform( std::string name, float value ) {
        setUniformFloat(std::move(name), &value, 1 );
    }
    void ShaderProgram::setUniform( std::string name, bool value ) {
        const auto convertedValue = static_cast<int>(value);
        setUniformInt(std::move(name), &convertedValue, 1 );
    }
    void ShaderProgram::setUniform( std::string name, double value ) {
        const auto convertedValue = static_cast<float>(value);
        setUniformFloat(std::move(name), &convertedValue, 1 );
    }
    void ShaderProgram::setUniform( std::string name, unsigned int value ) {
        setUniformUnsigned(std::move(name), &value, 1 );
    }


    void ShaderProgram::setUniformFloatMatrix( std::string name, const float* value, size_t sizeX, size_t sizeY, bool transpose ) {
        const auto location = getUniformLocation(std::move(name));

        switch ( sizeX ) {
            case 2:
                switch ( sizeY ) {
                    case 2:
                        glUniformMatrix2fv(location, 1, transpose, value);
                        break;
                    case 3:
                        glUniformMatrix2x3fv(location, 1, transpose, value);
                        break;
                    case 4:
                        glUniformMatrix2x4fv(location, 1, transpose, value);
                        break;
                    default:
                        throw std::invalid_argument("La taille Y fournie doit être comprise entre 2 et 4");
                }
                break;
            case 3:
                switch ( sizeY ) {
                    case 2:
                        glUniformMatrix3x2fv(location, 1, transpose, value);
                        break;
                    case 3:
                        glUniformMatrix3fv(location, 1, transpose, value);
                        break;
                    case 4:
                        glUniformMatrix3x4fv(location, 1, transpose, value);
                        break;
                    default:
                        throw std::invalid_argument("La taille Y fournie doit être comprise entre 2 et 4");
                }
                break;
            case 4:
                switch ( sizeY ) {
                    case 2:
                        glUniformMatrix4x2fv(location, 1, transpose, value);
                        break;
                    case 3:
                        glUniformMatrix4x3fv(location, 1, transpose, value);
                        break;
                    case 4:
                        glUniformMatrix4fv(location, 1, transpose, value);
                        break;
                    default:
                        throw std::invalid_argument("La taille Y fournie doit être comprise entre 2 et 4");
                }
                break;
            default:
                throw std::invalid_argument("La taille X fournie doit être comprise entre 2 et 4");
        }
    }

    void ShaderProgram::setUniform( std::string name, glm::mat2 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 2, 2, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::mat2x3 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 2, 3, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::mat2x4 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 2, 4, utility::to_underlying(transpose) );
    }

    void ShaderProgram::setUniform( std::string name, glm::mat3 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 3, 3, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::mat3x2 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 3, 2, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::mat3x4 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 3, 4, utility::to_underlying(transpose) );
    }

    void ShaderProgram::setUniform( std::string name, glm::mat4 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 4, 4, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::mat4x2 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 4, 2, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::mat4x3 value, TRANSPOSE transpose ) {
        setUniformFloatMatrix(std::move(name), glm::value_ptr(value), 4, 3, utility::to_underlying(transpose) );
    }


    void ShaderProgram::setUniform( std::string name, glm::dmat2 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat2>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 2,2, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::dmat2x3 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat2x3>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 2,3, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::dmat2x4 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat2x4>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 2,4, utility::to_underlying(transpose) );
    }

    void ShaderProgram::setUniform( std::string name, glm::dmat3 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat3>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 3,3, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::dmat3x2 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat3x2>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 3,2, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::dmat3x4 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat3x4>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 3,4, utility::to_underlying(transpose) );
    }

    void ShaderProgram::setUniform( std::string name, glm::dmat4 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat4>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 4,4, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::dmat4x2 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat4x2>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 4,2, utility::to_underlying(transpose) );
    }
    void ShaderProgram::setUniform( std::string name, glm::dmat4x3 value, TRANSPOSE transpose ) {
        const auto convertedValue = static_cast<glm::mat4x3>( value );
        setUniformFloatMatrix(std::move(name), glm::value_ptr(convertedValue), 4,3, utility::to_underlying(transpose) );
    }

}
