// This file is a part of FreePoly project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <freepoly.h>
#include <iostream>
#include <vector>

using container_t = std::vector<object_t<void, unsigned>>;

template <> void free_method_t(const container_t &x, unsigned y) {
  for (const auto &item : x) {
    item.method_t(y);
  }
}

template <> void free_method_t(const int &x, unsigned y) {
  std::cout << x * y << "\n";
}

template <> void free_method_t(const double &x, unsigned y) {
  std::cout << x * y << "\n";
}

template <> void free_method_t(const std::string &x, unsigned y) {
  while (y --> 0) {
    std::cout << x;
  }
  std::cout << "\n";
}

int main() {
  container_t vec;

  vec.push_back(13);
  vec.push_back(42);
  vec.push_back(std::string("hello"));
  vec.push_back(vec);
  vec.push_back(3.14);

  free_method_t<container_t, void, unsigned>(vec, 2U);

  return 0;
}
