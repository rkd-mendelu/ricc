set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)

set(
    CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-pedantic"
)

set(
    CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-pedantic"
)

add_subdirectory(curlpp)
