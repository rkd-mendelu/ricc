#include <iostream>
#include <string>
#include <sstream>

#include "syntax/Syntax.hpp"

using namespace RICC;

int main()
{
    long result = 0;
    {
        std::string inputProgram ("3+2");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("3*2");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("3.0/2");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("2 && 3");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("2 || 3");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("3*2-4");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("3*(2-4)");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("3 == 5");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("!1");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("!1.0");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }

    {
        std::string inputProgram ("-1");
        std::istringstream stream(inputProgram);
        Syntax syntax(stream);
        result += syntax.ParseExpression();
        if (result) return result;
        syntax.getIntepreter().append(Interpret::Instructions::PRINT);
        result += syntax.getIntepreter().run();
    }
   return result;
}