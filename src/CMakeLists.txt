include_directories( $(CMAKE_PROJECT_DIR)/src )

set( LIB_SOURCES tpj-parser.cpp util/slab.cpp )

add_library( tpj-shared SHARED ${LIB_SOURCES} )
add_library( tpj-static STATIC ${LIB_SOURCES} )
