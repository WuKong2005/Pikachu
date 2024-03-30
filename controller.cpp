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

void playSound(int type, bool stop, bool loop) {
	static vector<wstring> soundFile{L"bgm/menu.mp3", L"bgm/easy.mp3", L"bgm/medium.mp3", L"bgm/hard.mp3", L"bgm/extra.mp3", L"sfx/moveMenu.wav", L"sfx/moveIngame.wav" , L"sfx/error.wav", L"sfx/valid.wav", L"sfx/invalid.wav", L"sfx/win.wav", L"sfx/lose.wav"};
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
        // cerr << wcscmp(command.c_str(), L"play \"bgm/menu.mp3\" repeat") << '\n';
        // wcerr << command.c_str() << '\n';
        // wcerr << L"play \"bgm/menu.mp3\" repeat" << '\n';
        // mciSendStringW(L"play \"bgm/menu.mp3\" repeat", 0, 0, 0);
    }
    else {
        PlaySoundW(soundFile[type].c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }
}
