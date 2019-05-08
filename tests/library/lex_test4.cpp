/**
 * Lex test 4 - methods, other token types
 */

#include <iostream>
#include <lex/Lex.hpp>
#include <sstream>

#include "ricc/ricc-parser.hpp"

void printErrorMessage(std::string expected, std::string got) {
  std::cerr << "Expected ";
  std::cerr << expected;
  std::cerr << " got ";
  std::cerr << got;

  std::cerr << std::endl;
  std::cerr << "======================" << std::endl;
  std::cerr << "Test failed" << std::endl;
  std::cerr << "======================" << std::endl;
}

void printSuccessMessage() {
  std::cout << std::endl;
  std::cout << "======================" << std::endl;
  std::cout << "Test passed" << std::endl;
  std::cout << "======================" << std::endl;
}

void printTokenInfo(RICC::Token& token) {
  std::cout << "Token type ";
  std::cout << token.getTokenTypeText();
  if (token.getText().length() > 0) {
    std::cout << " | Token text ";
    std::cout << token.getText();
  }
  std::cout << std::endl;
}

int main() {
  /**
   *  EDIT INPUT PROGRAM HERE
   */
  std::string inputProgram(
      "int i = 10; float f = 50.5; bool function(int param1, float param2); "
      "struct.member; cout << i; name->id;");
  std::istringstream stream(inputProgram);
  RICC::Lex lex(stream);

  /**
   * EDIT EXPECTED RESULTS HERE
   */
  RICC::Token::tokenType expectedResult[] = {
      RICC::Token::KW_INT,
      RICC::Token::IDENTIFIER,
      RICC::Token::ASSIGNMENT,
      RICC::Token::INTEGER,
      RICC::Token::SEMICOLON,
      RICC::Token::KW_FLOAT,
      RICC::Token::IDENTIFIER,
      RICC::Token::ASSIGNMENT,
      RICC::Token::FLOAT,
      RICC::Token::SEMICOLON,
      RICC::Token::KW_BOOL,
      RICC::Token::IDENTIFIER,
      RICC::Token::BRACKET_ROUND_OPEN,
      RICC::Token::KW_INT,
      RICC::Token::IDENTIFIER,
      RICC::Token::COMMA,
      RICC::Token::KW_FLOAT,
      RICC::Token::IDENTIFIER,
      RICC::Token::BRACKET_ROUND_CLOSE,
      RICC::Token::SEMICOLON,
      RICC::Token::KW_STRUCT,
      RICC::Token::DOT,
      RICC::Token::IDENTIFIER,
      RICC::Token::SEMICOLON,
      RICC::Token::KW_COUT,
      RICC::Token::OUTPUT,
      RICC::Token::IDENTIFIER,
      RICC::Token::SEMICOLON,
      RICC::Token::IDENTIFIER,
      RICC::Token::POINTER,
      RICC::Token::IDENTIFIER,
      RICC::Token::SEMICOLON,
      RICC::Token::END_TOKEN,
  };

  int i = 0;
  while (true) {
    RICC::Token token = lex.getToken();

    if (token.getTokenType() != expectedResult[i]) {
      printErrorMessage(RICC::Token::getTokenTypeByText(expectedResult[i]),
                        token.getTokenTypeText());
      return 1;
    }

    printTokenInfo(token);

    if (token.getTokenType() == RICC::Token::END_TOKEN) {
      break;
    }
    i++;
  };

  printSuccessMessage();
  return 0;
}
