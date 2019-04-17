#include <iostream>

#include "ricc.hpp"

int main()
{
	RICC::Parser parser(std::cin);
    parser.Run();
	return 0;
}