#include "menu.h"

void Visual_moveArrow(int visual, int input) {
    switch (input) {
        case ESC:
            return;
        case UP:
            if (currentCursor.Y != FIRST_BLOCK[MAIN_MENU].Y) // check if cursor is at the first block
                currentCursor.Y -= distanceY[visual]; // move cursor UP
            break;
        case DOWN:
            if (currentCursor.Y != FIRST_BLOCK[MAIN_MENU].Y + (numBlock[visual] - 1) * distanceY[visual]) // check if cursor is at the last block
                currentCursor.Y += distanceY[visual]; // move cursor DOWN
            break;
        default:
            break;
    }
	SetConsoleCursorPosition(console, currentCursor); // Update new position of cursor 
    cout << arrow;
}

void MAIN_MENU_CONTROL() {
    printMainMenu();

    printAtCursor(arrow, FIRST_BLOCK[MAIN_MENU]);

    while (true) {
        int input = getKeyboardInput();

        removeArrow();

        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            // determine which block is chosen by player
            int posBlock = (currentCursor.Y - FIRST_BLOCK[MAIN_MENU].Y) / distanceY[MAIN_MENU];
            COORD preCursor; // store the previous coordinate of cursor
            switch (posBlock) {
                case 0: // PLAY_GAME
                    PLAY_GAME_CONTROL();

                    // Return MAIN_MENU after escape PLAY_GAME
                    cout << Visual[MAIN_MENU];
                    // Set up the cursor in MAIN_MENU
                    preCursor.X = FIRST_BLOCK[MAIN_MENU].X;
                    preCursor.Y = FIRST_BLOCK[MAIN_MENU].Y;
                    printAtCursor(arrow, preCursor);
                    break;
                case 1: // LEADERBOARD
                    LEADERBOARD_CONTROL();

                    // Return MAIN_MENU after escape LEADERBOARD
                    cout << Visual[MAIN_MENU];
                    // Set up the cursor in MAIN_MENU
                    preCursor.X = FIRST_BLOCK[MAIN_MENU].X;
                    preCursor.Y = FIRST_BLOCK[MAIN_MENU].Y + distanceY[MAIN_MENU];
                    printAtCursor(arrow, preCursor);
                    break;
                case 2: // HELP
                    HELP_CONTROL();

                    // Return MAIN_MENU after escape HELP
                    cout << Visual[MAIN_MENU];
                    // Set up the cursor in MAIN_MENU
                    preCursor.X = FIRST_BLOCK[MAIN_MENU].X;
                    preCursor.Y = FIRST_BLOCK[MAIN_MENU].Y + 2 * distanceY[MAIN_MENU];
                    printAtCursor(arrow, preCursor);
                    break;
                default: // EXIT
                    return;
            }
        }
        // if input is UP or DOWN, move the Cursor and print newArrow
        else
            Visual_moveArrow(MAIN_MENU, input);
    }
}

void PLAY_GAME_CONTROL() {
    printPlayGame();

    printAtCursor(arrow, FIRST_BLOCK[PLAY_GAME]);

    while (true) {
        int input = getKeyboardInput();
        
        removeArrow();

        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            // determine which block is chosen by player
            int posBlock = (currentCursor.Y - FIRST_BLOCK[PLAY_GAME].Y) / distanceY[PLAY_GAME];
            COORD preCursor; // store the previous coordinate of cursor
            switch (posBlock) {
                case 0: // NEW GAME --> choose the GAME_MODE (EASY -> MEDIUM --> HARD)
                    GAME_MODE_CONTROL();

                    // return PLAY_GAME after escape GAME_MODE
                    cout << Visual[PLAY_GAME];
                    // Set up the cursor in PLAY_GAME
                    preCursor.X = FIRST_BLOCK[PLAY_GAME].X;
                    preCursor.Y = FIRST_BLOCK[PLAY_GAME].Y;
                    printAtCursor(arrow, preCursor);
                    break;
                
                case 1: // LOAD GAME --> choose to load the game have saved before
                    LOAD_GAME_CONTROL();

                    // return PLAY_GAME after escape LOAD_GAME
                    cout << Visual[PLAY_GAME];
                     // Set up the cursor in PLAY_GAME
                    preCursor.X = FIRST_BLOCK[PLAY_GAME].X;
                    preCursor.Y = FIRST_BLOCK[PLAY_GAME].Y + distanceY[PLAY_GAME];
                    printAtCursor(arrow, preCursor);
                    break;

                default: // GO BACK
                    return;
            }
        }
        // if input is UP or DOWN, move the Cursor and print newArrow
        else
            Visual_moveArrow(PLAY_GAME, input);
    }
}

void GAME_MODE_CONTROL() {
    printGameMode();

    printAtCursor(arrow, FIRST_BLOCK[GAME_MODE]);

    while (true) {
        int input = getKeyboardInput();
        
        removeArrow();

        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            // determine which block is chosen by player
            int posBlock = (currentCursor.Y - FIRST_BLOCK[GAME_MODE].Y) / distanceY[GAME_MODE];
            COORD preCursor; // store the previous coordinate of cursor
            switch (posBlock) {
                case 0: // EASY
                    USERNAME_CONTROL();

                    // return GAME_MODE after escape USERNAME
                    cout << Visual[GAME_MODE];
                    // Set up the cursor in PLAY_GAME
                    preCursor.X = FIRST_BLOCK[GAME_MODE].X;
                    preCursor.Y = FIRST_BLOCK[GAME_MODE].Y;
                    printAtCursor(arrow, preCursor);
                    break;
                case 1: // MEDIUM
                    USERNAME_CONTROL();

                    // return GAME_MODE after escape USERNAME
                    cout << Visual[GAME_MODE];
                    // Set up the cursor in PLAY_GAME
                    preCursor.X = FIRST_BLOCK[GAME_MODE].X;
                    preCursor.Y = FIRST_BLOCK[GAME_MODE].Y + distanceY[GAME_MODE];
                    printAtCursor(arrow, preCursor);
                    break;
                case 2: // HARD
                    USERNAME_CONTROL();

                    // return GAME_MODE after escape USERNAME
                    cout << Visual[GAME_MODE];
                    // Set up the cursor in PLAY_GAME
                    preCursor.X = FIRST_BLOCK[GAME_MODE].X;
                    preCursor.Y = FIRST_BLOCK[GAME_MODE].Y + 2 * distanceY[GAME_MODE];
                    printAtCursor(arrow, preCursor);
                    break;
                default: // GO BACK
                    return;
            }
        }
        // if input is UP or DOWN, move the Cursor and print newArrow
        else 
            Visual_moveArrow(GAME_MODE, input);
    }
}

void LOAD_GAME_CONTROL() {
    printLoadGame();

    printAtCursor(arrow, FIRST_BLOCK[LOAD_GAME]);

    while (true) {
        int input = getKeyboardInput();
        
        removeArrow();

        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            int posBlock = (currentCursor.Y - FIRST_BLOCK[LOAD_GAME].Y) / distanceY[LOAD_GAME];
            switch (posBlock) {
                case 0: // SAVE FILE 1

                    return;
                    // break;
                case 1: // SAVE FILE 2

                    return;
                    // break;
                case 2: // SAVE FILE 3

                    return;
                    // break;
                default: // GO BACK
                    return;
            }
        }
        // if input is UP or DOWN, move the Cursor and print newArrow
        else
            Visual_moveArrow(LOAD_GAME, input);
    }
}

void LEADERBOARD_CONTROL() {
    printLeaderboard();

    ifstream fin;

    // print the LEADER_BOARD from easy -> medium -> hard
    for (int difficulty = easy; difficulty <= hard; ++difficulty) {
        currentCursor.Y = row_Leaderboard[difficulty];

        fin.open(fileName[difficulty].c_str());
        
        string buffer;

        if (!fin.is_open()) {
            system("cls");
            return;
        }

        // read information form file and print to console
        while (getline(fin, buffer, ';')) {
            currentCursor.X = column_Leaderboard[Username];
            printAtCursor(buffer, currentCursor);

            getline(fin, buffer, ';');
            currentCursor.X = column_Leaderboard[Time];
            printAtCursor(buffer, currentCursor);

            getline(fin, buffer, ';');
            currentCursor.X = column_Leaderboard[Score];
            printAtCursor(buffer, currentCursor);

            getline(fin, buffer);
            currentCursor.X = column_Leaderboard[Date];
            printAtCursor(buffer, currentCursor);

            currentCursor.Y++;
        }

        fin.close();
    }

    // wait for user to press any key to escape
    int buffer = _getch();
    system("cls");
}

void HELP_CONTROL() {
    COORD curCursor = {0, 4};
    SetConsoleCursorPosition(console, curCursor);
    printHelp();

    // wait for user to press any key to escape
    int buffer = _getch();
    system("cls");
}

string USERNAME_CONTROL() {
    printEnterUsername();

    string User = "";
    int numChar = 0;

    currentCursor = {36, 9}; // Coordinate of block USERNAME

    while (true) {
        char input = _getch();

        if (input == KEY_ESC) {
            system("cls");
            return "";
        }
            
        if (isprint(input)) {
            if (numChar > 29)
                continue;
            numChar++;
            SetConsoleCursorPosition(console, currentCursor);
            cout << input;
            User += input;
            currentCursor.X++;
        }
        else if (input == KEY_BACKSPACE) {
            if (numChar == 0)
                continue;
            numChar--;
            currentCursor.X--;
            SetConsoleCursorPosition(console, currentCursor);
            cout << " ";
            User.pop_back();
        }
        else if (input = KEY_ENTER) {
            if (numChar < 5)
                continue;
            
            // game starting
            break;
        }
    }

    return User;
}