set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)
set(
    CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic"
)
add_subdirectory(curlpp)
