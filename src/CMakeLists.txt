set(
    LIB_SOURCES
    tpj-parser.cpp
    ../include/tpj-parser.hpp
    tpj-parser-private.cpp
    tpj-parser-private.hpp
    util/ObjectPool.hpp
    lex/Token.cpp
    lex/Token.hpp
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
