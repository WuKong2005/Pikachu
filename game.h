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
    int getCurrentTime();   
    
    // Draw everything 
    void drawInterface();
    // Draw the board and its boundary
    void drawBoard();
    // Draw each cell from the board
    void drawCell(pair<int, int> cell, char key);
    // delete a cell
    void removeCell(pair<int, int> cell);
    // Draw the path between 2 cells
    void drawPath(vector<pair<int, int>> path, bool draw); 
    // Draw or delete the straight line between 2 cells
    void drawLine(pair<int, int> startCell, pair<int, int> endCell, bool draw); 
    // Draw or delete a vertical line
    void drawVerticalLine(int col, int row1, int row2, bool draw); 
    // Draw or delete a horizontal line
    void drawHorizontalLine(int row, int col1, int col2, bool draw);
    // Draw or delete a turning point
    void drawTurningPoint(int row, int col, int type, bool draw); 

    // Move the current cursor in this board in a direction
    void moveCell(int direction); 
    // Highlight a cell
    void highlightCell(int row, int col, string color); 
    // Unhighlight a cell
    void unHighlightCell(int row, int col); 
    // Select this cell or unselect it (if it is already selected)
    void select(); 
    // Determine if this move is valid, and respond to that decision
    void getRespond(pair<int, int> nextSelect); 

    // Get hint
    bool moveSuggestion();
    // 
    bool magicMove();
    // hidden cell feature
    void hiddenCell();
    // magic matching feature
    void magicMatch();
    // Open help menu when playing game
    void helpMenu();

    void saveScore();
    void saveGame();
    void saveGame(int slot);
    bool verifySaveFile(int slot);
    void loadGame(int slot);

    void startGame(); // Start the game
    bool finishGame(); // Finish the game

    void getBackground();

    void updateInfo();
    void renderScore();
    void renderHint();
    void renderMagic();
    void renderTime();
    void renderNotificate(string noti);
};

