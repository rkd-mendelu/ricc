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
    /*            ==   >   <   >=  <=  !=  +   -   *   /   )   (   $   id  &&  ||  li  !   =   */
    /* 0.  == */ { R,  R,  R,  R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  R,  R,  S,  S,  R },
    /* 1.  >  */ { R,  R,  R,  R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  R,  R,  S,  S,  R },
    /* 2.  <  */ { R,  R,  R,  R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  R,  R,  S,  S,  R },
    /* 3.  >= */ { R,  R,  R,  R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  R,  R,  S,  S,  R },
    /* 4.  <= */ { R,  R,  R,  R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  R,  R,  S,  S,  R },
    /* 5.  != */ { R,  R,  R,  R,  R,  R,  S,  S,  S,  S,  R,  S,  R,  S,  R,  R,  S,  S,  R },
    /* 6.  +  */ { R,  R,  R,  R,  R,  R,  R,  R,  S,  S,  R,  S,  R,  S,  R,  S,  S,  S,  S },
    /* 7.  -  */ { R,  R,  R,  R,  R,  R,  R,  R,  S,  S,  R,  S,  R,  S,  R,  S,  S,  S,  S },
    /* 8.  *  */ { R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  S,  R,  S,  R,  S,  S,  S,  S },
    /* 9.  /  */ { R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  S,  R,  S,  R,  S,  S,  S,  S },
    /* 10. )  */ { R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  E,  R,  E,  S,  S,  E,  S,  R },
    /* 11. (  */ { S,  S,  S,  S,  S,  S,  S,  S,  S,  S,  H,  S,  E,  S,  E,  S,  S,  S,  S },
    /* 12. $  */ { S,  S,  S,  S,  S,  S,  S,  S,  S,  S,  E,  S,  E,  S,  S,  S,  S,  S,  S },
    /* 13. id */ { R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  E,  R,  E,  R,  R,  E,  S,  R },
    /* 14. && */ { S,  S,  S,  S,  S,  S,  S,  S,  S,  S,  R,  S,  R,  S,  R,  R,  S,  S,  R },
    /* 15. || */ { S,  S,  S,  S,  S,  S,  S,  S,  S,  S,  R,  S,  R,  S,  S,  R,  S,  S,  R },
    /* 16. li */ { R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  E,  R,  E,  R,  R,  E,  R,  R },
    /* 17. !  */ { S,  S,  S,  S,  S,  S,  S,  S,  S,  S,  R,  E,  R,  S,  R,  R,  S,  R,  R },
    /* 18. =  */ { S,  S,  S,  S,  S,  S,  S,  S,  S,  S,  R,  S,  R,  S,  S,  S,  S,  S,  S },
    /*             0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  */
    };

    /*
     *
     *  R >
     *  S <    
    */

    const Token::tokenType Syntax::longRules[14][3] = {
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
        { Token::P_RVALUE, Token::AND, Token::P_RVALUE },
        { Token::P_RVALUE, Token::OR, Token::P_RVALUE },
        { Token::P_RVALUE, Token::ASSIGNMENT, Token::P_RVALUE },
        { Token::BRACKET_ROUND_OPEN, Token::P_RVALUE, Token::BRACKET_ROUND_CLOSE },
    };

    const Token::tokenType Syntax::shortRules[3][2] = {
        {Token::EXCLAMATION, Token::P_RVALUE},
        {Token::PLUS, Token::P_RVALUE},
        {Token::MINUS, Token::P_RVALUE},
    };

    void Syntax::visualizeStack() {
        auto s = this->_tokenStack;
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
        auto s = this->_tokenStack;

        while (!s.empty()) {
            if (s.top().get().isTerminal())
                return std::ref(s.top().get());
            s.pop();
        }
        return std::ref(ImplicitToken);
    }

    void Syntax::putShiftToken(Token& terminal) {
        decltype(this->_tokenStack) new_tokenStack;

        while(!this->_tokenStack.empty()) {
            if (this->_tokenStack.top().get().getTokenType() == terminal.getTokenType()){
                this->_tokenStack.push(Syntax::ShiftToken);
                break;
            }
            new_tokenStack.push(this->_tokenStack.top());
            this->_tokenStack.pop();
        }

        while(!new_tokenStack.empty()) {
            this->_tokenStack.push(new_tokenStack.top());
            new_tokenStack.pop();
        }
    }

    int Syntax::reduceStack() {
        constexpr size_t sizeOfLongRule = sizeof(longRules[0]);
        constexpr size_t numberOfLongRules = sizeof(longRules) / sizeOfLongRule;

        bool longRuleIndex[numberOfLongRules];
        std::fill(longRuleIndex, longRuleIndex + numberOfLongRules, true);

        constexpr size_t sizeOfShortRule = sizeof(shortRules[0]);
        constexpr size_t numberOfShortRules = sizeof(shortRules) / sizeOfShortRule;

        bool shortRuleIndex[numberOfShortRules];
        std::fill(shortRuleIndex, shortRuleIndex + numberOfShortRules, true);

        bool found = false;

        //visualizeStack();
        std::reference_wrapper<Token> token = this->_tokenStack.top();
        size_t counter = 1;

        do {
            if (counter > 3) {
                DEBUG("Trying to reduce stack more than expected" << "3<" << counter);
                // longest rule is 3
                DEBUG(" -> 1");
                return 1;
            }
            token = std::ref(this->_tokenStack.top());
            this->_tokenStack.pop();

            token.get().print();

            if (counter == 1
                && token.get().isRValue()
                && this->_tokenStack.top().get().getTokenType() == Token::P_SHIFT) {
                    /**
                     * Coverts all possible tokens that are RVALUES to RVALUE
                     * IDENTIFER or INT/STRING/FLOAT literals -> RVALUE
                     */
                    this->_tokenStack.pop();
                    token.get().setOriginalTokenType(token.get().getTokenType());
                    token.get().setTokenType(Token::P_RVALUE);
                    this->_tokenStack.push(token);
                    goto finish;
            } else {
                /**
                 * Standard size 3 rules
                 */
                for (size_t i = 0 ; i < numberOfLongRules ; ++i) {
                    if (token.get().getTokenType() != longRules[i][3 - counter]) {
                        longRuleIndex[i] = false;
                    }
                }
                /**
                 * Standard size 2 rules
                 */
                if (counter < 3) {
                    for (size_t i = 0 ; i < numberOfShortRules ; ++i) {
                        if (token.get().getTokenType() != shortRules[i][2 - counter]) {
                            shortRuleIndex[i] = false;
                        }
                    }
                }

                /**
                 * We need to save last valid token
                 */
                if (this->_tokenStack.top().get().getTokenType() == Token::P_SHIFT) {
                    this->_tokenStack.pop();
                    token.get().setOriginalTokenType(token.get().getTokenType());
                    token.get().setTokenType(Token::P_RVALUE);
                    this->_tokenStack.push(token);
                    break;
                }
            }

            counter++;
        } while(token.get().getTokenType() != Token::P_SHIFT);

        if (counter == 3) {
            for (size_t i = 0 ; i < numberOfLongRules ; ++i) {
                if (longRuleIndex[i]) {
                    DEBUG("MATCHED RULE NUMBER " << i << " -> "
                    <<  Token::getTokenTypeByText(longRules[i][0])
                        << " " << Token::getTokenTypeByText(longRules[i][1]) 
                        << " " << Token::getTokenTypeByText(longRules[i][2])
                        << std::endl);
                    found = true;
                    break;
                }
            }
        } else if (counter == 2) {
            for (size_t i = 0 ; i < numberOfShortRules ; ++i) {
                if (shortRuleIndex[i]) {
                    DEBUG("MATCHED RULE NUMBER " << i << " -> "
                    <<  Token::getTokenTypeByText(shortRules[i][0])
                        << " " << Token::getTokenTypeByText(shortRules[i][1])
                        << std::endl);
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            // err
            DEBUG("RULE WAS NOT FOUND" << std::endl);
            DEBUG(" -> 1");
            return 1;
        }

finish:
        return 0;
    }

    int Syntax::ParseExpression() {

        this->_tokenStack.push(std::ref(Syntax::ImplicitToken));

        bool run = true;

        do {
            std::reference_wrapper<Token> inputToken = this->_lex.getToken();
            std::reference_wrapper<Token> topToken = this->getFirstTerminalFromTop();

            if (inputToken.get().isLiteral()) {
                inputToken.get().setTokenType(Token::LITERAL);
            } else if(inputToken.get().getTokenType() > Token::ASSIGNMENT) {
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
                    if (this->reduceStack()) {
                        inputToken.get().setTokenType(inputToken.get().getOriginalTokenType());
                        _lex.ungetToken(inputToken);
                        return 1;
                    }
                    _lex.ungetToken(inputToken);
                    break;

                case S:
                    DEBUG("S - Branch");
                    this->putShiftToken(topToken);
                    this->_tokenStack.push(inputToken);
                    break;

                case H:
                    DEBUG("H - Branch");
                    this->_tokenStack.push(inputToken);
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

        if (this->_tokenStack.size() != 2) {
            DEBUG("ParseExpression didn't empty stack");
            DEBUG(" -> 1");
            return 1;
        } else {
            this->_tokenStack.pop();
            this->_tokenStack.pop();
        }

        return 0;
    }
}
