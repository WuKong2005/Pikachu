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
#include <tuple>

using namespace std;

//4 possible moves
int const dx[] = {1, 0, -1, 0};
int const dy[] = {0, 1, 0, -1};

//Size of alphabet used
int const ALPHABET = 26;

//Size of board based on difficult the player choosed
//Easy; Medium; Hard - Easy peasy; Medium is premium; Things may be hard, but I'm harder
int const sizeROW[] = {4, 6, 7};
int const sizeCOL[] = {6, 9, 12};
int const limTime[] = {60, 150, 300};

//Gamemode
enum DIFFICULT {
    EASY,
    MEDIUM,
    HARD,
};

// type of corner
enum corner {
    UPPER_LEFT,
    UPPER_RIGHT,
    LOWER_LEFT,
    LOWER_RIGHT
};

// ascii code of 4-corners
const int frame[4] = {201, 187, 200, 188};

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
    array<int, 3>*** flood;
    array<int, 4> suggestPair;

    board();
    board(int difficult);
    ~board();
    void createBoard(int difficult);

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
    
    void importBoard();
    pair<string*, int> readBoard(string pathSaveFile, bool checkOnly);
    void loadBoard(pair<string*, int> saveBoard);
};