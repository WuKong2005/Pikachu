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
    g.drawBoard();
    for (int i = 2; i <= 4; ++i)
        for (int j = 2; j <= 4; ++j) {
            g.map.grid[i][j] = '$';
        }
    // Sleep(2000);
    
    // g.removeCell({2, 2});
    // g.removeCell({2, 3});
    // g.removeCell({2, 4});

    g.drawHorizontalLine(3, 1, 4);
    Sleep(2000);
    g.drawTurningPoint(3, 4, LEFT_UP);
    Sleep(2000);
    g.drawVerticalLine(4, 1, 3);

    // cerr << "startgame\n";
    
    // game newGame(EASY);
    // // cerr << "finish create\n";
    // system("pause");
    // newGame.startGame();
    system("pause");
    return 0;
}