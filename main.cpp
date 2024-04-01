#include "controller.h"
#include "menu.h"
#include "game.h"

int main() {
    // initializeProgram();
    // SetConsoleOutputCP(65001);
    // printLogo();
    // MAIN_MENU_CONTROL();
    // playSound(MENU);
    // system("pause");
    // playSound(MENU, true);
    // system("pause");

    SetConsoleOutputCP(437);
    system("cls");
    game g(EASY);
    // assert(g.verifySaveFile());
    // g.loadGame();
    g.startGame();
    return 0;
}