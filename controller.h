#pragma once

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
#pragma comment(lib, "Winmm.lib")

using namespace std;

// enumerate the type of move in menu
enum move {
    ESC,
    DOWN,
    RIGHT,
    UP,
    LEFT,
    ENTER
};

enum special_input {
    GET_HINT = ENTER + 1,
    TOGGLE_MUSIC,
    SAVE_GAME,
    MAGIC_MOVE,
    HELP_MENU
};

enum SOUND_EFFECT {
    MENU,
    EASY_MODE,
    MEDIUM_MODE,
    HARD_MODE,
    EXTRA_MODE,
    CHOOSE,
    MOVE,
    VALID_MOVE,
    INVALID_MOVE,
    WIN,
    LOSE
};

// Ascii code of some navigation key 
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ESC = 27;
const int KEY_ENTER = 13;
const int KEY_BACKSPACE = 8;

// 
extern HANDLE console;
extern COORD currentCursor;

void initializeProgram();

// process and determine which type of input of user (UP, DOWN, LEFT, RIGHT, ESC)
int getInputKey();

// delete the current Arrow
void removeArrow();

// hide the Cursor in Console
void hideCursor();
// show the cursor
void showCursor();

// hide the Scroll bars
void hideScrollBars();

// set Cursor to coordinates (x, y)
void setCursor(short x, short y);

// update the currentCursor to newCursor and print content
void printAtCursor(string content, COORD cursor, string textColor = "\x1B[0m");

void clearScreen();

void playSound(int type, bool stop = false);

void toggleMusic(int type);