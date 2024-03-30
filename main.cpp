#include "controller.h"
#include "menu.h"
#include "game.h"

int main() {
    // initializeProgram();
    // SetConsoleOutputCP(65001);
    // printLogo();
    // MAIN_MENU_CONTROL();

    SetConsoleOutputCP(437);
    game g(HARD);
    g.drawBoard();
    g.highlightCell(1, 1, BACKGROUND_COLOR[RED]);
    Sleep(2000);
    g.unHighlightCell(1, 1);

    // cerr << "startgame\n";
    
    // game newGame(EASY);
    // // cerr << "finish create\n";
    // system("pause");
    // newGame.startGame();
    system("pause");

    return 0;
}