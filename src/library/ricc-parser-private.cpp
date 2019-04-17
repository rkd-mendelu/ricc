#include <iostream>

#include "ricc-parser-private.hpp"
#include "syntax/Syntax.hpp"

#include "util/Logger.hpp"

namespace RICC {

	ParserPrivate::ParserPrivate(std::istream& stream)
	 : _syntax(stream) {
		DEBUG("");
	 }

	void ParserPrivate::Run() {
		DEBUG("");
	}

}