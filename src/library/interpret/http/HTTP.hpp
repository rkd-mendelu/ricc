#pragma once

#include <iostream>
#include "nlohmann/json.hpp"

namespace RICC {
namespace Interpret {

class HTTP {
 public:
  HTTP(const std::string& url);
  HTTP(const std::string& url, const std::string& port);

  std::string curl(const std::string& url) const;

  std::string getTrainsURL() const;
  std::string getLoksURL() const;
  long getPort() const;

  void setURL(const std::string& url);
  void setPORT(const std::string& port);

 private:
  std::string _url;
  long _port;
};

}  // namespace Interpret
}  // namespace RICC
