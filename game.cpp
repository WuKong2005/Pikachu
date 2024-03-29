#include "game.h"

game::game() {
    map = board();
    background = NULL;
    currentSelect = {-1, -1};
    numLeft = 0;
    isPlaying = false;
    diff = -1;
    //currentPlayer = player();
}

game::~game() {
    
}

game::game(int difficult) {
    cerr << "create a new game\n";
    map.~board();
    cerr << "deconstructor\n";
    new (&map) board(difficult);
    cerr << "first, finish create board\n";
    map.initializeBoard();
    cerr << "then, finish initialize board\n";
    ROW = map.ROW, COL = map.COL;
    originBoard = {2, 2};
    //background
    //currentPlayer = player();
}

void game::drawInterface() {
    
}

void game::drawBoard() {
    // WIDTH_CELL * COL + 1 * (COL + 1) * 1 + WIDTH_CELL * 2
    // HEIGHT_CELL * ROW + 1 + HEIGHT_CELL * 2
    system("pause");
    for (int x = 0; x < WIDTH_CELL * COL + 1 * (COL + 1) * 1 + WIDTH_CELL * 2; x++) {
        printAtCursor("_", {(short)(originBoard.X + x), originBoard.Y});
        printAtCursor("_", {(short)(originBoard.X + x), (short)(originBoard.Y + HEIGHT_CELL * ROW + HEIGHT_CELL * 2)});
        Sleep(5);
    }

    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            drawCell(make_pair(r, c));
            Sleep(20);
        }
    }

    system("pause");
}

void game::drawCell(pair<int, int> cell) {
    // 3 | and 7 _ 
    COORD centralCell = {0, 0};
    centralCell.X = (short)(originBoard.X + WIDTH_CELL + (cell.second - 1) * WIDTH_CELL + (WIDTH_CELL + 1) / 2);
    centralCell.Y = (short)(originBoard.Y + HEIGHT_CELL + (cell.first - 1) * HEIGHT_CELL + (HEIGHT_CELL + 1) / 2);
    printAtCursor(string(1, map.getChar(cell)), centralCell);
}

void game::drawGuide() {

}

void game::startGame() {
    clearScreen();

    drawBoard();
    //drawInterface();


}

void game::finishGame() {
    clearScreen();
}