#include <iostream>

#include "syntax/Syntax.hpp"
#include "util/Logger.hpp"

#include "interpret/http/HTTP.hpp"

namespace RICC {

void Syntax::preDefineFunctions() {
  {
    // printINT(int x)
    auto print =
        this->_scope.define("printINT", SymbolTableItem::Kind::FUNCTION);
    print->setType(SymbolTableItem::Type::VOID);
    auto& args = print->getArgs();
    args.push_back({SymbolTableItem::Type::INT, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("printINT"));
    print->setJumpIndex(this->_interpret.getIP() - 2);
    print->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::PRINT);
    this->_interpret.genReturn(/*void*/ true);

    auto jindex = print->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // printFLOAT(float x)
  {
    auto print =
        this->_scope.define("printFLOAT", SymbolTableItem::Kind::FUNCTION);
    print->setType(SymbolTableItem::Type::VOID);
    auto& args = print->getArgs();
    args.push_back({SymbolTableItem::Type::FLOAT, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("printFLOAT"));
    print->setJumpIndex(this->_interpret.getIP() - 2);
    print->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::PRINT);
    this->_interpret.genReturn(/*void*/ true);

    auto jindex = print->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // printSTRING(float x)
  {
    auto print =
        this->_scope.define("printSTRING", SymbolTableItem::Kind::FUNCTION);
    print->setType(SymbolTableItem::Type::VOID);
    auto& args = print->getArgs();
    args.push_back({SymbolTableItem::Type::STRING, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("printSTRING"));
    print->setJumpIndex(this->_interpret.getIP() - 2);
    print->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::PRINT);
    this->_interpret.genReturn(/*void*/ true);

    auto jindex = print->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // printBOOL(bool x)
  {
    auto print =
        this->_scope.define("printBOOL", SymbolTableItem::Kind::FUNCTION);
    print->setType(SymbolTableItem::Type::VOID);
    auto& args = print->getArgs();
    args.push_back({SymbolTableItem::Type::BOOL, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("printBOOL"));
    print->setJumpIndex(this->_interpret.getIP() - 2);
    print->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::PRINT);
    this->_interpret.genReturn(/*void*/ true);

    auto jindex = print->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  /**********************************CAST********************************/

  // castF2I()
  {
    auto cast = this->_scope.define("castF2I", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::INT);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::FLOAT, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castF2I"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTINT);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castB2I()
  {
    auto cast = this->_scope.define("castB2I", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::INT);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::BOOL, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castB2I"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTINT);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castS2I()
  {
    auto cast = this->_scope.define("castS2I", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::INT);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::STRING, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castS2I"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTINT);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castI2F()
  {
    auto cast = this->_scope.define("castI2F", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::FLOAT);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::INT, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castI2F"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTFLOAT);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castB2F()
  {
    auto cast = this->_scope.define("castB2F", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::FLOAT);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::BOOL, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castB2F"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTFLOAT);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castS2F()
  {
    auto cast = this->_scope.define("castS2F", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::FLOAT);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::STRING, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castS2F"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTFLOAT);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castI2B()
  {
    auto cast = this->_scope.define("castI2B", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::BOOL);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::INT, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castI2B"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTBOOL);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castF2B()
  {
    auto cast = this->_scope.define("castF2B", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::BOOL);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::FLOAT, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castF2B"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTBOOL);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castS2B()
  {
    auto cast = this->_scope.define("castS2B", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::BOOL);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::STRING, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castS2B"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTBOOL);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castB2S()
  {
    auto cast = this->_scope.define("castB2S", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::STRING);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::BOOL, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castB2S"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTSTRING);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castF2S()
  {
    auto cast = this->_scope.define("castF2S", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::STRING);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::FLOAT, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castF2S"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTSTRING);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // castI2S()
  {
    auto cast = this->_scope.define("castI2S", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::STRING);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::INT, "x"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("castI2S"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CASTSTRING);
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // getTrains()
  {
    auto cast =
        this->_scope.define("getTrains", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::STRING);

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("getTrains"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    // this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CURL,
                            this->_interpret.getHTTPInstance().getTrainsURL());
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // getTrainByID()
  {
    auto cast =
        this->_scope.define("getTrainByID", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::STRING);
    auto& args = cast->getArgs();
    args.push_back({SymbolTableItem::Type::STRING, "trains"});
    args.push_back({SymbolTableItem::Type::INT, "id"});

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("getTrainByID"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    this->_interpret.append(Interpret::Instructions::LOAD, -4L);
    this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::GETTRAIN, "");
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }

  // getLoks()
  {
    auto cast = this->_scope.define("getLoks", SymbolTableItem::Kind::FUNCTION);
    cast->setType(SymbolTableItem::Type::STRING);

    this->_interpret.append(Interpret::Instructions::JUMP, -1L);
    this->_interpret.append(Interpret::Instructions::NOP,
                            std::string("getLoks"));
    cast->setJumpIndex(this->_interpret.getIP() - 2);
    cast->setStartAddress(this->_interpret.getIP());

    // this->_interpret.append(Interpret::Instructions::LOAD, -3L);
    this->_interpret.append(Interpret::Instructions::CURL,
                            this->_interpret.getHTTPInstance().getLoksURL());
    this->_interpret.genReturn(/*is void*/ false);

    auto jindex = cast->getJumpIndex();
    this->_interpret.getInstructionBuffer()[jindex]._rec._value =
        Interpret::Operand(this->_interpret.getIP());
  }
}

}  // namespace RICC
