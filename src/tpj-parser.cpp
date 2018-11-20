#include <iostream>
#include <memory>

#include "tpj-parser.hpp"
#include "tpj-parser-private.hpp"

#include "util/MakeUnique.hpp"

#include "util/Logger.hpp"

namespace TPJparser {

	Parser::Parser(std::istream& stream)
	: _d_pointer(TPJparser::make_unique<ParserPrivate>(stream)) {
		DEBUG("");
	}

	Parser::~Parser() = default;

	void Parser::Run() {
		DEBUG("");
		_d_pointer->Run();
	}

}
