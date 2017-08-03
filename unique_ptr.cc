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

/* This experiment was created to write my own unique pointer implementation */

#include <cstdlib>

template<class T>
class Unique_Ptr {
public:
  Unique_Ptr(T* ptr) : ptr_(ptr) {}
  ~Unique_Ptr() {
    delete ptr_;
  }

  Unique_Ptr(const Unique_Ptr&& other) { // move constructor
    ptr_ = other.ptr_;
    other.ptr_ = NULL;
  }

  Unique_Ptr& operator=(const Unique_Ptr&& other) { // move assignment
    ptr_ = other.ptr_;
    other.ptr_ = NULL;
    return *this;
  }

private:
    Unique_Ptr(const Unique_Ptr& other); // copy constructor
    const Unique_Ptr& operator=(const Unique_Ptr&); // copy assignment

private:
  T* ptr_;
};

struct Test {
  int id;
  char *prod_name;
};

int main() {
  Unique_Ptr<Test> test1(new Test);
  Unique_Ptr<Test> test2(new Test);
  // Unique_Ptr<Test> test3(test2); // prohibited copy constructor
  // test1 = test2; // prohibited assignment operator
  return 0;
}
