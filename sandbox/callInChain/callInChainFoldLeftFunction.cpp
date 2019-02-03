#include <tuple>
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

B convertAtoB(A a) { return {a.x + 5}; }

C convertBtoC(B b) { return {b.x * 7}; }


template<typename T>
struct function_traits;

template<typename Result, typename ...Args>
struct function_traits<Result(*)(Args...)> {
    static const size_t nargs = sizeof...(Args);

    using result_type = Result;

    template<size_t i>
    struct arg {
        using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};

template<typename OutT, typename InT, typename HeadFoo>
OutT callInChain(InT in, HeadFoo headFoo) {
    return headFoo(in);
}

template<typename OutT, typename InT, typename HeadFoo, typename... TailFoos>
OutT callInChain(InT in, HeadFoo headFoo, TailFoos... tailFoos) {
    return headFoo(callInChain<typename function_traits<HeadFoo>::template arg<0>::type>(in, tailFoos...));
}

int main() {
    A a{1};
    auto c = callInChain<C>(a, convertBtoC, convertAtoB);
    std::cout << c.x << std::endl;
    return 0;
}
