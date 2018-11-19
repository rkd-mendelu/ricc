#include <iostream>
#include <stack>

#include "Syntax.hpp"
#include "lex/Lex.hpp"
#include "lex/Token.hpp"

#include "util/Logger.hpp"

namespace TPJparser {

    Syntax::Syntax(std::istream& stream)
     : _lex(stream) {
        DEBUG("");
    }

    int Syntax::Parse() {
        DEBUG("");
        // for(Token& t = this->_lex.getToken() ; t.getTokenType() == Token::END_TOKEN ; t = this->_lex.getToken()) {

        // }

        return ParseExpression();
    }

    Lex& Syntax::getLex() {
        return this->_lex;
    }

    /* PRECEDENCE ANALYSIS */

    Token Syntax::ImplicitToken(Token::P_IMPLICIT, std::string("$"));
    Token Syntax::ShiftToken(Token::P_SHIFT);
    Token Syntax::ReduceToken(Token::P_REDUCE);

    const enum Syntax::Operations Syntax::precedence_table[Syntax::SIZE_OF_PRECEDENCE_TABLE][Syntax::SIZE_OF_PRECEDENCE_TABLE] = {
    //            ==   >   <  >=  <=  !=  +   -   *   /   )   (   $   id  li
    /* 0.  == */ { R,  R,  R, R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  S },
    /* 1.  >  */ { R,  R,  R, R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  S },
    /* 2.  <  */ { R,  R,  R, R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  S },
    /* 3.  >= */ { R,  R,  R, R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  S },
    /* 4.  <= */ { R,  R,  R, R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  S },
    /* 5.  != */ { R,  R,  R, R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  S },
    /* 6.  +  */ { R,  R,  R, R,  R,  R,  R,  R,  S,  S,  R,  S,  R,  S,  S },
    /* 7.  -  */ { R,  R,  R, R,  R,  R,  R,  R,  S,  S,  R,  S,  R,  S,  S },
    /* 8.  *  */ { R,  R,  R, R,  R,  R,  R,  R,  R,  R,  R,  S,  R,  S,  S },
    /* 9.  /  */ { R,  R,  R, R,  R,  R,  R,  R,  R,  R,  R,  S,  R,  S,  S },
    /* 10. )  */ { R,  R,  R, R,  R,  R,  R,  R,  R,  R,  R,  E,  R,  E,  E },
    /* 11. (  */ { S,  S,  S, S,  S,  S,  S,  S,  S,  S,  H,  S,  E,  S,  S },
    /* 12. $  */ { S,  S,  S, S,  S,  S,  S,  S,  S,  S,  E,  S,  E,  S,  S },
    /* 13. id */ { R,  R,  R, R,  R,  R,  R,  R,  R,  R,  R,  E,  R,  E,  E },
    /* 14. li */ { R,  R,  R, R,  R,  R,  R,  R,  R,  R,  R,  E,  R,  E,  E },
    /*             0   1   2  3   4   5   6   7   8   9   10  11  12  13  14  */
    };

    const Token::tokenType Syntax::longRules[11][3] = {
        { Token::P_RVALUE, Token::EQUAL, Token::P_RVALUE },
        { Token::P_RVALUE, Token::LARGE, Token::P_RVALUE },
        { Token::P_RVALUE, Token::LESS, Token::P_RVALUE },
        { Token::P_RVALUE, Token::LARGER_OR_EQUAL, Token::P_RVALUE },
        { Token::P_RVALUE, Token::LESS_OR_EQUAL, Token::P_RVALUE },
        { Token::P_RVALUE, Token::NOT_EQUAL, Token::P_RVALUE },
        { Token::P_RVALUE, Token::PLUS, Token::P_RVALUE },
        { Token::P_RVALUE, Token::MINUS, Token::P_RVALUE },
        { Token::P_RVALUE, Token::MULTI, Token::P_RVALUE },
        { Token::P_RVALUE, Token::DIV, Token::P_RVALUE },
        { Token::BRACKET_ROUND_OPEN, Token::P_RVALUE, Token::BRACKET_ROUND_CLOSE },
    };

    void Syntax::visualizeStack() {
        auto s = this->_stack;
        DEBUG("Printing stack size=" << s.size());
        DEBUG("==================================");
        while (!s.empty()) {
            auto t = s.top().get();
            t.print();
            s.pop();
        }
        DEBUG("End of report");
        DEBUG("==================================" << std::endl);
    }

    Token& Syntax::getFirstTerminalFromTop() {
        auto s = this->_stack;

        while (!s.empty()) {
            if (s.top().get().isTerminal())
                return std::ref(s.top().get());
            s.pop();
        }
        return std::ref(ImplicitToken);
    }

    void Syntax::putShiftToken(Token& terminal) {
        decltype(this->_stack) new_stack;

        while(!this->_stack.empty()) {
            if (this->_stack.top().get().getTokenType() == terminal.getTokenType()){
                this->_stack.push(Syntax::ShiftToken);
                break;
            }
            new_stack.push(this->_stack.top());
            this->_stack.pop();
        }

        while(!new_stack.empty()) {
            this->_stack.push(new_stack.top());
            new_stack.pop();
        }
    }

    int Syntax::reduceStack() {
        DEBUG("");
        constexpr size_t sizeOfRule = sizeof(longRules[0]);
        constexpr size_t numberOfRules = sizeof(longRules) / sizeOfRule;

        bool index[numberOfRules];
        std::fill(index, index + numberOfRules, true);

        bool found = false;

        DEBUG("ReduceStack:");

        visualizeStack();
        std::reference_wrapper<Token> token = this->_stack.top();
        size_t counter = 1;

        do {
            if (counter > 3) {
                DEBUG("Trying to reduce stack more than expected" << "3<" << counter);
                // longest rule is 3
                DEBUG(" -> 1");
                return 1;
            }
            token = std::ref(this->_stack.top());
            this->_stack.pop();

            DEBUG("Popped:");
            token.get().print();

            if (counter == 1
                && token.get().isRValue()
                && this->_stack.top().get().getTokenType() == Token::P_SHIFT) {
                    /**
                     * Coverts all possible tokens that are RVALUES to RVALUE
                     * IDENTIFER or INT/STRING/FLOAT literals -> RVALUE
                     */
                    this->_stack.pop();
                    token.get().setOriginalTokenType(token.get().getTokenType());
                    token.get().setTokenType(Token::P_RVALUE);
                    this->_stack.push(token);
                    goto finish;
            } else {
                /**
                 * Standard size 3 rules
                 */
                for (size_t i = 0 ; i < numberOfRules ; ++i) {
                    if (token.get().getTokenType() != longRules[i][3 - counter]) {
                        index[i] = false;
                    }
                }

                /**
                 * We need to save last valid token
                 */
                if (this->_stack.top().get().getTokenType() == Token::P_SHIFT) {
                    this->_stack.pop();
                    token.get().setOriginalTokenType(token.get().getTokenType());
                    token.get().setTokenType(Token::P_RVALUE);
                    this->_stack.push(token);
                    break;
                }
            }

            counter++;
        } while(token.get().getTokenType() != Token::P_SHIFT);

        for (size_t i = 0 ; i < numberOfRules ; ++i) {
            if (index[i]) {
                DEBUG("MATCHED RULE NUMBER " << i << " -> "
                <<  Token::getTokenTypeByText(longRules[i][2])
                    << " " << Token::getTokenTypeByText(longRules[i][1]) 
                    << " " << Token::getTokenTypeByText(longRules[i][0])
                    );
                found = true;
                break;
            }
        }

        if (!found) {
            // err
            DEBUG("RULE WAS NOT FOUND" << std::endl);
            DEBUG(" -> 1");
            return 1;
        }

finish:
        visualizeStack();
        DEBUG("END of ReduceStack");
        return 0;
    }

    int Syntax::ParseExpression() {
        DEBUG("");

        this->_stack.push(std::ref(Syntax::ImplicitToken));

        bool run = true;

        do {
            std::reference_wrapper<Token> inputToken = this->_lex.getToken();
            std::reference_wrapper<Token> topToken = this->getFirstTerminalFromTop();

            if (inputToken.get().isLiteral()) {
                inputToken.get().setTokenType(Token::LITERAL);
            } else if(inputToken.get().getTokenType() > Token::LITERAL) {
                //inputToken.get().setOriginalTokenType(inputToken.get().getTokenType());
                inputToken.get().setTokenType(Token::P_IMPLICIT);
            }

            DEBUG("InputToken:");
            inputToken.get().print();
            DEBUG("");
            DEBUG("topToken:");
            topToken.get().print();
            DEBUG("");

            this->visualizeStack();

            DEBUG("Switch:");
            DEBUG("Row: " << topToken.get().getTokenType() << " " << "Column:" << inputToken.get().getTokenType());

            switch( Syntax::precedence_table
                        [topToken.get().getTokenType()]
                        [inputToken.get().getTokenType()] ) {

                case R:
                    DEBUG("R - Branch");
                    if (this->reduceStack()) return 1;
                    _lex.ungetToken(inputToken);
                    break;

                case S:
                    DEBUG("S - Branch");
                    this->putShiftToken(topToken);
                    this->_stack.push(inputToken);
                    break;

                case H:
                    DEBUG("H - Branch");
                    this->_stack.push(inputToken);
                    break;

                case E:
                    DEBUG("E - Branch");
                    _lex.ungetToken(inputToken);
                    inputToken.get().setTokenType(inputToken.get().getOriginalTokenType());
                    run = false;
                    break;

            }

            if (inputToken.get().getTokenType() == Token::P_IMPLICIT && topToken.get().getTokenType() == Token::P_IMPLICIT) {
                inputToken.get().setTokenType(inputToken.get().getOriginalTokenType());
                run = false;
            }

        } while(run);

        if (this->_stack.size() != 2) {
            DEBUG("ParseExpression didn't empty stack");
            DEBUG(" -> 1");
            return 1;
        } else {
            this->_stack.pop();
            this->_stack.pop();
        }

        DEBUG("END of ParseExpression:");
        return 0;
    }
}
