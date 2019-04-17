#pragma once

#include <deque>
#include <iostream>

namespace RICC {

template <class T>
class ObjectPool {
 public:
  ObjectPool();

  T& getItem();
  void returnItem(T& ref);
  size_t getSize();
  void show();

 private:
  void markAsFree(size_t index);

  std::deque<T> _container;
  size_t _lastIndex;
};

}  // namespace RICC

#include "ObjectPool.cpp"  // hack to avoid linker problem with templates
