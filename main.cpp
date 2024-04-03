#include "controller.h"
#include "menu.h"
#include "game.h"
#include "game_extra.h"

int main() {
    srand(time(NULL));
    initializeProgram();
    printLogo();
    MAIN_MENU_CONTROL();

    // game_extra newGame(2);
    // cerr << "extra mode\n";
    // system("pause");
    // newGame.startGame();
    return 0;
}