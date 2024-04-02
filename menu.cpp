#include "menu.h"

void MAIN_MENU_CONTROL() {
    cout << TEXT_BLACK;
    printMainMenu();
    playSound(MENU);

    printAtCursor(arrow, ARROW_POS_FIRST_BLOCK[MAIN_MENU]); // set arrow point to first block (default)

    while (true) {
        int input = getInputKey();

        removeArrow();

        // check user's input
        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            playSound(CHOOSE);
            // determine which block is chosen by player
            int posBlock = (currentCursor.Y - ARROW_POS_FIRST_BLOCK[MAIN_MENU].Y) / distanceBlock[MAIN_MENU];
            COORD preCursor; // store the previous coordinate of cursor

            switch (posBlock) {
                case 0: // PLAY_GAME
                    PLAY_GAME_CONTROL();

                    // Return MAIN_MENU after escape PLAY_GAME
                    printMainMenu();
                    // Set up the cursor in MAIN_MENU - block PLAY_GAME
                    preCursor.X = ARROW_POS_FIRST_BLOCK[MAIN_MENU].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[MAIN_MENU].Y;
                    printAtCursor(arrow, preCursor);
                    break;

                case 1: // LEADERBOARD
                    LEADERBOARD_CONTROL();

                    // Return MAIN_MENU after escape LEADERBOARD
                    printMainMenu();
                    // Set up the cursor in MAIN_MENU - BLOCK LEADERBOARD
                    preCursor.X = ARROW_POS_FIRST_BLOCK[MAIN_MENU].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[MAIN_MENU].Y + distanceBlock[MAIN_MENU];
                    printAtCursor(arrow, preCursor);
                    break;

                case 2: // HELP
                    HELP_CONTROL();

                    // Return MAIN_MENU after escape HELP
                    printMainMenu();
                    // Set up the cursor in MAIN_MENU - BLOCK HELP
                    preCursor.X = ARROW_POS_FIRST_BLOCK[MAIN_MENU].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[MAIN_MENU].Y + 2 * distanceBlock[MAIN_MENU];
                    printAtCursor(arrow, preCursor);
                    break;

                default: // EXIT
                    return;
            }
        }
        // move the Cursor and print newArrow
        else
            Visual_moveArrow(MAIN_MENU, input);
    }
}

void PLAY_GAME_CONTROL() {
    printPlayGame();

    printAtCursor(arrow, ARROW_POS_FIRST_BLOCK[PLAY_GAME]); // set arrow point to first block (default)

    while (true) {
        int input = getInputKey();
        
        removeArrow();

        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            playSound(CHOOSE);
            // determine which block is chosen by player
            int posBlock = (currentCursor.Y - ARROW_POS_FIRST_BLOCK[PLAY_GAME].Y) / distanceBlock[PLAY_GAME];
            COORD preCursor; // store the previous coordinate of cursor

            switch (posBlock) {
                case 0: // NEW GAME --> choose the GAME_MODE (EASY -> MEDIUM --> HARD)
                    GAME_MODE_CONTROL();

                    // return PLAY_GAME after escape GAME_MODE
                    printPlayGame();
                    // Set up the cursor in PLAY_GAME - block NEW_GAME
                    preCursor.X = ARROW_POS_FIRST_BLOCK[PLAY_GAME].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[PLAY_GAME].Y;
                    printAtCursor(arrow, preCursor);
                    break;
                
                case 1: // LOAD GAME --> choose to load the game have saved before
                    LOAD_GAME_CONTROL();

                    // return PLAY_GAME after escape LOAD_GAME
                    printPlayGame();
                     // Set up the cursor in PLAY_GAME - block LOAD_GAME
                    preCursor.X = ARROW_POS_FIRST_BLOCK[PLAY_GAME].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[PLAY_GAME].Y + distanceBlock[PLAY_GAME];
                    printAtCursor(arrow, preCursor);
                    break;

                default: // GO BACK
                    return;
            }
        }
        // move the Cursor and print newArrow
        else
            Visual_moveArrow(PLAY_GAME, input);
    }
}

void GAME_MODE_CONTROL() {
    printGameMode();

    printAtCursor(arrow, ARROW_POS_FIRST_BLOCK[GAME_MODE]); // set arrow point to first block (default)

    while (true) {
        int input = getInputKey();
        
        removeArrow();

        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            playSound(CHOOSE);
            // determine which block is chosen by player
            int posBlock = (currentCursor.Y - ARROW_POS_FIRST_BLOCK[GAME_MODE].Y) / distanceBlock[GAME_MODE];
            COORD preCursor; // store the previous coordinate of cursor

            switch (posBlock) {
                case 0: // EASY
                {
                    string playerName = USERNAME_CONTROL();
                    //game start
                        
                    //

                    // return GAME_MODE after escape USERNAME
                    printGameMode();
                    // Set up the cursor in PLAY_GAME - block EASY
                    preCursor.X = ARROW_POS_FIRST_BLOCK[GAME_MODE].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[GAME_MODE].Y;
                    printAtCursor(arrow, preCursor);
                    break;
                }
                case 1: // MEDIUM
                {
                    string playerName = USERNAME_CONTROL(); //transfer of control bypasses initialization of: variable "playerName" (declared at line 167) ???

                    // return GAME_MODE after escape USERNAME
                    printGameMode();
                    // Set up the cursor in PLAY_GAME - block MEDIUM
                    preCursor.X = ARROW_POS_FIRST_BLOCK[GAME_MODE].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[GAME_MODE].Y + distanceBlock[GAME_MODE];
                    printAtCursor(arrow, preCursor);
                    break;
                }
                    
                case 2: // HARD
                {
                    string playerName = USERNAME_CONTROL();

                    // return GAME_MODE after escape USERNAME
                    cout << Visual[GAME_MODE];
                    // Set up the cursor in PLAY_GAME - block HARD
                    preCursor.X = ARROW_POS_FIRST_BLOCK[GAME_MODE].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[GAME_MODE].Y + 2 * distanceBlock[GAME_MODE];
                    printAtCursor(arrow, preCursor);
                    break;
                }
                default: // GO BACK
                    return;
            }
        }
        // move the Cursor and print newArrow
        else 
            Visual_moveArrow(GAME_MODE, input);
    }
}

void LOAD_GAME_CONTROL() {
    printLoadGame();

    printAtCursor(arrow, ARROW_POS_FIRST_BLOCK[LOAD_GAME]); // set arrow point to first block (default)
 
    while (true) {
        int input = getInputKey();
        
        removeArrow();

        if (input == ESC) {
            system("cls");
            break;
        }
        else if (input == ENTER) {
            system("cls");
            playSound(CHOOSE);
            int posBlock = (currentCursor.Y - ARROW_POS_FIRST_BLOCK[LOAD_GAME].Y) / distanceBlock[LOAD_GAME];
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

        fin.open(saveFilePath[difficulty].c_str());
        
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
            currentCursor.X = column_Leaderboard[Score];
            printAtCursor(buffer, currentCursor);

            getline(fin, buffer, ';');
            currentCursor.X = column_Leaderboard[Time];
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
    // get console and some cursor information
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD currentCursor = ARROW_POS_FIRST_BLOCK[USERNAME];
    COORD warningBlock = {29, 15};

    printUsername();

    string User = ""; // stored the USERNAME

    SetConsoleCursorPosition(console, currentCursor);
    showCursor();

    // get user input and check valid
    while (true) {
        getline(cin, User, '\n');

        // else if (input == ';') 
        //         continue;
        
        // Check valid and warning
        if (User.length() < 5) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "THE LENGTH OF USERNAME IS LESS THAN 5 CHARACTERS !!!";

            // wait for user to press any key to redo (or ESC)
            while (!_kbhit())
                continue;
        }
        if (User.length() > 30) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "THE LENGTH OF USERNAME IS OVER THAN 30 CHARACTERS !!!";

            // wait for user to press any key to redo (or ESC)
            while (!_kbhit())
                continue;
        }
        if (User.find(';') != string::npos) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "INVALID CHARACTER FOUND !!!";

            // wait for user to press any key to redo (or ESC)
            while (!_kbhit())
                continue;
        }
        cout << TEXT_BLACK;
        break;
    }

    hideCursor();

    system("cls");

    // start game

    return User;
}