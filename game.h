#pragma once

#include "menu.h"
#include "Visual.h"
#include "controller.h" 
#include "board.h"
//#include "player.h"

using namespace std;

int const WIDTH_CELL = 9;
int const HEIGHT_CELL = 5;

struct game {
    board map;
    char** background;
    pair<int, int> currentSelect;
    int numLeft;
    bool isPlaying;
    int diff;
    COORD originBoard;
    //player currentPlayer;

    game();
    ~game(); 
    game(int difficult); //Start a new game based on choosen difficult
    game(string pathSaveFile); //Load save file

    void drawInterface(); //Draw everything 
    void drawBoard(); //Draw the board and its boundary
    void drawCell(pair<int, int> cell, char key); //Draw each cell from the board
    void drawGuide(); //Draw text box of guide, help, etc

    void drawPath(pair<int, int> startCell, pair<int, int> endCell, vector<pair<int, int>> path); //Draw the path between 2 cells
    void drawLine(pair<int, int> startCell, pair<int, int> endCell); //Draw the straight line between 2 cells
    void drawVerticalLine(int r, int c1, int c2); //Draw a vertical line
    void drawHorizontalLine(int c, int r1, int r2); //Draw a horizontal line
    void drawTurningPoint(int type); //Draw the turning point

    void moveCell(int direction); //Move the current cursor in this board in a direction
    void highlightCell(); //Highlight a cell
    void unHighlightCell(); //Unhighlight a cell

    void select(); //Select this cell or unselect it (if it is already selected)
    void getRespond(pair<int, int> nextSelect); //Determine if this move is valid, and respond to that decision

    void startGame(); //Start the game
    void finishGame(); //Finish the game
};

