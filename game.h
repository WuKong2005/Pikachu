#pragma once

#include "menu.h"
#include "Visual.h"
#include "controller.h" 
#include "board.h"
//#include "player.h"

using namespace std;

int const WIDTH_CELL = 7;
int const HEIGHT_CELL = 3;

struct game {
    board map;
    int ROW, COL;
    char** background;
    pair<int, int> currentSelect;
    int numLeft;
    bool isPlaying;
    int diff;
    COORD originBoard;
    //player currentPlayer;

    game();
    ~game();
    game(int difficult);
    game(string pathSaveFile);

    void drawInterface();
    void drawBoard();
    void drawCell(pair<int, int> cell);
    void drawGuide();

    void drawPath(pair<int, int> startCell, pair<int, int> endCell);
    void drawLine(pair<int, int> startCell, pair<int, int> endCell);
    void drawVerticalLine(int r, int c1, int c2);
    void drawHorizontalLine(int c, int r1, int r2);
    void drawTurningPoint(int type);

    void moveCell(int direction);
    void highlightCell();
    void unHighlightCell();

    void select();
    void getRespond(pair<int, int> nextSelect);

    void startGame();
    void finishGame();
};

