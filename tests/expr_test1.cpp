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

std::map<std::string, std::pair<int, RICC::Token::tokenType>> m {
    // value return lefttoken
    {" id ", { 0 , RICC::Token::END_TOKEN } },
    {"id", { 0 , RICC::Token::END_TOKEN } },
    {"(id)", { 0 , RICC::Token::END_TOKEN } },
    {"id + ie", { 0 , RICC::Token::END_TOKEN } },
    {"id - ie", { 0 , RICC::Token::END_TOKEN } },
    {"id * ie", { 0 , RICC::Token::END_TOKEN } },
    {"id / ie", { 0 , RICC::Token::END_TOKEN } },
    {"(a+(b+c))", { 0 , RICC::Token::END_TOKEN } },

    {"((a+)b+c)", {1 , RICC::Token::BRACKET_ROUND_CLOSE} },
    {"(((a)))", { 0 , RICC::Token::END_TOKEN } },
    {"((d+f)+(b+c))", { 0 , RICC::Token::END_TOKEN } },
    {"(a))", { 0 , RICC::Token::BRACKET_ROUND_CLOSE } },
    {"((a)", { 1 , RICC::Token::END_TOKEN } },

    {"((((()))))", { 1 , RICC::Token::BRACKET_ROUND_CLOSE } },
     {"()", { 1 , RICC::Token::END_TOKEN } },
    {"1 + 1", { 0 , RICC::Token::END_TOKEN } },
    {"id && id", {0, RICC::Token::END_TOKEN} },
    {"1 && 1", {0, RICC::Token::END_TOKEN} },

    {"a+b && b+a", {0, RICC::Token::END_TOKEN} },
    {"a-b && b-a", {0, RICC::Token::END_TOKEN} },
    {"a*b && b*a", {0, RICC::Token::END_TOKEN} },
    {"a/b && b/a", {0, RICC::Token::END_TOKEN} },

    {"&&", {1, RICC::Token::END_TOKEN} },
    {"&& &&", {1, RICC::Token::AND} },

    {"a+b || b+a", {0, RICC::Token::END_TOKEN} },
    {"a-b || b-a", {0, RICC::Token::END_TOKEN} },
    {"a*b || b*a", {0, RICC::Token::END_TOKEN} },
    {"a/b || b/a", {0, RICC::Token::END_TOKEN} },

    {"||", {1, RICC::Token::END_TOKEN}},
    {"|| ||", {1, RICC::Token::OR}},

    {"a || b && c", {0, RICC::Token::END_TOKEN} },
    {"a && b || c", {0, RICC::Token::END_TOKEN} },
    {"a && b && c", {0, RICC::Token::END_TOKEN} },
    {"a || b || c", {0, RICC::Token::END_TOKEN} },

    {"a || b &&", {1, RICC::Token::END_TOKEN} },
    {"a && b ||", {1, RICC::Token::END_TOKEN} },
    {"&& b && c", {1, RICC::Token::AND} },
    {"|| b || c", {1, RICC::Token::OR} },

    {"+id", {0, RICC::Token::END_TOKEN} },
    {"(-id)", {0, RICC::Token::END_TOKEN} },
    {"-(id)", {0, RICC::Token::END_TOKEN} },
    {"a == b && b != a", {0, RICC::Token::END_TOKEN} },
    {"a == b || b != a", {0, RICC::Token::END_TOKEN} },
    {"a > b && b < a", {0, RICC::Token::END_TOKEN} },


    {"a == b + (!a)", {0, RICC::Token::END_TOKEN} },
    {"ab && !bc", {0, RICC::Token::END_TOKEN} },
    {"ab + !bc", {0, RICC::Token::END_TOKEN} },
    {"a == !b", {0, RICC::Token::END_TOKEN} },
    {"!a && 2", {0, RICC::Token::END_TOKEN} },
    {"!!a", {1, RICC::Token::EXCLAMATION} },

    {"a = b", {0, RICC::Token::END_TOKEN} },
    {"a = b + c", {0, RICC::Token::END_TOKEN} },
    {"a = b - c", {0, RICC::Token::END_TOKEN} },
    {"a = b * c", {0, RICC::Token::END_TOKEN} },
    {"a = b / c", {0, RICC::Token::END_TOKEN} },

    {"a = 2 + 8", {0, RICC::Token::END_TOKEN} },
    {"a = 2 - 8", {0, RICC::Token::END_TOKEN} },
    {"a = 2 * 8", {0, RICC::Token::END_TOKEN} },
    {"a = 2 / 8", {0, RICC::Token::END_TOKEN} },

    {"a + b = 2", {0, RICC::Token::END_TOKEN} },
    {"a - b = 2", {0, RICC::Token::END_TOKEN} },
    {"a * b = 2", {0, RICC::Token::END_TOKEN} },
    {"a / b = 2", {0, RICC::Token::END_TOKEN} },

    // will be error in future
    {"(a + b) = 2", {0, RICC::Token::END_TOKEN} },
    {"(a - b) = 2", {0, RICC::Token::END_TOKEN} },
    {"(a * b) = 2", {0, RICC::Token::END_TOKEN} },
    {"(a / b) = 2", {0, RICC::Token::END_TOKEN} },

    {" = a + b", {1, RICC::Token::END_TOKEN} },
    {"a = b = c = 2", {0, RICC::Token::END_TOKEN} },
    {"a * b = 2", {0, RICC::Token::END_TOKEN} },
    {"a / b = 2", {0, RICC::Token::END_TOKEN} },

    {"a + b = 67 / cdfds", {0, RICC::Token::END_TOKEN} },
};

int main()
{
    int count = 0;
    for (auto p: m){

        std::cout << "Value: " << "\"" << p.first << "\"" << std::endl;
        std::string input(p.first);
        std::stringstream ss(input);
        RICC::Syntax syntax(ss);

        RICC::Lex& lex = syntax.getLex();

        int rc = 0;
        syntax.setSemanticsCheck(false);
        rc = syntax.ParseExpression();

        // std::cout << lex._tokenStack.size() << std::endl;
        // std::cout << lex._tokenPool.getSize() << std::endl;

        std::reference_wrapper<RICC::Token> nextToken = lex.getToken();

        std::cout << "Got: " << rc << " Expected: " <<  p.second.first << std::endl;
        std::cout << "Expected Left Token: " << RICC::Token::getTokenTypeByText(p.second.second) << std::endl;
        std::cout << "Got Left Token: " << nextToken.get().getTokenTypeText() << std::endl;

        if (rc != p.second.first || p.second.second != nextToken.get().getTokenType()) {
            std::cout << "ERROR!" << std::endl;
            count++;
        }

        std::cout << std::endl;
    }

    return count;
}
