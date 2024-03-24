#include "controller.h"

char getKeyboard;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD currentCursor = {0, 0};

void initializeProgram() {
    
}

int getKeyboardInput () {
    getKeyboard = _getch(); // store the keyboard input

    // check if the input is arrow key
    if (getKeyboard == 0 || getKeyboard == 224) {
        switch(_getch()) {
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

void printAtCursor(string content, COORD cursor) {
    currentCursor.X = cursor.X;
	currentCursor.Y = cursor.Y;
    SetConsoleCursorPosition(console, currentCursor);
    cout << content;
}
