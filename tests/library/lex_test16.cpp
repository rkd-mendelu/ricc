#include <iostream>
#include <lex/Lex.hpp>
#include <sstream>

#include "ricc-parser.hpp"

int main() {
  /**
   *  EDIT INPUT PROGRAM HERE
   */
  std::string inputProgram(")");
  std::istringstream stream(inputProgram);
  RICC::Lex lex(stream);

  RICC::Token token = lex.getToken();

  if (token.getText() != ")") {
    std::cout << token.getText() << " != "
              << ")" << std::endl;
    return 1;
  }

  return 0;
}
