#include <iostream>

using namespace std;

typedef unsigned int generic_counter_t;

class Widget {
private:
    generic_counter_t value;
public:
    Widget(int a);
    ~Widget();
    void Context() &;
    void Context() &&;
    generic_counter_t get() const;
    friend std::ostream& operator<<(std::ostream& os, const Widget & w);
};

Widget::Widget(int a) : value(a) {
}

Widget::~Widget() {
}

void Widget::Context() & {
  asm volatile("int $3");
  std::cout << "lvalue" << std::endl;
}

void Widget::Context() && {
    std::cout << "universal reference" << std::endl;
}

generic_counter_t Widget::get() const {
    return value;
}

ostream& operator<<(std::ostream& os, const Widget & w){
    os << w.get();
    return os;
}


auto foo(generic_counter_t a) {
    return a * a;
}

int main()
{
    int i;
    (new Widget(5))->Context();
    Widget w = Widget(6);
    w.Context();
    cin >> i;

    cout << foo(i) << endl;
    return 0;
}

