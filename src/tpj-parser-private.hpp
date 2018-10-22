#ifndef TPJ_PARSER_PRIVATE_HPP
#define TPJ_PARSER_PRIVATE_HPP

#include <iostream>

#include "syntax/Syntax.hpp"

namespace TPJparser {

    class ParserPrivate {
        public:
            ParserPrivate(std::istream& stream);
            void Run();
        private:
            Syntax _syntax;
    };

}

#endif