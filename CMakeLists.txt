cmake_minimum_required( VERSION 2.6 )
cmake_policy(SET CMP0048 NEW)


project(
    RICC
    VERSION 0.0.1
)


include_directories( ${PROJECT_SOURCE_DIR}/include )
include_directories( ${PROJECT_SOURCE_DIR}/third_party/json/single_include )
include_directories( ${PROJECT_SOURCE_DIR}/third_party/curlpp/include )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(
    CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/CMakeModules/"
)

set(
    CMAKE_CXX_FLAGS_DEBUG
    "-g -Wall -Wextra -pedantic -O0 -DDEBUG_MODE"
)

set(
    CMAKE_CXX_FLAGS_RELEASE
    "-Wall -Wextra -pedantic -O2"
)

set(
    CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'"
)

set(
    EXECUTABLE_OUTPUT_PATH
    ${CMAKE_BINARY_DIR}/bin
)

install(
    FILES
    ${PROJECT_SOURCE_DIR}/include/ricc-parser.hpp
    DESTINATION
    include
)

add_custom_target(
    uninstall
    cat install_manifest.txt | xargs rm
)


add_subdirectory(third_party)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
