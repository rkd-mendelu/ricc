/**
 * Strings
 */

#include <iostream>
#include <sstream>
#include <lex/Lex.hpp>

#include "tpj-parser.hpp"

void printErrorMessage(std::string expected, std::string got, bool unexpectedValue = false) {
    std::cerr << "Expected ";
    if(unexpectedValue) {
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

void printTokenInfo(TPJparser::Token& token) {
    std::cout << "Token type ";
    std::cout << token.getTokenTypeText();
    if ( token.getText().length() > 0) {
        std::cout << " | Token text ";
        std::cout << token.getText();
    }
    std::cout << std::endl;
}

int main()
{
    /**
     *  EDIT INPUT PROGRAM HERE
     */
    std::string inputProgram ("\"string bla bla bla\"; string _string = \'test         string\'");
    std::istringstream stream(inputProgram);
    TPJparser::Lex lex(stream);

    /**
     * EDIT EXPECTED RESULTS HERE
     */
    TPJparser::Token::tokenType expectedResult[] = {
            TPJparser::Token::STRING,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::KW_STRING,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::STRING,
            TPJparser::Token::END_TOKEN,
    };

    std::map<int, std::string> expectedValues = {
            {0, "string bla bla bla"},
            {3, "_string"},
            {5, "test         string"},
    };

    int i = 0;
    while(true) {
        TPJparser::Token token = lex.getToken();

        if(token.getTokenType() != expectedResult[i]) {
            printErrorMessage(TPJparser::Token::getTokenTypeByText(expectedResult[i]), token.getTokenTypeText());
            return 1;
        }

        if(expectedValues.find(i) != expectedValues.end()) {
            if(token.getText() != expectedValues.at(i)) {
                printErrorMessage(expectedValues.at(i), token.getText(), true);
                return 1;
            }
        }

        printTokenInfo(token);

        if(token.getTokenType() == TPJparser::Token::END_TOKEN) {
            break;
        }
        i++;
    };

    printSuccessMessage();
    return 0;
}
