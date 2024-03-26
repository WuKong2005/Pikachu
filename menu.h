#pragma once

#include "Visual.h"
#include "controller.h"
#include <fstream>
#include <windows.h>
#include <iostream>

// Coordinate of first block of each Visual
const COORD FIRST_BLOCK[5] = {
    {52, 20}, // MAIN_MENU
    {52, 20}, // PLAY_GAME
    {52, 20}, // GAME_MODE
    {52, 20}, // LOAD_GAME
    {36, 9} // USERNAME
};

// distance between each block of each Visual
const int distanceBlock[4] = {
    3, // MAIN_MENU
    4, // PLAY_GAME
    3, // GAME_MODE
    3 // LOAD_GAME
};

// number of block of each Visual
const int numBlock[4] = {
    4, // MAIN_MENU
    3, // PLAY_GAME
    4, // GAME_MODE
    4 // LOAD_GAME
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
    Time,
    Score,
    Date
};

// row of no.1 of each difficulty in LEADERBOARD
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

// file name which is stored data of LEADERBOARD
const string fileName[3] = {
    "easy.txt", // easy
    "medium.txt", // medium
    "hard.txt" // hard
};

// control the user interface
void MAIN_MENU_CONTROL();
void PLAY_GAME_CONTROL();
void GAME_MODE_CONTROL();
void LOAD_GAME_CONTROL();
void LEADERBOARD_CONTROL();
void HELP_CONTROL();
string USERNAME_CONTROL();