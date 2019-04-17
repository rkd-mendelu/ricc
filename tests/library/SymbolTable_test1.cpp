#include <iostream>
#include <vector>

#include "lex/Token.hpp"
#include "semantic/SymbolTable.hpp"

#include <ctime>

using namespace std;

int main() {
  RICC::SymbolTable s;
  string varname = "var";
  string funcname = "func";
  string arg = "arg";

  for (int i = 0; i < 1000; i++) {
    auto var = s.defineVar(varname + to_string(i));
    var->setType(RICC::SymbolTableItem::Type::INT);
  }

  for (int i = 0; i < 1000; i++) {
    if (!s.isVarDeclared(varname + to_string(i))) {
      return 1;
    }
  }

  for (int i = 0; i < 1000; i++) {
    auto func = s.defineFunc(funcname + to_string(i));
    func->setType(RICC::SymbolTableItem::Type::INT);

    int r = rand() % 10;
    for (int j = 0; j < r; j++) {
      string tmp = arg + to_string(j);
      func->addArg(RICC::SymbolTableItem::Type::FLOAT, tmp);
    }
  }

  for (int i = 0; i < 1000; i++) {
    if (!s.isFuncDeclared(funcname + to_string(i))) {
      return 2;
    }
  }

  s.printContent();

  return 0;
}