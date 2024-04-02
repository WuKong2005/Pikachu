#include "controller.h"
#include "menu.h"
#include "game.h"

int main() {
    srand(time(NULL));
    initializeProgram();
    printLogo();
    MAIN_MENU_CONTROL();
    return 0;
}