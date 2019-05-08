/**
 * Keywords
 */

#include <iostream>
#include <lex/Lex.hpp>
#include <sstream>

#include "ricc/ricc-parser.hpp"

void printErrorMessage(std::string expected, std::string got,
                       bool unexpectedValue = false) {
  std::cerr << "Expected ";
  if (unexpectedValue) {
    std::cerr << "value ";
  }
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
      "int bool float void string if else return switch case default break "
      "continue class private protected public struct cout true false while ");
  std::istringstream stream(inputProgram);
  RICC::Lex lex(stream);

  /**
   * EDIT EXPECTED RESULTS HERE
   */
  RICC::Token::tokenType expectedResult[] = {
      RICC::Token::KW_INT,      RICC::Token::KW_BOOL,
      RICC::Token::KW_FLOAT,    RICC::Token::KW_VOID,
      RICC::Token::KW_STRING,   RICC::Token::KW_IF,
      RICC::Token::KW_ELSE,     RICC::Token::KW_RETURN,
      RICC::Token::KW_SWITCH,   RICC::Token::KW_CASE,
      RICC::Token::KW_DEFAULT,  RICC::Token::KW_BREAK,
      RICC::Token::KW_CONTINUE, RICC::Token::KW_CLASS,
      RICC::Token::KW_PRIVATE,  RICC::Token::KW_PROTECTED,
      RICC::Token::KW_PUBLIC,   RICC::Token::KW_STRUCT,
      RICC::Token::KW_COUT,     RICC::Token::BOOL,
      RICC::Token::BOOL,        RICC::Token::KW_WHILE,
      RICC::Token::END_TOKEN,
  };

  std::map<int, std::string> expectedValues = {};

  int i = 0;
  while (true) {
    RICC::Token token = lex.getToken();

    if (token.getTokenType() != expectedResult[i]) {
      printErrorMessage(RICC::Token::getTokenTypeByText(expectedResult[i]),
                        token.getTokenTypeText());
      return 1;
    }

    if (expectedValues.find(i) != expectedValues.end()) {
      if (token.getText() != expectedValues.at(i)) {
        printErrorMessage(expectedValues.at(i), token.getText(), true);
        return 1;
      }
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
