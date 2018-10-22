#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>

namespace TPJparser {

    class Token {
        public:
            Token();
            size_t getID();
            void setID(size_t id);
            void free();
            void alloc();
            bool isAllocated();

        private:

            std::string _text;
            size_t _id;
            bool _allocated;
    };
}

#endif