include_directories( ${PROJECT_SOURCE_DIR}/src/library )

set(
    LIB_SOURCES
    ${RICC_PUBLIC_HEADER}
    ricc-parser.cpp
    ricc-parser-private.cpp
    ricc-parser-private.hpp
    lex/Token.cpp
    lex/Token.hpp
    lex/Lex.cpp
    lex/Lex.hpp
    interpret/Interpret.cpp
    interpret/Interpret.hpp
    interpret/http/HTTP.cpp
    interpret/http/HTTP.hpp
    interpret/objects/Object.cpp
    interpret/objects/Object.hpp
    interpret/objects/Train.cpp
    interpret/objects/Train.hpp
    semantic/Semantic.cpp
    semantic/Semantic.hpp
    semantic/SymbolTable.cpp
    semantic/SymbolTable.hpp
    semantic/SymbolTableItem.cpp
    semantic/SymbolTableItem.hpp
    syntax/PredefinedFuncs.cpp
    syntax/Syntax.cpp
    syntax/Syntax.hpp
    util/Logger.hpp
    util/ObjectPool.hpp
)

add_library(
    ricc-shared
    SHARED
    ${LIB_SOURCES}
)

add_library(
    ricc-static
    STATIC
    ${LIB_SOURCES}
)

target_link_libraries(
    ricc-shared
    curlpp
)

target_link_libraries(
    ricc-static
    curlpp_static
)

install(
    TARGETS
    ricc-shared
    DESTINATION
    lib64
)
