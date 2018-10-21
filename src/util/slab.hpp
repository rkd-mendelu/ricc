#include <iostream>

#include <vector>

namespace TPJparser {

    template<class T>
    class ObjectPool {
        public:
            ObjectPool(size_t size);

        private:
            std::vector<T> _vector;
    };

}