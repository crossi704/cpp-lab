/* The MIT License (MIT)

Copyright (c) 2017 zmechz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

/* This experiment was created to evaluate copy vs move semantics performance */
/* This code compile on c++98 standard, and if you want to reimplement move constructor and assignment, just uncomment the key Cplusplus11 */

#include <sys/time.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

// #define Cplusplus11
namespace {
int movect = 0;
int copyct = 0;
int copyassign = 0;;
int moveassign = 0;
}

class VectorContainer {
public:
  VectorContainer() {}
  explicit VectorContainer(std::vector<int> v) : v_(v) {}
  ~VectorContainer() {}
  VectorContainer(const VectorContainer& other) { // copy constructor
    ++copyct;
    v_ = other.v_;
  }
  VectorContainer& operator=(const VectorContainer& other) { // copy assignment operator
    ++copyassign;
    if (this != &other)  {
      v_ = other.v_;
    }
    return *this;
  }
#ifdef Cplusplus11
  VectorContainer(const VectorContainer&& other) { // move constructor
    ++movect;
    v_ = std::move(other.v_);
  }
  VectorContainer& operator=(const VectorContainer&& other) { // move assignment operator
    ++moveassign;
    if (this != &other)  {
      v_ = std::move(other.v_);
    }
    return *this;
  }
#endif

public:
  std::vector<int> v_;
};



VectorContainer CreateVectorContainer(VectorContainer vec) {
  for(int i = 0; i < 9000; i++) {
    vec.v_.push_back(i);
  }
  return vec;
}


void D(VectorContainer str) {
  VectorContainer v2 = str;
}

void C(VectorContainer str) {
  D(str);
}

void B(VectorContainer str) {
  C(str);
}

void A(VectorContainer str) {
  B(str);
}

int main() {
  uint32_t n = 0;
  uint64_t miliseconds_before;
  uint64_t miliseconds_after;
  struct timeval tv, tv2;
  gettimeofday(&tv, NULL);
  while(n++ < 1000) {
    VectorContainer vec;
    vec = CreateVectorContainer(vec);
    // A(vec);
  }
  gettimeofday(&tv2, NULL);
  miliseconds_before = uint64_t((uint64_t)tv.tv_usec / (uint64_t) 1000);
  miliseconds_before += uint64_t((uint64_t) tv.tv_sec * (uint64_t) 1000);
  miliseconds_after = uint64_t((uint64_t)tv2.tv_usec / (uint64_t) 1000);
  miliseconds_after += uint64_t((uint64_t) tv2.tv_sec * (uint64_t) 1000);
  std::cout << "Copy constructor was called " << copyct << " times.\n";
  std::cout << "Copy assignment was called " << copyassign << " times.\n";
  std::cout << "Move constructor was called " << movect << " times.\n";
  std::cout << "Move assignment was called " << moveassign << " times.\n";
  std::cout << "The process has taken " << miliseconds_after-miliseconds_before << " miliseconds\n";
  return 0;
}
