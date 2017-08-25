// This file is a part of ModernCpp project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <vector>
#include <iostream>

using byte = unsigned char;
using Row = std::vector<byte>;
using Board = std::vector<Row>;

using CandidateMoves = std::vector<bool>;

CandidateMoves getMoves(Board &board, int x, int y) {
    CandidateMoves cm = CandidateMoves(10, true);
    for (int p = 0; p < 9; p++) {
        if (board[p][y] > 0) {
            cm[board[p][y]] = false;
        }
        if (board[x][p] > 0) {
            cm[board[x][p]] = false;
        }
    }
    int ax = (x / 3) * 3;
    int ay = (y / 3) * 3;
    for (int px = ax; px < ax + 3; px++) {
        for (int py = ay; py < ay + 3; py++) {
            if (board[px][py] > 0) {
                cm[board[px][py]] = false;
            }
        }
    }
    return cm;
}

std::pair<int, int> getNext(Board &board, int x, int y) {
    while (board[x][y] > 0) {
        x++;
        y += x / 9;
        x %= 9;
        if (y == 9) {
            return {9, 9};
        }
    }
    return {x, y};
}

void print(Board &board) {
    for (auto row : board) {
        for (auto e : row) {
            std::cout << (int) e << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void solve(Board &board, int x, int y) {
    auto next = getNext(board, x, y);
    if (next.first == 9) {
        print(board);
    } else {
        auto cms = getMoves(board, next.first, next.second);
        for(byte cm = 1; cm < 10; cm++) {
            if (cms[cm]) {
                board[next.first][next.second] = cm;
                solve(board, next.first, next.second);
                board[next.first][next.second] = 0;
            }
        }
    }
}

int main() {
    Board board(9, Row(9));
    unsigned int preset;
    int x;
    int y;
    int c;
    std::cin >> preset;
    while(preset-- != 0) {
        std::cin >> x >> y >> c;
        board[x][y] = static_cast<byte>(c);
    }
    solve(board, 0, 0);
}
