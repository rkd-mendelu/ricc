/**
 * Token values
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
    std::cout << token.getTokenTypeText(token.getTokenType());
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
    std::string inputProgram ("int i = 10; float fff = 10.5; bool boolVar=true;");
    std::istringstream stream(inputProgram);
    TPJparser::Lex lex(stream);

    /**
     * EDIT EXPECTED RESULTS HERE
     */
    TPJparser::Token::tokenType expectedResult[] = {
            TPJparser::Token::KW_INT,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::INTEGER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::KW_FLOAT,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::FLOAT,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::KW_BOOL,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::KW_TRUE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::END_TOKEN,
    };

    std::map<int, std::string> expectedValues = {
            {1, "i"},
            {3, "10"},
            {6, "fff"},
            {8, "10.5"},
            {11, "boolVar"},
            {11, "true"},
    };

    int i = 0;
    while(true) {
        TPJparser::Token token = lex.getToken();

        if(token.getTokenType() != expectedResult[i]) {
            printErrorMessage(token.getTokenTypeText(expectedResult[i]), token.getTokenTypeText(token.getTokenType()));
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
