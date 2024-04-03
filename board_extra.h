#pragma once

#include "linkedlist_2darray.h"
#include "board.h"

const string backGroundImageExtra = "background\\hard.txt";

struct board_extra {
    int ROW, COL;
    linked_list_2d grid;
    int timeCheck = 0;
    array<int, 3>*** flood;
    array<int, 4> suggestPair;
    pair<int, int> boardPos = {2, 5}; 

    board_extra(int difficult = 2);
    ~board_extra();

    void initializeBoard();
    void shuffleBoard();

    char getChar(pair<int, int> cell);
    void assignCell(pair<int, int> cell, char c);

    bool checkMatch(pair<int, int> startCell, pair<int, int> endCell, bool magic = false, bool* found = NULL);
    vector<pair<int, int>> getPath(pair<int, int> startCell, pair<int, int> endCell);
    int getTypePath(vector<pair<int, int>> path);

    void deleteCell(pair<int, int> cell);
    void deleteMatch(pair<int, int> startCell, pair<int, int> endCell);

    bool automaticCheck();
    array<int, 4> suggestMove();
};