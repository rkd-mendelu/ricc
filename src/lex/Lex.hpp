#ifndef LEX_HPP
#define LEX_HPP

#include <iostream>

#include "util/ObjectPool.hpp"
#include "lex/Token.hpp"

namespace TPJparser {

    class Lex {
        public:
            Lex(std::istream& stream);
            Token& getToken();
            void ungetToken(Token& t);

        private:
            std::istream& _stream;
            ObjectPool<Token> tokenPool;
    };
}

#endif