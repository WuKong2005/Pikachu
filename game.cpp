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
    upperLeftCorner = {9, 5};
}

void game::drawInterface() {
    
}

void game::drawBoard() {
    SetConsoleCursorPosition(console, upperLeftCorner);
    
    int WidthBorder = 5 * 2 + (WIDTH_CELL - 1) * sizeCOL[diff];
    int HeightBorder = 3 * 2 + (HEIGHT_CELL - 1) * sizeROW[diff];

    for (int col = 0; col < WidthBorder; ++col) {
        if (col == 0)
            cout << char(frame[UPPER_LEFT]);
        else if (col == WidthBorder - 1)
            cout << char(frame[UPPER_RIGHT]);
        else
            cout << char(205);
        Sleep(1);
    }
    
    setCursor(upperLeftCorner.X + WidthBorder - 1, upperLeftCorner.Y + 1);
    
    for (int row = 0; row < HeightBorder - 2; ++row) {
        cout << char(186);
        setCursor(upperLeftCorner.X + WidthBorder - 1, upperLeftCorner.Y + 2 + row);
        Sleep(1);
    }

    for (int col = WidthBorder - 1; col >= 0; --col) {
        if (col == 0)
            cout << char(frame[LOWER_RIGHT]);
        else if (col == WidthBorder - 1)
            cout << char(frame[LOWER_LEFT]);
        else
            cout << char(205);

        setCursor(upperLeftCorner.X + col, upperLeftCorner.Y + HeightBorder - 1);
        Sleep(1);
    }

    for (int row = HeightBorder - 1; row > 0; --row) {
        setCursor(upperLeftCorner.X, upperLeftCorner.Y + row);
        if (row == HeightBorder - 1)
            cout << char(frame[LOWER_LEFT]);
        else
            cout << char(186);
        Sleep(1);
    }

    for (int row = 1; row <= map.ROW; ++row)
        for (int col = 1; col <= map.COL; ++col)
            drawCell({row, col}, 'A'); // direction access
}

void game::drawCell(pair<int, int> cell, char key) {
    short posX = upperLeftCorner.X + cell.second * (WIDTH_CELL - 1);
    short posY = upperLeftCorner.Y + cell.first * (HEIGHT_CELL - 1);
    COORD position = {posX, posY};
    SetConsoleCursorPosition(console, position);
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