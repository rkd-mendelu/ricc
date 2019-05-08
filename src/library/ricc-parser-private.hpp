#pragma once

#include <iostream>

#include "syntax/Syntax.hpp"

namespace RICC {

class ParserPrivate {
 public:
  ParserPrivate(std::istream& stream);
  int Parse();
  int Run();

 private:
  Syntax _syntax;
};

}  // namespace RICC
