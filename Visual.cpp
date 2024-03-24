#include "Visual.h"

void hideCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // get Handle of the output console
	CONSOLE_CURSOR_INFO cursorInfo; // get the infomation of the cursor
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false; // hide the cursor
	cursorInfo.dwSize = 100; // set the cursor size to a large value
	SetConsoleCursorInfo(console, &cursorInfo); // apply the changes
}

void printLogo() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // get Handle of the output console
    COORD cursorPosition; // store the position of the cursor
	hideCursor();

    // while player not enter any thing from keyboard
    while (true) {
        bool flag = true;
        for (int time = 0; time < 7; ++time) {
            cursorPosition = {0, 0};
            SetConsoleCursorPosition(console, cursorPosition);
            cout << TEXT_COLOR[time % 4];
            cout << GAME_LOGO[time];
            Sleep(200);
            if (_kbhit()) {
                int buffer = _getch();
                flag = false;
                break;
            }
        }
        system("cls");
        if (flag == false)
            break;
    }

	// SetConsoleOutputCP(65001); // set the Font of console to UNICODE

	for (int time = 0; time < 4; ++time)
		for (int color = 0; color < 4; ++color) {
		cout << TEXT_COLOR[color];
		cout << Visual[MAIN_MENU];
		Sleep(100);
		system("cls");
		}
}

void printMainMenu() {
    cout << TEXT_BLACK;
    cout << Visual[MAIN_MENU];
}

void printPlayGame() {
    cout << TEXT_BLACK;
    cout << Visual[PLAY_GAME];
}

void printGameMode() {
    cout << TEXT_BLACK;
    cout << Visual[GAME_MODE];
}

void printLoadGame() {
	cout << TEXT_BLACK;
	cout << Visual[LOAD_GAME];
}

void printLeaderboard() {
    cout << TEXT_BLACK;
	cout << 
	R"(					
                                                    THESE ARE THE TOP 5 PLAYERS WITH HIGHEST SCORE
							
                                                            PRESS ANY KEY TO GO BACK !
	)";
    cout << Visual[LEADERBOARD];
}

void printHelp() {
    cout << TEXT_BLACK;
    // cout << Visual[HELP];
}