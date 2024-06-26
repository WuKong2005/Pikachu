#include "game.h"

// type of magic move: 0 - 
bool randomMagicMove = 0;

game::game() {
    upperLeftCorner = {7, 4};
    currentPos = {1, 1};
    currentSelect = {0, 0};
    timeUsed = numLeft = score = useHint = useMagicMatching = useHiddenCell = applyMagicMatching = applyHiddenCell = isPlaying = 0;
    diff = -1;
    tempCell = make_pair(make_pair(0, 0), '$');
    background = NULL;
}

game::~game() {
    if (!background)
        delete [] background;
}

game::game(int difficult) {
    map.~board();
    new (&map) board(difficult);
    map.initializeBoard();

    currentSelect = {0, 0};
    timeUsed = 0;
    numLeft = map.ROW * map.COL;
    diff = difficult;
    score = 0;
    useHint = 3;
    int total = diff * 2 + 1;
    randomMagicMove = rand() % 2;
    useMagicMatching = total * randomMagicMove;
    useHiddenCell = total - useMagicMatching;
    isPlaying = true;
    applyMagicMatching = applyHiddenCell = false;
    tempCell = make_pair(make_pair(0, 0), '$');
    
    upperLeftCorner.X = (short)map.boardPos[difficult].first;
    upperLeftCorner.Y = (short)map.boardPos[difficult].second;
    currentPos = {1, 1};
    
    getBackground();
}

int game::timeDuration() {
    return (int)difftime(time(0), timeStart);
}

int game::getCurrentTime() {
    return limTime[diff] - (timeUsed + timeDuration());
}

void game::drawInterface() {
    drawBoard(); 

    //print information in game at position about 4 (or 6) spaces away from the board frame
    printInfoInGame((upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6),
                     upperLeftCorner.Y);

    // print the help menu in game at position about 4 (or 6) spaces away from board frame 
    // and lower than information in game 19 spaces
    printHelpInGame((upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6),
                     upperLeftCorner.Y + 19);

    // print user information
    setCursor(map.boardPos[diff].first, 1);
    cout << TEXT_COLOR[YELLOW] << "USERNAME: " << player.username;
    setCursor(45 + map.boardPos[diff].first, 1);
    cout << "DIFFICULTY: ";
    if (diff == EASY)
        cout << "EASY";
    else if (diff == MEDIUM)
        cout << "MEDIUM";
    else
        cout << "HARD";
    setCursor(90 + map.boardPos[diff].first, 1);
    cout << "TIME REMAIN: ";

    renderScore();
    renderHint();
    renderMagic();
    renderTime();

    cout << TEXT_BLACK;
}

void game::drawBoard() {
    SetConsoleCursorPosition(console, upperLeftCorner);

// Animation draw the frame of board
    // size of the outline of board
    int WidthBorder = BUFFER_WIDTH_CELL * 2 + (WIDTH_CELL - 1) * sizeCOL[diff] + 1;
    int HeightBorder = BUFFER_HEIGHT_CELL * 2 + (HEIGHT_CELL -1) * sizeROW[diff] + 1;

    // print the top outline's side (left -> right)
    for (int col = 0; col < WidthBorder; ++col) {
        if (col == 0)
            cout << char(frame[UPPER_LEFT]);
        else if (col == WidthBorder - 1)
            cout << char(frame[UPPER_RIGHT]);
        else
            cout << char(205);
        Sleep(1);
    }
    
    // print the right outline's side (up -> down)
    setCursor(upperLeftCorner.X + WidthBorder - 1, upperLeftCorner.Y + 1);
    for (int row = 0; row < HeightBorder - 2; ++row) {
        cout << char(186);
        setCursor(upperLeftCorner.X + WidthBorder - 1, upperLeftCorner.Y + 2 + row);
        Sleep(1);
    }

    // print the bottom outline's side (right -> left)
    for (int col = WidthBorder - 1; col >= 0; --col) {
        if (col == 0)
            cout << char(frame[LOWER_LEFT]);
        else if (col == WidthBorder - 1)
            cout << char(frame[LOWER_RIGHT]);
        else
            cout << char(205);

        setCursor(upperLeftCorner.X + col - 1, upperLeftCorner.Y + HeightBorder - 1);
        Sleep(1);
    }

    // print the left outline's side (down -> up)
    for (int row = HeightBorder - 2; row > 0; --row) {
        setCursor(upperLeftCorner.X, upperLeftCorner.Y + row);
        cout << char(186);
        Sleep(10);
    }

// draw board
    for (int row = 1; row <= map.ROW; ++row) {
        for (int col = 1; col <= map.COL; ++col) {
            if (map.grid[row][col] != '$') {
                drawCell({row, col}, map.grid[row][col]); 
                Sleep(3);
            }
            else {
                removeCell({row, col});
                Sleep(3);
            }
        } 
    }
        
    cout << TEXT_BLACK;
}

void game::drawCell(pair<int, int> cell, char key) {
    // set cursor to position of cell (upper-left corner)
    short posX = upperLeftCorner.X + (cell.second - 1) * (WIDTH_CELL - 1) + BUFFER_WIDTH_CELL;
    short posY = upperLeftCorner.Y + (cell.first - 1) * (HEIGHT_CELL - 1) + BUFFER_HEIGHT_CELL;
    setCursor(posX, posY);

    //store the horizontal side except the corner
    string side;
    side.append(WIDTH_CELL - 2, char(196));
    
    cout << TEXT_COLOR[BRIGHT_BLUE];

    // print top and bottom side
    setCursor(posX + 1, posY);
    cout << side;
    setCursor(posX + 1, posY + HEIGHT_CELL - 1);
    cout << side;

    // print left and right side
    for (int col = 1; col <= HEIGHT_CELL - 2; ++col) {
        setCursor(posX, posY + col);
        cout << char(179);
        setCursor(posX + WIDTH_CELL - 1, posY + col);
        cout << char(179);
    }

    // print key of cell
    setCursor(posX + WIDTH_CELL / 2, posY + HEIGHT_CELL / 2);
    cout << TEXT_COLOR[WHITE] << key;
}

void game::removeCell(pair<int, int> cell) {
    // check valid cell
    if (cell.first < 1 || cell.second < 1 || cell.first > map.ROW || cell.second > map.COL||
        map.grid[cell.first][cell.second] != '$')
        return;

    // set Cursor to coordinate of upperLeftCorner of cell
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (cell.second - 1) * (WIDTH_CELL - 1);
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (cell.first - 1) * (HEIGHT_CELL - 1);

    // check if the 4 cells next to cell is deleted of not 
    bool cellTop, cellBottom, cellLeft, cellRight;
    cellTop = map.grid[cell.first - 1][cell.second] == '$';
    cellBottom = map.grid[cell.first + 1][cell.second] == '$';
    cellLeft = map.grid[cell.first][cell.second - 1] == '$';
    cellRight = map.grid[cell.first][cell.second + 1] == '$';

//Check 4 sides
    // check and delete top side
    if (cellTop) {
        setCursor(posX + 1, posY);
        for (int numChar = 1; numChar < WIDTH_CELL - 1; ++numChar)    
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)]
                              [(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1) + numChar];
    }
    //check and delete bottom side
    if (cellBottom) {
        setCursor(posX + 1, posY + (HEIGHT_CELL - 1));
        for (int numChar = 1; numChar < WIDTH_CELL - 1; ++numChar)
            cout << background[cell.first * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)]
                              [(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1) + numChar];
    }
    //check and delete left side
    if (cellLeft)
        for (int numChar = 1; numChar < HEIGHT_CELL - 1; ++numChar) {
            setCursor(posX, posY + numChar);
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1) + numChar]
                              [(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
        }
    // check and delete right side
    if (cellRight)
        for (int numChar = 1; numChar < HEIGHT_CELL - 1; ++numChar) {
            setCursor(posX + (WIDTH_CELL - 1), posY + numChar);
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1) + numChar]
                              [cell.second * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
        }

// Check 4 corners
    // upper left corner
    if(cellTop && cellLeft && map.grid[cell.first - 1][cell.second - 1] == '$') {
        setCursor(posX, posY);
        cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)]
                          [(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
    }
    // upper right corner
    if (cellTop && cellRight && map.grid[cell.first - 1][cell.second + 1] == '$') {
        setCursor(posX + (WIDTH_CELL - 1), posY);
        cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)]
                          [cell.second * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
    }
    // lower left corner
    if (cellBottom && cellLeft && map.grid[cell.first + 1][cell.second - 1] == '$') {
        setCursor(posX, posY + (HEIGHT_CELL - 1));
        cout << background[cell.first * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)]
                          [(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
    }
    // lower right corner
    if (cellBottom && cellRight && map.grid[cell.first + 1][cell.second + 1] == '$') {
        setCursor(posX + (WIDTH_CELL - 1), posY + (HEIGHT_CELL - 1));
        cout << background[cell.first * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)]
                          [cell.second * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
    }

    cout << TEXT_BLACK;

    unHighlightCell(cell.first, cell.second);
}

void game::drawPath(vector<pair<int, int>> path, bool draw) {
    assert(path.size() >= 2);
    int numCell = path.size();
    
    // draw line between each 2 turning cell
    for (int cell = 0; cell + 1 < numCell; ++cell) {
        drawLine(path[cell], path[cell + 1], draw);
    }
    // vector of 2 consecutive turning cell
    vector<pair<int, int>> vec;
    for (int i = 0; i < numCell - 1; ++i)
        vec.push_back({path[i].first - path[i + 1].first, path[i].second - path[i + 1].second});
    
    // draw the turning point
    for (int i = 0; i < numCell - 2; ++i) {
        if ((vec[i].first > 0 && vec[i + 1].second > 0) || (vec[i].second < 0 && vec[i + 1].first < 0))
            drawTurningPoint(path[i + 1].first, path[i + 1].second, DOWN_LEFT, draw);
        else if ((vec[i].first > 0 && vec[i + 1].second < 0) || (vec[i].second > 0 && vec[i + 1].first < 0))
            drawTurningPoint(path[i + 1].first, path[i + 1].second, DOWN_RIGHT, draw);
        else if ((vec[i].first < 0 && vec[i + 1].second > 0) || (vec[i].second < 0 && vec[i + 1].first > 0))
            drawTurningPoint(path[i + 1].first, path[i + 1].second, UP_LEFT, draw);
        else
            drawTurningPoint(path[i + 1].first, path[i + 1].second, UP_RIGHT, draw);
    }
}

void game::drawLine(pair<int, int> startCell, pair<int, int> endCell, bool draw) {
    if (startCell == endCell)
        return;
    if (startCell.first == endCell.first)
        drawHorizontalLine(startCell.first, startCell.second, endCell.second, draw);
    if (startCell.second == endCell.second)
        drawVerticalLine(startCell.second, startCell.first, endCell.first, draw);
}

void game::drawVerticalLine(int col, int row1, int row2, bool draw) {
    if (row1 > row2)
        swap(row1, row2);
    //store the center coordinates of each cell
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY1 = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row1 - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    short posY2 = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row2 - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;

    cout << (draw ? TEXT_COLOR[BRIGHT_YELLOW] : TEXT_BLACK);
    if (!draw) // delete line --> print background
        while (posY1 < posY2 - 1) {
            posY1++;
            setCursor(posX, posY1);
            cout << background[posY1 - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL) + (BUFFER_HEIGHT_CELL - 1)]
                              [posX - (upperLeftCorner.X + BUFFER_WIDTH_CELL) + (BUFFER_WIDTH_CELL - 1)];
        }
    else  // print line
        while (posY1 < posY2 - 1) {
            posY1++;
            setCursor(posX, posY1);
            cout << char(179);
        }
    cout << TEXT_BLACK;
}

void game::drawHorizontalLine(int row, int col1, int col2, bool draw) {
    if (col1 > col2)
        swap(col1, col2);
    //store the center coordinates of each cell
    short posX1 = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col1 - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posX2 = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col2 - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;

    cout << (draw ? TEXT_COLOR[BRIGHT_YELLOW] : TEXT_BLACK);

    if (!draw)
        while (posX1 < posX2 - 1) {
            posX1++;
            setCursor(posX1, posY);
            cout << background[posY - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL) + (BUFFER_HEIGHT_CELL - 1)]
                              [posX1 - (upperLeftCorner.X + BUFFER_WIDTH_CELL) + (BUFFER_WIDTH_CELL - 1)];
        }
    else
        while (posX1 < posX2 - 1) {
            posX1++;
            setCursor(posX1, posY);
            cout << char(196);
        }
    cout << TEXT_BLACK;
}

void game::drawTurningPoint(int row, int col, int type, bool draw) {
    // set cursor to the center of cell
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    setCursor(posX, posY);

    if (draw) {
        cout << TEXT_COLOR[BRIGHT_YELLOW] << char(turning[type]);
    }
    else {
        cout << TEXT_BLACK;
        cout << background[posY - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL) + (BUFFER_HEIGHT_CELL - 1)]
                          [posX - (upperLeftCorner.X + BUFFER_WIDTH_CELL) + (BUFFER_WIDTH_CELL - 1)];
    }
    cout << TEXT_BLACK;
}

void game::moveCell(int direction) {
    playSound(MOVE);
    // unhighlight old cell
    unHighlightCell(currentPos.first, currentPos.second);
    // go to and highline new cell
    currentPos.first = ((currentPos.first + dx[direction - 1] + map.ROW - 1) % map.ROW) + 1;
    currentPos.second = ((currentPos.second + dy[direction - 1] + map.COL - 1) % map.COL) + 1;
    highlightCell(currentPos.first, currentPos.second, BACKGROUND_COLOR[CYAN]);
}

void game::highlightCell(int row, int col, string color) {
    // set cursor to the coordinate of upper-left corner of cell(row, col)
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + 1;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + 1;
    setCursor(posX, posY);
    cout << color;

    if (map.grid[row][col] != '$') // if Cell isn't deleted 
    {
        for (int rowCell = 1; rowCell <= HEIGHT_CELL - 2; ++rowCell) {
            if (rowCell != HEIGHT_CELL / 2)
                for (int colCell = 1; colCell <= WIDTH_CELL - 2; ++colCell)
                    cout << " ";
            else
                for (int colCell = 1; colCell <= WIDTH_CELL - 2; ++colCell)
                    if (colCell != WIDTH_CELL / 2)
                        cout << " ";
                    else
                        cout << TEXT_COLOR[WHITE] << map.grid[row][col] << color;
            setCursor(upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + 1,
                      upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + 1 + rowCell);
        }
    }
    else // if Cell is deleted --> draw Background
    {
        for (int rowCell = 1; rowCell <= HEIGHT_CELL - 2; ++rowCell) {
            for (int colCell = 1; colCell <= WIDTH_CELL - 2; ++colCell) {
                cout << background[(HEIGHT_CELL - 1) * (row - 1) + (BUFFER_HEIGHT_CELL - 1) + rowCell]
                                  [(WIDTH_CELL - 1) * (col - 1) + (BUFFER_WIDTH_CELL - 1) + colCell];
            }
                
            posY++;
            setCursor(posX, posY);
        }
    }
    cout << BACKGROUND_COLOR[BLACK] << TEXT_BLACK;
}

void game::unHighlightCell(int row, int col) {
    highlightCell(row, col, BACKGROUND_COLOR[BLACK]);
}

void game::select() {
    // does not select deleted cell
    if (map.grid[currentPos.first][currentPos.second] == '$') {
        return;
    }
    playSound(CHOOSE);

    if (currentSelect == make_pair(0, 0)) {
        if (applyHiddenCell) {
            tempCell = make_pair(currentPos, map.getChar(currentPos));
            applyHiddenCell = false;

            map.deleteCell(currentPos);
            removeCell(currentPos);
        }
        else {
            currentSelect = currentPos;
            highlightCell(currentPos.first, currentPos.second, BACKGROUND_COLOR[YELLOW]);
        }
        return;
    }
    if (currentSelect == currentPos) {
        unHighlightCell(currentPos.first, currentPos.second);
        currentSelect = {0, 0};
        return;
    }

    bool success = false;
    if (map.checkMatch(currentSelect, currentPos, applyMagicMatching)) {
        success = true;
        playSound(VALID_MOVE);
        vector<pair<int, int>> path = map.getPath(currentSelect, currentPos);
        drawPath(path, true);
        highlightCell(currentPos.first, currentPos.second, BACKGROUND_COLOR[GREEN]);
        highlightCell(currentSelect.first, currentSelect.second, BACKGROUND_COLOR[GREEN]);
        
        score += path.size() - 1;
        // drawPath(path, true);
        Sleep(100);

        map.deleteCell(currentSelect);
        map.deleteCell(currentPos);
        removeCell(currentPos);
        removeCell(currentSelect);
        drawPath(path, false);

        numLeft -= 2;

        int typeMatch = map.getTypePath(path);
        switch (typeMatch)
        {
            case I_MATCHING:
                renderNotificate("I MATCHING!!!");
                break;
            case L_MATCHING:
                renderNotificate("L MATCHING!!!");
                break;
            case Z_MATCHING:
                renderNotificate("Z MATCHING!!!");
                break;
            case U_MATCHING:
                renderNotificate("U MATCHING!!!");
                break;
            case MAGIC_MATCHING:
                renderNotificate("MAGIC MATCHING!!!");
                break;
            default:
                break;
        }
    }
    else {
        playSound(INVALID_MOVE);
        highlightCell(currentPos.first, currentPos.second, BACKGROUND_COLOR[RED]);
        highlightCell(currentSelect.first, currentSelect.second, BACKGROUND_COLOR[RED]);
        Sleep(100);

        highlightCell(currentPos.first, currentPos.second, BACKGROUND_COLOR[CYAN]);
        unHighlightCell(currentSelect.first, currentSelect.second);

        renderNotificate("WRONG MOVE!!!");
    }

    currentSelect = {0, 0};
    applyMagicMatching = false;
    if (tempCell.second != '$') {
        map.assignCell(tempCell.first, tempCell.second);
        drawCell(tempCell.first, tempCell.second);
        unHighlightCell(tempCell.first.first, tempCell.first.second);
        tempCell = make_pair(make_pair(0, 0), '$');
    }

    if (success && numLeft > 0 && !map.automaticCheck()) {
        renderNotificate("NO VALID MOVE EXIST!!!");
        Sleep(2000);
        map.shuffleBoard();
        clearScreen();
        SetConsoleOutputCP(437);
        drawInterface();
        renderNotificate("AUTO SHUFFLE COMPLETE");
    }
} 

void game::getRespond(pair<int, int> nextSelect) {

}

bool game::moveSuggestion() {
    if (useHint == 0) {
        renderNotificate("NO MORE HINT!!!");
        return false;
    }
    if (applyMagicMatching || applyHiddenCell || ((tempCell.second != '$'))) {
        renderNotificate("HINT NOT ALLOWED!!!");
        return false;
    }

    --useHint;
    score -= 2;
    renderNotificate("HINT!!!");
    renderHint();
    
    assert(map.automaticCheck());
    array<int, 4> suggestion = map.suggestMove();
    pair<int, int> startCell = {suggestion[0], suggestion[1]};
    pair<int, int> endCell = {suggestion[2], suggestion[3]};
    highlightCell(suggestion[0], suggestion[1], BACKGROUND_COLOR[MAGENTA]);
    highlightCell(suggestion[2], suggestion[3], BACKGROUND_COLOR[MAGENTA]);

    return true;
}

bool game::magicMove() {
    assert(useHiddenCell * useMagicMatching == 0);
    if (!useHiddenCell && !useMagicMatching) {
        renderNotificate("NO MORE MAGIC!!!");
        return false;
    }
    
    if (useHiddenCell)
        hiddenCell();
    else
        magicMatch();
    return true;
}

void game::hiddenCell() {
    if (applyHiddenCell || (tempCell.second != '$')) {
        renderNotificate("ALREADY USE!!!");
        return;
    }
    renderNotificate("HIDDEN CELL!!!");
    --useHiddenCell;
    applyHiddenCell = true;
}
void game::magicMatch() {
    if (applyMagicMatching) {
        renderNotificate("ALREADY USE!!!");
        return;
    }
    renderNotificate("MAGIC MATCHING");
    --useMagicMatching;
    applyMagicMatching = true;
}

void game::helpMenu() {
    clearScreen();
    Sleep(1000);
    HELP_CONTROL();
    Sleep(1000);
    SetConsoleOutputCP(437);
    drawInterface();
}

void game::saveScore() {
    assert(numLeft == 0);
    ifstream inp;
    inp.open(saveFilePath[diff].c_str());
    if (!inp.is_open()) {
        return;
    }

    record resultGame(score, timeUsed + timeDuration()); // swap them

    vector<pair<int, string>> record;
    string inputline;
    while(true) {
        getline(inp, inputline, '\n');
        if (inputline.empty()) {
            break;
        }

        int firstPos = inputline.find(';');
        int secondPos = inputline.find(';', firstPos + 1);
        int recordScore = stoi(inputline.substr(firstPos + 1, secondPos - firstPos - 1));
        
        record.emplace_back(recordScore, inputline);
        inputline.clear();
    }
    inp.close();

    pair<int, string> thisGame = make_pair(resultGame.score, player.accountInfo(resultGame));
    bool add = false;
    for (int i = 0; i < (int)record.size(); i++) {
        if (thisGame.first > record[i].first) {
            record.insert(record.begin() + i, thisGame);
            add = true;
            break;
        }
    }
    if (!add)
        record.push_back(thisGame);
        
    if (record.size() > MAX_PLAYER)
        record.pop_back();
    
    ofstream out;
    out.open(saveFilePath[diff].c_str());
    if (!out.is_open()) {
        return;
    }

    for (auto it: record) {
        out << it.second << '\n';
    }

    out.close();
}
void game::saveGame() {
    renderNotificate("SAVE AT SLOT 0, 1 OR 2?");
    int option = getch();
    if (option - (int)'0' >= 0 && option - (int)'0' < 3) {
        saveGame(option - (int)'0');
    }
    else {
        renderNotificate("INVALID SLOT INDEX");
    }
}

void game::saveGame(int slot) {
    ofstream out;
    out.open("record/savegame" + to_string(slot) + ".txt");
    if (!out.is_open())
        return;
    
    map.importBoard();
    ifstream inp;
    inp.open("record/board.txt");

    out << player.username << ';' << player.password << ';' << score << ';' << timeUsed + timeDuration() << ';' << useHint << ';' << useMagicMatching << ';' << useHiddenCell << ';';
    string val;
    while(true) {
        inp >> val;
        if (val.empty()) 
            break;
        out << val << ' ';
        val.clear();
    }

    inp.close();
    out.close();

    renderNotificate("GAME SAVED!!!");
}

bool game::verifySaveFile(int slot) {
    ifstream inp;
    inp.open("record/savegame" + to_string(slot) + ".txt");
    if (!inp.is_open())
        return false;
    
    string __score, __timeUsed, __useHint, __useMagicMatching, __useHiddenCell, infoBoard;
    int index = 0;
    string token;

    while(true) {
        getline(inp, token, ';');
        if (token.empty()) 
            break;
        
        switch (index)
        {
            case 0:
                player.username = token;
                break;
            case 1:
                player.password = token;
                break;
            case 2:
                __score = token;
                break;
            case 3:
                __timeUsed = token;
                break;
            case 4:
                __useHint = token;
                break;
            case 5:
                __useMagicMatching = token;
                break;
            case 6:
                __useHiddenCell = token;
                break;
            case 7:
                infoBoard = token;
                break;
            default:
                break;
        }

        index++;
        token.clear();
    }
    
    if (player.username.empty() || player.password.empty() || __timeUsed.empty() || __useHint.empty() || __useMagicMatching.empty() || __useHiddenCell.empty()) {
        inp.close();
        return false;
    }
    if (__useHint.size() > 1 || (__useHint[0] > '3' || __useHint[0] < '0')) {
        inp.close();
        return false;
    }
    if (__useMagicMatching.size() > 1 || (__useMagicMatching[0] > '5' || __useMagicMatching[0] < '0')) {
        inp.close();
        return false;
    }
    if (__useHiddenCell.size() > 1 || (__useHiddenCell[0] > '5' || __useHiddenCell[0] < '0')) {
        inp.close();
        return false;
    }
    for (char digit: __timeUsed) {
        if (digit < '0' || '9' < digit) {
            inp.close();
            return false;
        }
    }
    for (char digit: __score) {
        if (digit < '0' || '9' < digit) {
            inp.close();
            return false;
        }
    }
    if (stod(__useMagicMatching) * stoi(__useHiddenCell) > 0) {
        inp.close();
        return false;
    }

    ofstream out;
    out.open("record/board.txt");

    out << infoBoard;

    inp.close();
    out.close();

    board tmp;
    return (tmp.readBoard("record/board.txt", true).second >= 0);
}

void game::loadGame(int slot) {
    ifstream inp;
    inp.open("record/savegame" + to_string(slot) + ".txt");
    if (!inp.is_open())
        return;
    
    int index = 0;
    string token, infoBoard;

    while(true) {
        getline(inp, token, ';');
        if (token.empty()) 
            break;
        
        switch (index)
        {
            case 0:
                player.username = token;
                break;
            case 1:
                player.password = token;
                break;
            case 2:
                score = stoi(token);
                break;
            case 3:
                timeUsed = stoi(token);
                break;
            case 4:
                useHint = stoi(token);
                break;
            case 5:
                useMagicMatching = stoi(token);
                break;
            case 6:
                useHiddenCell = stoi(token);
                break;
            case 7:
                infoBoard = token;
                break;
            default:
                break;
        }

        index++;
        token.clear();
    }

    ofstream out;
    out.open("record/board.txt");
    out << infoBoard;

    inp.close();
    out.close();

    pair<string*, int> buffer = map.readBoard("record/board.txt", false);
    map.loadBoard(buffer);
    diff = buffer.second;
    isPlaying = true;

    for (int r = 1; r <= map.ROW; r++)
        for (int c = 1; c <= map.COL; c++)
            numLeft += (map.grid[r][c] != '$');

    getBackground();
}

void game::startGame() {
    // set up to get started
    clearScreen();
    hideCursor();
    timeStart = time(0);
    playSound(diff + 1);

    drawInterface();

    // go into game
    while(isPlaying) {
        // get input from user and check 
        int input = getInputKey(); 
        switch (input) {
            case ESC: // escape the game
            {
                renderNotificate("PRESS ESC AGAIN TO LEAVE");
                if (getInputKey() == ESC) {
                    playSound(diff + 1, true);
                    isPlaying = false;
                    clearScreen();
                }
                else {
                    renderNotificate("                        ");
                }
                break;
            }
            case DOWN : case RIGHT : case UP : case LEFT:
                moveCell(input);
                break;
            case ENTER:
                select();
                break;
            case GET_HINT:
                moveSuggestion();
                break;
            case TOGGLE_MUSIC:
                toggleMusic(diff + 1);
                break;
            case SAVE_GAME: 
            {
                saveGame();
                break;
            }
            case MAGIC_MOVE:
                magicMove();
                break;
            case HELP_MENU:
                helpMenu();
                break;
            default:
                break;
        }
        
        updateInfo();
        if (currentSelect.first != 0 && currentSelect.second != 0) {
            highlightCell(currentSelect.first, currentSelect.second, BACKGROUND_COLOR[YELLOW]);
        }
        if (finishGame()) {
            isPlaying = false;
        }
    }

    clearScreen();
}

bool game::finishGame() {
    if (numLeft == 0 && getCurrentTime() >= 0) {
        playSound(diff + 1, true);
        playSound(WIN);
        saveScore();
        Sleep(3000);
        renderNotificate("YOU WIN!!!");
        LEADERBOARD_CONTROL();
        return true;
    }
    if (getCurrentTime() < 0) {
        playSound(diff + 1, true);
        playSound(LOSE);
        renderNotificate("YOU LOSE!!!");
        Sleep(4000);
        return true;
    }
    
    return false;
}

void game::getBackground() {
    ifstream fin;
    background = NULL;
    // size of background equal to size of outline but minus by 1 for each height and width
    int height = sizeROW[diff] * (HEIGHT_CELL - 1) + 1 + 2 * (BUFFER_HEIGHT_CELL - 1);
    int width = sizeCOL[diff] * (WIDTH_CELL - 1) + 1 + 2 * (BUFFER_WIDTH_CELL - 1);
    background = new string [height] {};
    
    //open file to read background
    fin.open(backGroundImage[diff].c_str());

    if (!fin.is_open()) {
        cerr << "error file";
        return;
    }

    // get background
    int count = 0;
    while (count < height && getline(fin, background[count])) {
        // check and add space padding characters
        if (background[count].length() < width) {
            int curLength = background[count].length();
            background[count].append(width - curLength, ' ');
        }
        count++;
    }

    // check and add background padding
    while (count < height) {
        background[count].append(width, ' ');
        count++;
    }

    fin.close();
}

void game::updateInfo() {
    renderScore();
    renderTime();
    renderHint();
    renderMagic();
}

void game::renderScore() {
    // set up the position of information table
    short infor_PosX = (upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6);
    short infor_PosY = upperLeftCorner.Y;
    setCursor(infor_PosX + 14, infor_PosY + 3);
    cout << TEXT_BLACK << "      ";
    setCursor(infor_PosX + 14, infor_PosY + 3);
    cout << score;
}

void game::renderHint() {
    // set up the position of information table
    short infor_PosX = (upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6);
    short infor_PosY = upperLeftCorner.Y;
    setCursor(infor_PosX + 14, infor_PosY + 4);
    cout << TEXT_BLACK << "      ";
    setCursor(infor_PosX + 14, infor_PosY + 4);
    cout << useHint;
}

void game::renderMagic() {
    // set up the position of information table
    short infor_PosX = (upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6);
    short infor_PosY = upperLeftCorner.Y;
    // clear the old infomation
    setCursor(infor_PosX + 14, infor_PosY + 5);
    cout << TEXT_BLACK << "             ";
    // render new infomation
    setCursor(infor_PosX + 14, infor_PosY + 5);
    // check what type of magic move
    if (!randomMagicMove) {
        cout << "HIDDEN CELL";
        setCursor(infor_PosX + 14, infor_PosY + 6);
        cout << useHiddenCell;
    }
    else {
        cout << "MAGIC MATCHING";
        setCursor(infor_PosX + 14, infor_PosY + 6);
        cout << useMagicMatching;
    }
}

void game::renderTime() {
    // clear the old time
    setCursor(103 + map.boardPos[diff].first, 1);
    cout << TEXT_BLACK << "    ";
    // render new time
    setCursor(103 + map.boardPos[diff].first, 1);
    cout << getCurrentTime();
}

void game::renderNotificate(string noti) {
    // set up the position of information table
    short infor_PosX = (upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6);
    short infor_PosY = upperLeftCorner.Y;
    // clear the old information
    setCursor(infor_PosX + 3, infor_PosY + 10);
    cout << TEXT_BLACK << "                         ";
    // render new information
    setCursor(infor_PosX + 3, infor_PosY + 10);
    cout << TEXT_COLOR[RED] << noti << TEXT_BLACK;
}