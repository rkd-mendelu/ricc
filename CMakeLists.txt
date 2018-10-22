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
    "-std=c++14 -g -Wall -Wextra -pedantic -O2"
)

SET(
    EXECUTABLE_OUTPUT_PATH
    ${CMAKE_BINARY_DIR}/bin
)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
