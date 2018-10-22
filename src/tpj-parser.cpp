#include <iostream>
#include <memory>

#include "tpj-parser.hpp"
#include "tpj-parser-private.hpp"

namespace TPJparser {

	Parser::Parser(std::istream &stream)
	: _d_pointer(std::make_unique<ParserPrivate>(stream)) {}

	Parser::~Parser() = default;

	void Parser::Run() {
		_d_pointer->Run();
	}

}
