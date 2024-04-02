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
            int posBlock = (currentCursor.Y - ARROW_POS_FIRST_BLOCK[MAIN_MENU].Y) / distanceBlock;
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
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[MAIN_MENU].Y + distanceBlock;
                    printAtCursor(arrow, preCursor);
                    break;

                case 2: // HELP
                    HELP_CONTROL();

                    // Return MAIN_MENU after escape HELP
                    printMainMenu();
                    // Set up the cursor in MAIN_MENU - BLOCK HELP
                    preCursor.X = ARROW_POS_FIRST_BLOCK[MAIN_MENU].X;
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[MAIN_MENU].Y + 2 * distanceBlock;
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
            int posBlock = (currentCursor.Y - ARROW_POS_FIRST_BLOCK[PLAY_GAME].Y) / distanceBlock;
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
                    preCursor.Y = ARROW_POS_FIRST_BLOCK[PLAY_GAME].Y + distanceBlock;
                    printAtCursor(arrow, preCursor);
                    break;

                case 2: // EXTRA
                    return;

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
            int posBlock = (currentCursor.Y - ARROW_POS_FIRST_BLOCK[GAME_MODE].Y) / distanceBlock;
            COORD preCursor; // store the previous coordinate of cursor

            if (posBlock <= HARD) {
                string username, password;
                if (USERNAME_CONTROL(username, password)) {
                    // cerr << "account valid\n";
                    SetConsoleOutputCP(437);
                    playSound(MENU, true);
                    game newGame(posBlock);
                    newGame.player.username = username;
                    newGame.player.password = encrypt(password);
                    newGame.startGame();
                }
                playSound(MENU);
                // return GAME_MODE after escape USERNAME
                hideCursor();
                printGameMode();
                // Set up the cursor in PLAY_GAME - block EASY
                preCursor.X = ARROW_POS_FIRST_BLOCK[GAME_MODE].X;
                preCursor.Y = ARROW_POS_FIRST_BLOCK[GAME_MODE].Y + distanceBlock * posBlock;
                printAtCursor(arrow, preCursor);
            }
            else {
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
            int posBlock = (currentCursor.Y - ARROW_POS_FIRST_BLOCK[LOAD_GAME].Y) / distanceBlock;
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
    // coordinate of first row of each difficulty in LEADERBOARD
    const int row_Leaderboard[3] = {
        8, // easy
        14, // medium
        20 // hard
    };

    // column of information in LEADERBOARD
    const int column_Leaderboard[4] {
        41, // Username
        82, // Time
        99, // Score
        113 // Date
    };
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

bool USERNAME_CONTROL(string& username, string& password) {
    // get console and some cursor information
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    
    COORD warningBlock = {50, 20};

    username = "";
    password = "";

    // get user input and check valid
    while (true) {
        COORD currentCursor = ARROW_POS_FIRST_BLOCK[USERNAME];
        system("cls");
        printUsername();
        SetConsoleCursorPosition(console, currentCursor);
        showCursor();

        getline(cin, username, '\n');
        
        // Check valid USERNAME and warning
        if (username.length() < 5) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "THE LENGTH OF USERNAME IS LESS THAN 5 CHARACTERS !!!";

            // wait for user to press any key to redo (or ESC)
            int buffer = _getch();

            if (buffer == KEY_ESC) {
                clearScreen();
                return false;
            }
                
            continue;
        }
        if (username.length() > 30) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "THE LENGTH OF USERNAME IS OVER THAN 30 CHARACTERS !!!";

            // wait for user to press any key to redo (or ESC)
            int buffer = _getch();

            if (buffer == KEY_ESC) {
                clearScreen();
                return false;
            }

            continue;
        }
        if (username.find(';') != string::npos) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "INVALID CHARACTER ';' FOUND !!!";

            // wait for user to press any key to redo (or ESC)
            int buffer = _getch();

            if (buffer == KEY_ESC) {
                clearScreen();
                return false;
            }

            continue;
        }

        // if USERNAME is valid, move to PASSWORD
        currentCursor.Y += 3;
        SetConsoleCursorPosition(console, currentCursor);

        getline(cin, password);

        // check valid PASSWORD
        if (password.length() < 5) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "THE LENGTH OF PASSWORD IS LESS THAN 5 CHARACTERS !!!";

            // wait for user to press any key to redo (or ESC)
            int buffer = _getch();

            if (buffer == KEY_ESC) {
                clearScreen();
                return false;
            }
                
            continue;
        }
        if (password.length() > 30) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "THE LENGTH OF PASSWORD IS OVER THAN 30 CHARACTERS !!!";

            // wait for user to press any key to redo (or ESC)
            int buffer = _getch();

            if (buffer == KEY_ESC) {
                clearScreen();
                return false;
            }

            continue;
        }
        bool isValidPassword = true;
        for (char ch : password)
            if (!isalnum(ch)) {
                isValidPassword = false;
                break;
            }
        if (!isValidPassword) {
            SetConsoleCursorPosition(console, warningBlock);
            cout << TEXT_COLOR[RED];
            cout << "INVALID PASSWORD!!!";

            // wait for user to press any key to redo (or ESC)
            int buffer = _getch();

            if (buffer == KEY_ESC) {
                clearScreen();
                return false;
            }

            continue;
        }

        cout << TEXT_BLACK;
        break;
    }

    hideCursor();
    system("cls");

    // start game

    return true;
}