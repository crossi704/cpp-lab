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

/* This experiment was created to write my own shared pointer implementation */

#include <cstdlib>
#include <string>
#include <iostream>

class RefCount {
public:
  RefCount() : counter_(0) {}
  ~RefCount() {}

  void Inc() {
    ++counter_;
  }

  int Dec() {
    return --counter_;
  }

private:
  int counter_;
};

template<class T>
class Shared_Ptr {
public:
  Shared_Ptr() : ptr_(NULL), rf_(NULL) {}
  Shared_Ptr(T* ptr) : ptr_(NULL), rf_(NULL) {
    ptr_ = ptr;
    rf_ = new RefCount();
    rf_->Inc();
  }

  ~Shared_Ptr() {
    if (rf_->Dec() == 0) {
      delete ptr_;
      delete rf_;
    }
  }

  Shared_Ptr(const Shared_Ptr<T>& other) {
    ptr_ = other.ptr_;
    rf_ = other.rf_;
    rf_->Inc();
  }

  const Shared_Ptr<T>& operator=(const Shared_Ptr<T> &other) {
    if (ptr_ != other.ptr_) {
      if (rf_->Dec() == 0) {
        delete ptr_;
        delete rf_;
      }

      ptr_ = other.ptr_;
      rf_ = other.rf_;
      rf_->Inc();
    }

    return *this;
  }

  T* operator->() {
    return ptr_;
  }

  T* operator*() {
    return *ptr_;
  }

  T* get() {
    return ptr_;
  }

  void reset() {
    if (rf_->Dec() == 0) {
      delete ptr_;
      delete rf_;
    }
  }

private:
  T* ptr_;
  RefCount *rf_;
};


struct Test {
  int id;
  std::string prod_name;
};

void example() {
  Shared_Ptr<Test> test1(new Test());
  Shared_Ptr<Test> test2(new Test());
  test1->id = 5;
  test2->id = 7;
  test1->prod_name = std::string("Test 1");
  test2->prod_name = std::string("Test 2");

  std::cout << "Test1 ID: " << test1->id << std::endl;
  std::cout << "Test1 Name: " << test1->prod_name << std::endl;
  std::cout << "Test2 ID: " << test2->id << std::endl;
  std::cout << "Test2 Name: " << test2->prod_name << std::endl;

  test1 = test2;

  std::cout << "After assignment:" << std::endl;
  std::cout << "Test1 ID: " << test1->id << std::endl;
  std::cout << "Test1 Name: " << test1->prod_name << std::endl;
  std::cout << "Test2 ID: " << test2->id << std::endl;
  std::cout << "Test2 Name: " << test2->prod_name << std::endl;
}

int main() {
  example();
  return 0;
}
