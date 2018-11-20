#include <iostream>
#include <sstream>
#include <lex/Lex.hpp>

#include "tpj-parser.hpp"


int main()
{
    /**
     *  EDIT INPUT PROGRAM HERE
     */
    std::string inputProgram (")");
    std::istringstream stream(inputProgram);
    TPJparser::Lex lex(stream);

    TPJparser::Token token = lex.getToken();

    if (token.getOriginalTokenTypeText() != ")") {
        std::cout << token.getOriginalTokenTypeText() << " != " << ")" << std::endl;
        return 1;
    }

    return 0;
}
