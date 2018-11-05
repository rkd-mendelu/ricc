#ifndef TOKEN_HPP
#define TOKEN_HPP

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
                PLUS, // +
                MINUS, // -
                DIV, // /
                MULTI, // *
                EQUAL, // ==
                NOT_EQUAL, // !=
                LARGE, // >
                LESS, // <
                EXCLAMATION, // !
                AND, // &&
                OR, // ||
                //BRACKETS
                BRACKET_ROUND_OPEN, // (
                BRACKET_ROUND_CLOSE, // )
                BRACKET_SQUARE_OPEN, // [
                BRACKET_SQUARE_CLOSE, // ]
                BRACKET_CURLY_OPEN, // {
                BRACKET_CURLY_CLOSE, // }
                //Identifiers
                IDENTIFIER,
                //Numbers
                INTEGER,
                FLOAT,
                STRING,
                //Other
                ASSIGNMENT, // =
                SEMICOLON, // ;
                COLON, // :
                COMMA, // ,
                DOT, // .
                OUTPUT, // <<
                //Reserved words
                KW_EOF, //
                KW_INT,
                KW_BOOL,
                KW_FLOAT,
                KW_VOID,
                KW_STRING,
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
                //
                ERROR_TOKEN,
                EOF_CHAR,
                END_TOKEN,
            };

            static std::map<Token::tokenType,std::string> tokenTypeEnumMap;

            /**
             * Constructor
             */
            Token();

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
            std::string getTokenTypeText(tokenType type);

            /**
             * Method sets type for token
             * @param Token::tokenType type to be set
             */
            void setTokenType(tokenType tokenType);

            /**
             * Method appends actual char of lex stream stack to the token content (text)
             * @param char c
             */
            void addChar(char c);

            /**
             * @return std::string content of the token
             */
            std::string getText();

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
    };
}

#endif