#pragma once

#include "menu.h"
#include "Visual.h"
#include "controller.h" 

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD currentCursor = {0, 0};
int getKeyboard;

