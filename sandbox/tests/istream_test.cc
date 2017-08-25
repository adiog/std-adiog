// This file is a part of cpp-training project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <io>
#include <vector>

int main() {
    std::pair<int, std::string> pair;
    std::cin >> pair;
    std::cout << pair << std::endl;

    std::tuple<int, std::string, char> tuple;
    std::cin >> tuple;
    std::cout << tuple << std::endl;

    std::array<int, 4> array;
    std::cin >> array;
    std::cout << array << std::endl;

    std::vector<int> vector(4);
    std::cin >> vector;
    std::cout << vector << std::endl;

    return 0;

}