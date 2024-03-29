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

COORD upperLeftCorner = {1, 1};

//Gamemode
enum DIFFICULT {
    EASY,
    MEDIUM,
    HARD,
};

enum corner {
    UPPER_LEFT,
    UPPER_RIGHT,
    LOWER_LEFT,
    LOWER_RIGHT
}

const int frame[] = {218, 191, 192, 217};

//Type of matching
enum MATCHING {
    I_MATCHING,
    L_MATCHING,
    Z_MATCHING,
    U_MATCHING,
    MAGIC_MATCHING
};

struct board {
    int ROW, COL;
    char** grid;
    int timeCheck = 0;
    array<int, 3>** flood;
    array<int, 4> suggestPair;

    board();
    board(int difficult);
    ~board();

    void initializeBoard();
    void shuffleBoard();

    char getChar(pair<int, int> cell);

    bool checkMatch(pair<int, int> startCell, pair<int, int> endCell, bool magic = false, bool* found = NULL);
    vector<pair<int, int>> getPath(pair<int, int> startCell, pair<int, int> endCell);
    int getTypePath(vector<pair<int, int>> path);

    void deleteCell(pair<int, int> cell);
    void deleteMatch(pair<int, int> startCell, pair<int, int> endCell);

    bool automaticCheck();
    array<int, 4> suggestMove();
    
    void importBoard();
    pair<string*, int> readBoard(string pathSaveFile);
    void loadBoard(pair<string*, int> saveBoard);
};