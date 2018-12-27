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
            void print();
        };

        enum Instructions {
            SUM = 1,
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
            PRINT,
            CAST,
        };

        const std::map<Instructions, std::string> InstructionsMap {
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
            { PRINT, "PRINT" },
            { CAST, "CAST" },
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

                void call();
                void ret();
                void push(StackRecord& s);
                void pop();
                void print();
                void cast();

                void op(const char& op);

                void copyToTop(size_t index);
                void copyTop(size_t index);
        };

        class Interpret {
            public:
                Interpret();
                int run();

                void append(Instructions inst);
                void append(Instructions inst, long value);
                void append(Instructions inst, double value);
                void append(Instructions inst, bool value);
                void append(Instructions inst, std::string value);

                void pushLiteral(Token& token);

            private:
                int execute(Instruction& i);

                size_t _ip;
                std::vector<Instruction> _inst;
                myStack _stack;
        };
    }
}