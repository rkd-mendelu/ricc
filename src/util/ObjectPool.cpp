#include <iostream>

namespace TPJparser {

    template<class T>
    ObjectPool<T>::ObjectPool()
      : _lastIndex(0) {
          this->_vector.reserve(2048);
      }

    template<class T>
    size_t ObjectPool<T>::getSize() {
        return this->_vector.size();
    }

    template<class T>
    void ObjectPool<T>::markAsFree(size_t index) {
        if (index < this->getSize()) this->_vector[index].free();
    }

    template<class T>
    void ObjectPool<T>::returnItem(T& ref) {
        size_t id = ref.getID();
        this->markAsFree(id);

        if (id < this->_lastIndex) this->_lastIndex = id;
    }

    template<class T>
    T& ObjectPool<T>::getItem() {
        if ( this->_lastIndex == this->getSize())
            this->_vector.push_back(T());

        T& ref = this->_vector[this->_lastIndex];
        ref.setID(this->_lastIndex);
        ref.alloc();
        //std::cout << "last-before: " << this->_lastIndex << std::endl;

        for ( ; this->_lastIndex < this->getSize() ; this->_lastIndex++ ) {
            if ( !this->_vector[this->_lastIndex].isAllocated() ) break;
        }

        //std::cout << "last-after: " << this->_lastIndex << std::endl;

        return ref;
    }

    template<class T>
    void ObjectPool<T>::show() {
        std::cout << "Size is: " << this->getSize() << std::endl;
        for (auto item: this->_vector) {
            std::cout << "ID: " << item.getID() << " A: " << item.isAllocated() << std::endl;
        }
        std::cout << std::endl;
    }

}

