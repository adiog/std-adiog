#include <iostream>

struct A {
    int x;
};

struct B {
    int x;
};

struct C {
    int x;
};

B convertAtoB(A a) { return {a.x+5}; }

C convertBtoC(B b) { return {b.x*7}; }



template<typename OutT, typename InT, typename HeadFoo>
OutT callInChain(InT in, HeadFoo headFoo) {
    return headFoo(in);
}

template<typename OutT, typename InT, typename HeadFoo, typename... TailFoos>
OutT callInChain(InT in, HeadFoo headFoo, TailFoos... tailFoos) {
    return callInChain<OutT>(headFoo(in), tailFoos...);
}

int main() {
    A a{1};
    auto c = callInChain<C>(a, convertAtoB, convertBtoC);
    std::cout << c.x << std::endl;
    return 0;
}
