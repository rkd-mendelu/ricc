#include <iostream>
#include <sstream>
#include <string>

#include "syntax/Syntax.hpp"

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
    std::string program = "castB2I(true);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castS2I(\"false\");";  // returns 0L
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
    std::string program = "castS2I(\"200.9\");";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castS2F(\"3.14\");";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castB2F(false);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castB2F(true);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castI2F(9);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castI2B(8);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castI2B(0);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castF2B(0.12);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castF2B(0.0);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castS2B(\"false\");";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castS2B(\"true\");";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castS2B(\"\");";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castB2S(false);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castB2S(true);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castI2S(109);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  {
    std::string program = "castF2S(903.5);";
    std::cout << program << std::endl;
    std::istringstream ss(program);
    Syntax s(ss);

    result += s.Parse();
    s.getIntepreter().printCode();
    result += s.getIntepreter().run();
  }

  return result;
}
