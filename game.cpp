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
    for (int row = 1; row <= map.ROW; ++row)
        for (int col = 1; col <= map.COL; ++col)
            drawCell({row, col}, map.grid[row][col]); // direction access

    for (int r = 0; r <= map.ROW; ++r) {
        if (r == 0)
            for (int c = 0; c <= map.COL; ++c) {
                setCursor(upperLeftCorner.X + r * (WIDTH_CELL - 1), upperLeftCorner.Y + c * (HEIGHT_CELL - 1));
                if (c == 0)
                    cout << char(frame[UPPER_LEFT]);
                else if (c == map.COL)
                    cout << char(frame[UPPER_RIGHT]);
                else
                    cout << char(194);
            }
        else if (r == map.ROW)
            for (int c = 0; c <= map.COL; ++c) {
                setCursor(upperLeftCorner.X + r * (WIDTH_CELL - 1), upperLeftCorner.Y + c * (HEIGHT_CELL - 1));
                if (c == 0)
                    cout << char(frame[LOWER_LEFT]);
                else if (c == map.COL)
                    cout << char(frame[LOWER_RIGHT]);
                else
                    cout << char(193);
            }
        else
            for (int c = 0; c <= map.COL; ++c) {
                setCursor(upperLeftCorner.X + r * (WIDTH_CELL - 1), upperLeftCorner.Y + c * (HEIGHT_CELL - 1));
                if (c == 0)
                    cout << char(195);
                else if (c == map.COL)
                    cout << char(180);
                else
                    cout << char(197);
            }
    }
}

void game::drawCell(pair<int, int> cell, char key) {
    short posX = upperLeftCorner.X + cell.second * WIDTH_CELL;
    short posY = upperLeftCorner.Y + cell.first * HEIGHT_CELL;
    COORD position = {posX, posY};

    string side;
    side.append(WIDTH_CELL - 2, char(196));

    setCursor(position.X + 1, position.Y);
    cout << side;
    setCursor(position.X + 1, position.Y + HEIGHT_CELL - 1);
    cout << side;

    for (int col = 1; col <= HEIGHT_CELL - 2; ++col) {
        setCursor(position.X, position.Y + col);
        cout << char(179);
        setCursor(position.X + WIDTH_CELL - 1, position.Y + col);
        cout << char(179);
    }

    setCursor(position.X + WIDTH_CELL / 2, position.Y + HEIGHT_CELL / 2);
    cout << key;
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