#include "controller.h"
#include "menu.h"
#include "game.h"

int main() {
    // initializeProgram();
    // SetConsoleOutputCP(65001);
    // printLogo();
    // MAIN_MENU_CONTROL();

    SetConsoleOutputCP(437);
    game g(EASY);
    g.drawBoard();

    // cerr << "startgame\n";
    
    // game newGame(EASY);
    // // cerr << "finish create\n";
    // system("pause");
    // newGame.startGame();
    system("pause");

    return 0;
}