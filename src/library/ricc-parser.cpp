#include <iostream>
#include <memory>

#include "ricc-parser-private.hpp"
#include "ricc/ricc-parser.hpp"

#include "util/MakeUnique.hpp"

#include "util/Logger.hpp"

namespace RICC {

Parser::Parser(std::istream& stream)
    : _d_pointer(RICC::make_unique<ParserPrivate>(stream)) {
  DEBUG("");
}

Parser::~Parser() = default;

int Parser::Parse() {
  DEBUG("");
  return _d_pointer->Parse();
}

int Parser::Run() {
  DEBUG("");
  return _d_pointer->Run();
}

int Parser::SetServerDetails(const std::string& url, const std::string& port) {
  DEBUG("");
  return _d_pointer->SetServerDetails(url, port);
}

}  // namespace RICC
