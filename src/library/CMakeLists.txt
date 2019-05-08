include_directories( ${PROJECT_SOURCE_DIR}/src/library )

set(
    LIB_SOURCES
    ricc-parser.cpp
    ${RICC_PUBLIC_HEADER}
    ricc-parser-private.cpp
    ricc-parser-private.hpp
    lex/Token.cpp
    lex/Token.hpp
    lex/Lex.cpp
    lex/Lex.hpp
    interpret/Interpret.cpp
    interpret/Interpret.hpp
    semantic/Semantic.cpp
    semantic/Semantic.hpp
    semantic/SymbolTable.cpp
    semantic/SymbolTable.hpp
    semantic/SymbolTableItem.cpp
    semantic/SymbolTableItem.hpp
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

install(
    TARGETS
    ricc-shared
    DESTINATION
    lib64
)
