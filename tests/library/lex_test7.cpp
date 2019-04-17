/**
 * Strings
 */

#include <iostream>
#include <lex/Lex.hpp>
#include <sstream>

#include "ricc-parser.hpp"

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
      "\"string bla bla bla\"; string _string = \'test         string\'");
  std::istringstream stream(inputProgram);
  RICC::Lex lex(stream);

  /**
   * EDIT EXPECTED RESULTS HERE
   */
  RICC::Token::tokenType expectedResult[] = {
      RICC::Token::STRING,     RICC::Token::SEMICOLON,  RICC::Token::KW_STRING,
      RICC::Token::IDENTIFIER, RICC::Token::ASSIGNMENT, RICC::Token::STRING,
      RICC::Token::END_TOKEN,
  };

  std::map<int, std::string> expectedValues = {
      {0, "string bla bla bla"},
      {3, "_string"},
      {5, "test         string"},
  };

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
