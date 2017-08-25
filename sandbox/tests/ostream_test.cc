#include <iostream>
#include <io>
#include <vector>
#include <stack>
#include <set>

int main() {
    std::pair<int, std::string> pair = {13, "pair"};
    std::cout << pair << std::endl;

    auto tuple = std::make_tuple(45, "tuple", 'X');
    std::cout << tuple << std::endl;

    auto array = std::array<int, 4>{1,2,3,4};
    std::cout << array << std::endl;

    auto vector = std::vector<int>{1,2,3,4};
    std::cout << vector << std::endl;

    std::queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(5);
    queue.push(4);
    queue.push(3);
    std::cout << queue << std::endl;

    std::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(5);
    stack.push(4);
    stack.push(3);
    std::cout << stack << std::endl;

    std::priority_queue<int> priority_queue;
    priority_queue.push(1);
    priority_queue.push(2);
    priority_queue.push(5);
    priority_queue.push(4);
    priority_queue.push(3);
    std::cout << priority_queue << std::endl;

    std::set<int> set = {1, 2, 5, 4, 3};
    std::cout << set << std::endl;

    std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    std::cout << map << std::endl;

    return 0;
}