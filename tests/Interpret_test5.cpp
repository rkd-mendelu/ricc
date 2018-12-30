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

    {
        std::string program = "castF2I(9.9);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "castB2I(false);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "castS2I(\"false\");"; // returns 0L
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "castS2I(\"200\");";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "castS2I(\"200\");";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }



    {
        std::string program = "castS2F(\"200.0\");";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    return result;
}
