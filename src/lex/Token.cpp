#include <iostream>

#include "Token.hpp"

namespace TPJparser {

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

}
