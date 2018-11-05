/**
 * Lex test 4 - methods, other token types
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
    std::string inputProgram ("int i = 10; float f = 50.5; bool function(int param1, float param2); struct.member; cout << i;");
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
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::KW_INT,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::COMMA,
            TPJparser::Token::KW_FLOAT,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::KW_STRUCT,
            TPJparser::Token::DOT,
            TPJparser::Token::IDENTIFIER,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::KW_COUT,
            TPJparser::Token::OUTPUT,
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
