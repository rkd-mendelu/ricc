#include <iostream>
#include <sstream>

#include <ricc/ricc-parser.hpp>

int main() {
  RICC::Parser parser(std::cin);

  int rc = parser.Parse();
  if (rc) {
    std::cerr << "Cannot parse input" << std::endl;
    return rc;
  }

  rc = parser.Run();
  if (rc) {
    std::cerr << "Interpret error" << std::endl;
    return rc;
  }

  return 0;
}
