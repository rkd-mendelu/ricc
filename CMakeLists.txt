cmake_minimum_required(VERSION 2.6)

project(TPJ)

include_directories($(CMAKE_PROJECT_DIR)/include)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Wextra -pedantic -O2")
set(CMAKE_SOURCE_DIR $(CMAKE_PROJECT_DIR)/src )
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

enable_testing()

add_subdirectory(src)
#add_subdirectory(utils)
add_subdirectory(tests)
