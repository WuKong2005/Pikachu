#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <array>
#include <assert.h>
#include <numeric>
#include <tuple>

using namespace std;

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

enum turningCorner {
    DOWN_RIGHT,
    DOWN_LEFT,
    UP_RIGHT,
    UP_LEFT
};

//Type of matching
enum MATCHING {
    I_MATCHING,
    L_MATCHING,
    Z_MATCHING,
    U_MATCHING,
    MAGIC_MATCHING
};

//Size of alphabet used
int const ALPHABET = 26;

//4 possible moves
int const dx[] = {1, 0, -1, 0};
int const dy[] = {0, 1, 0, -1};

//Size of board based on difficult the player choosed
//Easy; Medium; Hard - Easy peasy; Medium is premium; Things may be hard, but I'm harder
int const sizeROW[] = {6, 6, 7};
int const sizeCOL[] = {7, 10, 12};
int const limTime[] = {240, 420, 600};

// ascii code of 4-corners
const int frame[4] = {201, 187, 200, 188};

// ascii code of 4 turingCorner
const int turning[4] = {218, 191, 192, 217};

const string backGroundImage[3] = {"background\\easy.txt", "background\\medium.txt", "background\\hard.txt"};

struct board {
    int ROW, COL;
    char** grid;
    int timeCheck = 0;
    array<int, 3>*** flood;
    array<int, 4> suggestPair;
    pair<int, int> boardPos[3] = {{11, 5}, {6, 5} , {2, 5}}; 

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