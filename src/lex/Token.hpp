#pragma once

#include <iostream>
#include <map>

namespace TPJparser {
    /**
     * Ths class represents the single token build in the parser
     */
    class Token {

        public:
            /**
             * Enum for single token type
             */
            enum tokenType {
                //MATH AND LOGICAL OPERATIONS
                EQUAL = 0, // ==
                LARGE, // >
                LESS, // <
                LARGER_OR_EQUAL, // >=
                LESS_OR_EQUAL, // <=
                NOT_EQUAL, // !=
                PLUS, // +
                MINUS, // -
                MULTI, // *
                DIV, // /
                // BRACKETS
                BRACKET_ROUND_CLOSE, // )
                BRACKET_ROUND_OPEN, // (

                P_IMPLICIT,
                //Identifiers
                IDENTIFIER,
                AND, // &&
                OR, // ||
                LITERAL,
                EXCLAMATION, // !
                ASSIGNMENT, // =
                // Precedence until here --^

                //BRACKETS
                BRACKET_SQUARE_OPEN, // [
                BRACKET_SQUARE_CLOSE, // ]
                BRACKET_CURLY_OPEN, // {
                BRACKET_CURLY_CLOSE, // }

                //Numbers
                INTEGER,
                FLOAT,
                STRING,
                //Other

                SEMICOLON, // ;
                COMMA, // ,
                DOT, // .
                POINTER, // ->
                OUTPUT, // <<
                //Reserved words
                KW_EOF, //

                // void function()
                KW_VOID,
                // types for variables and functions
                KW_INT,
                KW_STRING,
                KW_BOOL,
                KW_FLOAT,

                KW_IF,
                KW_ELSE,
                KW_RETURN,
                KW_SWITCH,
                KW_CASE,
                KW_DEFAULT,
                KW_BREAK,
                KW_CONTINUE,
                KW_CLASS,
                KW_PRIVATE,
                KW_PROTECTED,
                KW_PUBLIC,
                KW_STRUCT,
                KW_COUT,
                KW_TRUE,
                KW_FALSE,
                KW_WHILE,
                KW_NEW,
                KW_FOR,
                //
                ERROR_TOKEN,
                EOF_CHAR,
                END_TOKEN,
                // precedence
                P_SHIFT,
                P_REDUCE,
               // P_IMPLICIT,
                P_RVALUE,
            };

            static std::map<Token::tokenType,std::string> tokenTypeEnumMap;

            /**
             * Constructor
             */
            Token();

            /**
             * Constructor
             */
            Token(tokenType t);

            /**
             * Constructor
             */
            Token(tokenType t, std::string s);

            /**
             * @return id of token
             */
            size_t getID();

            /**
             * @param id for token to be set
             */
            void setID(size_t id);

            /**
             * Method releases all memory allocated for token
             */
            void free();

            /**
             * Method allocates memory for single token
             */
            void alloc();

            /**
             * @return is/is not allocated token
             */
            bool isAllocated();

            /**
             * Method returns type of token
             * @return Token::tokenType type of token
             */
            tokenType getTokenType();

            /**
             * Returns enum type formatted as string
             * @return token type string
             */
            std::string getTokenTypeText();

            /**
             * Returns enum type formatted as string
             * @return token type string
             */
            static std::string getTokenTypeByText(tokenType t);

            /**
             * Method sets type for token
             * @param Token::tokenType type to be set
             */
            void setTokenType(tokenType t);

            /**
             * Method returns type of token
             * @return Token::tokenType type of token
             */
            tokenType getOriginalTokenType();

            /**
             * Returns enum type formatted as string
             * @return token type string
             */
            std::string getOriginalTokenTypeText();

            /**
             * Method sets type for token
             * @param Token::tokenType type to be set
             */
            void setOriginalTokenType(tokenType t);

            /**
             * Method appends actual char of lex stream stack to the token content (text)
             * @param char c
             */
            void addChar(char c);

            /**
             * @return std::string content of the token
             */
            std::string getText();

            /**
             * Method returns true if it is RVALUE
             * @return bool
             */
            bool isRValue();

            /**
             * Method returns true if it is Terminal
             * @return bool
             */
            bool isTerminal();

            /**
             * Method returns true if it is Terminal
             * @return bool
             */
            bool isLiteral();

            /**
             * Method prints token class
             */
            void print();

        private:
            /**
             * Variable for storing content of token
             */
            std::string _text;

            /**
             * Id of token for destroy method
             */
            size_t _id;

            /**
             * Storing information about token allocation state
             */
            bool _allocated;

            /**
             * Actual type of token
             */
            tokenType _tokenType;

            /**
             * Original type of token
             */
            tokenType _originalTokenType;
    };
}
