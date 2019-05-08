#include <iostream>

#include "ricc/ricc-parser.hpp"

int main() {
  RICC::Parser parser(std::cin);
  parser.Run();
  return 0;
}