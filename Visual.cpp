#include "Visual.h"

void Visual_moveArrow(int visual, int input) {
    switch (input) {
        case ESC:
            return;
        case UP:
            if (currentCursor.Y != FIRST_BLOCK[MAIN_MENU].Y) // check if cursor is at the first block
                currentCursor.Y -= distanceBlock[visual]; // move cursor UP
            break;
        case DOWN:
            if (currentCursor.Y != FIRST_BLOCK[MAIN_MENU].Y + (numBlock[visual] - 1) * distanceBlock[visual]) // check if cursor is at the last block
                currentCursor.Y += distanceBlock[visual]; // move cursor DOWN
            break;
        default:
            break;
    }
    // Update new position of cursor and print arrow
	SetConsoleCursorPosition(console, currentCursor); 
    cout << arrow;
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

void printLogo() {
    SetConsoleOutputCP(65001); // set the console code page to print UTF-8 characters

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // get Handle of the output console
    COORD cursorPosition; // store the position of the cursor
	hideCursor();

    // while player not enter any thing from keyboard
    while (true) {
        bool flag = true; // check if user input any thing
        // print Animation
        for (int time = 0; time < 7; ++time) {
            cursorPosition = {0, 0};
            SetConsoleCursorPosition(console, cursorPosition);
            cout << TEXT_COLOR[time % 4];
            cout << GAME_LOGO[time];
            Sleep(200);
            // check if user input any thing
            if (_kbhit()) {
                int buffer = _getch();
                flag = false;
                break;
            }
        }
        system("cls"); // clear the screen
        if (flag == false)
            break;
    }

    // Animation
	for (int time = 0; time < 4; ++time)
		for (int color = 0; color < 4; ++color) {
		cout << TEXT_COLOR[color];
		printMainMenu();
		Sleep(100);
		system("cls");
		}
}

void printMainMenu() {
    cout << Visual[MAIN_MENU];
    printFrameBlock(MAIN_MENU);
}

void printPlayGame() {
    cout << TEXT_BLACK;
    cout << Visual[PLAY_GAME];
    printFrameBlock(PLAY_GAME);
}

void printGameMode() {
    cout << TEXT_BLACK;
    cout << Visual[GAME_MODE];
    printFrameBlock(GAME_MODE);
}

void printLoadGame() {
	cout << TEXT_BLACK;
	cout << Visual[LOAD_GAME];
    printFrameBlock(LOAD_GAME);
}

void printLeaderboard() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(437);
    cout << TEXT_BLACK;
	cout << 
	R"(					
                                                    THESE ARE THE TOP 5 PLAYERS WITH HIGHEST SCORE
							
                                                            PRESS ANY KEY TO GO BACK !
	)";
    cout << Visual[LEADERBOARD];

    int lengthSide = 128;
    string firstSideFrame, middleSideFrame, lastSideFrame, contentLine;

    firstSideFrame = firstSideFrame + char(201);
    firstSideFrame.append(lengthSide, char(205));
    firstSideFrame = firstSideFrame + char(187);
    
    middleSideFrame = middleSideFrame + char(204);
    middleSideFrame.append(lengthSide, char(205));
    middleSideFrame = middleSideFrame + char(185);

    lastSideFrame = lastSideFrame + char(200);
    lastSideFrame.append(lengthSide, char(205));
    lastSideFrame = lastSideFrame + char(188);

    COORD upperLeftCorner = {8, 5};
    SetConsoleCursorPosition(console, upperLeftCorner);

    cout << firstSideFrame;

    upperLeftCorner.Y += 2;
    SetConsoleCursorPosition(console, upperLeftCorner);
    cout << middleSideFrame;

    SetConsoleOutputCP(65001);
}

void printHelp() {
    cout << TEXT_BLACK;
    cout << Visual[HELP];
}

void printUsername() {
    cout << TEXT_BLACK;
    cout << Visual[USERNAME];
    printFrameBlock(USERNAME);
}

void printFrameBlock(int Visual) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(437);
    for (int numblock = 0; numblock < numBlock[Visual]; ++numblock) {
        COORD currentCursor = FIRST_BLOCK[Visual];
        currentCursor.Y += numblock * distanceBlock[Visual];

        SetConsoleCursorPosition(console, currentCursor);
        string sideFrame;
        sideFrame.assign(lengthBlock[Visual], char(205));
        cout << char(201);
        cout << sideFrame;
        cout << char(187);

        currentCursor.Y++;
        SetConsoleCursorPosition(console, currentCursor);
        cout << char(186);

        currentCursor.X += lengthBlock[Visual] + 1;
        SetConsoleCursorPosition(console, currentCursor);
        cout << char(186);

        currentCursor.X -= lengthBlock[Visual] + 1;
        currentCursor.Y++;
        SetConsoleCursorPosition(console, currentCursor);
        cout << char(200);
        cout << sideFrame;
        cout << char(188);
    }
    SetConsoleOutputCP(65001);
}