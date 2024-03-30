#include "controller.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD currentCursor = {0, 0};

void initializeProgram() {
    SetConsoleOutputCP(65001);
}

int getInputKey() {
    int input = _getch(); // store the keyboard input

    // check if the input is arrow key
    if (input == 0 || input == 224) {
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
    } else { // if input is W, A, S, D or ENTER
        switch(input) {
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

void setCursor(short x, short y) {
    COORD cursor = {x, y};
    SetConsoleCursorPosition(console, cursor);
}

void printAtCursor(string content, COORD cursor, string textColor) {
    // setup the surrentCursor to cursor
    currentCursor.X = cursor.X;
	currentCursor.Y = cursor.Y;
    SetConsoleCursorPosition(console, currentCursor);
    // print content
    cout << content;
}

void clearScreen() {
    system("cls");
}
