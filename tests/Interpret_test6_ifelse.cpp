#include <iostream>
#include <string>
#include <sstream>

#include "syntax/Syntax.hpp"

using namespace TPJparser;

int main()
{
    long result = 0;

    {
        std::string program = "if (true) {printSTRING(\"if-branch\");} printSTRING(\"afterIF\");";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "if (false) {printSTRING(\"if-branch\");} printSTRING(\"afterIF\");";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    {
        std::string program = "int x = 5; if (true) {int y = 4;}printSTRING(\"after\");";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }


    {
        std::string program = "if (false) {printSTRING(\"if\");} else {printSTRING(\"else\");}";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }


    {
        std::string program = "if (false) {printSTRING(\"if\");} int x = 5; printINT(x);";
        std::cout << program << std::endl;
        std::istringstream ss(program);
        Syntax s(ss);

        result += s.Parse();
        s.getIntepreter().printCode();
        result += s.getIntepreter().run();
    }

    return result;
}
