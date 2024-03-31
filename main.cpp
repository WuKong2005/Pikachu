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
    game g(EASY);
    g.startGame();
    return 0;
}