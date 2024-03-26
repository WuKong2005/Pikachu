#pragma once

#include "menu.h"
#include "Visual.h"
#include "controller.h" 
#include "board.h"

using namespace std;

struct game {
    board map;
    char** background;
    pair<int, int> currentSelect;
    int numLeft;
    bool isPlaying;

    game();
    ~game();
    game(int difficult);
    game(string pathSaveFile);

    void select();

    void startGame();
    void finishGame();
};

