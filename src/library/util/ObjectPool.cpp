#include <iostream>

#include "ObjectPool.hpp"
#include "util/Logger.hpp"

namespace RICC {

template <class T>
ObjectPool<T>::ObjectPool() : _lastIndex(0) {}

template <class T>
size_t ObjectPool<T>::getSize() {
  return this->_container.size();
}

template <class T>
void ObjectPool<T>::markAsFree(size_t index) {
  if (index < this->getSize()) this->_container[index].free();
}

template <class T>
void ObjectPool<T>::returnItem(T& ref) {
  size_t id = ref.getID();
  this->markAsFree(id);

  if (id < this->_lastIndex) this->_lastIndex = id;
}

template <class T>
T& ObjectPool<T>::getItem() {
  if (this->_lastIndex == this->getSize()) this->_container.push_back(T());

  T& ref = this->_container[this->_lastIndex];
  ref.setID(this->_lastIndex);
  ref.alloc();
  // std::cout << "last-before: " << this->_lastIndex << std::endl;

  for (; this->_lastIndex < this->getSize(); this->_lastIndex++) {
    if (!this->_container[this->_lastIndex].isAllocated()) break;
  }

  // std::cout << "last-after: " << this->_lastIndex << std::endl;
  return ref;
}

template <class T>
void ObjectPool<T>::show() {
  DEBUG("");
  DEBUG("Size is: " << this->getSize());
  for (auto item : this->_container) {
    DEBUG("ID: " << item.getID() << " A: " << item.isAllocated());
  }
  DEBUG("");
}

}  // namespace RICC
