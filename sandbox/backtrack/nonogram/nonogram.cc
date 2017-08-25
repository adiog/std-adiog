// This file is a part of ModernCpp project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

// types
using byte = unsigned char;
using ulong = unsigned long;

enum class Field : byte { Empty, Marked, Forbidden };

using Row = std::vector<Field>;
using Board = std::vector<Row>;

using ClueSet = std::vector<ulong>;
using ClueSets = std::vector<ClueSet>;

// globals
Board board;
ClueSets clueSetsBuild;
ClueSets clueSetsCheck;

template <class ForwardIt>
ulong getSum(ForwardIt begin, ForwardIt end) {
    ulong sum = *begin;
    while (++begin != end) {
        sum += *begin;
    }
    return sum;
}
ulong getLength(const ClueSet &clueSet) {
    ulong length = 0;
    for (auto i : clueSet) {
        length += i;
    }
    return length;
}

void print(const Row &row) {
    for (auto field : row) {
        switch (field) {
            case Field::Marked:
                std::cout << "X";
                break;
            case Field::Forbidden:
                std::cout << "_";
                break;
            default:
                std::cout << "_";
                break;
        }
    }
    std::cout << std::endl;
}

void printBoard(const Board &board) {
    for (const auto &row : board) {
        print(row);
    }
    std::cout << std::endl;
}

template <class ForwardIt>
bool isEmpty(ForwardIt beg, ForwardIt end) {
    return std::all_of(beg, end,
                       [](const Field &f) { return f != Field::Marked; });
}

template <class ForwardIt>
bool canApplyBlock(ForwardIt rowBegin, ForwardIt rowEnd, ForwardIt beg,
                   ForwardIt end) {
    return (((beg == rowBegin) || ((*(beg - 1)) != Field::Marked)) &&
            ((end == rowEnd) || ((*end) != Field::Marked)) &&
            (std::all_of(beg, end, [](const Field &f) {
                return f != Field::Forbidden;
            })));
}

template <class ForwardIt>
void applyBlock(ForwardIt beg, ForwardIt end) {
    std::fill(beg, end, Field::Marked);
}

template <class ForwardIt, class Backup>
void applyBackup(ForwardIt targetBegin, Backup backup) {
    std::copy(backup.begin(), backup.end(), targetBegin);
}

template <class ForwardIt1, class ForwardIt2, class Pred2>
bool all_of_2(ForwardIt1 begin1, ForwardIt1 end1, ForwardIt2 begin2,
              ForwardIt2 end2, Pred2 pred2) {
    bool ret = true;
    while ((begin1 < end1) && (begin2 < end2)) {
        ret = ret && pred2(*begin1, *begin2);
        begin1++;
        begin2++;
    }
    return ret;
}

template <class ForwardIt1, class ForwardIt2, class ForwardIt3, class Pred3>
bool all_of_3(ForwardIt1 begin1, ForwardIt1 end1, ForwardIt2 begin2,
              ForwardIt2 end2, ForwardIt3 begin3, ForwardIt3 end3,
              Pred3 pred3) {
    bool ret = true;
    while ((begin1 < end1) && (begin2 < end2) && (begin3 < end3)) {
        ret = ret && pred3(*begin1, *begin2, *begin3);
        begin1++;
        begin2++;
        begin3++;
    }
    return ret;
}

bool isBoardValid(ulong rowNum) {
    ulong leftRows = static_cast<ulong>(board.size() - rowNum - 1);
    if (rowNum == 0)
        return all_of_2(
            board[rowNum].begin(), board[rowNum].end(), clueSetsCheck.begin(),
            clueSetsCheck.end(), [leftRows](Field curr, ClueSet clueSet) {
                if (curr == Field::Marked) {
                    ulong remaining = static_cast<ulong>(getLength(clueSet) +
                                                         clueSet.size() - 2);
                    return ((remaining <= leftRows) && (clueSet.size() >= 1));
                } else {
                    return true;
                }
            });
    return all_of_3(
        board[rowNum - 1].begin(), board[rowNum - 1].end(),
        board[rowNum].begin(), board[rowNum].end(), clueSetsCheck.begin(),
        clueSetsCheck.end(),
        [leftRows](Field prev, Field curr, ClueSet clueSet) {
            if ((prev != Field::Marked) && (curr == Field::Marked)) {
                ulong remaining =
                    static_cast<ulong>(getLength(clueSet) + clueSet.size() - 2);
                return ((remaining <= leftRows) && (clueSet.size() >= 1));
            } else {
                return true;
            }
        });
}

void applyClues(int rowNum) {
    for (ulong i = 0; i < board[rowNum].size(); i++) {
        if (((rowNum == 0) || (board[rowNum - 1][i] != Field::Marked)) &&
            (board[rowNum][i] == Field::Marked)) {
            ulong line = clueSetsCheck[i].back();
            clueSetsCheck[i].resize(clueSetsCheck[i].size() - 1);
            for (ulong j = 1; j < line; j++) {
                board[rowNum + j][i] = Field::Marked;
            }
            if (rowNum + line < board.size()) {
                board[rowNum + line][i] = Field::Forbidden;
            }
        }
    }
}

void revertClues(ulong rowNum) {
    for (ulong i = 0; i < board[rowNum].size(); i++) {
        if (((rowNum == 0) || (board[rowNum - 1][i] != Field::Marked)) &&
            (board[rowNum][i] == Field::Marked)) {
            ulong line = 1;

            while ((rowNum + line < board.size()) &&
                   (board[rowNum + line][i] == Field::Marked)) {
                board[rowNum + line][i] = Field::Empty;
                line++;
            }
            if (rowNum + line < board.size()) {
                board[rowNum + line][i] = Field::Empty;
            }
            clueSetsCheck[i].push_back(line);
        }
    }
}

template <typename ForwardIt>
Row getBackup(ForwardIt blockBegin, ForwardIt blockEnd) {
    return Row(blockBegin, blockEnd);
}

/**
 * Solves the nonogram.
 *
 * Params:
 *  - rowNum - current row (assuming board till rowNum is valid (i.e. is a
 * partial solution))
 *  - currentPosition - iterator pointing to last position in current row that
 * was not filled
 *  - endPosition - iterator pointing to end of current row
 *  - currentClueIt - iterator pointing to first not applied clue in current row
 *  - endClueIt - iterator pointing to end of the clues in current row
 * */
template <class ForwardItRow, class ForwardItClue>
void doSolve(ulong rowNum, ForwardItRow currentPosition,
             ForwardItRow endPosition, ForwardItClue currentClueIt,
             ForwardItClue endClueIt) {
    // are all clues placed at given rowNum
    if (currentClueIt >= endClueIt) {
        // all clues at current row are placed

        // check if
        // - the remaining part of the row is valid (isEmpty)
        // - current board is valid with respect to vertical clues
        if (isEmpty(currentPosition, endPosition) && isBoardValid(rowNum)) {
            // fill the rest of the board according to current valid row
            applyClues(rowNum);
            ulong nextRow = rowNum + 1;
            if (nextRow == board.size()) {
                // the board is valid - print the result
                printBoard(board);
            } else {
                // continue with next row
                doSolve(nextRow, board[nextRow].begin(), board[nextRow].end(),
                        clueSetsBuild[nextRow].begin(),
                        clueSetsBuild[nextRow].end());
            }
            // revert the rest of the board
            revertClues(rowNum);
        }
    } else {
        // continue placing blocks in current row
        auto currentClue = *currentClueIt;

        // get total length of remaining clues/blocks with single separators
        // between them (needed to calculate last valid position of current
        // block)
        ulong remainingSpan = static_cast<ulong>(
            getSum(currentClueIt, endClueIt) + (endClueIt - currentClueIt) - 1);

        // try every position of current block
        for (auto blockBegin = currentPosition;
             blockBegin <= endPosition - remainingSpan; blockBegin++) {
            auto blockEnd = blockBegin + currentClue;
            if (canApplyBlock(currentPosition, endPosition, blockBegin,
                              blockEnd)) {
                auto backup = getBackup(blockBegin, blockEnd);
                applyBlock(blockBegin, blockEnd);
                doSolve(rowNum, blockEnd + 1, endPosition, currentClueIt + 1,
                        endClueIt);
                applyBackup(blockBegin, backup);
            } else {
                // current state of the row is invalid
                if (*blockBegin == Field::Marked) {
                    break;
                }
            }
        }
    }
}

std::vector<ulong> readLine(void) {
    std::vector<ulong> ret;
    ulong i;
    std::string line;
    getline(std::cin, line);
    std::istringstream iss(line);
    while (iss >> i) {
        ret.push_back(i);
    }
    return ret;
}

void solve() {
    doSolve(0, board[0].begin(), board[0].end(), clueSetsBuild[0].begin(),
            clueSetsBuild[0].end());
}

int main() {
    auto dim = readLine();
    ulong x = dim[0];
    ulong y = dim[1];
    board.resize(y, Row(x));
    for (ulong i = 0; i < y; i++) {
        clueSetsBuild.emplace_back(readLine());
    }
    for (ulong i = 0; i < x; i++) {
        clueSetsCheck.emplace_back(readLine());
    }

    solve();

    return 0;
}