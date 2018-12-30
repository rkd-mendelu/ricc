#include <iostream>
#include <string>
#include <sstream>

#include "syntax/Syntax.hpp"

using namespace TPJparser;

/* int var1;
 * int var2;
 * var1 = -20;
 * var2 = 40;
 * var1 = var1 + var2;
 * print(var2);
 */

int main()
{
    long result = 0;
    // {
    //     std::string program = "int main(){int x = 4;}";
    //     std::istringstream ss(program);
    //     Syntax s(ss);

    //     s.Parse();
    //     s.getIntepreter().useVariable(0);
    //     s.getIntepreter().run();
    //     const auto  res = s.getIntepreter().getStack().back();
    //     if (res._type != SymbolTableItem::Type::INT) result++;
    //     if (nonstd::get<long>(res._value) != 4) result++;
    // }

    // {
    //     std::string program = "int main(){int x = 4; int y = x + 2;}";
    //     std::istringstream ss(program);
    //     Syntax s(ss);

    //     s.Parse();
    //     s.getIntepreter().useVariable(1);
    //     s.getIntepreter().run();
    //     const auto  res = s.getIntepreter().getStack().back();
    //     if (res._type != SymbolTableItem::Type::INT) result++;
    //     if (nonstd::get<long>(res._value) != 6) result++;

    //     s.getIntepreter().append(Interpret::Instructions::PRINT);
    //     s.getIntepreter().run();
    // }

    // {
    //     std::string program = "int main(){int x = 4; x = 5;}";
    //     std::istringstream ss(program);
    //     Syntax s(ss);

    //     s.Parse();
    //     s.getIntepreter().useVariable(0);
    //     s.getIntepreter().run();
    //     const auto  res = s.getIntepreter().getStack().back();
    //     if (res._type != SymbolTableItem::Type::INT) result++;
    //     if (nonstd::get<long>(res._value) != 5) result++;

    //     s.getIntepreter().append(Interpret::Instructions::PRINT);
    //     s.getIntepreter().run();
    // }

    // {
    //     std::string program = "int main(){int x = 4; int y = x = 5 + 2;}";
    //     std::istringstream ss(program);
    //     Syntax s(ss);

    //     s.Parse();
    //     s.getIntepreter().useVariable(1);
    //     s.getIntepreter().run();
    //     const auto  res = s.getIntepreter().getStack().back();
    //     if (res._type != SymbolTableItem::Type::INT) result++;
    //     if (nonstd::get<long>(res._value) != 5) result++;

    //     s.getIntepreter().append(Interpret::Instructions::PRINT);
    //     s.getIntepreter().run();
    // }

    {
        std::string program = "int func(){int x; float y;} int main(){func();} main();";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {

        std::string program = "int func(){int x; float y;} func();";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "int func(){int x; float y; return 5;} func();";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "int x = 1; int y = 2; int z = 3; printINT(x); printINT(y); printINT(z);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "printINT(5);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "printINT(5+2);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "int a = 60; printINT(a);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "printFLOAT(80.0);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "printSTRING(\"some string\");";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "printBOOL(true);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

        {
        std::string program = "printBOOL(false);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }




   return result;
}