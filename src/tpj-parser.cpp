#include <iostream>
#include <memory>

#include "tpj-parser.hpp"
#include "tpj-parser-private.hpp"

#include "util/MakeUnique.hpp"

namespace TPJparser {

	Parser::Parser(std::istream& stream)
	: _d_pointer(TPJparser::make_unique<ParserPrivate>(stream)) {}

	Parser::~Parser() = default;

	void Parser::Run() {
		_d_pointer->Run();
	}

}
