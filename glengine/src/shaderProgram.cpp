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

#include <glengine/shaderProgram.hpp>
#include <glengine/shader.hpp>
#include <glengine/utility.hpp>

// Constructor
gl_engine::ShaderProgram::ShaderProgram() {
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml
    // TODO Vérifier GL
    // Vérifier création prgm
}

// Destructor
gl_engine::ShaderProgram::~ShaderProgram() noexcept {
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
    // TODO Vérifier erreru GL
    open_gl::deleteProgram(id_);
    // TODO Vérifier erreur GL
}

// Utilities
void gl_engine::ShaderProgram::use() const {
    if ( !compiled_ ) {
        throw std::logic_error("Impossible d'utiliser un programme non compilé");
    }

    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUseProgram.xhtml

    // TODO Vérifier erreur GL
    open_gl::useProgram(id_);
    // TODO Vérifier erreur GL
}

void gl_engine::ShaderProgram::attachShader( Shader shader ) {
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
    auto& modifiedShader = vertex_;

    switch (interface::Shader_Program::getType(shader).get()) {
        case Shader_t::VERTEX.get() :
            modifiedShader = vertex_;
            break;

        case Shader_t::FRAGMENT.get() :
            modifiedShader = fragment_;
            break;

        case Shader_t::GEOMETRY.get() :
            modifiedShader = geometry_;
            break;

        default:
            throw std::logic_error("Erreur : impossible que cela puisse arriver le type est inconnu");
    }

    // Vérifie que le shader a modifié n'est pas présent
    if ( modifiedShader.has_value() ) {
        throw std::logic_error("Impossible d'assigner le shader, un shader déjà existant est présent, s'il vous plait détacher le shader précédent");
    }

    modifiedShader = std::move(shader);

    open_gl::attachShader(id_, interface::Shader_Program::getId(modifiedShader) );
    // TODO checker les erreurs ( shader déjà attacher)

    compile();
}

void gl_engine::ShaderProgram::attachShader( std::initializer_list<Shader> shaders ) {
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
    if ( shaders.size() > 3 ) {
        throw std::invalid_argument("Impossible d'ajouter plus que 3 shaders à un programme");
    }

    for ( auto shader : shaders ) {
        auto& modifiedShader = vertex_;

        switch (interface::Shader_Program::getType(shader).get()) {
            case Shader_t::VERTEX.get() :
                modifiedShader = vertex_;
                break;

            case Shader_t::FRAGMENT.get() :
                modifiedShader = fragment_;
                break;

            case Shader_t::GEOMETRY.get() :
                modifiedShader = geometry_;
                break;

            default:
                throw std::logic_error("Erreur : impossible que cela puisse arriver le type est inconnu");
        }

        // Vérifie que le shader a modifié n'est pas présent
        if ( modifiedShader.has_value() ) {
            throw std::logic_error("Impossible d'assigner le shader, un shader déjà existant est présent, s'il vous plait détacher le shader précédent");
        }

        modifiedShader = std::move(shader);

        open_gl::attachShader(id_, interface::Shader_Program::getId(modifiedShader) );
    }

    // TODO checker les erreurs ( shader déjà attacher)

    compile();
}

void gl_engine::ShaderProgram::detachShader() {
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDetachShader.xhtml
    // TODO Vérifier GL
    vertex_.reset();
    fragment_.reset();
    geometry_.reset();

    // Vérifier erreurs finales
}

void gl_engine::ShaderProgram::detachShader( const Shader_t type ) {
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDetachShader.xhtml
    // TODO Vérifier GL
    switch ( type.get() ) {
        case Shader_t::VERTEX.get()     : vertex_.reset(); break;
        case Shader_t::FRAGMENT.get()   : fragment_.reset(); break;
        case Shader_t::GEOMETRY.get()   : geometry_.reset(); break;

        default :
            throw std::logic_error("Impossible d'arriver ici : erreur interne dans les valeurs de types");
    }

    // Vérifier erreurs finales
}

void gl_engine::ShaderProgram::compile() {
    // TODO Déterminer comment gérer un programme non compilé en cas d'exception
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
    open_gl::linkProgram(id_);

    // TODO Checker les erreurs

    compiled_ = true;
}

template<typename T>
void gl_engine::ShaderProgram::setUniform( std::string name, T value ) {
    throw std::runtime_error("Do nothing");
}
