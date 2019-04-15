#pragma once

#include <vector>
#include <stack>

#include "semantic/Semantic.hpp"
#include "util/variant.hpp"

namespace TPJparser {
    namespace Interpret {

        using Operand = nonstd::variant<long, double, bool, std::string>;

        struct StackRecord {
            SymbolTableItem::Type _type;
            Operand _value;

            StackRecord(SymbolTableItem::Type type, Operand value);
            void castTo(SymbolTableItem::Type type);
            void print() const;
        };

        enum Instructions {
NOP = 1,
SUM,
SUB,
MUL,
DIV,
NEG,
MINUS,
OR,
AND,
EQ,
MORE,
LESS,
MOEQ,
LOEQ,
NEQ,
CALL,
RET,
PUSH,
POP,
POPN,
LOAD,
STORE,
SAVEBP,
RESTOREBP,
JUMP,
JUMPIFNOTTRUE,
DUP,
PRINT,
CASTINT,
CASTFLOAT,
CASTBOOL,
CASTSTRING,
        };

        const std::map<Instructions, std::string> InstructionsMap {
            { NOP, "NOP"},
            { SUM, "SUM" },
            { SUB, "SUB" },
            { MUL, "MUL" },
            { DIV, "DIV" },
            { NEG, "NEG" },
            { MINUS, "MINUS" },
            { OR, "OR" },
            { AND, "AND" },
            { EQ, "EQ" },
            { MORE, "MORE" },
            { LESS, "LESS" },
            { MOEQ, "MOEQ" },
            { LOEQ, "LOEQ" },
            { NEQ, "NEQ" },
            { CALL, "CALL" },
            { RET, "RET" },
            { PUSH, "PUSH" },
            { POP, "POP" },
            { POPN, "POPN" },
            { LOAD, "LOAD" },
            { STORE, "STORE" },
            { SAVEBP, "SAVEBP" },
            { RESTOREBP, "RESTOREBP" },
            { JUMP, "JUMP"},
            { JUMPIFNOTTRUE, "JUMPIFNOTTRUE"},
            { DUP, "DUP"},
            { PRINT, "PRINT" },
            { CASTINT, "CASTINT," },
            { CASTFLOAT, "CASTFLOAT," },
            { CASTBOOL, "CASTBOOL," },
            { CASTSTRING, "CASTSTRING," },
        };

        struct Instruction {
            Instructions _type;
            StackRecord _rec;

            Instruction(Instructions type, StackRecord s);
            // void print();

        };

        class myStack : public std::vector<StackRecord> {
            public:
                void sum();
                void sub();
                void mul();
                void div();
                void neg();
                void minus();
                void oor();
                void aand();

                void eq();
                void more();
                void less();
                void moeq();
                void loeq();
                void neq();

                void push(StackRecord& s);
                void pop();
                void popn();
                void print();
                void castInt();
                void castFloat();
                void castBool();
                void castString();

                void op(const char& op);

                void load(StackRecord& s, long bp);
                void store(StackRecord& s, long bp);

                void dup();

                void printContent() const;
        };

        class Interpret {
            public:
                Interpret();
                int run();

                void append(Instructions inst);
                void append(Instructions inst, long value);
                void append(Instructions inst, double value);
                void append(Instructions inst, bool value);
                void append(Instructions inst, const std::string& value);

                void pushLiteral(Token& token);
                void pushLiteral(long value);
                void pushLiteral(double value);
                void pushLiteral(bool value);
                void pushLiteral(const std::string& value);

                void pushVariable(SymbolTableItem::Type type);
                void useVariable(long id);
                void moveFromTop(long id);

                void dupTop();

                void genFunCall(long address);
                void genReturn(bool _void);

                myStack& getStack();
                std::vector<Instruction>& getInstructionBuffer();
                long getIP();

                void printCode() const;


            private:
                int execute(Instruction& i);

                void call(const StackRecord& s);
                void ret(const StackRecord& s);
                void saveBP();
                void restoreBP();
                void saveIP();
                void restoreIP();
                void jump(const StackRecord& s);
                void jumpIfNotTrue(const StackRecord& s);

                size_t _ip;
                size_t _bp;
                std::vector<Instruction> _inst;
                myStack _stack;
        };
    }
}
