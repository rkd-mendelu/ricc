#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <iostream>

#include "lex/Lex.hpp"

namespace TPJparser {

    class Syntax {
        public:
            Syntax(std::istream& stream);
        private:
            Lex _lex;
    };
}

#endif