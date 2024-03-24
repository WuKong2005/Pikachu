#pragma once

#include "menu.h"
#include "Visual.h"
#include "controller.h" 
#include "board.h"

using namespace std;

struct game {
    board map;
    char** background;
    pair<int, int> curSelect;
    pair<int, int> choosenCell;
    int numLeft;
    bool isPlaying;

    game();
    ~game();
    game(int difficult);
    game(string pathSaveFile);

    void select();
    void deSelect();
    

};

