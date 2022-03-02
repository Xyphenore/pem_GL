#include <unordered_map>

#include <GLFW/glfw3.h>

#include "utils.hpp"

std::string bidon::getCodeName( const bidon::GLFWErrorCode code ) {
    // SRC : https://www.glfw.org/docs/3.3/group__errors.html#gad44162d78100ea5e87cdd38426b8c7a1
    static const std::unordered_map<bidon::GLFWErrorCode, const std::string> glfwErrorCode( {
       { GLFW_NO_ERROR,            "GLFW_NO_ERROR" },
       { GLFW_NOT_INITIALIZED,     "GLFW_NOT_INITIALIZED" },
       { GLFW_NO_CURRENT_CONTEXT,  "GLFW_NO_CURRENT_CONTEXT" },
       { GLFW_INVALID_ENUM,        "GLFW_INVALID_ENUM" },
       { GLFW_INVALID_VALUE,       "GLFW_INVALID_VALUE" },
       { GLFW_OUT_OF_MEMORY,       "GLFW_OUT_OF_MEMORY" },
       { GLFW_API_UNAVAILABLE,     "GLFW_API_UNAVAILABLE" },
       { GLFW_VERSION_UNAVAILABLE, "GLFW_VERSION_UNAVAILABLE" },
       { GLFW_PLATFORM_ERROR,      "GLFW_PLATFORM_ERROR" },
       { GLFW_FORMAT_UNAVAILABLE,  "GLFW_FORMAT_UNAVAILABLE" },
       { GLFW_NO_WINDOW_CONTEXT,   "GLFW_NO_WINDOW_CONTEXT" }
   } );

    const auto itStr = glfwErrorCode.find(code);

    if ( itStr == glfwErrorCode.cend() ) {
        throw bidon::GLFWUnknownException("Le code d'erreur passé est inconnu");
    }

    return itStr->second;
}
