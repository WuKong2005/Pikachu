#include "controller.h"
#include "menu.h"
#include "game.h"

int main() {
    srand(time(NULL));
    // SetConsoleScreenBufferSize(console, )
    // initializeProgram();
    // SetConsoleOutputCP(65001);
    // printLogo();
    // MAIN_MENU_CONTROL();
    // playSound(MENU);
    // system("pause");
    // playSound(MENU, true);
    


    SetConsoleOutputCP(437);
    game g(EASY);
    system("pause");
    Sleep(1000);
    g.startGame();
    return 0;
}