#include "game.h"

game::game() {
    
}

game::~game() {
    
}

game::game(int difficult) {
    map.~board();
    new (&map) board(difficult);
    numLeft = map.ROW * map.COL;
    isPlaying = true;
    diff = difficult;
    originBoard = {2, 2};
}

void game::drawInterface() {
    
}

void game::drawBoard() {

}

void game::drawCell(pair<int, int> cell) {
    
    
}

void game::drawGuide() {

}

void game::drawPath(pair<int, int> startCell, pair<int, int> endCell, vector<pair<int, int>> path) {

}

void game::drawLine(pair<int, int> startCell, pair<int, int> endCell) {

} 

void game::game::drawVerticalLine(int r, int c1, int c2) {

}

void game::drawHorizontalLine(int c, int r1, int r2) {

}

void game::drawTurningPoint(int type) {

}

void game::moveCell(int direction) {

}

void game::highlightCell() {

}

void game::unHighlightCell() {

}

void game::select() {

} 

void game::getRespond(pair<int, int> nextSelect) {

}

void game::startGame() {

}

void game::finishGame() {
    
}