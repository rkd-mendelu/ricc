#include <iostream>
#include <sstream>
#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"
#include "curlpp/cURLpp.hpp"
#include "nlohmann/json.hpp"

using namespace nlohmann;
using namespace curlpp::options;

int main() {
  // create object from string literal
  // json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

  // or even nicer with a raw string literal
  auto j2 = R"(
  {
    "happy": true,
    "pi": 3.141
  }
  )"_json;

  std::cout << j2.dump(4) << std::endl;

  try {
    // That's all that is needed to do cleanup of used resources (RAII style).
    curlpp::Cleanup myCleanup;

    // Our request to be sent.
    curlpp::Easy myRequest;

    // Set the URL.
    std::stringstream res;
    // Set the writer callback to enable cURL
    // to write result in a memory area
    myRequest.setOpt(new curlpp::options::WriteStream(&res));

    myRequest.setOpt<Url>(
        "https://raw.githubusercontent.com/rkd-mendelu/"
        "track-topology/master/example-data/bloky.json");

    // Send request and get a result.
    // By default the result goes to standard output.
    myRequest.perform();

    std::cout << res.str();
  }

  catch (curlpp::RuntimeError& e) {
    std::cout << e.what() << std::endl;
  }

  catch (curlpp::LogicError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
