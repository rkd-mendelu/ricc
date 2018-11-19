/**
 * Whole source code
 */

#include <iostream>
#include <sstream>
#include <lex/Lex.hpp>
#include <fstream>

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
    std::ifstream stream;
    std::string line;
    stream.open("../../tests/example_source_codes/example1.txt");

    TPJparser::Lex lex(stream);

    /**
     * EDIT EXPECTED RESULTS HERE
     */
    TPJparser::Token::tokenType expectedResult[] = {
            TPJparser::Token::KW_INT,
            TPJparser::Token::IDENTIFIER, //1
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::BRACKET_CURLY_OPEN,
            TPJparser::Token::IDENTIFIER, //5
            TPJparser::Token::IDENTIFIER, //6
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //8
            TPJparser::Token::IDENTIFIER, //9
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //11
            TPJparser::Token::IDENTIFIER, //12
            TPJparser::Token::COMMA,
            TPJparser::Token::IDENTIFIER, //14
            TPJparser::Token::COMMA,
            TPJparser::Token::IDENTIFIER, //16
            TPJparser::Token::COMMA,
            TPJparser::Token::IDENTIFIER, //18
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //20
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::KW_NEW,
            TPJparser::Token::IDENTIFIER, //23
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::STRING, //25
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //28
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::KW_NEW,
            TPJparser::Token::IDENTIFIER, //31
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::STRING, //33
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //36
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::KW_NEW,
            TPJparser::Token::IDENTIFIER, //39
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::STRING, //41
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //44
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::KW_NEW,
            TPJparser::Token::IDENTIFIER, //47
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::STRING, //49
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //52
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::KW_NEW,
            TPJparser::Token::IDENTIFIER, //55
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //57
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //59
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::INTEGER, //61
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //64
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //66
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::INTEGER, //68
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //71
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //73
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::INTEGER, //75
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //78
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //80
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::INTEGER, //82
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //85
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //87
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::INTEGER, //89
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //92
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //94
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::STRING, //96
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::KW_IF,
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::IDENTIFIER, //101
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //103
            TPJparser::Token::EQUAL,
            TPJparser::Token::STRING, //105
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::BRACKET_CURLY_OPEN,
            TPJparser::Token::IDENTIFIER, //108
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //110
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::BRACKET_CURLY_CLOSE,
            TPJparser::Token::IDENTIFIER, //115
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::KW_NEW,
            TPJparser::Token::IDENTIFIER, //118
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::STRING, //120
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //123
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //125
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::KW_FOR,
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::KW_INT,
            TPJparser::Token::IDENTIFIER, //132
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::INTEGER, //134
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //136
            TPJparser::Token::LESS_OR_EQUAL,
            TPJparser::Token::INTEGER, //138
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //140
            TPJparser::Token::ASSIGNMENT,
            TPJparser::Token::IDENTIFIER, //142
            TPJparser::Token::PLUS,
            TPJparser::Token::INTEGER, //144
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::BRACKET_CURLY_OPEN,
            TPJparser::Token::IDENTIFIER, //147
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //149
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::IDENTIFIER, //151
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::IDENTIFIER, //154
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::INTEGER, //156
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::BRACKET_CURLY_CLOSE,
            TPJparser::Token::KW_WHILE,
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::EXCLAMATION,
            TPJparser::Token::IDENTIFIER, //163
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //165
            TPJparser::Token::BRACKET_SQUARE_OPEN,
            TPJparser::Token::INTEGER, //167
            TPJparser::Token::BRACKET_SQUARE_CLOSE,
            TPJparser::Token::DOT,
            TPJparser::Token::IDENTIFIER, //170
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::BRACKET_CURLY_OPEN,
            TPJparser::Token::IDENTIFIER, //173
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::INTEGER, //175
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::BRACKET_CURLY_CLOSE,
            TPJparser::Token::IDENTIFIER, //179
            TPJparser::Token::POINTER,
            TPJparser::Token::IDENTIFIER, //181
            TPJparser::Token::BRACKET_ROUND_OPEN,
            TPJparser::Token::INTEGER, //183
            TPJparser::Token::BRACKET_ROUND_CLOSE,
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::KW_RETURN,
            TPJparser::Token::INTEGER, //187
            TPJparser::Token::SEMICOLON,
            TPJparser::Token::BRACKET_CURLY_CLOSE,
            TPJparser::Token::END_TOKEN,
    };

    std::map<int, std::string> expectedValues = {
            {1, "main"},
            {5, "Engine"},
            {6, "L"},
            {8, "Track"},
            {9, "T"},
            {11, "Switch"},
            {12, "KuV1"},
            {14, "KuV2"},
            {16, "KuV5"},
            {18, "KuV6"},
            {18, "KuV1"},
            {23, "Switch"},
            {25, "Ku V1"},
            {28, "KuV2"},
            {31, "Switch"},
            {33, "Ku V2"},
            {36, "KuV5"},
            {39, "Switch"},
            {41, "Ku V5"},
            {44, "KuV6"},
            {47, "Switch"},
            {49, "Ku V6"},
            {52, "T"},
            {55, "Track"},
            {57, "T"},
            {59, "pridej"},
            {61, "345"},
            {64, "T"},
            {66, "pridej"},
            {68, "346"},
            {71, "T"},
            {73, "pridej"},
            {75, "347"},
            {78, "T"},
            {80, "pridej"},
            {82, "348"},
            {85, "T"},
            {87, "pridej"},
            {89, "349"},
            {92, "KuV1"},
            {94, "nastavpolohu"},
            {96, "+"},
            {101, "KuV2"},
            {103, "poloha"},
            {105, "-"},
            {108, "KuV2"},
            {110, "prehod"},
            {115, "L"},
            {118, "Engine"},
            {120, "Bardotka"},
            {123, "L"},
            {125, "zmensmer"},
            {132, "i"},
            {134, "1"},
            {136, "i"},
            {138, "14"},
            {140, "i"},
            {142, "i"},
            {144, "1"},
            {147, "L"},
            {149, "jed"},
            {151, "i"},
            {154, "cekej"},
            {156, "2"},
            {163, "T"},
            {165, "usek"},
            {167, "349"},
            {170, "jeobsazen"},
            {173, "cekej"},
            {175, "1"},
            {179, "L"},
            {181, "jed"},
            {183, "0"},
            {187, "0"},
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

    stream.close();
    return 0;
}
