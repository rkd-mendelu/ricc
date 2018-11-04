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
    std::cout << token.getTokenTypeText(token.getTokenType());
    std::cout << " | Token text ";
    std::cout << token.getText() << std::endl;
}

int main()
{
    /**
     *  EDIT INPUT PROGRAM HERE
     */
    std::string inputProgram ("10 < 0; 555.5 == 555.5; 1!=2; 0> -5; c && a; d || b;");
    std::istringstream stream(inputProgram);
    TPJparser::Lex lex(stream);

    /**
     * EDIT EXPECTED RESULTS HERE
     */
    TPJparser::Token::tokenType expectedResult[] = {
            TPJparser::Token::INTEGER,
            TPJparser::Token::LESS,
            TPJparser::Token::INTEGER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::FLOAT,
            TPJparser::Token::EQUAL,
            TPJparser::Token::FLOAT,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::INTEGER,
            TPJparser::Token::NOT_EQUAL,
            TPJparser::Token::INTEGER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::INTEGER,
            TPJparser::Token::LARGE,
            TPJparser::Token::MINUS,
            TPJparser::Token::INTEGER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::AND,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::OR,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::END_TOKEN,
    };

    int i = 0;
    while(true) {
        TPJparser::Token token = lex.getToken();

        if(token.getTokenType() != expectedResult[i]) {
            printErrorMessage(token.getTokenTypeText(expectedResult[i]), token.getTokenTypeText(token.getTokenType()));
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
