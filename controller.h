#pragma once

#include <windows.h>
#include <conio.h>
#include "game.h"

// enumerate the type of move in menu
enum move {
    ESC,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER
};

// Ascii code 
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ESC = 27;
const int KEY_ENTER = 13;

// process and determine which type of input of user (UP, DOWN, LEFT, RIGHT, ESC)
int getKeyboardInput();

// delete the current Arrow
void removeArrow();

// setup, update the currentCursor to newCursor and print content
void printAtCursor(string content, COORD cursor, string color = TEXT_BLACK);