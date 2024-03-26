#include "controller.h"
#include "menu.h"

int main() {
    initializeProgram();
    SetConsoleOutputCP(65001);
    printLogo();
    MAIN_MENU_CONTROL();

    return 0;
}