#pragma once

#include <iostream>
#include <stack>
#include <functional>
#include <map>

#include "util/ObjectPool.hpp"
#include "lex/Token.hpp"

namespace RICC {

    /**
     * Class representing the scanner of an interpret. Main task of this class is reading the input source program and parsing data into tokens.
     */
    class Lex {
        private:
            /**
             * Internal states of automaton
             */
            enum lexState {
                START,
                IDENTIFIER,
                INTEGER,
                FLOAT,
                LESS, // <
                LARGE, // <
                ASSIGNMENT, // =
                DIV, // /
                EXCL_MARK, // !
                COMMENT_LINE, // //
                COMMENT_BLOCK_START, // /*
                COMMENT_BLOCK_STAR, // * in the block comment - possible end of block comment
                STRING_DOUBLE_QUOTES_START, // "
                STRING_DOUBLE_QUOTES_BODY, // "anything
                STRING_SINGLE_QUOTES_START, // '
                STRING_SINGLE_QUOTES_BODY, // 'anything
                AND_FIRST_MARK,
                OR_FIRST_MARK,
                MINUS_SIGN,
            };

        public:
            /**
             * Constructor
             * @param stream input stream with source code to be interpreted
             */
            Lex(std::istream& stream);

            /**
             * Main public method. If there is a token on stack (from previous ungetToken method calling), that token is returned. Otherwise, the new token is read from stream
             * @return
             */
            Token& getToken();

            /**
             * Method pushes token to stack
             * @param t
             */
            void ungetToken(Token& t);

            /**
             * @return  current automaton state
             */
            lexState getCurrentState();

            /**
             * Method sets state for lex automaton
             * @param currentState state to be setted
             */
            void setCurrentState(lexState currentState);

            /**
             * Map of string-Token::tokenType. It is used for keyword checking
             */
            static std::map<std::string,Token::tokenType> keywordMap;

        //private:
            /**
             * Stream with source program
             */
            std::istream& _stream;

            /**
             * Pool of tokens for easier allocation and deallocation
             */
            ObjectPool<Token> _tokenPool;

            /**
             * Current state of automaton
             */
            lexState _currentState;

            /**
             * Stack of ungetted tokens
             */
            std::stack<std::reference_wrapper<Token>> _tokenStack;

            /**
             * Method reads another token from file
             * @return new token from file
             */
            Token& getTokenFromFile();

            /**
             * Method pops token from token stack
             * @return  ungetted token from top of stack
             */
            Token& getTokenFromStack();

            /**
             * Method resets automaton state to start state
             */
            void clearLexState();
    };
}
