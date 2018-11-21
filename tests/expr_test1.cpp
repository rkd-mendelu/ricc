/**
 * basic expression test
 */ 

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "lex/Token.hpp"
#include "lex/Lex.hpp"
#include "syntax/Syntax.hpp"

std::map<std::string, std::pair<int, TPJparser::Token::tokenType>> m {
    // value return lefttoken
    {" id ", { 0 , TPJparser::Token::END_TOKEN } },
    {"id", { 0 , TPJparser::Token::END_TOKEN } },
    {"(id)", { 0 , TPJparser::Token::END_TOKEN } },
    {"id + ie", { 0 , TPJparser::Token::END_TOKEN } },
    {"id - ie", { 0 , TPJparser::Token::END_TOKEN } },
    {"id * ie", { 0 , TPJparser::Token::END_TOKEN } },
    {"id / ie", { 0 , TPJparser::Token::END_TOKEN } },
    {"(a+(b+c))", { 0 , TPJparser::Token::END_TOKEN } },
    {"((a+)b+c)", {1 , TPJparser::Token::IDENTIFIER} },
    {"(((a)))", { 0 , TPJparser::Token::END_TOKEN } },
    {"((d+f)+(b+c))", { 0 , TPJparser::Token::END_TOKEN } },
    {"(a))", { 0 , TPJparser::Token::BRACKET_ROUND_CLOSE } },
    {"((a)", { 1 , TPJparser::Token::END_TOKEN } },
    {"((((()))))", { 1 , TPJparser::Token::BRACKET_ROUND_CLOSE } },
    {"()", { 1 , TPJparser::Token::END_TOKEN } },
    {"1 + 1", { 0 , TPJparser::Token::END_TOKEN } },

};

int main()
{
    int count = 0;
    for (auto p: m){

        std::cout << "Value: " << "\"" << p.first << "\"" << std::endl;
        std::string input(p.first);
        std::stringstream ss(input);
        TPJparser::Syntax syntax(ss);

        TPJparser::Lex& lex = syntax.getLex();

        int rc = 0;
        rc = syntax.ParseExpression();

        // std::cout << lex._tokenStack.size() << std::endl;
        // std::cout << lex._tokenPool.getSize() << std::endl;

        std::reference_wrapper<TPJparser::Token> nextToken = lex.getToken();

        std::cout << "Got: " << rc << " Expected: " <<  p.second.first << std::endl;
        std::cout << "Expected Left Token: " << TPJparser::Token::getTokenTypeByText(p.second.second) << std::endl;
        std::cout << "Got Left Token: " << nextToken.get().getTokenTypeText() << std::endl;

        if (rc != p.second.first || p.second.second != nextToken.get().getTokenType()) {
            std::cout << "ERROR!" << std::endl;
            count++;
        }

        std::cout << std::endl;
    }

    return count;
}
