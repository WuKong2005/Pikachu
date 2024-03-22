#pragma once

#include <iostream>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <queue>
#include <array>
#include <assert.h>
#include <numeric>

using namespace std;

//4 possible moves
int const dx[] = {1, 0, -1, 0};
int const dy[] = {0, 1, 0, -1};

//Size of alphabet used
int const ALPHABET = 26;

//Size of board based on difficult the player choosed
//Easy; Medium; Hard - Easy peasy; Medium is premium; Things may be hard, but I'm harder
int const sizeROW[] = {4, 6, 9};
int const sizeCOL[] = {6, 9, 16};

//Gamemode
enum DIFFICULT {
    EASY,
    MEDIUM,
    HARD,
};

struct board {
    int ROW, COL;
    char** grid;
    int timeCheck = 0;
    array<int, 3>** flood;

    board();
    board(int difficult);
    ~board();

    bool readSaveFile(string pathSaveFile);
    void initializeBoard();
    void shuffleBoard();
    bool checkMatch(pair<int, int> startCell, pair<int, int> endCell, bool magic = false, bool* found = NULL);
    void deleteCell(pair<int, int> cell);
    void deleteMatch(pair<int, int> startCell, pair<int, int> endCell);
    bool automatic_check();

    void importBoard();
    vector<pair<int, int>> getPath(pair<int, int> startCell, pair<int, int> endCell);
};