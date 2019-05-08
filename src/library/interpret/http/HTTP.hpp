#pragma once

#include <iostream>
#include "nlohmann/json.hpp"

namespace RICC {
namespace Interpret {

class HTTP {
 public:
  HTTP(const std::string& url);
  HTTP(const std::string& url, const std::string& port);

  nlohmann::json jsonGetTrains();

 private:
  const std::string _url;
  long _port;
};

}  // namespace Interpret
}  // namespace RICC
