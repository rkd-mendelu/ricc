/**
 * Library interface
 */

#include <iostream>

namespace TPJparser {

    class Parser {
        public:
            Parser(std::istream &stream);
            void Run();

        private:
            std::istream &_stream;
    };

}