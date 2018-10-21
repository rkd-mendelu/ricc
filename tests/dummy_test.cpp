#include <iostream>

#include "tpj-parser.hpp"

int main()
{
	TPJparser::Parser parser(std::cin);
    parser.Run();
	return 0;
}