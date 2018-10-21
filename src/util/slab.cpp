#include <iostream>

#include "slab.hpp"

namespace TPJparser {

    template<class T>
    ObjectPool<T>::ObjectPool(size_t size) {
        this->_vector.reserve(size);
    }
}

