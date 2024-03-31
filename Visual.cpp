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


/*
    this function just using some animation to print LEADERBOARD and
    using some "magic numbers" - which is the coordinate of some special position
    or Ascii code of some extra characters
*/
void printLeaderboard() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(437);

    COORD cursor = {8, 0};
    SetConsoleCursorPosition(console, cursor);
    cout << TEXT_COLOR[GREEN];
	cout << 
	R"(					
                                                    THESE ARE THE TOP 5 PLAYERS WITH HIGHEST SCORE
							
                                                            PRESS ANY KEY TO GO BACK !
	)";

    cout << TEXT_BLACK << Visual[LEADERBOARD];

    cursor = {8, 5}; // initialized with the coordinate of upper left corner of board
    SetConsoleCursorPosition(console, cursor);
    int lengthSide = 130;
    int widthSide = 19;

// Animation draw the LEARDBOARD
    // draw borders
    for (int col = 0; col < lengthSide; ++col) {
        if (col == 0)
            cout << char(218);
        else if (col == 21 || col == 27 || col == 68 || col == 84 || col == 100)
            cout << char(194);
        else if (col == lengthSide - 1)
            cout << char(191);
        else
            cout << char(196);
        Sleep(1);
    }
    cursor.X += lengthSide - 1;
    cursor.Y ++;
    SetConsoleCursorPosition(console, cursor);
    
    for (int row = 0; row < widthSide; ++row) {
        if (row == 1 || row == 7 || row == 13)
            cout << char(180);
        else
            cout << char(179);
        cursor.Y++;
        SetConsoleCursorPosition(console, cursor);
        Sleep(1);
    }

    for (int col = lengthSide - 1; col >= 0; --col) {
        if (col == 0)
            cout << char(192);
        else if (col == 21 || col == 27 || col == 68 || col == 84 || col == 100)
            cout << char(193);
        else if (col == lengthSide - 1)
            cout << char(217);
        else
            cout << char(196);

        cursor.X--;
        SetConsoleCursorPosition(console, cursor);
        Sleep(1);
    }

    cursor.X++;
    for (int row = widthSide - 1; row >= 0; --row) {
        cursor.Y--;
        SetConsoleCursorPosition(console, cursor);

        if (row == 1 || row == 7 || row == 13)
            cout << char(195);
        else
            cout << char(179);
        
        Sleep(1);
    }

// print the entire of board
    int specialCol[] = {21, 27, 68, 84, 100};
    int specialRow[] = {2, 8, 14};

    for (int row = 0; row < 3; ++row) {
        short newRow = 5 + specialRow[row];
        cursor = {9, newRow};
        SetConsoleCursorPosition(console, cursor);
        string content;
        content.append(lengthSide - 2, char(196));
        cout << content;
    }

    for (int col = 0; col < 5; ++col) {
        short newCol = 8 + specialCol[col];
        cursor = {newCol, 6};
        SetConsoleCursorPosition(console, cursor);
        for (int row = 0; row < widthSide; ++row) {
            if (row == 1 || row == 7 || row == 13)
                cout << char(197);
            else
                cout << char(179);
            cursor.Y++;
            SetConsoleCursorPosition(console, cursor);
        }
    }

    cout << TEXT_BLACK;
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


/*
    this function use to print the frame of block Visual (MAIN_MENU, ...)
    and using some "magic numbers" - which is the Ascii code of some extra characters
*/
void printFrameBlock(int Visual) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(437);
    for (int numblock = 0; numblock < numBlock[Visual]; ++numblock) {
        COORD currentCursor = FIRST_BLOCK[Visual];
        currentCursor.Y += numblock * distanceBlock[Visual];

        SetConsoleCursorPosition(console, currentCursor);
        string sideFrame;
        sideFrame.assign(WidthBlock[Visual], char(205));
        cout << char(201);
        cout << sideFrame;
        cout << char(187);

        currentCursor.Y++;
        SetConsoleCursorPosition(console, currentCursor);
        cout << char(186);

        currentCursor.X += WidthBlock[Visual] + 1;
        SetConsoleCursorPosition(console, currentCursor);
        cout << char(186);

        currentCursor.X -= WidthBlock[Visual] + 1;
        currentCursor.Y++;
        SetConsoleCursorPosition(console, currentCursor);
        cout << char(200);
        cout << sideFrame;
        cout << char(188);
    }
    SetConsoleOutputCP(65001);
}