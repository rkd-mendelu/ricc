set(
    LIB_SOURCES
    tpj-parser.cpp
    ../include/tpj-parser.hpp
    tpj-parser-private.cpp
    tpj-parser-private.hpp
    lex/Token.cpp
    lex/Token.hpp
    lex/Lex.cpp
    lex/Lex.hpp
    syntax/Syntax.cpp
    syntax/Syntax.hpp
    util/ObjectPool.hpp
)

add_library(
    tpj-shared
    SHARED
    ${LIB_SOURCES}
)

add_library(
    tpj-static
    STATIC
    ${LIB_SOURCES}
)

install(
    TARGETS
    tpj-shared
    DESTINATION
    lib64
)
