#include <iostream>

#include "Syntax.hpp"

namespace TPJparser {
    Syntax::Syntax(std::istream& stream) : _lex(stream) {}
}