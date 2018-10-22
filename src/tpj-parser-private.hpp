#ifndef TPJ_PARSER_PRIVATE_HPP
#define TPJ_PARSER_PRIVATE_HPP

#include <iostream>

#include "util/ObjectPool.hpp"
#include "lex/Token.hpp"

namespace TPJparser {

    class ParserPrivate {
        public:
            ParserPrivate(std::istream &stream);
            void Run();

        private:
            std::istream &_stream;
            ObjectPool<Token> mypool;
    };

}

#endif