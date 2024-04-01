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
            case 'H': case 'h':
                return GET_HINT;
            case 'M': case 'm':
                return TOGGLE_MUSIC;
            case 'P': case 'p':
                return SAVE_GAME;
            case 'G': case 'g':
                return MAGIC_MOVE;
            case 'C': case 'c':
                return HELP_MENU;
            default:
                return -1;
        }
    }
}

void removeArrow() {
    SetConsoleCursorPosition(console, currentCursor);
    cout << "   ";
}

void hideCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // get Handle of the output console
	CONSOLE_CURSOR_INFO cursorInfo; // get the infomation of the cursor
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false; // hide the cursor
	cursorInfo.dwSize = 100; // set the cursor size to a large value
	SetConsoleCursorInfo(console, &cursorInfo); // apply the changes
}

void showCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // get Handle of the output console
	CONSOLE_CURSOR_INFO cursorInfo; // get the infomation of the cursor
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = true; // show the cursor
	cursorInfo.dwSize = 1; // set the cursor size to 1
	SetConsoleCursorInfo(console, &cursorInfo); // apply the changes
}

void hideScrollBars() {
    HWND consoleWindow = GetConsoleWindow();
	ShowScrollBar(consoleWindow, SB_BOTH, false);
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

void playSound(int type, bool stop, bool loop) {
	static vector<wstring> soundFile{L"bgm/menu.mp3", L"bgm/easy.mp3", L"bgm/medium.mp3", L"bgm/hard.mp3", L"bgm/extra.mp3", L"sfx/choose.wav", L"sfx/move.wav" , L"sfx/valid.wav", L"sfx/invalid.wav", L"sfx/win.wav", L"sfx/lose.wav"};
    if (type <= EXTRA_MODE) {
        wstring command;
        if (!stop) {
            command += LR"(play ")" + soundFile[type] + LR"(")";
            if (loop) {
                command += LR"( repeat)";
            }
        }
        else {
            command += LR"(stop ")" + soundFile[type] + LR"(")";
        }
        mciSendStringW(command.c_str(), 0, 0, 0);
    }
    else {
        PlaySoundW(soundFile[type].c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }
}
