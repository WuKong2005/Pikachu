#pragma once

#include <windows.h>
#include <conio.h>
#include "game.h"

enum move {
    ESC,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER
};

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ESC = 27;
const int KEY_ENTER = 13;

int getKeyboardInput();

void removeArrow();
void setCursor(COORD);
