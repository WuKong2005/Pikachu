#pragma once

#include <windows.h>
#include <conio.h>
#include "visual.h"

// enumerate the type of move in menu
enum move {
    ESC,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER
};

enum special_input {
    GET_HINT,
    TOGGLE_MUSIC,
    SAVE_GAME,
    MAGIC_MOVE
};

// Ascii code 
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ESC = 27;
const int KEY_ENTER = 13;

extern HANDLE console;
extern COORD currentCursor;

void initializeProgram();

// process and determine which type of input of user (UP, DOWN, LEFT, RIGHT, ESC)
int getKeyboardInput();

// delete the current Arrow
void removeArrow();

// Arrow
const string arrow = ">>>";

// setup, update the currentCursor to newCursor and print content
void printAtCursor(string content, COORD cursor);