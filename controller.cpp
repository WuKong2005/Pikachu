#include "controller.h"

int getKeyboardInput () {
    getKeyboard = _getch();
    if (getKeyboard == 0 || getKeyboard == 224) {
        switch(getKeyboard) {
            case KEY_UP:
                return UP;
            case KEY_DOWN:
                return DOWN;
            case KEY_LEFT:
                return LEFT;
            case KEY_RIGHT:
                return RIGHT;
            default:
                return -1;
        }
    } else {
        switch(getKeyboard) {
            case KEY_ESC:
                return ESC;
            case 'W': case 'w':
                return UP;
            case 'S': case 's':
                return DOWN;
            case 'A': case 'a':
                return LEFT;
            case 'D': case 'd':
                return RIGHT;
            case KEY_ENTER:
                return ENTER;
            default:
                return -1;
        }
    }
}


void removeArrow() {
    SetConsoleCursorPosition(console, currentCursor);
    cout << "   ";
}

void setCursor(COORD newCursor) {
    currentCursor.X = newCursor.X;
	currentCursor.Y = newCursor.Y;
    SetConsoleCursorPosition(console, currentCursor);
}

