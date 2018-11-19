/**
 * Math operations test
 */

#include <iostream>
#include <sstream>
#include <lex/Lex.hpp>

#include "tpj-parser.hpp"

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
    std::string inputProgram ("10+10; 0-5; 10/5; 5*5;");
    std::istringstream stream(inputProgram);
    TPJparser::Lex lex(stream);

    /**
     * EDIT EXPECTED RESULTS HERE
     */
    TPJparser::Token::tokenType expectedResult[] = {
            TPJparser::Token::INTEGER,
            TPJparser::Token::PLUS,
            TPJparser::Token::INTEGER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::INTEGER,
            TPJparser::Token::MINUS,
            TPJparser::Token::INTEGER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::INTEGER,
            TPJparser::Token::DIV,
            TPJparser::Token::INTEGER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::INTEGER,
            TPJparser::Token::MULTI,
            TPJparser::Token::INTEGER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::END_TOKEN,
    };

    int i = 0;
    while(true) {
        TPJparser::Token token = lex.getToken();

        if(token.getTokenType() != expectedResult[i]) {
            printErrorMessage(TPJparser::Token::getTokenTypeByText(expectedResult[i]), token.getTokenTypeText());
            return 1;
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
