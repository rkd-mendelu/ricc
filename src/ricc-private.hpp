#pragma once

#include <iostream>

#include "syntax/Syntax.hpp"

namespace RICC {

    class ParserPrivate {
        public:
            ParserPrivate(std::istream& stream);
            void Run();
        private:
            Syntax _syntax;
    };

}
