#include <iostream>
#include <sstream>
#include <string>

#include "interpret/Interpret.hpp"
#include "semantic/Semantic.hpp"

using namespace RICC;

/* int var1;
 * int var2;
 * var1 = -20;
 * var2 = 40;
 * var1 = var1 + var2;
 * print(var2);
 */

int main() {
  long result = 0;
  {
    Interpret::Interpret i;
    Semantic::Scope s;
    s.enterScope(true);

    auto var1 = s.define("var1", SymbolTableItem::Kind::VARIABLE);
    auto id1 = var1->getOffset();
    i.pushVariable(SymbolTableItem::Type::INT);
    i.pushLiteral(-20L);
    i.moveFromTop(id1);

    auto var2 = s.define("var2", SymbolTableItem::Kind::VARIABLE);
    auto id2 = var2->getOffset();
    i.pushVariable(SymbolTableItem::Type::INT);
    i.pushLiteral(40L);
    i.moveFromTop(id2);

    i.useVariable(id1);
    i.useVariable(id2);

    i.append(Interpret::Instructions::SUM);
    i.moveFromTop(id1);

    i.useVariable(id1);
    // i.append(Interpret::Instructions::PRINT);

    result += i.run();

    const auto& top = i.getStack().back();

    if (top._type != SymbolTableItem::Type::INT) result++;
    long res = nonstd::get<long>(top._value);

    if (res != 20) result++;
  }

  return result;
}