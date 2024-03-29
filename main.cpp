#include "controller.h"
#include "menu.h"
#include "game.h"

int main() {
    // initializeProgram();
    SetConsoleOutputCP(65001);
    printLogo();
    MAIN_MENU_CONTROL();

    // cerr << "startgame\n";
    
    // game newGame(EASY);
    // // cerr << "finish create\n";
    // system("pause");
    // newGame.startGame();

    return 0;
}