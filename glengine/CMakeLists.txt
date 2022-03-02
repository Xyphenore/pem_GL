project( glengine )

cmake_minimum_required( VERSION 3.0.2 )

set( RESOURCES_DIRECTORY "${PROJECT_SOURCE_DIR}/resources/" )
set( SRC_DIR "${PROJECT_SOURCE_DIR}/src" )
set( INC_DIR "${PROJECT_SOURCE_DIR}/include/" )

#Configure config.hpp.in
configure_file(
        ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.hpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/config.hpp @ONLY
)

include_directories( ${CMAKE_CURRENT_BINARY_DIR}/include BEFORE )

set( SRC
     ${SRC_DIR}/glengine.cpp
     ${SRC_DIR}/shader.cpp
     ${SRC_DIR}/shaderProgram.cpp
     ${SRC_DIR}/window.cpp
     ${SRC_DIR}/utility.cpp
     ${SRC_DIR}/utils.cpp
     ${SRC_DIR}/glEnum2String.cpp
     ${SRC_DIR}/app.cpp
     )

set( HEADER
     # ${INC_DIR}/${PROJECT_NAME}/config.hpp.in
     ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.hpp.in
     ${INC_DIR}/${PROJECT_NAME}/glengine.hpp
     ${INC_DIR}/${PROJECT_NAME}/shader.hpp
     ${INC_DIR}/${PROJECT_NAME}/shaderProgram.hpp
     ${INC_DIR}/${PROJECT_NAME}/window.hpp
     ${INC_DIR}/${PROJECT_NAME}/utility.hpp
     ${INC_DIR}/${PROJECT_NAME}/utils.hpp
     ${INC_DIR}/${PROJECT_NAME}/app.hpp
     ${INC_DIR}/${PROJECT_NAME}/glfw.hpp
     ${INC_DIR}/${PROJECT_NAME}/glfw_exception.hpp
     )


add_library( ${PROJECT_NAME} ${SRC} ${HEADER} )
target_include_directories( ${PROJECT_NAME}
                            PUBLIC ${INC_DIR}
                            )

install(
        TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_subdirectory( doc )
