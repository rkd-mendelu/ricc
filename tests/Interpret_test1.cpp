#include <iostream>

#include "interpret/Interpret.hpp"

using namespace TPJparser;

int main()
{
    long result = 0;
    {
        Interpret::Interpret interpret;
        interpret.append(Interpret::Instructions::PUSH, 43L);
        interpret.append(Interpret::Instructions::PUSH, 27L);
        interpret.append(Interpret::Instructions::SUM);
        interpret.append(Interpret::Instructions::PRINT);
        result += interpret.run();
    }

    {
        Interpret::Interpret interpret;
        interpret.append(Interpret::Instructions::PUSH, 43L);
        interpret.append(Interpret::Instructions::PUSH, 27L);
        interpret.append(Interpret::Instructions::SUM);
        interpret.append(Interpret::Instructions::PUSH, 100L);
        interpret.append(Interpret::Instructions::SUB);
        interpret.append(Interpret::Instructions::PRINT);
        result += interpret.run();
    }

    {
        Interpret::Interpret interpret;
        interpret.append(Interpret::Instructions::PUSH, 44L);
        interpret.append(Interpret::Instructions::PUSH, 2L);
        interpret.append(Interpret::Instructions::MUL);
        interpret.append(Interpret::Instructions::PRINT);
        result += interpret.run();
    }

    {
        Interpret::Interpret interpret;
        interpret.append(Interpret::Instructions::PUSH, 44L);
        interpret.append(Interpret::Instructions::PUSH, 2L);
        interpret.append(Interpret::Instructions::DIV);
        interpret.append(Interpret::Instructions::PRINT);
        result += interpret.run();
    }

    {
        Interpret::Interpret interpret;
        interpret.append(Interpret::Instructions::PUSH, 44L);
        interpret.append(Interpret::Instructions::PUSH, 0L);
        interpret.append(Interpret::Instructions::DIV);
        interpret.append(Interpret::Instructions::PRINT);
        result += interpret.run();
    }

    {
        Interpret::Interpret interpret;
        interpret.append(Interpret::Instructions::PUSH, 44L);
        interpret.append(Interpret::Instructions::PUSH, 22.0);
        interpret.append(Interpret::Instructions::SUM);
        interpret.append(Interpret::Instructions::PRINT);
        result += interpret.run();
    }

    {
        Interpret::Interpret interpret;
        interpret.append(Interpret::Instructions::PUSH, 44.0);
        interpret.append(Interpret::Instructions::PUSH, 21L);
        interpret.append(Interpret::Instructions::SUM);
        interpret.append(Interpret::Instructions::PRINT);
        result += interpret.run();
    }

    {
        Interpret::Interpret interpret;
        interpret.append(Interpret::Instructions::PUSH, 44.0);
        interpret.append(Interpret::Instructions::PUSH, 21L);
        interpret.append(Interpret::Instructions::DIV);
        interpret.append(Interpret::Instructions::PRINT);
        result += interpret.run();
    }

   return result;
}