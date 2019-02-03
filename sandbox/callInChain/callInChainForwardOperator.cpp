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



template<typename T>
struct Wrapper {
    explicit Wrapper(T value) : value(value) {};
    operator T() {return value;}
    T value;
};

template<typename T>
Wrapper<T> FORWARD(T x)
{
    return Wrapper<T>(x);
}

template<typename InT, typename OutT>
OutT operator>>(Wrapper<InT> arg, OutT(*foo)(InT))
{
    return foo(arg.value);
}

template<typename InT, typename OutT>
Wrapper<OutT> operator>>(Wrapper<InT> arg, Wrapper<OutT(*)(InT)> foo)
{
    return Wrapper<OutT>((*foo.value)(arg.value));
}


int main() {
    A a{1};
    C c = FORWARD(a) >> FORWARD(convertAtoB) >> FORWARD(convertBtoC);
    std::cout << c.x << std::endl;
    return 0;
}
