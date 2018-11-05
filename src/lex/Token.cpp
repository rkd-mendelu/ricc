#include <iostream>

#include "Token.hpp"

namespace TPJparser {

    std::map<Token::tokenType,std::string> Token::tokenTypeEnumMap = {
            {Token::PLUS, "PLUS"},
            {Token::MINUS, "MINUS"},
            {Token::DIV, "DIV"},
            {Token::MULTI, "MULTI"},
            {Token::EQUAL, "EQUAL"},
            {Token::NOT_EQUAL, "NOT_EQUAL"},
            {Token::LARGE, "LARGE"},
            {Token::LESS, "LESS"},
            {Token::EXCLAMATION, "EXCLAMATION"},
            {Token::AND, "AND"},
            {Token::OR, "OR"},
            {Token::BRACKET_ROUND_OPEN, "BRACKET_ROUND_OPEN"},
            {Token::BRACKET_ROUND_CLOSE, "BRACKET_ROUND_CLOSE"},
            {Token::BRACKET_SQUARE_OPEN, "BRACKET_SQUARE_OPEN"},
            {Token::BRACKET_SQUARE_CLOSE, "BRACKET_SQUARE_CLOSE"},
            {Token::BRACKET_CURLY_OPEN, "BRACKET_CURLY_OPEN"},
            {Token::BRACKET_CURLY_CLOSE, "BRACKET_CURLY_CLOSE"},
            {Token::IDENTIFIER, "IDENTIFIER"},
            {Token::INTEGER, "INTEGER"},
            {Token::FLOAT, "FLOAT"},
            {Token::STRING, "STRING"},
            {Token::ASSIGNMENT, "ASSIGNMENT"},
            {Token::SEMICOLON, "SEMICOLON"},
            {Token::COLON, "COLON"},
            {Token::COMMA, "COMMA"},
            {Token::DOT, "DOT"},
            {Token::OUTPUT, "OUTPUT"},
            {Token::KW_EOF, "KW_EOF"},
            {Token::KW_INT, "KW_INT"},
            {Token::KW_BOOL, "KW_BOOL"},
            {Token::KW_FLOAT, "KW_FLOAT"},
            {Token::KW_VOID, "KW_VOID"},
            {Token::KW_STRING, "KW_STRING"},
            {Token::KW_IF, "KW_IF"},
            {Token::KW_ELSE, "KW_ELSE"},
            {Token::KW_RETURN, "KW_RETURN"},
            {Token::KW_SWITCH, "KW_SWITCH"},
            {Token::KW_CASE, "KW_CASE"},
            {Token::KW_DEFAULT, "KW_DEFAULT"},
            {Token::KW_BREAK, "KW_BREAK"},
            {Token::KW_CONTINUE, "KW_CONTINUE"},
            {Token::KW_CLASS, "KW_CLASS"},
            {Token::KW_PRIVATE, "KW_PRIVATE"},
            {Token::KW_PROTECTED, "KW_PROTECTED"},
            {Token::KW_PUBLIC, "KW_PUBLIC"},
            {Token::KW_STRUCT, "KW_STRUCT"},
            {Token::KW_COUT, "KW_COUT"},
            {Token::ERROR_TOKEN, "ERROR_TOKEN"},
            {Token::EOF_CHAR, "EOF_CHAR"},
            {Token::END_TOKEN, "END_TOKEN"},
            {Token::KW_TRUE, "KW_TRUE"},
            {Token::END_TOKEN, "KW_FALSE"},
    };

    Token::Token() {
        this->free(); // just cleanup
    }

    size_t Token::getID() {
        return this->_id;
    }

    void Token::setID(size_t id) {
        this->_id = id;
    }

    void Token::free() {
        this->_text = "";
        this->_allocated = false;
    }

    void Token::alloc() {
        this->_allocated = true;
    }

    bool Token::isAllocated() {
        return this->_allocated;
    }

    Token::tokenType Token::getTokenType() {
        return this->_tokenType;
    }

    void Token::setTokenType(tokenType tokenType) {
        this->_tokenType = tokenType;
    }

    void Token::addChar(char c) {
        this->_text.push_back(c);
    }

    std::string Token::getText() {
        return this->_text;
    }

    std::string Token::getTokenTypeText(tokenType type) {
        return tokenTypeEnumMap[type];
    }

}
