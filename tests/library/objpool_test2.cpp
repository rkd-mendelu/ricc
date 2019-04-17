#include <iostream>

#include "lex/Token.hpp"
#include "util/ObjectPool.hpp"

#define SIZE 1000000

using namespace std;

int main() {
  RICC::ObjectPool<RICC::Token> my_pool;

  for (size_t i = 0; i < SIZE; i++) {
    (void)my_pool.getItem();
  }

  if (my_pool.getSize() != SIZE) {
    cerr << "getsize returns something wrong" << endl;
    return 1;
  }

  return 0;
}