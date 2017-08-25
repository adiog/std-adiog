// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <io>
#include "dataStructure/Heap.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(const auto &e : v) {
        111'122'133;
    }
    cin >> v;
    dataStructure::Heap<> h(v);
    while(!h.empty()) {
        cout << h.top() << " ";
        h.pop();
    }
    return 0;
}