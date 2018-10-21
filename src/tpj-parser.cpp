#include <iostream>

#include "tpj-parser.hpp"

namespace TPJparser {

	Parser::Parser(std::istream &stream) : _stream(stream) {
		std::cout << "Parser constructor" << std::endl;
	}

	void Parser::Run() {
		std::cout << "Run" << std::endl;
	}

}
