#include <iostream>
#include <stack>

#include "Syntax.hpp"
#include "lex/Lex.hpp"
#include "lex/Token.hpp"

#include "util/Logger.hpp"

namespace TPJparser {

    std::map<Syntax::nonTerminals, std::string> Syntax::nonTerminalsMap = {
        { Syntax::START, "START" },
        { Syntax::INLINE_START, "INLINE_START" },
        { Syntax::CONT_INLINE, "CONT_INLINE" },
        { Syntax::FUNCDECL_INLINE, "FUNCDECL_INLINE" },
        { Syntax::FUNCTIONS, "FUNCTIONS" },
        { Syntax::FUNCTIONS_CONT, "FUNCTIONS_CONT" },
        { Syntax::FUNCDECL, "FUNCDECL" },
        { Syntax::TAIL, "TAIL" },
        { Syntax::HEAD , "HEAD " },
        { Syntax::DECL, "DECL" },
        { Syntax::ARGUMENTS, "ARGUMENTS" },
        { Syntax::ARGUMENTS_N, "ARGUMENTS_N" },
        { Syntax::BODY, "BODY" },
        { Syntax::CONTSTMNT, "CONTSTMNT" },
        { Syntax::STATEMENT, "STATEMENT" },
        { Syntax::STATEMENTS, "STATEMENTS" },
        { Syntax::STATEMENTBODY, "STATEMENTBODY" },
        { Syntax::VARIABLEDEF, "VARIABLEDEF" },
        { Syntax::VARIABLEDEF_N, "VARIABLEDEF_N" },
        { Syntax::ASSIGN, "ASSIGN" },
        { Syntax::IFSTMNT, "IFSTMNT" },
        { Syntax::ELSEBODY, "ELSEBODY" },
        { Syntax::LOOPSTATEMENTS, "LOOPSTATEMENTS" },
        { Syntax::WHILESTMT, "WHILESTMT" },
        { Syntax::FORSTMT, "FORSTMT" },
        { Syntax::RETURNSTMT, "RETURNSTMT" },
        { Syntax::ASSIGNMENT, "ASSIGNMENT" },
        { Syntax::OPERATION, "OPERATION" },
        { Syntax::OPERATION_KIND, "OPERATION_KIND" },
        { Syntax::TYPE, "TYPE" },
        { Syntax::NAME, "NAME" },
        { Syntax::FUNCTIONCALL, "FUNCTIONCALL" },
        { Syntax::PARAMETERS, "PARAMETERS"},
        { Syntax::PARAMETERS_N, "PARAMETERS_N"},
    };

    Syntax::Syntax(std::istream& stream)
     : _lex(stream) {
        DEBUG("");
    }

    void Syntax::setSemanticsCheck(bool check){
        DEBUG("setSemanticCheck");
        this->_semanticsCheck = check;
    }

    int Syntax::Parse() {
        DEBUG("");

        int res = 0;
        _scope.enterScope(/*new*/true);
        this->preDefineFunctions();
        if ((res = parseSyntax(INLINE_START, INLINE_START))) return res;
        _scope.leaveScope();
        //if ((res = this->_interpret.run())) return res;

        return 0;
    }

    Lex& Syntax::getLex() {
        return this->_lex;
    }

    Interpret::Interpret& Syntax::getIntepreter() {
        return this->_interpret;
    }

    void Syntax::preDefineFunctions() {

        {
        // printINT(int x)
            auto print = this->_scope.define("printINT", SymbolTableItem::Kind::FUNCTION);
            print->setType(SymbolTableItem::Type::VOID);
            auto& args = print->getArgs();
            args.push_back({SymbolTableItem::Type::INT, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("printINT"));
            print->setJumpIndex(this->_interpret.getIP()-2);
            print->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::PRINT);
            this->_interpret.genReturn(/*void*/true);

            auto jindex = print->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // printFLOAT(float x)
        {
            auto print = this->_scope.define("printFLOAT", SymbolTableItem::Kind::FUNCTION);
            print->setType(SymbolTableItem::Type::VOID);
            auto& args = print->getArgs();
            args.push_back({SymbolTableItem::Type::FLOAT, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("printFLOAT"));
            print->setJumpIndex(this->_interpret.getIP()-2);
            print->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::PRINT);
            this->_interpret.genReturn(/*void*/true);

            auto jindex = print->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // printSTRING(float x)
        {
            auto print = this->_scope.define("printSTRING", SymbolTableItem::Kind::FUNCTION);
            print->setType(SymbolTableItem::Type::VOID);
            auto& args = print->getArgs();
            args.push_back({SymbolTableItem::Type::STRING, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("printSTRING"));
            print->setJumpIndex(this->_interpret.getIP()-2);
            print->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::PRINT);
            this->_interpret.genReturn(/*void*/true);

            auto jindex = print->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // printBOOL(bool x)
        {
            auto print = this->_scope.define("printBOOL", SymbolTableItem::Kind::FUNCTION);
            print->setType(SymbolTableItem::Type::VOID);
            auto& args = print->getArgs();
            args.push_back({SymbolTableItem::Type::BOOL, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("printBOOL"));
            print->setJumpIndex(this->_interpret.getIP()-2);
            print->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::PRINT);
            this->_interpret.genReturn(/*void*/true);

            auto jindex = print->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        /**********************************CAST********************************/

        // castF2I()
        {
            auto cast = this->_scope.define("castF2I", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::INT);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::FLOAT, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castF2I"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTINT);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castB2I()
        {
            auto cast = this->_scope.define("castB2I", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::INT);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::BOOL, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castB2I"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTINT);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castS2I()
        {
            auto cast = this->_scope.define("castS2I", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::INT);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::STRING, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castS2I"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTINT);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castI2F()
        {
            auto cast = this->_scope.define("castI2F", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::FLOAT);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::INT, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castI2F"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTFLOAT);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castB2F()
        {
            auto cast = this->_scope.define("castB2F", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::FLOAT);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::BOOL, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castB2F"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTFLOAT);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castS2F()
        {
            auto cast = this->_scope.define("castS2F", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::FLOAT);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::STRING, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castS2F"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTFLOAT);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castI2B()
        {
            auto cast = this->_scope.define("castI2B", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::BOOL);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::INT, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castI2B"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTBOOL);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castF2B()
        {
            auto cast = this->_scope.define("castF2B", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::BOOL);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::FLOAT, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castF2B"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTBOOL);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castS2B()
        {
            auto cast = this->_scope.define("castS2B", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::BOOL);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::STRING, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castS2B"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTBOOL);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castB2S()
        {
            auto cast = this->_scope.define("castB2S", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::STRING);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::BOOL, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castB2S"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTSTRING);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castF2S()
        {
            auto cast = this->_scope.define("castF2S", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::STRING);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::FLOAT, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castF2S"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTSTRING);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

        // castI2S()
        {
            auto cast = this->_scope.define("castI2S", SymbolTableItem::Kind::FUNCTION);
            cast->setType(SymbolTableItem::Type::STRING);
            auto& args = cast->getArgs();
            args.push_back({SymbolTableItem::Type::INT, "x"});

            this->_interpret.append(Interpret::Instructions::JUMP, -1L);
            this->_interpret.append(Interpret::Instructions::NOP, std::string("castI2S"));
            cast->setJumpIndex(this->_interpret.getIP()-2);
            cast->setStartAddress(this->_interpret.getIP());

            this->_interpret.append(Interpret::Instructions::LOAD, -3L);
            this->_interpret.append(Interpret::Instructions::CASTSTRING);
            this->_interpret.genReturn(/*is void*/false);

            auto jindex = cast->getJumpIndex();
            this->_interpret.getInstructionBuffer()[jindex]._rec._value
                = Interpret::Operand(this->_interpret.getIP());
        }

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
    /* 13. id */ { R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  R,  E,  R,  R,  E,  S,  R },
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

    void Syntax::genLongOperation(size_t index) {
        if (index >= Syntax::numberOfLongRules) return;

        switch(longRules[index][1]) {
            case Token::EQUAL:
                this->_interpret.append(Interpret::Instructions::EQ);
                break;
            case Token::LARGE:
                this->_interpret.append(Interpret::Instructions::MORE);
                break;
            case Token::LESS:
                this->_interpret.append(Interpret::Instructions::LESS);
                break;
            case Token::LARGER_OR_EQUAL:
                this->_interpret.append(Interpret::Instructions::MOEQ);
                break;
            case Token::LESS_OR_EQUAL:
                this->_interpret.append(Interpret::Instructions::LOEQ);
                break;
            case Token::NOT_EQUAL:
                this->_interpret.append(Interpret::Instructions::NEQ);
                break;
            case Token::PLUS:
                this->_interpret.append(Interpret::Instructions::SUM);
                break;
            case Token::MINUS:
                this->_interpret.append(Interpret::Instructions::SUB);
                break;
            case Token::MULTI:
                this->_interpret.append(Interpret::Instructions::MUL);
                break;
            case Token::DIV:
                this->_interpret.append(Interpret::Instructions::DIV);
                break;
            case Token::AND:
                this->_interpret.append(Interpret::Instructions::AND);
                break;
            case Token::OR:
                this->_interpret.append(Interpret::Instructions::OR);
                break;
            case Token::ASSIGNMENT:
               // this->_interpret.append(Interpret::Instructions::OR);
                break;
            case Token::P_RVALUE:
            default:
                break;
        }
    }

    void Syntax::genShortOperation(size_t index) {
        if (index >= Syntax::numberOfShortRules) return;

        switch(shortRules[index][0]) {
            case Token::tokenType::EXCLAMATION:
                this->_interpret.append(Interpret::Instructions::NEG);
                break;
            case Token::tokenType::MINUS:
                this->_interpret.append(Interpret::Instructions::MINUS);
                break;
            case Token::tokenType::PLUS:
            default:
                break;
        }
    }

    void Syntax::visualizeStack(std::stack<std::reference_wrapper<Token>>& tokenStack) {
        auto s = tokenStack;
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

    Token& Syntax::getFirstTerminalFromTop(std::stack<std::reference_wrapper<Token>>& tokenStack) {
        auto s = tokenStack;

        while (!s.empty()) {
            if (s.top().get().isTerminal())
                return std::ref(s.top().get());
            s.pop();
        }
        return std::ref(ImplicitToken);
    }

    void Syntax::putShiftToken(std::stack<std::reference_wrapper<Token>>& tokenStack, Token& terminal) {
        std::stack<std::reference_wrapper<Token>> new_tokenStack;

        while(!tokenStack.empty()) {
            if (tokenStack.top().get().getTokenType() == terminal.getTokenType()){
                tokenStack.push(Syntax::ShiftToken);
                break;
            }
            new_tokenStack.push(tokenStack.top());
            tokenStack.pop();
        }

        while(!new_tokenStack.empty()) {
            tokenStack.push(new_tokenStack.top());
            new_tokenStack.pop();
        }
    }

    int Syntax::reduceStack(std::stack<std::reference_wrapper<Token>>& tokenStack, std::reference_wrapper<Token>& inputToken) {

        bool longRuleIndex[numberOfLongRules];
        std::fill(longRuleIndex, longRuleIndex + numberOfLongRules, true);

        bool shortRuleIndex[numberOfShortRules];
        std::fill(shortRuleIndex, shortRuleIndex + numberOfShortRules, true);

        bool found = false;

        //visualizeStack();
        std::reference_wrapper<Token> token = tokenStack.top();
        size_t counter = 1;

        do {
            if (counter > 3) {
                DEBUG("Trying to reduce stack more than expected" << "3<" << counter);
                // longest rule is 3
                DEBUG(" -> 1");
                return 1;
            }
            token = std::ref(tokenStack.top());
            tokenStack.pop();

            token.get().print();

            if (counter == 1
                && token.get().isRValue()
                && tokenStack.top().get().getTokenType() == Token::P_SHIFT) {

                    if (token.get().isLiteral()) {
                        this->_interpret.pushLiteral(token);
                    } else if (token.get().getTokenType() == Token::tokenType::IDENTIFIER) {

                        auto item = this->_scope.getItemByName(token.get().getText());
                        if (item.get() == nullptr) {
                            if (this->_semanticsCheck)
                                return SEMANTICS_ERROR;
                        } else if (item->isVar()) {
                            auto id = item->getOffset();
                            this->_interpret.useVariable(id);
                        } else if (item->isFunc()) {
                            this->_lex.ungetToken(inputToken);
                            this->_lex.ungetToken(token);
                            int ret = this->parseSyntax(OPERATION, FUNCTIONCALL);
                            inputToken = _lex.getToken();
                            if (ret != RET_OK) return ret;
                        }

                    }
                    /**
                     * Coverts all possible tokens that are RVALUES to RVALUE
                     * IDENTIFIER or INT/STRING/FLOAT/BOOL literals -> RVALUE
                     */
                    tokenStack.pop();
                    token.get().setOriginalTokenType(token.get().getTokenType());
                    token.get().setTokenType(Token::P_RVALUE);
                    tokenStack.push(token);
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
                if (tokenStack.top().get().getTokenType() == Token::P_SHIFT) {
                    tokenStack.pop();
                    token.get().setOriginalTokenType(token.get().getTokenType());
                    token.get().setTokenType(Token::P_RVALUE);
                    tokenStack.push(token);
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

                    this->genLongOperation(i);
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
                    this->genShortOperation(i);
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

        std::stack<std::reference_wrapper<Token>> tokenStack;

        tokenStack.push(std::ref(Syntax::ImplicitToken));

        bool run = true;

        do {
            std::reference_wrapper<Token> inputToken = this->_lex.getToken();
            std::reference_wrapper<Token> topToken = this->getFirstTerminalFromTop(tokenStack);

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

            this->visualizeStack(tokenStack);

            DEBUG("Switch:");
            DEBUG("Row: " << topToken.get().getTokenType() << " " << "Column:" << inputToken.get().getTokenType());

            switch( Syntax::precedence_table
                        [topToken.get().getTokenType()]
                        [inputToken.get().getTokenType()] ) {

                case R:
                    DEBUG("R - Branch");
                    if (this->reduceStack(tokenStack, inputToken)) {
                        inputToken.get().setTokenType(inputToken.get().getOriginalTokenType());
                        _lex.ungetToken(inputToken);
                        return 1;
                    }
                    _lex.ungetToken(inputToken);
                    break;

                case S:
                    DEBUG("S - Branch");
                    this->putShiftToken(tokenStack, topToken);
                    tokenStack.push(inputToken);
                    break;

                case H:
                    DEBUG("H - Branch");
                    tokenStack.push(inputToken);
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

        if (tokenStack.size() != 2) {
            DEBUG("ParseExpression didn't empty stack");
            DEBUG(" -> 1");
            return 1;
        } else {
            tokenStack.pop();
            tokenStack.pop();
        }

        return 0;
    }

    int Syntax::parseSyntax(int nonTerminal, int inGrammarRule){

        /* Static variables used for semantics check */
        static SymbolTableItem::Type dataType;
        static std::string actualScope = _globalScopeName;
        static std::vector<std::string> calledFunctionName;
        static std::vector<size_t> paramCnt;
        static std::vector<std::vector<std::pair<SymbolTableItem::Type, std::string>>> calledFuncArgs;

        /* actual token */
        std::reference_wrapper<Token> actualToken = this->_lex.getToken();

        long jumpAddress = 0;
        long jumpBackAddress = 0;

        static std::shared_ptr<SymbolTableItem> variable = nullptr;
        static std::shared_ptr<SymbolTableItem> function = nullptr;


        /* Return code 0 by default */
        int ret = RET_OK;

        if(nonTerminal > START) {
            DEBUG("==================================");
            DEBUG("going through nonTerminal: " << nonTerminalsMap[static_cast<nonTerminals>(nonTerminal)] << " Token: " << actualToken.get().getText());
            DEBUG("==================================");
        } else {
            DEBUG("==================================");
            DEBUG("going through Terminal:");
            actualToken.get().print();
            DEBUG("==================================");
        }

        if (_semanticsCheck) {
            DEBUG("_________________________________________________________SYMBOL_TABLE:");
            DEBUG("\nIn scope: " << actualScope << "\n");
            _scope.printScope();
            DEBUG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SEMANTICS");
        }

        switch (nonTerminal) {
            /****************************/
            case START:
            /*   START ⇒ #include lrkv; FUNCTIONS MAINPROGRAM */
                _lex.ungetToken(actualToken);
                ret = parseSyntax(FUNCTIONS, inGrammarRule);
                break;

            /****************************/

            case INLINE_START:
            /*   INLINE_START ⇒ ε | IFSTMNT | FORSTMT | WHILESTMT | STATEMENTS | FUNCDECL_INLINE + CONT_INLINE*/
                _lex.ungetToken(actualToken);

                if (actualToken.get().getTokenType() == Token::END_TOKEN){ // EMPTY
                    break;
                } else if (actualToken.get().getTokenType() == Token::KW_IF){
                    if ((ret = parseSyntax(IFSTMNT, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(CONT_INLINE, inGrammarRule);
                    }
                } /*else if(actualToken.get().getTokenType() == Token::KW_FOR){
                    if ((ret = parseSyntax(FORSTMT, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(CONT_INLINE, inGrammarRule);
                    }
                }*/ else if(actualToken.get().getTokenType() == Token::KW_WHILE){
                    if ((ret = parseSyntax(WHILESTMT, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(CONT_INLINE, inGrammarRule);
                    }
                } else {
                    bool jumpInlineFunc = false;
                    std::vector<Token> hax_stack;

                    // eat 3 tokens vector HAX to distinguish between FUNCDECL_INLINE and inline STATEMENTS
                    hax_stack.push_back(this->_lex.getToken());
                    hax_stack.push_back(this->_lex.getToken());
                    hax_stack.push_back(this->_lex.getToken());

                    if ((hax_stack.front().getTokenType() >= Token::KW_VOID && \
                            hax_stack.front().getTokenType() <= Token::KW_FLOAT) \
                        && hax_stack.back().getTokenType() == Token::BRACKET_ROUND_OPEN) {
                        jumpInlineFunc = true;
                    }
                    // return 3 tokens
                    _lex.ungetToken(hax_stack.back());
                    hax_stack.pop_back();
                    _lex.ungetToken(hax_stack.back());
                    hax_stack.pop_back();
                    _lex.ungetToken(hax_stack.back());
                    hax_stack.pop_back();

                    if (jumpInlineFunc) {
                        if ((ret = parseSyntax(FUNCDECL_INLINE, inGrammarRule)) != RET_OK){
                            break;
                        } else {
                            ret = parseSyntax(CONT_INLINE, inGrammarRule);
                        }
                    } else {
                        if ((ret = parseSyntax(STATEMENTS, inGrammarRule)) != RET_OK){
                            break;
                        } else {
                            ret = parseSyntax(CONT_INLINE, inGrammarRule);
                        }
                    }
                }
                break;

            case CONT_INLINE:
            /*   CONT_INLINE ⇒ ε | INLINE_START */
                if (actualToken.get().getTokenType() == Token::END_TOKEN){
                    break;
                } else {
                    _lex.ungetToken(actualToken);
                    ret = parseSyntax(INLINE_START, inGrammarRule);
                    break;
                }

            case FUNCDECL_INLINE:
            /*   FUNCDECL_INLINE ⇒ FUNCDECL CONT_INLINE */
                _lex.ungetToken(actualToken);

                if ((ret = parseSyntax(FUNCDECL, FUNCDECL)) != RET_OK){
                    break;
                } else {
                    ret = parseSyntax(CONT_INLINE, inGrammarRule);
                    break;
                }

            case FUNCTIONS:
            /*   FUNCTIONS ⇒ ε | FUNCDECL FUNCTIONS_CONT */
                _lex.ungetToken(actualToken);

                if ((ret = parseSyntax(FUNCDECL, FUNCDECL)) != RET_OK){
                    break;
                } else {
                    ret = parseSyntax(FUNCTIONS_CONT, inGrammarRule);
                    break;
                }

            /****************************/
            case FUNCTIONS_CONT:
            /*   FUNCTIONS_CONT ⇒ ε | FUNCTIONS */
                if (actualToken.get().getTokenType() == Token::END_TOKEN){
                    break;
                } else {
                    _lex.ungetToken(actualToken);
                    ret = parseSyntax(FUNCTIONS, inGrammarRule);
                    break;
                }

            /****************************/
            case FUNCDECL:
            /*   FUNCDECL ⇒ HEAD TAIL  */
                _lex.ungetToken(actualToken);

                if ((ret = parseSyntax(HEAD, inGrammarRule)) != RET_OK){
                    break;
                } else {
                    ret = parseSyntax(TAIL, inGrammarRule);
                    if (_semanticsCheck) {
                        _scope.leaveScope();
                        actualScope = _globalScopeName;
                    }
                    break;
                }

            /****************************/
            case TAIL:
            /*  TAIL ⇒ ; | { BODY } */
                _lex.ungetToken(actualToken);

                if (actualToken.get().getTokenType() == Token::BRACKET_CURLY_OPEN){
                    ret = parseSyntax(BODY, inGrammarRule);
                } /* else if (actualToken.get().getTokenType() == Token::SEMICOLON){
                    ret = parseSyntax(Token::SEMICOLON, inGrammarRule); // FIXME uncomment this to support func declaration rule. // TODO logic for this needs to be added
                }*/ else {
                    ret = SYNTAX_ERROR;
                }
                break;

            /****************************/
            case HEAD:
            /*   HEAD ⇒ DECL ( ARGUMENTS ) */
                _lex.ungetToken(actualToken);

                this->_interpret.append(Interpret::Instructions::JUMP, -1L);
                if ((ret = parseSyntax(DECL, inGrammarRule)) != RET_OK){
                    break;
                }
                if (function.get() != nullptr) {
                    this->_interpret.append(Interpret::Instructions::NOP, function->getName());
                    function->setJumpIndex(this->_interpret.getIP()-2);
                }
                if ((ret = parseSyntax(Token::BRACKET_ROUND_OPEN, inGrammarRule)) != RET_OK){
                    break;
                }
                if ((ret = parseSyntax(ARGUMENTS, ARGUMENTS)) != RET_OK){
                    break;
                }

                if (function.get() != nullptr){
                    int index = function->getArgs().size()-1;
                    for (std::vector<std::pair<SymbolTableItem::Type, std::string>>::const_reverse_iterator rit = function->getArgs().crbegin(); function->getArgs().crend() != rit ; ++rit) {
                        this->_interpret.append(Interpret::Instructions::LOAD, -3L-(long)(index--));
                    }
                }

                ret = parseSyntax(Token::BRACKET_ROUND_CLOSE, inGrammarRule);
                break;

            /****************************/
            case DECL :
            /*  DECL ⇒ TYPE NAME */
                _lex.ungetToken(actualToken);

                if ((ret = parseSyntax(TYPE, inGrammarRule)) != RET_OK){
                    break;
                }
                ret = parseSyntax(NAME, inGrammarRule);
                break;

            /****************************/
            case ARGUMENTS :
            /*  ARGUMENTS ⇒ ε | DECL ARGUMENTS_N  */
                _lex.ungetToken(actualToken);
                if (actualToken.get().getTokenType() == Token::BRACKET_ROUND_CLOSE){
                    break;
                } else if ((ret = parseSyntax(DECL, inGrammarRule)) != RET_OK){
                    break;
                } else {
                    ret = parseSyntax(ARGUMENTS_N, inGrammarRule);
                    break;
                }

            /****************************/
            case ARGUMENTS_N :
            /*   ARGUMENTS ⇒ ε | , DECL ARGUMENTS_N  */
                _lex.ungetToken(actualToken);
                if (actualToken.get().getTokenType() == Token::BRACKET_ROUND_CLOSE){
                    break; // END_OF_ARGUMENTS_N
                } else if (actualToken.get().getTokenType() == Token::COMMA) {
                    if ((ret = parseSyntax(Token::COMMA, inGrammarRule)) != RET_OK){
                        break;
                    } else if ((ret = parseSyntax(DECL, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(ARGUMENTS_N, inGrammarRule);
                    }
                } else {
                    ret = SYNTAX_ERROR;
                }
                break;

            /****************************/
            case BODY :
            /*   BODY ⇒  STATEMENT CONTSTMNT  */
                _lex.ungetToken(actualToken);
                if (inGrammarRule != FUNCDECL) {
                    _scope.enterScope(false);
                }
                if ((ret = parseSyntax(Token::BRACKET_CURLY_OPEN, inGrammarRule)) != RET_OK ){
                    break;
                } else if ((ret = parseSyntax(STATEMENT, inGrammarRule)) != RET_OK) {
                    break;
                } else {
                    ret = parseSyntax(Token::BRACKET_CURLY_CLOSE, inGrammarRule);
                    if (inGrammarRule == FUNCDECL && function.get() != nullptr) {
                        this->_interpret.genReturn(/*void*/true);
                        auto index = function->getJumpIndex();
                        this->_interpret.getInstructionBuffer()[index]._rec._value
                            = Interpret::Operand(this->_interpret.getIP());
                    }
                }
                if (inGrammarRule != FUNCDECL) {
                    _scope.leaveScope();
                }
                break;


            /****************************/
            case CONTSTMNT :
            /*   CONTSTMNT ⇒ ε | BODY */
                _lex.ungetToken(actualToken);
                if (actualToken.get().getTokenType() == Token::BRACKET_CURLY_CLOSE) {
                    break;
                } else {
                    ret = parseSyntax(STATEMENT, inGrammarRule);
                    break;
                }

            /****************************/
            case STATEMENT :
            /*   STATEMENT ⇒ ε | IFSTMNT | FORSTMT | WHILESTMT | STATEMENTS*/
                _lex.ungetToken(actualToken);

                if (actualToken.get().getTokenType() == Token::BRACKET_CURLY_CLOSE){
                    break;
                } else if (actualToken.get().getTokenType() == Token::KW_IF){
                    if ((ret = parseSyntax(IFSTMNT, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(CONTSTMNT, inGrammarRule);
                    }
                } else if(actualToken.get().getTokenType() == Token::KW_FOR){
                    if ((ret = parseSyntax(FORSTMT, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(CONTSTMNT, inGrammarRule);
                    }
                } else if(actualToken.get().getTokenType() == Token::KW_WHILE){
                    if ((ret = parseSyntax(WHILESTMT, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(CONTSTMNT, inGrammarRule);
                    }
                } else {
                    if ((ret = parseSyntax(STATEMENTS, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(CONTSTMNT, inGrammarRule);
                    }
                }
                break;

            /****************************/
            case STATEMENTS :
            /*   STATEMENTS ⇒ STATEMENTBODY ; */
                _lex.ungetToken(actualToken);

                if ((ret = parseSyntax(STATEMENTBODY, inGrammarRule)) != RET_OK){
                    break;
                } else {
                    ret = parseSyntax(Token::SEMICOLON, inGrammarRule);
                    break;
                }

            /****************************/
            case STATEMENTBODY :
            /*   STATEMENTBODY ⇒ VARIABLEDEF | RETURNSTMT | OPERATION */
                _lex.ungetToken(actualToken);
                if (actualToken.get().getTokenType() == Token::KW_RETURN){
                    ret = parseSyntax(RETURNSTMT, RETURNSTMT);
                } else if (actualToken.get().getTokenType() == Token::IDENTIFIER){
                    ret = parseSyntax(OPERATION, OPERATION); // TODO GRAMMAR
                } else if (actualToken.get().getTokenType() >= Token::KW_INT \
                        && actualToken.get().getTokenType() <= Token::KW_FLOAT){
                    ret = parseSyntax(VARIABLEDEF, VARIABLEDEF);
                } else {
                    ret = SYNTAX_ERROR;
                }
                break;

            /****************************/
            case OPERATION :
            /*   OPERATION ⇒ NAME OPERATION_KIND */
                _lex.ungetToken(actualToken);
                if ((ret = parseSyntax(NAME, OPERATION)) != RET_OK) {
                    break;
                } else {
                    ret = parseSyntax(OPERATION_KIND, OPERATION);
                }
                break;

            /****************************/
            case OPERATION_KIND :
            /*   OPERATION_KIND ⇒ FUNCCALL, ASSIGNMENT */
                _lex.ungetToken(actualToken);
                if (actualToken.get().getTokenType() == Token::BRACKET_ROUND_OPEN){
                    ret = parseSyntax(FUNCTIONCALL, FUNCTIONCALL);
                } else if ( actualToken.get().getTokenType() == Token::ASSIGNMENT
                            && inGrammarRule != FUNCTIONCALL){
                    ret = parseSyntax(ASSIGN, ASSIGN);
                } else {
                    ret = SYNTAX_ERROR;
                }
                break;

            /****************************/
            case VARIABLEDEF :
            /*   VARIABLEDEF ⇒ TYPE NAME ASSIGN VARIABLES */
                _lex.ungetToken(actualToken);
                actualToken.get().print();
                if ((ret = parseSyntax(TYPE, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(NAME, inGrammarRule)) != RET_OK){
                    // TODO define IDENTIFIER
                    break;
                } else if ((ret = parseSyntax(ASSIGN, inGrammarRule)) != RET_OK) {
                    break;
                } else {
                    ret = parseSyntax(VARIABLEDEF_N, inGrammarRule);
                    break;
                }

            /****************************/
            case VARIABLEDEF_N :
            /*   VARIABLEDEF_N ⇒ ε | , NAME ASSIGN VARIABLEDEF_N */
                _lex.ungetToken(actualToken);
                if (actualToken.get().getTokenType() == Token::SEMICOLON) {
                    break; // VARIABLEDEF_N ⇒ ε
                } else if (actualToken.get().getTokenType() == Token::COMMA) {
                    if ((ret = parseSyntax(Token::COMMA, inGrammarRule)) != RET_OK){
                        break;
                    } else if ((ret = parseSyntax(NAME, inGrammarRule)) != RET_OK){
                        // TODO define IDENTIFIER
                        break;
                    } else if ((ret = parseSyntax(ASSIGN, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = parseSyntax(VARIABLEDEF_N, inGrammarRule);
                    }
                } else {
                    ret = SYNTAX_ERROR;
                }
                break;

            /****************************/
            case ASSIGN :
            /*   ASSIGN ⇒ ε | = EXPRESSION */
                _lex.ungetToken(actualToken);
                if (actualToken.get().getTokenType() == Token::ASSIGNMENT) {
                    if ((ret = parseSyntax(Token::ASSIGNMENT, inGrammarRule)) != RET_OK){
                        break;
                    } else if (ParseExpression() != RET_OK) {
                        ret = EXPRESSION_ERROR;
                        break;
                    } else {
                        if (variable.get() != nullptr)
                            this->_interpret.moveFromTop(variable->getOffset());
                        break;
                    }
                } else {
                    break; // ASSIGN ⇒ ε
                }

            /****************************/
            case IFSTMNT :
            /*   IFSTMNT ⇒ if ( EXPRESSION ) { BODY } ELSEBODY  */
                _lex.ungetToken(actualToken);

                if ((ret = parseSyntax(Token::KW_IF, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(Token::BRACKET_ROUND_OPEN, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = ParseExpression()) != RET_OK){
                    ret = EXPRESSION_ERROR;
		    break;
                } else if ((ret = parseSyntax(Token::BRACKET_ROUND_CLOSE, inGrammarRule)) != RET_OK){
                    break;
                } else {
                    this->_interpret.append(Interpret::Instructions::JUMPIFNOTTRUE, -1L);
                    jumpAddress = this->_interpret.getIP()-1;
                }

                if ((ret = parseSyntax(BODY, inGrammarRule)) != RET_OK){
                    break;
                } else {
                    this->_interpret.getInstructionBuffer()[jumpAddress]._rec._value
                        = Interpret::Operand(this->_interpret.getIP()+1);

                    ret = parseSyntax(ELSEBODY, inGrammarRule);
                }
                break;

            /****************************/
            case ELSEBODY :
            /*  ELSEBODY ⇒ ε | else { BODY } */
                _lex.ungetToken(actualToken);
                if (actualToken.get().getTokenType() == Token::KW_ELSE) {
                    if ((ret = parseSyntax(Token::KW_ELSE, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        this->_interpret.append(Interpret::Instructions::JUMP, -1L);
                        jumpAddress = this->_interpret.getIP()-1;

                        ret = parseSyntax(BODY, inGrammarRule);

                        this->_interpret.getInstructionBuffer()[jumpAddress]._rec._value
                            = Interpret::Operand(this->_interpret.getIP());
                    }
                } else {
                    this->_interpret.append(Interpret::Instructions::NOP);
                    break; // ELSEBODY ⇒ ε
                }

                break;


            /****************************/
            case WHILESTMT :
            /*   WHILESTMT ⇒ while ( EXPRESSION ) { BODY } */
                _lex.ungetToken(actualToken);
                if ((ret = parseSyntax(Token::KW_WHILE, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(Token::BRACKET_ROUND_OPEN, inGrammarRule)) != RET_OK){
                    break;
                } else {
                    jumpBackAddress = this->_interpret.getIP();
                }

                if ((ret = ParseExpression()) != RET_OK){
                    ret = EXPRESSION_ERROR;
                    break;
                } else {
                    this->_interpret.append(Interpret::Instructions::JUMPIFNOTTRUE, -1L);
                    jumpAddress = this->_interpret.getIP()-1;
                }

                if ((ret = parseSyntax(Token::BRACKET_ROUND_CLOSE, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(BODY, inGrammarRule)) != RET_OK) {
                    break;
                } else {
                    this->_interpret.append(Interpret::Instructions::JUMP, jumpBackAddress);
                    this->_interpret.getInstructionBuffer()[jumpAddress]._rec._value
                      = Interpret::Operand(this->_interpret.getIP());
                }
                break;

            /****************************/
            case FORSTMT :
            /*   FORSTMT ⇒ for ( VARIABLEDEF; EXPRESSION ; ASSIGNMENT ) { BODY } */
                _lex.ungetToken(actualToken);
                if ((ret = parseSyntax(Token::KW_FOR, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(Token::BRACKET_ROUND_OPEN, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(VARIABLEDEF, VARIABLEDEF)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(Token::SEMICOLON, inGrammarRule)) != RET_OK){
                    break;
                } else if (ParseExpression() != RET_OK){
                    ret = EXPRESSION_ERROR;
                } else if ((ret = parseSyntax(Token::SEMICOLON, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(ASSIGNMENT, inGrammarRule)) != RET_OK){
                    break;
                } else if ((ret = parseSyntax(Token::BRACKET_ROUND_CLOSE, inGrammarRule)) != RET_OK){
                    break;
                } else {
                    ret = parseSyntax(BODY, inGrammarRule);
                }
                break;

            /****************************/
            case RETURNSTMT :
            /*   RETURNSTMT ⇒ return EXPRESSION */
                _lex.ungetToken(actualToken);

                if ((ret = parseSyntax(Token::KW_RETURN, inGrammarRule)) != RET_OK){
                    break;
                } else if (! _semanticsCheck || static_cast<Token::tokenType>(_scope.getItemByName(actualScope).get()->getType()) != Token::KW_VOID){
                    // if function type is void bare return is ok

                    if (ParseExpression() != RET_OK && _semanticsCheck) {
                        ret = EXPRESSION_ERROR;
                        break;
                    }
                    this->_interpret.genReturn(/*void*/false);
                } else {
                    this->_interpret.genReturn(/*void*/true);
                }
                break;

            /****************************/
            case ASSIGNMENT :
            /*   ASSIGNMENT ⇒ NAME = EXPRESSION */
                _lex.ungetToken(actualToken);
                if ((ret = parseSyntax(NAME, ASSIGNMENT)) != RET_OK) {
                    break;
                } else if ((ret = parseSyntax(Token::ASSIGNMENT, inGrammarRule)) != RET_OK){
                    break;
                } else if (ParseExpression() != RET_OK) {
                    ret = EXPRESSION_ERROR;
                }
                break;

            /****************************/
            case TYPE:
            /*   TYPE ⇒ int|string|bool|float in case of FUNCDECL void allowed*/
                if (!(actualToken.get().getTokenType() >= Token::KW_INT \
                    && actualToken.get().getTokenType() <= Token::KW_FLOAT)
                    && !(inGrammarRule == FUNCDECL && actualToken.get().getTokenType() == Token::KW_VOID)){
                    DEBUG(actualToken.get().getText());
                    ret = SYNTAX_ERROR;
                } else {
                    dataType = static_cast<SymbolTableItem::Type>(actualToken.get().getTokenType());
                }
                break;

            /****************************/
            case FUNCTIONCALL:
            /*   FUNCTIONCALL ⇒ NAME ( PARAMETERS ) */
                _lex.ungetToken(actualToken);
                if ((ret = parseSyntax(Token::BRACKET_ROUND_OPEN, inGrammarRule)) != RET_OK){
                    break;
                } else {
                    if (_semanticsCheck){
                        auto calledFunc = _scope.getItemByName(calledFunctionName.back()); // get function from symbol table
                        DEBUG("____________________________________________________________________SEMANTICS");
                        DEBUG("Checking function call:" << calledFunctionName.back());
                        if(calledFunc.get() == nullptr || ! calledFunc->isFunc()){
                            DEBUG("SEMANTICS ERROR: Function '" << calledFunctionName.back() << "' is not defined");
                            ret = SEMANTICS_ERROR;
                            break;
                        }
                        calledFuncArgs.push_back(calledFunc->getArgs());
                        // DEBUG("SUPERDEBUG ARGvectorSIZE"<< calledFuncArgs.back().size());
                        paramCnt.push_back(0);
                    }

                    if ((ret = parseSyntax(PARAMETERS, PARAMETERS)) != RET_OK){
                        break;
                    } else {
                        if (_semanticsCheck){
                            auto calledFunc = _scope.getItemByName(calledFunctionName.back());

                            if (paramCnt.back() != calledFuncArgs.back().size()){
                                ret = SEMANTICS_ERROR;
                                DEBUG(calledFunctionName.size());
                                calledFunctionName.pop_back();
                                calledFuncArgs.pop_back();
                                paramCnt.pop_back();
                                break;
                            } else {
                                calledFunctionName.pop_back();
                                calledFuncArgs.pop_back();
                                paramCnt.pop_back();
                            }
                            ret = parseSyntax(Token::BRACKET_ROUND_CLOSE, inGrammarRule);
                            if(calledFunc.get() != nullptr) {
                                this->_interpret.genFunCall(calledFunc->getStartAddress());
                                Interpret::Instructions inst = Interpret::Instructions::POPN;
                                if (calledFunc->getType() == SymbolTableItem::Type::VOID) inst = Interpret::Instructions::POP;
                                for(size_t i = 0 ; i < calledFunc->getArgs().size() ; i++) {
                                    this->_interpret.append(inst);
                                }
                            }
                        } else {
                            ret = parseSyntax(Token::BRACKET_ROUND_CLOSE, inGrammarRule);
                        }
                    }
                    break;
                }

            /****************************/
            case PARAMETERS:
            /*    */
                _lex.ungetToken(actualToken);

                if (actualToken.get().getTokenType() == Token::BRACKET_ROUND_CLOSE){
                    break;
                } else {
                    ret = ParseExpression();
                    if (_semanticsCheck) {
                        DEBUG("____________________________________________________________________SEMANTICS");
                        DEBUG("Checking Parameters of function:" << calledFunctionName.back());
                        // DEBUG("SUPERDEBUG " << calledFunctionName.back() << " SIZEIS " << calledFuncArgs.back().size() );
                        // DEBUG("SUPERDEBUG " << "Expr" << " RETIS " << ret );
                        if (calledFuncArgs.back().size() != 0 && ret != RET_OK) {
                            DEBUG("SEMANTICS ERROR: Parameter '" << actualToken.get().getText() << "' does not match the called function's positional argument data type");
                            ret = SEMANTICS_ERROR;
                            break;
                        } else {
                            paramCnt.back()++;
                        }
                        DEBUG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SEMANTICS");
                    }

                    if (ret != RET_OK) {
                        ret = EXPRESSION_ERROR;
                        break;
                    } else {
                        ret = parseSyntax(PARAMETERS_N, inGrammarRule);
                        break;
                    }
                }


            /****************************/
            case PARAMETERS_N:
            /*    */
                _lex.ungetToken(actualToken);

                if (actualToken.get().getTokenType() == Token::BRACKET_ROUND_CLOSE){
                    break;
                } else if (actualToken.get().getTokenType() == Token::COMMA){
                    if ((ret = parseSyntax(Token::COMMA, inGrammarRule)) != RET_OK){
                        break;
                    } else {
                        ret = ParseExpression();
                        if (_semanticsCheck) {
                            DEBUG("____________________________________________________________________SEMANTICS");
                            DEBUG("Checking Parameters of function:" << calledFunctionName.back());
                            if (calledFuncArgs.back().size() != 0 && ret != RET_OK) { // FIXME check the type of expression
                                ret = SEMANTICS_ERROR;
                                break;
                            } else {
                                paramCnt.back()++;
                            }
                            DEBUG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SEMANTICS");
                        }

                        if (ret != RET_OK) {
                            ret = EXPRESSION_ERROR;
                            break;
                        } else {
                            ret = parseSyntax(PARAMETERS_N, inGrammarRule);
                            break;
                        }
                    }
                } else {
                    ret = SYNTAX_ERROR;
                }
                break;

            /****************************/
            case NAME: // terminal IDENTIFIER
                if (actualToken.get().getTokenType() != Token::IDENTIFIER \
                    && ! actualToken.get().isLiteral()){
                    ret = SYNTAX_ERROR;
                } else {
                    if (_semanticsCheck && actualToken.get().getTokenType() == Token::IDENTIFIER) { // FIXME
                        switch (inGrammarRule) {
                            case ARGUMENTS:{
                                DEBUG("____________________________________________________________________SEMANTICS");
                                DEBUG("Defining function argument:" << actualToken.get().getText());
                                auto actualFunction = _scope.getItemByName(actualScope);
                                if (actualFunction.get() == nullptr) {
                                    DEBUG("SEMANTICS ERROR: Function '" << actualToken.get().getText() << "' does not exist");
                                    ret = SEMANTICS_ERROR;
                                } else {
                                    actualFunction->addArg(dataType, actualToken.get().getText());
                                }
                                DEBUG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SEMANTICS");
                            }/* FALLTHRU */

                            case VARIABLEDEF:{
                                DEBUG("____________________________________________________________________SEMANTICS");
                                DEBUG("Defining variable:" << actualToken.get().getText());
                                variable = _scope.define(actualToken.get().getText(), SymbolTableItem::Kind::VARIABLE);
                                if (variable.get() == nullptr) {
                                    DEBUG("SEMANTICS ERROR: Function '" << actualToken.get().getText() << "' already exists in this scope, can not define variable with same name");
                                    ret = SEMANTICS_ERROR;
                                } else {
                                    variable->setType(dataType);
                                    if (inGrammarRule == VARIABLEDEF ) {
                                        this->_interpret.pushVariable(dataType);
                                    }

                                }
                                DEBUG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SEMANTICS");
                            } break;

                            case FUNCDECL:{
                                DEBUG("____________________________________________________________________SEMANTICS");
                                DEBUG("Defining function:" << actualToken.get().getText());
                                function =_scope.define(actualToken.get().getText(), SymbolTableItem::Kind::FUNCTION);
                                if (function.get() == nullptr) {
                                    DEBUG("SEMANTICS ERROR: Name '" << actualToken.get().getText() << "' already exists in this scope, can not define function with same name");
                                    ret = SEMANTICS_ERROR;
                                } else {
                                    function->setType(dataType);
                                    function->setStartAddress(this->_interpret.getIP());
                                    actualScope = actualToken.get().getText();
                                    _scope.enterScope(/*new*/true);
                                }
                                DEBUG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SEMANTICS");
                            } break;

                            case ASSIGNMENT:{
                            }/* FALLTHRU */
                            case OPERATION:{
                                DEBUG("____________________________________________________________________SEMANTICS");
                                DEBUG("Checking existence of:" << actualToken.get().getText());
                                if (! _scope.isDefined(actualToken.get().getText(), SymbolTableItem::Kind::VARIABLE) &&
                                        ! _scope.isDefined(actualToken.get().getText(), SymbolTableItem::Kind::FUNCTION)){
                                    DEBUG("SEMANTICS ERROR: Name '" << actualToken.get().getText() << "' is not defined");
                                    ret = SEMANTICS_ERROR;
                                } else {
                                    DEBUG("\n\n\n\n\n____________________________________________________________________\n\nPUSH:" <<actualToken.get().getText());
                                    calledFunctionName.push_back(actualToken.get().getText());
                                }
                                DEBUG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SEMANTICS");
                            } break;

                            default:{
                                DEBUG("Something bad happened in " << nonTerminalsMap[static_cast<nonTerminals>(inGrammarRule)] << " rule with " << nonTerminalsMap[static_cast<nonTerminals>(nonTerminal)] << " , please call the priest!" );
                                ret = INTERNAL_ERROR;
                            } break;

                        }

                        DEBUG("___________________________________________________________SYMBOL_TABLE_AFER:");
                        DEBUG("\nScope after: " << actualScope << "\n");
                        _scope.printScope();
                        DEBUG("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^SEMANTICS");
                        break;
                    }
                    DEBUG("I just ate: '" << actualToken.get().getText() << "' OMNOMNOM");
                }
                break;

            default: /*   other TERMINALS
                In case that this method has been invoked with parameter
                nonTerminal set to scope for terminals it checks actualToken
                for terminal which has to follow. */
                if (nonTerminal != actualToken.get().getTokenType()){
                    ret = SYNTAX_ERROR;
                }
                DEBUG("I just ate: '" << actualToken.get().getText() << "' OMNOMNOM");
                break;
        }

        if(nonTerminal > START) {
            DEBUG("==================================");
            DEBUG("going out nonTerminal: " << nonTerminalsMap[static_cast<nonTerminals>(nonTerminal)] << " Token: " << actualToken.get().getText() << " RC: " << ret);
            DEBUG("==================================");
        } else {
            DEBUG("==================================");
            DEBUG("going out Terminal:");
            actualToken.get().print();
            DEBUG("==================================");
        }

        return ret;
    }

}
