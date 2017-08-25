// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <iostream>
#include <vector>
#include <queue>
#include <include/erange>

int main() {
    uint v;
    uint e;
    std::cin >> v;
    std::cin >> e;
    std::vector<int> level(v, 0);
    std::vector<std::vector<int>> edge(v);
    int v1;
    int v2;
    while (e-- > 0U) {
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        edge[v1].push_back(v2);
        level[v2]++;
    }

    std::queue<int> queue;
    for (auto ev : erange(level)) {
        if (ev.second == 0) {
            queue.push(ev.first);
        }
    }

    while (!queue.empty()) {
        auto v1 = queue.front();
        queue.pop();
        std::cout << (v1+1) << std::endl;
        for (auto v2 : edge[v1]) {
            level[v2]--;
            if (level[v2] == 0) {
                queue.push(v2);
            }
        }
        v--;
    }

    if (v > 0U) {
        std::cout << "cycle" << std::endl;
    }

    return 0;
}
