#pragma once

#include "Visual.h"
#include "controller.h"

// Coordinate of first block of each Visual
const COORD FIRST_BLOCK[6] = {
    {52, 20}, // MAIN_MENU
    {52, 20}, // PLAY_GAME
    {52, 20}, // GAME_MODE
    {52, 20}, // LOAD_GAME
    {52, 0},
    {52, 0}
};

// distance between each block of each Visual
const int distanceY[6] = {
    3, // MAIN_MENU
    4, // PLAY_GAME
    3, // GAME_MODE
    3, // LOAD_GAME
    0,
    0
};

// number of block of each Visual
const int numBlock[6] = {
    4, // MAIN_MENU
    3, // PLAY_GAME
    4, // GAME_MODE
    4, // LOAD_GAME
    0,
    0
};

// Arrow
const string arrow = ">>>";

// move the Cursor according to keyboardInput (UP, DOWN, ESC)
void Visual_moveCursor(int visual, int input);

// control the user interface
void MAIN_MENU_CONTROL();
void PLAY_GAME_CONTROL();
void GAME_MODE_CONTROL();
void LOAD_GAME_CONTROL();
void LEADERBOARD_CONTROL();