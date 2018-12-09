#pragma once

#include <iostream>
#include <vector>

namespace TPJparser {

    template<class T>
    class ObjectPool {
        public:
            ObjectPool();

            T& getItem();
            void returnItem(T& ref);
            size_t getSize();
            void show();

        private:
            void markAsFree(size_t index);

            std::vector<T> _vector;
            size_t _lastIndex;
    };

}

#include "ObjectPool.cpp" // hack to avoid linker problem with templates
