#CMakeLists myProject
cmake_minimum_required( VERSION 3.0.2 )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

#CMAKE_BUILD_TYPE
if ( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug CACHE STRING
         "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."
         FORCE )
endif ()

# The project version number.
set( VERSION_MAJOR 0 CACHE STRING "Project major version number." )
set( VERSION_MINOR 1 CACHE STRING "Project minor version number." )
set( VERSION_PATCH 0 CACHE STRING "Project patch version number." )
mark_as_advanced( VERSION_MAJOR VERSION_MINOR VERSION_PATCH )

# Configuration du projet
project( baseGL )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra" )
set( CMAKE_CXX_STANDARD "17" )

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    # GLX <-> Utilisation du serveur X pour le rendu
    # LEGACY <-> Utilisation Driver OpenGL
    # https://en.wikipedia.org/wiki/GLX#:~:text=GLX%20(initialism%20for%20%22OpenGL%20Extension,by%20the%20X%20Window%20System.
    # https://softwareengineering.stackexchange.com/questions/164997/what-is-the-relationship-between-opengl-glx-dri-and-mesa3d
    set( OpenGL_GL_PREFERENCE "GLVND" )
endif ()


## Lib dependency
# OpenGL
find_package( OpenGL REQUIRED )

# stb_image
add_subdirectory( stbimage )
include_directories(
        stbimage/include/
)

# GLAD
add_subdirectory( glad )
include_directories(
        glad/include/
)

# GLFW
add_subdirectory( glfw-3.3.6 )
include_directories(
        glfw-3.3.6/include/
)

# GLM
add_subdirectory( glm-0.9.9.9/glm )
include_directories(
        glm-0.9.9.9
)

# imgui
add_subdirectory( imgui )
include_directories(
        imgui
)

add_subdirectory( glengine )
add_subdirectory( exosTP )
add_subdirectory( modules )
