#include <iostream>

#include "tpj-parser-private.hpp"
#include "syntax/Syntax.hpp"

namespace TPJparser {

	ParserPrivate::ParserPrivate(std::istream& stream) : _syntax(stream) {}

	void ParserPrivate::Run() {}

}