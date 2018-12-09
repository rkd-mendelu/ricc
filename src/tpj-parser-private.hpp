#pragma once

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
