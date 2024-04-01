#pragma once

#include "menu.h"
#include "Visual.h"
#include "controller.h" 
#include "board.h"
#include "account.h"

using namespace std;

int const WIDTH_CELL = 9;
int const HEIGHT_CELL = 5;
int const BUFFER_WIDTH_CELL = 7;
int const BUFFER_HEIGHT_CELL = 3;

struct game {
    board map;
    string* background;
    pair<int, int> currentPos, currentSelect;
    int timeUsed, numLeft, diff, score, useHint, useMagicMatching, useHiddenCell;
    bool isPlaying, applyMagicMatching, applyHiddenCell;
    pair<pair<int, int>, char> tempCell;
    COORD upperLeftCorner;
    account player;
    time_t timeStart;

    game();
    ~game(); 
    game(int difficult); // Start a new game based on choosen difficult
    
    int timeDuration();

    void drawInterface(); // Draw everything 
    void drawBoard(); // Draw the board and its boundary
    void drawCell(pair<int, int> cell, char key); // Draw each cell from the board
    void removeCell(pair<int, int> cell); // delete a cell
    void drawGuide(); // Draw text box of guide, help, etc

    void drawPath(vector<pair<int, int>> path, bool draw); // Draw the path between 2 cells
    void drawLine(pair<int, int> startCell, pair<int, int> endCell, bool draw); // Draw or delete the straight line between 2 cells
    void drawVerticalLine(int col, int row1, int row2, bool draw); // Draw or delete a vertical line
    void drawHorizontalLine(int row, int col1, int col2, bool draw); // Draw or delete a horizontal line
    void drawTurningPoint(int row, int col, int type, bool draw); // Draw or delete a turning point

    void moveCell(int direction); // Move the current cursor in this board in a direction
    void highlightCell(int row, int col, string color); // Highlight a cell
    void unHighlightCell(int row, int col); // Unhighlight a cell
    
    void select(); // Select this cell or unselect it (if it is already selected)
    void getRespond(pair<int, int> nextSelect); // Determine if this move is valid, and respond to that decision
    bool moveSuggestion();
    bool magicMove();
    void hiddenCell();
    void magicMatch();
    void helpMenu();

    void saveScore();
    void saveGame();
    bool verifySaveFile();
    void loadGame();

    void startGame(); // Start the game
    void finishGame(); // Finish the game
};

