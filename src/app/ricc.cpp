#include <iostream>
#include "nlohmann/json.hpp"

using namespace nlohmann;

int main() {
  // create object from string literal
  json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

  // or even nicer with a raw string literal
  auto j2 = R"(
  {
    "happy": true,
    "pi": 3.141
  }
  )"_json;

  std::cout << j2.dump(4) << std::endl;
  return 0;
}
