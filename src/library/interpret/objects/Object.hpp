#pragma once

#include <iostream>
#include "nlohmann/json.hpp"

namespace RICC {
namespace Interpret {

class Object {
 public:
  virtual int loadFromJSON(nlohmann::json json) = 0;
  static long nextObjectID;

 private:
  //  long _objectID;
  // std::string _name;
  // std::string _id;
};
}  // namespace Interpret
}  // namespace RICC
