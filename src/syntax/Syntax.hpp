#pragma once

#define SYNTAX_OK 0
#define SYNTAX_ERROR 2
#define EXPRESSION_ERROR 3

#include <iostream>

#include "semantic/SymbolTable.hpp"
#include "lex/Lex.hpp"
#include "lex/Token.hpp"

namespace TPJparser {

    class Syntax {
        public:

            enum nonTerminals {
                START = 100,
                FUNCTIONS,
                FUNCTIONS_CONT,
                FUNCDECL,
                TAIL,
                HEAD ,
                DECL,
                ARGUMENTS,
                ARGUMENTS_N,
                BODY,
                CONTSTMNT,
                STATEMENT,
                STATEMENTS,
                STATEMENTBODY,
                VARIABLEDEF,
                VARS,
                ASSIGN,
                IFSTMNT,
                ELSEBODY,
                LOOPSTATEMENTS,
                WHILESTMT,
                FORSTMT,
                RETURNSTMT,
                ASSIGNMENT,
                OPERATION,
                TYPE,
                NAME,
                FUNCTIONCALL,
                PARAMETERS,
                PARAMETERS_N,
            };

            static std::map<nonTerminals, std::string> nonTerminalsMap;
            //std::string getName(int nonterminal);

            Syntax(std::istream& stream);
            int Parse();
            int ParseExpression();

            Lex& getLex();

            enum Operations {
                S,    // SHIFT
                R,    // REDUCE
                H,    // ??
                E,    // ERROR
            };

            static Token ImplicitToken;
            static Token ShiftToken;
            static Token ReduceToken;

            static const int SIZE_OF_PRECEDENCE_TABLE = 19;
            static const enum Operations precedence_table[SIZE_OF_PRECEDENCE_TABLE][SIZE_OF_PRECEDENCE_TABLE];
            static const Token::tokenType longRules[14][3];
            static const Token::tokenType shortRules[3][2];

        private:
            int parseSyntax(int nonTerminal);

            int reduceStack();
            void visualizeStack();
            Token& getFirstTerminalFromTop();
            void putShiftToken(Token& terminal);

            void startScope();
            void endScope();

            bool isDefined(const std::string& name, SymbolTableItem::Kind);

            Lex _lex;

            std::stack<SymbolTable> _tableStack;
            std::stack<std::reference_wrapper<Token>> _tokenStack;
    };
}
