cmake_minimum_required( VERSION 2.6 )

project( TPJ )

include_directories( ${PROJECT_SOURCE_DIR}/include )
include_directories( ${PROJECT_SOURCE_DIR}/src )

set(
    CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/CMakeModules/"
)

set(
    CMAKE_CXX_FLAGS
    "-std=c++11 -g -Wall -Wextra -pedantic -O2"
)

set(
    EXECUTABLE_OUTPUT_PATH
    ${CMAKE_BINARY_DIR}/bin
)

install(
    FILES
    ${PROJECT_SOURCE_DIR}/include/tpj-parser.hpp
    DESTINATION
    include
)

add_custom_target(
    uninstall
    cat install_manifest.txt | xargs rm
)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
