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

#ifndef GLENGINE_EXCEPTION_HPP
#define GLENGINE_EXCEPTION_HPP

#include <stdexcept>

namespace gl_engine {
    // Exceptions
    using app_already_exists = std::logic_error;

    using appWindow_already_exists = std::logic_error;

class Exception : public std::exception {
public:
    Exception( const std::string& what_arg )
    : std::exception(), what_arg_(what_arg) {}

    const char* what() const noexcept override { return what_arg_.c_str(); }

private:
    std::string what_arg_;
};

class IOException : public Exception {
public:
    explicit IOException( const std::string& what_arg )
    : Exception(what_arg) {}
};

class InvalidArgument : public Exception {
public:
    InvalidArgument( const std::string& what_arg )
    : Exception(what_arg) {}

    InvalidArgument( const char* what_arg );
};

class LogicError : public Exception {
public:
    LogicError( const std::string& what_arg )
    : Exception(what_arg) {}
};

class RuntimeError : public Exception {
public:
    RuntimeError( const std::string& what_arg )
    : Exception(what_arg) {}
};

}

#endif // GLENGINE_EXCEPTION_HPP
