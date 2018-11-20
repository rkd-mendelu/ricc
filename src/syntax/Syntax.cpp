#include <iostream>

#include "Syntax.hpp"

#include "util/Logger.hpp"

namespace TPJparser {
    Syntax::Syntax(std::istream& stream)
     : _lex(stream) {
        DEBUG("");
    }
}