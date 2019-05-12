#include <iostream>
#include <sstream>

#include "HTTP.hpp"
#include "util/Logger.hpp"

#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"
#include "curlpp/cURLpp.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace RICC {
namespace Interpret {

  HTTP::HTTP(const std::string& url) : HTTP(url, "80") { DEBUG(""); }

HTTP::HTTP(const std::string& url, const std::string& port)
  : _url(url), _port(80) {
  DEBUG("");
  try {
    _port = std::stol(port);
  } catch (...) {
    std::cerr << "Warning! : Can not cast string \"" << port
              << "\" to integer." << std::endl;
    std::cerr << "Port conversion failed, using default."
              << std::endl;
    _port = 80;
  }

}

void HTTP::setURL(const std::string& url) { _url = url; }
void HTTP::setPORT(const std::string& port) {
  try {
    _port = std::stol(port);
  } catch (...) {
    std::cerr << "Warning! : Can not cast string \"" << port << "\" to integer."
              << std::endl;
    std::cerr << "Port conversion failed, using default." << std::endl;
    _port = 80;
  }
}

json HTTP::getTrainsJson() {
  DEBUG("");

  DEBUG("Query for:");
  DEBUG("URL: " << _url);
  DEBUG("PORT: " << _port);

  std::stringstream res;

  try {
    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;

    myRequest.setOpt(new curlpp::options::WriteStream(&res));
    myRequest.setOpt<curlpp::Options::Url>(_url);
    // myRequest.setOpt<curlpp::Options::Port>(_port);

    myRequest.perform();

    DEBUG(res.str());
  }

  catch (curlpp::RuntimeError& e) {
    std::cerr << e.what() << std::endl;
  }

  catch (curlpp::LogicError& e) {
    std::cerr << e.what() << std::endl;
  }

  return json(res.str());
}

}  // namespace Interpret
}  // namespace RICC
