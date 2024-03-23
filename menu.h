#pragma once

#include "Visual.h"
#include "controller.h"

const COORD FIRST_BLOCK[5] = {
    {52, 20}, // MAIN_MENU
    {52, 20}, // PLAY_GAME
    {52, 20}, // GAME_MODE
    {52, 0},
    {52, 0}
};

const int distanceY[5] = {
    10, // MAIN_MENU
    0, // PLAY_GAME
    0, // GAME_MODE
    0,
    0,
};
const int numBlock[5] = {
    4, // MAIN_MENU
    3, // PLAY_GAME
    3, // GAME_MODE
    0,
    0
};


void moveCursor(int visual, int input);

void MAIN_MENU_CONTROL();
void PLAY_GAME_CONTROL();
void GAME_MODE_CONTROL();