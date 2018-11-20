#include <iostream>

#include "tpj-parser-private.hpp"
#include "syntax/Syntax.hpp"

#include "util/Logger.hpp"

namespace TPJparser {

	ParserPrivate::ParserPrivate(std::istream& stream)
	 : _syntax(stream) {
		DEBUG("");
	 }

	void ParserPrivate::Run() {
		DEBUG("");
	}

}