/**
 * Keywords
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
    std::string inputProgram ("int bool float void string if else return switch case default break continue class private protected public struct cout true false while ");
    std::istringstream stream(inputProgram);
    TPJparser::Lex lex(stream);

    /**
     * EDIT EXPECTED RESULTS HERE
     */
    TPJparser::Token::tokenType expectedResult[] = {
            TPJparser::Token::KW_INT,
            TPJparser::Token::KW_BOOL,
            TPJparser::Token::KW_FLOAT,
            TPJparser::Token::KW_VOID,
            TPJparser::Token::KW_STRING,
            TPJparser::Token::KW_IF,
            TPJparser::Token::KW_ELSE,
            TPJparser::Token::KW_RETURN,
            TPJparser::Token::KW_SWITCH,
            TPJparser::Token::KW_CASE,
            TPJparser::Token::KW_DEFAULT,
            TPJparser::Token::KW_BREAK,
            TPJparser::Token::KW_CONTINUE,
            TPJparser::Token::KW_CLASS,
            TPJparser::Token::KW_PRIVATE,
            TPJparser::Token::KW_PROTECTED,
            TPJparser::Token::KW_PUBLIC,
            TPJparser::Token::KW_STRUCT,
            TPJparser::Token::KW_COUT,
            TPJparser::Token::KW_TRUE,
            TPJparser::Token::KW_FALSE,
            TPJparser::Token::KW_WHILE,
            TPJparser::Token::END_TOKEN,
    };

    std::map<int, std::string> expectedValues = {
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
