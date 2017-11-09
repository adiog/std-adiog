// This file is a part of FreePoly project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <freepoly.h>
#include <iostream>
#include <vector>


METHOD_CONTAINER(MethodContainer);

using CallableAny = object_t<MethodContainer, void, unsigned, unsigned>;

using container_t = std::vector<CallableAny>;


template<>
void MethodContainer::method(const int &x, unsigned indent, unsigned y) {
    std::cout << std::string(indent, ' ');
    std::cout << x * y << "\n";
}

template<>
void MethodContainer::method(const double &x, unsigned indent, unsigned y) {
    std::cout << std::string(indent, ' ');
    std::cout << x * y << "\n";
}

template<>
void MethodContainer::method(const std::string &x, unsigned indent, unsigned y) {
    std::cout << std::string(indent, ' ');
    while (y-- > 0) {
        std::cout << x;
    }
    std::cout << "\n";
}

template<>
void MethodContainer::method(const container_t& x, unsigned indent, unsigned y)
{
    std::cout << std::string(indent, ' ');
    std::cout << "BEGIN\n";
    for (auto &item : x)
    {
        item.method_t(indent+2, y);
    }
    std::cout << std::string(indent, ' ');
    std::cout << "END\n";
}

int main() {
  container_t vec;

  vec.push_back(13);
  vec.push_back(42);
  vec.push_back(std::string("hello"));
  vec.push_back(vec);
  vec.push_back(3.14);

  (void) MethodContainer::method<void>(vec, 0U, 3U);

  return 0;
}
