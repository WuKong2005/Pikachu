#include "menu.h"

void moveCursor(int visual, int input) {
    switch (input) {
        case ESC:
            return;
        case UP:
            if (currentCursor.Y != FIRST_BLOCK[MAIN_MENU].Y)
                currentCursor.Y -= distanceY[visual];
            break;
        case DOWN:
            if (currentCursor.Y != FIRST_BLOCK[MAIN_MENU].Y + (numBlock[visual] - 1) * distanceY[visual])
                currentCursor.Y += distanceY[visual];
            break;
        default:
            break;
    }
	SetConsoleCursorPosition(console, currentCursor);
}

void MAIN_MENU_CONTROL() {
    cout << TEXT_BLACK; // set BLACK color (default)
    cout << Visual[MAIN_MENU];

    setCursor(FIRST_BLOCK[MAIN_MENU]);
    cout << ">>>";

    while (true) {
        int input = getKeyboardInput();
        setCursor(currentCursor);
        cout << "   ";
        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            int pos = (currentCursor.Y - FIRST_BLOCK[MAIN_MENU].Y) / distanceY[MAIN_MENU];
            switch (pos) {
                case 0:
                    return PLAY_GAME_CONTROL();
                default:
                    return;
            }
        }
        moveCursor(MAIN_MENU, input);
        cout << ">>>";
    }
}

void PLAY_GAME_CONTROL() {
    cout << Visual[PLAY_GAME];
}

void GAME_MODE_CONTROL() {
}