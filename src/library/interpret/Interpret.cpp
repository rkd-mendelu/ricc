#include <map>
#include <string>

#include "Interpret.hpp"
#include "http/HTTP.hpp"
#include "util/Logger.hpp"

namespace RICC {
namespace Interpret {
StackRecord::StackRecord(SymbolTableItem::Type type, Operand value)
    : _type(type), _value(value) {}

void StackRecord::castTo(SymbolTableItem::Type castType) {
  auto& actualType = this->_type;

  if (actualType == castType) return;

  DEBUG(SymbolTableItem::TypeMap.at(actualType)
        << " >> " << SymbolTableItem::TypeMap.at(castType) << std::endl);

  switch (actualType) {
    case SymbolTableItem::Type::BOOL: {
      auto value = nonstd::get<bool>(this->_value);
      switch (castType) {
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
    } break;

    case SymbolTableItem::Type::INT: {
      auto value = nonstd::get<long>(this->_value);
      switch (castType) {
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
    } break;

    case SymbolTableItem::Type::FLOAT: {
      auto value = nonstd::get<double>(this->_value);
      switch (castType) {
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
    } break;

    case SymbolTableItem::Type::STRING: {
      auto value = nonstd::get<std::string>(this->_value);
      switch (castType) {
        case SymbolTableItem::Type::BOOL:
          actualType = SymbolTableItem::Type::BOOL;
          this->_value = Operand(value != "");
          break;
        case SymbolTableItem::Type::INT:
          actualType = SymbolTableItem::Type::INT;
          try {
            this->_value = Operand(std::stol(value));
          } catch (...) {
            std::cerr << "Warning! : Can not cast string \"" << value
                      << "\" to integer." << std::endl;
            this->_value = Operand(0L);
          }
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
    } break;

    case SymbolTableItem::Type::VOID: {
      DEBUG("Trying to cast void!");
    } break;
  }
}

void StackRecord::print() const {
#ifdef DEBUG_MODE
  switch (this->_type) {
    case SymbolTableItem::Type::BOOL:
      DEBUG("\tBOOL " << nonstd::get<bool>(this->_value));
      break;

    case SymbolTableItem::Type::INT:
      DEBUG("\tINT " << nonstd::get<long>(this->_value));
      break;

    case SymbolTableItem::Type::STRING:
      DEBUG("\tSTRING " << nonstd::get<std::string>(this->_value));
      break;

    case SymbolTableItem::Type::FLOAT:
      DEBUG("\tFLOAT " << nonstd::get<double>(this->_value));
      break;

    case SymbolTableItem::Type::VOID:
      DEBUG("\tVOID " << nonstd::get<std::string>(this->_value));
      break;
  }
#endif
}

Instruction::Instruction(Instructions type, StackRecord s)
    : _type(type), _rec(s) {}

Interpret::Interpret()
    : _http(
          "https://github.com/rkd-mendelu/track-topology/blob/master/"
          "example-data/loks.json"),
      _ip(0),
      _bp(0),
      _inst({Instruction(NOP,
                         StackRecord(SymbolTableItem::Type::INT, Operand(0L)))})

{}

long Interpret::getIP() { return this->_inst.size(); }

void Interpret::append(Instructions inst) {
  this->_inst.push_back(
      Instruction(inst, StackRecord(SymbolTableItem::Type::VOID,
                                    Operand(std::string("void-string")))));
}

void Interpret::append(Instructions inst, long value) {
  this->_inst.push_back(Instruction(
      inst, StackRecord(SymbolTableItem::Type::INT, Operand(value))));
}

void Interpret::append(Instructions inst, double value) {
  this->_inst.push_back(Instruction(
      inst, StackRecord(SymbolTableItem::Type::FLOAT, Operand(value))));
}

void Interpret::append(Instructions inst, bool value) {
  this->_inst.push_back(Instruction(
      inst, StackRecord(SymbolTableItem::Type::BOOL, Operand(value))));
}

void Interpret::append(Instructions inst, const std::string& value) {
  this->_inst.push_back(Instruction(
      inst, StackRecord(SymbolTableItem::Type::STRING, Operand(value))));
}

void Interpret::pushLiteral(Token& token) {
  if (!token.isLiteral()) return;

  switch (token.getOriginalTokenType()) {
    case Token::INTEGER:
      this->pushLiteral(std::stol(token.getText()));
      break;

    case Token::FLOAT:
      this->pushLiteral(std::stod(token.getText()));
      break;

    case Token::BOOL:
      this->pushLiteral(token.getText() == "true" ? true : false);
      break;

    default:
      this->pushLiteral(token.getText());
      break;
  }
}

void Interpret::pushLiteral(long value) { this->append(PUSH, value); }

void Interpret::pushLiteral(bool value) { this->append(PUSH, value); }

void Interpret::pushLiteral(double value) { this->append(PUSH, value); }

void Interpret::pushLiteral(const std::string& value) {
  this->append(PUSH, value);
}

void Interpret::pushVariable(SymbolTableItem::Type type) {
  switch (type) {
    case SymbolTableItem::Type::BOOL:
      this->append(Instructions::PUSH, false);
      break;
    case SymbolTableItem::Type::INT:
      this->append(Instructions::PUSH, 0L);
      break;
    case SymbolTableItem::Type::STRING:
      this->append(Instructions::PUSH, std::string());
      break;
    case SymbolTableItem::Type::FLOAT:
      this->append(Instructions::PUSH, 0.0);
      break;
    default:
      this->append(Instructions::PUSH);
      break;
  }
}

void Interpret::useVariable(long id) { this->append(Instructions::LOAD, id); }

void Interpret::moveFromTop(long id) { this->append(Instructions::STORE, id); }

void Interpret::genFunCall(long address) {
  this->append(Instructions::CALL, address);
}

void Interpret::genReturn(bool _void) {
  this->append(Instructions::RET, _void);
}

void Interpret::call(const StackRecord& s) {
  DEBUG("");
  this->saveBP();
  this->saveIP();
  this->_ip = nonstd::get<long>(s._value) - 1;
  this->_bp = this->_stack.size();
}

void Interpret::ret(const StackRecord& s) {
  DEBUG("");
  bool _void = nonstd::get<bool>(s._value);
  StackRecord returnValue = this->_stack.back();

  while (this->_stack.size() > this->_bp) {
    this->_stack.pop_back();
  }

  this->restoreIP();
  this->restoreBP();

  if (!_void) this->_stack.push_back(returnValue);
}

void Interpret::saveBP() {
  DEBUG("");
  this->_stack.push_back(
      StackRecord(SymbolTableItem::Type::INT, (long)this->_bp));
}

void Interpret::restoreBP() {
  DEBUG("");
  this->_bp = nonstd::get<long>(this->_stack.back()._value);
  this->_stack.pop();
}

void Interpret::jump(const StackRecord& s) {
  DEBUG("");
  this->_ip = nonstd::get<long>(s._value) - 1;
}

void Interpret::jumpIfNotTrue(const StackRecord& s) {
  DEBUG("");

  auto top = this->_stack.back();
  this->_stack.pop_back();
  top.castTo(SymbolTableItem::Type::BOOL);
  if (!nonstd::get<bool>(top._value)) {
    this->_ip = nonstd::get<long>(s._value) - 1;
  }
}

void Interpret::saveIP() {
  DEBUG("");
  this->_stack.push_back(
      StackRecord(SymbolTableItem::Type::INT, (long)this->_ip));
}

void Interpret::restoreIP() {
  DEBUG("");
  this->_ip = nonstd::get<long>(this->_stack.back()._value);
  this->_stack.pop();
}

void Interpret::dupTop() { this->append(Instructions::DUP); }

myStack& Interpret::getStack() { return this->_stack; }

std::vector<Instruction>& Interpret::getInstructionBuffer() {
  return this->_inst;
}

int Interpret::run() {
  for (; this->_ip < this->_inst.size(); this->_ip++) {
    if (this->execute(this->_inst[this->_ip])) {
      return 1;
    }
  }
  return 0;
}

void Interpret::printCode() const {
  std::cout << "Printing instruction buffer!" << std::endl;
  long cnt = 0;
  for (const auto& i : this->_inst) {
    std::cout << cnt << " " << InstructionsMap.at(i._type) << " "
              << SymbolTableItem::TypeMap.at(i._rec._type) << " ";

    if (i._rec._type == SymbolTableItem::Type::INT)
      std::cout << nonstd::get<long>(i._rec._value) << std::endl;
    if (i._rec._type == SymbolTableItem::Type::FLOAT)
      std::cout << nonstd::get<double>(i._rec._value) << std::endl;
    if (i._rec._type == SymbolTableItem::Type::STRING)
      std::cout << nonstd::get<std::string>(i._rec._value) << std::endl;
    if (i._rec._type == SymbolTableItem::Type::BOOL)
      std::cout << nonstd::get<bool>(i._rec._value) << std::endl;
    if (i._rec._type == SymbolTableItem::Type::VOID)
      std::cout << nonstd::get<std::string>(i._rec._value) << std::endl;

    cnt++;
  }
  std::cout << "End of the instruction buffer" << std::endl << std::endl;
}

int Interpret::execute(Instruction& i) {
  DEBUG(std::endl
        << std::endl
        << "IP: " << this->_ip << " BP: " << this->_bp << std::endl);
  this->_stack.printContent();
  DEBUG("\t" << InstructionsMap.at(i._type));
  i._rec.print();

  switch (i._type) {
    case NOP:
      break;
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
      this->call(i._rec);
      break;
    case RET:
      this->ret(i._rec);
      this->_stack.printContent();
      break;
    case PUSH:
      this->_stack.push(i._rec);
      break;
    case POP:
      this->_stack.pop();
      break;
    case POPN:
      this->_stack.popn();
      this->_stack.printContent();
      break;
    case LOAD:
      this->_stack.load(i._rec, this->_bp);
      break;
    case STORE:
      this->_stack.store(i._rec, this->_bp);
      break;
    case SAVEBP:
      this->saveBP();
      break;
    case RESTOREBP:
      this->restoreBP();
      break;
    case JUMP:
      this->jump(i._rec);
      break;
    case JUMPIFNOTTRUE:
      this->jumpIfNotTrue(i._rec);
      break;
    case DUP:
      this->_stack.dup();
      break;
    case PRINT:
      this->_stack.print();
      break;
    case CASTINT:
      this->_stack.castInt();
      break;
    case CASTFLOAT:
      this->_stack.castFloat();
      break;
    case CASTBOOL:
      this->_stack.castBool();
      break;
    case CASTSTRING:
      this->_stack.castString();
      break;
    default:
      DEBUG("Execute error!");
      return 1;
  }
  return 0;
}

void myStack::sum() { this->op('+'); }

void myStack::sub() { this->op('-'); }

void myStack::mul() { this->op('*'); }

void myStack::div() { this->op('/'); }

void myStack::eq() {
  this->op('e');  // ==
}

void myStack::more() { this->op('>'); }

void myStack::less() { this->op('<'); }

void myStack::moeq() {
  this->op(']');  // >=
}

void myStack::loeq() {
  this->op('[');  // <=
}

void myStack::neq() {
  this->op('n');  // !=
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
  StackRecord top = this->back();
  this->pop_back();

  top.castTo(SymbolTableItem::Type::BOOL);
  this->back().castTo(SymbolTableItem::Type::BOOL);

  this->back()._value = Operand(nonstd::get<bool>(this->back()._value) &&
                                nonstd::get<bool>(top._value));
}

void myStack::oor() {
  StackRecord top = this->back();
  this->pop_back();

  top.castTo(SymbolTableItem::Type::BOOL);
  this->back().castTo(SymbolTableItem::Type::BOOL);

  this->back()._value = Operand(nonstd::get<bool>(this->back()._value) ||
                                nonstd::get<bool>(top._value));
}

void myStack::op(const char& c) {
  StackRecord top = this->back();
  this->pop_back();
  StackRecord under = this->back();
  this->pop_back();

  if (top._type == under._type) {
    switch (top._type) {
      case SymbolTableItem::Type::INT: {
        auto topValue = nonstd::get<long>(top._value);
        auto underValue = nonstd::get<long>(under._value);
        switch (c) {
          case '+': {
            auto result = underValue + topValue;
            top._value = Operand(result);
          } break;
          case '-': {
            auto result = underValue - topValue;
            top._value = Operand(result);
          } break;
          case '*': {
            auto result = underValue * topValue;
            top._value = Operand(result);
          } break;
          case '/': {
            if (topValue == 0) {
              std::cerr << "Dividing by zero! Ignoring..." << std::endl;
              break;
            }
            auto result = underValue / topValue;
            top._value = Operand(result);
          } break;
          case 'e': {
            auto result = underValue == topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '>': {
            auto result = underValue > topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '<': {
            auto result = underValue < topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case ']': {
            auto result = underValue >= topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '[': {
            auto result = underValue <= topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case 'n': {
            auto result = underValue != topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;

          default:
            std::cerr << "Unknown operation" << std::endl;
            break;
        }
        this->push_back(top);

      } break;

      case SymbolTableItem::Type::FLOAT: {
        auto topValue = nonstd::get<double>(top._value);
        auto underValue = nonstd::get<double>(under._value);
        switch (c) {
          case '+': {
            auto result = underValue + topValue;
            top._value = Operand(result);
          } break;
          case '-': {
            auto result = underValue - topValue;
            top._value = Operand(result);
          } break;
          case '*': {
            auto result = underValue * topValue;
            top._value = Operand(result);
          } break;
          case '/': {
            if (topValue == 0.0) {
              std::cerr << "Dividing by zero! Ignoring..." << std::endl;
              break;
            }
            auto result = underValue / topValue;
            top._value = Operand(result);
          } break;
          case 'e': {
            auto result = underValue == topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '>': {
            auto result = underValue > topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '<': {
            auto result = underValue < topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case ']': {
            auto result = underValue >= topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '[': {
            auto result = underValue <= topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case 'n': {
            auto result = underValue != topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;

          default:
            std::cerr << "Unknown operation" << std::endl;
            break;
        }

        this->push_back(top);

      } break;

      case SymbolTableItem::Type::STRING: {
        auto topValue = nonstd::get<std::string>(top._value);
        auto underValue = nonstd::get<std::string>(under._value);

        switch (c) {
          case '+': {
            auto result = underValue + topValue;
            top._value = Operand(result);
          } break;
          case 'e': {
            auto result = underValue == topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '>': {
            auto result = underValue > topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '<': {
            auto result = underValue < topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case ']': {
            auto result = underValue >= topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case '[': {
            auto result = underValue <= topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;
          case 'n': {
            auto result = underValue != topValue;
            top._value = Operand(result);
            top._type = SymbolTableItem::Type::BOOL;
          } break;

          default:
            std::cerr << "Unknown operation" << std::endl;
            break;
        }

        this->push_back(top);

      } break;

      case SymbolTableItem::Type::BOOL: {
        auto topValue = nonstd::get<bool>(top._value);
        auto underValue = nonstd::get<bool>(under._value);

        switch (c) {
          case '+': {
            bool result = underValue + topValue;
            top._value = Operand(result);
          } break;
          case 'e': {
            auto result = underValue == topValue;
            top._value = Operand(result);
          } break;
          case '>': {
            auto result = underValue > topValue;
            top._value = Operand(result);
          } break;
          case '<': {
            auto result = underValue < topValue;
            top._value = Operand(result);
          } break;
          case ']': {
            auto result = underValue >= topValue;
            top._value = Operand(result);
          } break;
          case '[': {
            auto result = underValue <= topValue;
            top._value = Operand(result);
          } break;
          case 'n': {
            auto result = underValue != topValue;
            top._value = Operand(result);
          } break;
          default:
            std::cerr << "Unknown operation" << std::endl;
            break;
        }

        this->push_back(top);

      } break;

      default:
        std::cerr << "Operation with VOID not permited" << std::endl;
        break;
    }
  } else {
    if (c == 'e' || c == '>' || c == '<' || c == ']' || c == '[' || c == 'n') {
      std::cerr << "Comparing different types, this shoud never happen!"
                << std::endl;
      return;
    }
    top.castTo(under._type);
    this->push_back(under);
    this->push_back(top);

    this->op(c);
  }
}

void myStack::push(StackRecord& s) { this->push_back(s); }

void myStack::pop() { this->pop_back(); }

void myStack::popn() {
  auto tmp = this->back();
  this->pop_back();
  this->pop_back();
  this->push_back(tmp);
}

void myStack::load(StackRecord& s, long bp) {
  if (s._type != SymbolTableItem::Type::INT) {
    DEBUG("Cannot load; variant is not a long");
    return;
  }

  this->push_back(this->at(bp + nonstd::get<long>(s._value)));
}

void myStack::store(StackRecord& s, long bp) {
  if (s._type != SymbolTableItem::Type::INT) {
    DEBUG("Cannot store; bad variant is not a long");
    return;
  }

  this->at(bp + nonstd::get<long>(s._value)) = this->back();
  this->pop_back();
}

void myStack::dup() { this->push_back(this->back()); }

void myStack::print() {
  auto item = this->back();
  this->pop();
  DEBUG(SymbolTableItem::TypeMap.at(item._type));
  switch (item._type) {
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

void myStack::printContent() const {
#ifdef DEBUG_MODE
  DEBUG("");
  for (myStack::const_reverse_iterator i = this->crbegin(); i < this->crend();
       ++i) {
    DEBUG("=====================================");
    i->print();
    DEBUG("=====================================" << std::endl);
  }
#endif
}

void myStack::castInt() { this->back().castTo(SymbolTableItem::Type::INT); }

void myStack::castFloat() { this->back().castTo(SymbolTableItem::Type::FLOAT); }

void myStack::castBool() { this->back().castTo(SymbolTableItem::Type::BOOL); }

void myStack::castString() {
  this->back().castTo(SymbolTableItem::Type::STRING);
}
}  // namespace Interpret
}  // namespace RICC
