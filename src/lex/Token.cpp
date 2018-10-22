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

}