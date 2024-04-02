#pragma once

#include "Visual.h"
#include "controller.h"
#include "game.h"
#include <fstream>
#include <windows.h>
#include <iostream>

using namespace std;

// Arrow
const string arrow = ">>>";

// Coordinate of the arrow points to the first block of each Visual
const COORD ARROW_POS_FIRST_BLOCK[5] = {
    {52, 20}, // MAIN_MENU
    {52, 20}, // PLAY_GAME
    {52, 20}, // GAME_MODE
    {52, 20}, // LOAD_GAME
    {44, 10} // USERNAME
};

// enumerate the difficulty (use for row of LEADERBOARD)
enum difficulty {
    easy,
    medium,
    hard
};

// enumerate the information (use for column of LEADERBOARD)
enum information {
    Username,
    Score,
    Time,
    Date
};

// coordinate of first row of each difficulty in LEADERBOARD
const int row_Leaderboard[3] = {
    8, // easy
    14, // medium
    20 // hard
};

// column of information in LEADERBOARD
const int column_Leaderboard[4] {
    41, // Username
    82, // Time
    99, // Score
    113 // Date
};

// filename which is stored data of LEADERBOARD
const string saveFilePath[3] = {
    "record/easy.txt", // easy
    "record/medium.txt", // medium
    "record/hard.txt" // hard
};

// control the user interface
void MAIN_MENU_CONTROL();
void PLAY_GAME_CONTROL();
void GAME_MODE_CONTROL();
void LOAD_GAME_CONTROL();
void LEADERBOARD_CONTROL();
void HELP_CONTROL();
string USERNAME_CONTROL();