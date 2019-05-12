#include <iostream>

#include "ricc-parser-private.hpp"
#include "syntax/Syntax.hpp"

#include "util/Logger.hpp"

namespace RICC {

ParserPrivate::ParserPrivate(std::istream& stream) : _syntax(stream) {
  DEBUG("");
}

int ParserPrivate::Parse() {
  DEBUG("");
  return _syntax.Parse();
}

int ParserPrivate::Run() {
  DEBUG("");
  return _syntax.Run();
}

int ParserPrivate::SetServerDetails(const std::string& url,
                                    const std::string& port) {
  DEBUG("");
  return _syntax.getIntepreter().setHTTPSettings(url, port);
}
}  // namespace RICC
