#pragma once

#include "Visual.h"
#include "controller.h"
#include "game.h"
#include "game_extra.h"
#include <fstream>
#include <windows.h>
#include <iostream>

using namespace std;

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

// Arrow
const string arrow = ">>>";

// Coordinate of the arrow points to the first block of each Visual
const COORD ARROW_POS_FIRST_BLOCK[5] = {
    {60, 20}, // MAIN_MENU
    {60, 20}, // PLAY_GAME
    {60, 20}, // GAME_MODE
    {60, 20}, // LOAD_GAME
    {60, 11} // USERNAME
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
bool USERNAME_CONTROL(string& username, string& password, bool loadFile = false, string usernameSaveFile = "", string passwordSaveFile = "");