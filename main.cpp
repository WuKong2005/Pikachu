#include "controller.h"
#include "menu.h"
#include "game.h"

int main() {
    // initializeProgram();
    // SetConsoleOutputCP(65001);
    SetConsoleOutputCP(437);
    game g;
    g.drawCell({1,1}, EASY);
    // printLogo();
    // MAIN_MENU_CONTROL();

    // cerr << "startgame\n";
    
    // game newGame(EASY);
    // // cerr << "finish create\n";
    // system("pause");
    // newGame.startGame();
    system("pause");

    return 0;
}