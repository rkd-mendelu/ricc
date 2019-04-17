/**
 * Whole source code
 */

#include <iostream>
#include <sstream>
#include <lex/Lex.hpp>
#include <fstream>

#include "ricc-parser.hpp"

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

void printTokenInfo(RICC::Token& token) {
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

    RICC::Lex lex(stream);

    /**
     * EDIT EXPECTED RESULTS HERE
     */
    RICC::Token::tokenType expectedResult[] = {
            RICC::Token::KW_INT,
            RICC::Token::IDENTIFIER, //1
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::BRACKET_CURLY_OPEN,
            RICC::Token::IDENTIFIER, //5
            RICC::Token::IDENTIFIER, //6
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //8
            RICC::Token::IDENTIFIER, //9
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //11
            RICC::Token::IDENTIFIER, //12
            RICC::Token::COMMA,
            RICC::Token::IDENTIFIER, //14
            RICC::Token::COMMA,
            RICC::Token::IDENTIFIER, //16
            RICC::Token::COMMA,
            RICC::Token::IDENTIFIER, //18
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //20
            RICC::Token::ASSIGNMENT,
            RICC::Token::KW_NEW,
            RICC::Token::IDENTIFIER, //23
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::STRING, //25
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //28
            RICC::Token::ASSIGNMENT,
            RICC::Token::KW_NEW,
            RICC::Token::IDENTIFIER, //31
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::STRING, //33
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //36
            RICC::Token::ASSIGNMENT,
            RICC::Token::KW_NEW,
            RICC::Token::IDENTIFIER, //39
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::STRING, //41
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //44
            RICC::Token::ASSIGNMENT,
            RICC::Token::KW_NEW,
            RICC::Token::IDENTIFIER, //47
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::STRING, //49
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //52
            RICC::Token::ASSIGNMENT,
            RICC::Token::KW_NEW,
            RICC::Token::IDENTIFIER, //55
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //57
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //59
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::INTEGER, //61
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //64
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //66
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::INTEGER, //68
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //71
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //73
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::INTEGER, //75
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //78
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //80
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::INTEGER, //82
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //85
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //87
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::INTEGER, //89
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //92
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //94
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::STRING, //96
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::KW_IF,
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::IDENTIFIER, //101
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //103
            RICC::Token::EQUAL,
            RICC::Token::STRING, //105
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::BRACKET_CURLY_OPEN,
            RICC::Token::IDENTIFIER, //108
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //110
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::BRACKET_CURLY_CLOSE,
            RICC::Token::IDENTIFIER, //115
            RICC::Token::ASSIGNMENT,
            RICC::Token::KW_NEW,
            RICC::Token::IDENTIFIER, //118
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::STRING, //120
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //123
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //125
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::KW_FOR,
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::KW_INT,
            RICC::Token::IDENTIFIER, //132
            RICC::Token::ASSIGNMENT,
            RICC::Token::INTEGER, //134
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //136
            RICC::Token::LESS_OR_EQUAL,
            RICC::Token::INTEGER, //138
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //140
            RICC::Token::ASSIGNMENT,
            RICC::Token::IDENTIFIER, //142
            RICC::Token::PLUS,
            RICC::Token::INTEGER, //144
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::BRACKET_CURLY_OPEN,
            RICC::Token::IDENTIFIER, //147
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //149
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::IDENTIFIER, //151
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::IDENTIFIER, //154
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::INTEGER, //156
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::BRACKET_CURLY_CLOSE,
            RICC::Token::KW_WHILE,
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::EXCLAMATION,
            RICC::Token::IDENTIFIER, //163
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //165
            RICC::Token::BRACKET_SQUARE_OPEN,
            RICC::Token::INTEGER, //167
            RICC::Token::BRACKET_SQUARE_CLOSE,
            RICC::Token::DOT,
            RICC::Token::IDENTIFIER, //170
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::BRACKET_CURLY_OPEN,
            RICC::Token::IDENTIFIER, //173
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::INTEGER, //175
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::BRACKET_CURLY_CLOSE,
            RICC::Token::IDENTIFIER, //179
            RICC::Token::POINTER,
            RICC::Token::IDENTIFIER, //181
            RICC::Token::BRACKET_ROUND_OPEN,
            RICC::Token::INTEGER, //183
            RICC::Token::BRACKET_ROUND_CLOSE,
            RICC::Token::SEMICOLON,
            RICC::Token::KW_RETURN,
            RICC::Token::INTEGER, //187
            RICC::Token::SEMICOLON,
            RICC::Token::BRACKET_CURLY_CLOSE,
            RICC::Token::END_TOKEN,
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
        RICC::Token token = lex.getToken();

        if(token.getTokenType() != expectedResult[i]) {
            printErrorMessage(RICC::Token::getTokenTypeByText(expectedResult[i]), token.getTokenTypeText());
            return 1;
        }

        if(expectedValues.find(i) != expectedValues.end()) {
            if(token.getText() != expectedValues.at(i)) {
                printErrorMessage(expectedValues.at(i), token.getText(), true);
                return 1;
            }
        }

        printTokenInfo(token);

        if(token.getTokenType() == RICC::Token::END_TOKEN) {
            break;
        }
        i++;
    };

    printSuccessMessage();

    stream.close();
    return 0;
}
