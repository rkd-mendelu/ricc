#pragma once

#include <iostream>

#include "syntax/Syntax.hpp"

namespace RICC {

class ParserPrivate {
 public:
  ParserPrivate(std::istream& stream);
  int Parse();
  int Run();
  int SetServerDetails(const std::string& url, const std::string& port);

 private:
  Syntax _syntax;
};

}  // namespace RICC
