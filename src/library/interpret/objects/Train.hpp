#pragma once

#include <iostream>
#include "Object.hpp"

#include "nlohmann/json.hpp"

namespace RICC {
namespace Interpret {
class Train : public Object {
 public:
  Train();
  int loadFromJSON(nlohmann::json json) override;
};
}  // namespace Interpret
}  // namespace RICC
