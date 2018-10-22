#include <iostream>

#include "tpj-parser-private.hpp"

#include "util/ObjectPool.hpp"
#include "lex/Token.hpp"

namespace TPJparser {

	ParserPrivate::ParserPrivate(std::istream &stream) : _stream(stream) {}

	void ParserPrivate::Run() {}

}