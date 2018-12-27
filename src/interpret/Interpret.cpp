#include <string>

#include "Interpret.hpp"
#include "util/Logger.hpp"
#include <map>

namespace TPJparser {
    namespace Interpret {
        StackRecord::StackRecord(SymbolTableItem::Type type, Operand value)
          :  _type(type),
             _value(value) {}

        void StackRecord::castTo(SymbolTableItem::Type castType) {
            auto& actualType = this->_type;

            if (actualType == castType) return;

            DEBUG(SymbolTableItem::TypeMap.at(actualType) << " >> " << SymbolTableItem::TypeMap.at(castType) << std::endl);

            switch(actualType) {
                case SymbolTableItem::Type::BOOL: {
                    auto value = nonstd::get<bool>(this->_value);
                    switch(castType) {
                        case SymbolTableItem::Type::BOOL:
                            break;
                        case SymbolTableItem::Type::INT:
                            actualType = SymbolTableItem::Type::INT;
                            this->_value = Operand(static_cast<long>(value));
                            break;
                        case SymbolTableItem::Type::FLOAT:
                            actualType = SymbolTableItem::Type::FLOAT;
                            this->_value = Operand(static_cast<double>(value));
                            break;
                        case SymbolTableItem::Type::STRING:
                            actualType = SymbolTableItem::Type::STRING;
                            this->_value = Operand(static_cast<std::string>(value ? "1" : "0"));
                            break;
                        case SymbolTableItem::Type::VOID:
                            actualType = SymbolTableItem::Type::VOID;
                            this->_value = Operand("void");
                            break;
                        default:
                            break;
                    }
                }
                break;


                case SymbolTableItem::Type::INT: {
                    auto value = nonstd::get<long>(this->_value);
                    switch(castType) {
                        case SymbolTableItem::Type::BOOL:
                            actualType = SymbolTableItem::Type::BOOL;
                            this->_value = Operand(static_cast<bool>(value));
                            break;
                        case SymbolTableItem::Type::INT:
                            break;
                        case SymbolTableItem::Type::FLOAT:
                            actualType = SymbolTableItem::Type::FLOAT;
                            this->_value = Operand(static_cast<double>(value));
                            break;
                        case SymbolTableItem::Type::STRING:
                            actualType = SymbolTableItem::Type::STRING;
                            this->_value = Operand(std::to_string(value));
                            break;
                        case SymbolTableItem::Type::VOID:
                            actualType = SymbolTableItem::Type::VOID;
                            this->_value = Operand("void");
                            break;
                        default:
                            break;
                    }
                }
                break;


                case SymbolTableItem::Type::FLOAT: {
                    auto value = nonstd::get<double>(this->_value);
                    switch(castType) {
                        case SymbolTableItem::Type::BOOL:
                            actualType = SymbolTableItem::Type::BOOL;
                            this->_value = Operand(static_cast<bool>(value));
                            break;
                        case SymbolTableItem::Type::INT:
                            actualType = SymbolTableItem::Type::INT;
                            this->_value = Operand(static_cast<long>(value));
                            break;
                        case SymbolTableItem::Type::FLOAT:
                            break;
                        case SymbolTableItem::Type::STRING:
                            actualType = SymbolTableItem::Type::STRING;
                            this->_value = Operand(std::to_string(value));
                            break;
                        case SymbolTableItem::Type::VOID:
                            actualType = SymbolTableItem::Type::VOID;
                            this->_value = Operand("void");
                            break;
                        default:
                            break;
                    }
                }
                break;


                case SymbolTableItem::Type::STRING: {
                    auto value = nonstd::get<std::string>(this->_value);
                    switch(castType) {
                        case SymbolTableItem::Type::BOOL:
                            actualType = SymbolTableItem::Type::BOOL;
                            this->_value = Operand(value != "");
                            break;
                        case SymbolTableItem::Type::INT:
                            actualType = SymbolTableItem::Type::INT;
                            this->_value = Operand(std::stol(value));
                            break;
                        case SymbolTableItem::Type::FLOAT:
                            actualType = SymbolTableItem::Type::FLOAT;
                            this->_value = Operand(std::stod(value));
                            break;
                        case SymbolTableItem::Type::STRING:
                            break;
                        case SymbolTableItem::Type::VOID:
                            actualType = SymbolTableItem::Type::VOID;
                            this->_value = Operand("void");
                            break;
                        default:
                            break;
                    }
                }
                break;


                case SymbolTableItem::Type::VOID: {
                    DEBUG("Trying to cast void!");
                }
                break;

            }
        }

        void StackRecord::print() {
#ifdef DEBUG_MODE
            switch (this->_type) {
                case SymbolTableItem::Type::BOOL:
                    DEBUG("BOOL " << nonstd::get<bool>(this->_value));
                    break;

                case SymbolTableItem::Type::INT:
                    DEBUG("INT " << nonstd::get<long>(this->_value));
                    break;

                case SymbolTableItem::Type::STRING:
                    DEBUG("STRING " << nonstd::get<std::string>(this->_value));
                    break;

                case SymbolTableItem::Type::FLOAT:
                    DEBUG("FLOAT " << nonstd::get<double>(this->_value));
                    break;

                case SymbolTableItem::Type::VOID:
                    DEBUG("VOID");
                    break;
            }
#endif
        }

        Instruction::Instruction(Instructions type, StackRecord s)
          :  _type(type),
             _rec(s) {}

        Interpret::Interpret()
          :  _ip(0) {}

        int Interpret::run() {
            for ( ; this->_ip < this->_inst.size() ; this->_ip++ ) {
                if(this->execute(this->_inst[this->_ip])) {
                    return 1;
                }
            }
            return 0;
        }

        void Interpret::append(Instructions inst) {
            this->_inst.push_back(Instruction(inst, StackRecord(SymbolTableItem::Type::VOID, Operand("something"))));
        }

        void Interpret::append(Instructions inst, long value) {
            this->_inst.push_back(Instruction(inst, StackRecord(SymbolTableItem::Type::INT, Operand(value))));
        }

        void Interpret::append(Instructions inst, double value) {
            this->_inst.push_back(Instruction(inst, StackRecord(SymbolTableItem::Type::FLOAT, Operand(value))));
        }

        void Interpret::append(Instructions inst, bool value) {
            this->_inst.push_back(Instruction(inst, StackRecord(SymbolTableItem::Type::BOOL, Operand(value))));
        }

        void Interpret::append(Instructions inst, std::string value) {
            this->_inst.push_back(Instruction(inst, StackRecord(SymbolTableItem::Type::STRING, Operand(value))));
        }

        void Interpret::pushLiteral(Token& token) {

            if(!token.isLiteral()) return;

            switch(token.getOriginalTokenType()) {
                case Token::INTEGER:
                    this->append(PUSH, std::stol(token.getText()));
                    break;

                case Token::FLOAT:
                    this->append(PUSH, std::stod(token.getText()));
                    break;

                default:
                    this->append(PUSH, token.getText());
                    break;
            }
        }

        int Interpret::execute(Instruction& i) {

            DEBUG(InstructionsMap.at(i._type));
            i._rec.print();
            DEBUG("" << std::endl);

            switch(i._type) {
                case SUM:
                    this->_stack.sum();
                    break;
                case SUB:
                    this->_stack.sub();
                    break;
                case MUL:
                    this->_stack.mul();
                    break;
                case DIV:
                    this->_stack.div();
                    break;
                case NEG:
                    this->_stack.neg();
                    break;
                case MINUS:
                    this->_stack.minus();
                    break;
                case OR:
                    this->_stack.oor();
                    break;
                case AND:
                    this->_stack.aand();
                    break;
                case EQ:
                    this->_stack.eq();
                    break;
                case MORE:
                    this->_stack.more();
                    break;
                case LESS:
                    this->_stack.less();
                    break;
                case MOEQ:
                    this->_stack.moeq();
                    break;
                case LOEQ:
                    this->_stack.loeq();
                    break;
                case NEQ:
                    this->_stack.neq();
                    break;
                case CALL:
                    this->_stack.call();
                    break;
                case RET:
                    this->_stack.ret();
                    break;
                case PUSH:
                    this->_stack.push(i._rec);
                    break;
                case POP:
                    this->_stack.pop();
                    break;
                case PRINT:
                    this->_stack.print();
                    break;
                default:
                    DEBUG("Execute error!");
                    return 1;
            }
            return 0;
        }

        void myStack::sum() {
            this->op('+');
        }

        void myStack::sub() {
            this->op('-');
        }

        void myStack::mul() {
            this->op('*');
        }

        void myStack::div() {
            this->op('/');
        }

        void myStack::eq() {
            this->op('e'); // ==
        }

        void myStack::more() {
            this->op('>');
        }

        void myStack::less() {
            this->op('<');
        }

        void myStack::moeq() {
            this->op(']'); // >=
        }

        void myStack::loeq() {
            this->op('['); // <=
        }

        void myStack::neq() {
            this->op('n'); // !=
        }

        void myStack::minus() {
            auto& top = this->back();

            switch (top._type) {
                case SymbolTableItem::Type::BOOL:
                    top._value = !nonstd::get<bool>(top._value);
                    break;

                case SymbolTableItem::Type::INT:
                    top._value = -nonstd::get<long>(top._value);
                    break;

                case SymbolTableItem::Type::STRING:
                    std::cerr << "Cannot put unary minus on string!!!" << std::endl;
                    break;

                case SymbolTableItem::Type::FLOAT:
                    top._value = -nonstd::get<double>(top._value);
                    break;

                case SymbolTableItem::Type::VOID:
                    std::cerr << "Cannot put unary minus on void!!!" << std::endl;
                    break;
            }
        }

        void myStack::neg() {
            auto& top = this->back();

            switch (top._type) {
                case SymbolTableItem::Type::BOOL:
                    top._value = !nonstd::get<bool>(top._value);
                    break;

                case SymbolTableItem::Type::INT:
                    top._type = SymbolTableItem::Type::BOOL;
                    top._value = !nonstd::get<long>(top._value);
                    break;

                case SymbolTableItem::Type::STRING:
                    std::cerr << "Cannot negate string!!!" << std::endl;
                    break;

                case SymbolTableItem::Type::FLOAT:
                    top._type = SymbolTableItem::Type::BOOL;
                    top._value = !nonstd::get<double>(top._value);
                    break;

                case SymbolTableItem::Type::VOID:
                    std::cerr << "Cannot negate void!!!" << std::endl;
                    break;
            }
        }

        void myStack::aand() {
            StackRecord top = this->back(); this->pop_back();

            top.castTo(SymbolTableItem::Type::BOOL);
            this->back().castTo(SymbolTableItem::Type::BOOL);

            this->back()._value = Operand(nonstd::get<bool>(this->back()._value) && nonstd::get<bool>(top._value));
        }

        void myStack::oor() {
            StackRecord top = this->back(); this->pop_back();

            top.castTo(SymbolTableItem::Type::BOOL);
            this->back().castTo(SymbolTableItem::Type::BOOL);

            this->back()._value = Operand(nonstd::get<bool>(this->back()._value) || nonstd::get<bool>(top._value));
        }

        void myStack::op(const char& c) {
            StackRecord top = this->back(); this->pop_back();
            StackRecord under = this->back(); this->pop_back();

            if(top._type == under._type) {

                switch (top._type) {
                    case SymbolTableItem::Type::INT: {
                        auto topValue = nonstd::get<long>(top._value);
                        auto underValue = nonstd::get<long>(under._value);
                        switch (c) {
                            case '+': {
                                auto result = underValue + topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '-': {
                                auto result = underValue - topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '*': {
                                auto result = underValue * topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '/': {
                                if(topValue == 0) {
                                    std::cerr << "Dividing by zero! Ignoring..." << std::endl;
                                    break;
                                }
                                auto result = underValue / topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case 'e': {
                                auto result = underValue == topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '>': {
                                auto result = underValue > topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '<': {
                                auto result = underValue < topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case ']': {
                                auto result = underValue >= topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '[': {
                                auto result = underValue <= topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case 'n': {
                                auto result = underValue != topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;

                            default:
                                std::cerr << "Unknown operation" << std::endl;
                                break;

                        }
                        this->push_back(top);

                        }
                        break;


                        case SymbolTableItem::Type::FLOAT: {
                        auto topValue = nonstd::get<double>(top._value);
                        auto underValue = nonstd::get<double>(under._value);
                        switch (c) {
                            case '+': {
                                auto result = underValue + topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '-': {
                                auto result = underValue - topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '*': {
                                auto result = underValue * topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '/': {
                                if(topValue == 0.0) {
                                    std::cerr << "Dividing by zero! Ignoring..." << std::endl;
                                    break;
                                }
                                auto result = underValue / topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case 'e': {
                                auto result = underValue == topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '>': {
                                auto result = underValue > topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '<': {
                                auto result = underValue < topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case ']': {
                                auto result = underValue >= topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '[': {
                                auto result = underValue <= topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case 'n': {
                                auto result = underValue != topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;

                            default:
                                std::cerr << "Unknown operation" << std::endl;
                                break;

                        }

                        this->push_back(top);

                        }
                        break;


                        case SymbolTableItem::Type::STRING: {
                        auto topValue = nonstd::get<std::string>(top._value);
                        auto underValue = nonstd::get<std::string>(under._value);

                        switch (c) {
                            case '+': {
                                auto result = underValue + topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case 'e': {
                                auto result = underValue == topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '>': {
                                auto result = underValue > topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '<': {
                                auto result = underValue < topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case ']': {
                                auto result = underValue >= topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case '[': {
                                auto result = underValue <= topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;
                            case 'n': {
                                auto result = underValue != topValue;
                                top._value = Operand(result);
                                top._type = SymbolTableItem::Type::BOOL;
                                }
                                break;

                            default:
                                std::cerr << "Unknown operation" << std::endl;
                                break;
                        }

                        this->push_back(top);

                        }
                        break;


                        case SymbolTableItem::Type::BOOL: {
                        auto topValue = nonstd::get<bool>(top._value);
                        auto underValue = nonstd::get<bool>(under._value);

                        switch (c) {
                            case '+': {
                                bool result = underValue + topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case 'e': {
                                auto result = underValue == topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '>': {
                                auto result = underValue > topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '<': {
                                auto result = underValue < topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case ']': {
                                auto result = underValue >= topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case '[': {
                                auto result = underValue <= topValue;
                                top._value = Operand(result);
                                }
                                break;
                            case 'n': {
                                auto result = underValue != topValue;
                                top._value = Operand(result);
                                }
                                break;
                            default:
                                std::cerr << "Unknown operation" << std::endl;
                                break;
                        }

                        this->push_back(top);

                        }
                        break;

                        default:
                            std::cerr << "Operation with VOID not permited" << std::endl;
                            break;
                }
            } else {
                if (c == 'e' || c == '>' || c == '<' || c == ']' || c == '[' || c== 'n') {
                    std::cerr << "Comparing different types, this shoud never happen!" << std::endl;
                    return;
                }
                top.castTo(under._type);
                this->push_back(under);
                this->push_back(top);

                this->op(c);
            }
        }

        void myStack::call() {

        }

        void myStack::ret() {

        }

        void myStack::push(StackRecord& s) {
            this->push_back(s);
        }

        void myStack::pop() {
            this->pop_back();
        }

        void myStack::print() {
            auto item = this->back(); this->pop();
            DEBUG(SymbolTableItem::TypeMap.at(item._type));
            switch(item._type) {
                case SymbolTableItem::Type::BOOL:
                    std::cout << nonstd::get<bool>(item._value) << std::endl;
                    break;
                case SymbolTableItem::Type::STRING:
                    std::cout << nonstd::get<std::string>(item._value) << std::endl;
                    break;
                case SymbolTableItem::Type::INT:
                    std::cout << nonstd::get<long>(item._value) << std::endl;
                    break;
                case SymbolTableItem::Type::FLOAT:
                    std::cout << nonstd::get<double>(item._value) << std::endl;
                    break;
                case SymbolTableItem::Type::VOID:
                    break;
            }
        }
    }
}