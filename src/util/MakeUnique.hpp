#pragma once

#include <memory>

namespace RICC {

    template<typename T, typename... Params>
    std::unique_ptr<T> make_unique(Params&& ... params)
    {
        return std::unique_ptr<T>(new T(std::forward<Params>(params)...));
    }
}
