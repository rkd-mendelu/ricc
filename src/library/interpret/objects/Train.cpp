#include <iostream>

#include "Train.hpp"
#include "util/Logger.hpp"

#include "nlohmann/json.hpp"

namespace RICC {
namespace Interpret {

Train::Train() { DEBUG(""); }

int Train::loadFromJSON(nlohmann::json json) { return json.empty(); }

}  // namespace Interpret
}  // namespace RICC
