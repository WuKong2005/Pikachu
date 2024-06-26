#include "game_extra.h"

game_extra::~game_extra() {
    if (!background)
        delete [] background;
}

game_extra::game_extra(int difficult = 2) {
    map.initializeBoard();

    currentSelect = {0, 0};
    timeUsed = 0;
    numLeft = map.ROW * map.COL;
    diff = difficult;
    score = 0;
    useHint = 3;
    int total = diff * 2 + 1;
    useMagicMatching = total;
    isPlaying = true;
    applyMagicMatching = false;
    
    upperLeftCorner.X = (short)map.boardPos.first;
    upperLeftCorner.Y = (short)map.boardPos.second;
    currentPos = {1, 1};
    
    getBackground();
}

int game_extra::timeDuration() {
    return (int)difftime(time(0), timeStart);
}

int game_extra::getCurrentTime() {
    return limTime[diff] - (timeUsed + timeDuration());
}

void game_extra::drawInterface() {
    drawBoard(); 

    //print information in game at position about 4 (or 6) spaces away from the board frame
    printInfoInGame((upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6),
                     upperLeftCorner.Y);

    // print the help menu in game at position about 4 (or 6) spaces away from board frame 
    // and lower than information in game 19 spaces
    printHelpInGame((upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6),
                     upperLeftCorner.Y + 19);

    // print user information
    setCursor(map.boardPos.first, 1);
    cout << TEXT_COLOR[YELLOW] << "USERNAME: " << player.username;
    setCursor(45 + map.boardPos.first, 1);
    cout << "DIFFICULTY: ";
    if (diff == EASY)
        cout << "EASY";
    else if (diff == MEDIUM)
        cout << "MEDIUM";
    else
        cout << "HARD";
    setCursor(90 + map.boardPos.first, 1);
    cout << "TIME REMAIN: ";

    renderScore();
    renderHint();
    renderMagic();
    renderTime();

    cout << TEXT_BLACK;
}

void game_extra::drawBoard() {
    SetConsoleCursorPosition(console, upperLeftCorner);

// Animation draw the frame of board
    int WidthBorder = BUFFER_WIDTH_CELL * 2 + (WIDTH_CELL - 1) * sizeCOL[diff] + 1;
    int HeightBorder = BUFFER_HEIGHT_CELL * 2 + (HEIGHT_CELL -1) * sizeROW[diff] + 1;

    for (int col = 0; col < WidthBorder; ++col) {
        if (col == 0)
            cout << char(frame[UPPER_LEFT]);
        else if (col == WidthBorder - 1)
            cout << char(frame[UPPER_RIGHT]);
        else
            cout << char(205);
        Sleep(1);
    }
    
    setCursor(upperLeftCorner.X + WidthBorder - 1, upperLeftCorner.Y + 1);
    
    for (int row = 0; row < HeightBorder - 2; ++row) {
        cout << char(186);
        setCursor(upperLeftCorner.X + WidthBorder - 1, upperLeftCorner.Y + 2 + row);
        Sleep(1);
    }

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

    for (int row = HeightBorder - 2; row > 0; --row) {
        setCursor(upperLeftCorner.X, upperLeftCorner.Y + row);
        cout << char(186);
        Sleep(10);
    }

// draw board
    for (int row = 1; row <= map.ROW; ++row) {
        for (int col = 1; col <= map.COL; ++col) {
            if (map.grid[row][col] != '$') {
                drawCell({row, col}, map.grid[row][col]); // direction access
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

void game_extra::drawCell(pair<int, int> cell, char key) {
    short posX = upperLeftCorner.X + (cell.second - 1) * (WIDTH_CELL - 1) + BUFFER_WIDTH_CELL;
    short posY = upperLeftCorner.Y + (cell.first - 1) * (HEIGHT_CELL - 1) + BUFFER_HEIGHT_CELL;
    COORD position = {posX, posY};
    SetConsoleCursorPosition(console, position);
    string side;
    side.append(WIDTH_CELL - 2, char(196));
    
    cout << TEXT_COLOR[BRIGHT_BLUE];

    setCursor(position.X + 1, position.Y);
    cout << side;
    setCursor(position.X + 1, position.Y + HEIGHT_CELL - 1);
    cout << side;

    for (int col = 1; col <= HEIGHT_CELL - 2; ++col) {
        setCursor(position.X, position.Y + col);
        cout << char(179);
        setCursor(position.X + WIDTH_CELL - 1, position.Y + col);
        cout << char(179);
    }

    setCursor(position.X + WIDTH_CELL / 2, position.Y + HEIGHT_CELL / 2);
    cout << TEXT_COLOR[WHITE] << key;
}

void game_extra::removeCell(pair<int, int> cell) {
    if (cell.first < 1 || cell.second < 1 || cell.first > map.ROW || cell.second > map.COL||
        map.grid[cell.first][cell.second] != '$')
        return;
    
    // highlightCell(cell.first, cell.second, BACKGROUND_COLOR[GREEN]);

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
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)][(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1) + numChar];
    }
    //check and delete bottom side
    if (cellBottom) {
        setCursor(posX + 1, posY + (HEIGHT_CELL - 1));
        for (int numChar = 1; numChar < WIDTH_CELL - 1; ++numChar)
            cout << background[cell.first * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)][(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1) + numChar];
    }
    //check and delete left side
    if (cellLeft)
        for (int numChar = 1; numChar < HEIGHT_CELL - 1; ++numChar) {
            setCursor(posX, posY + numChar);
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1) + numChar][(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
        }
    // check and delete right side
    if (cellRight)
        for (int numChar = 1; numChar < HEIGHT_CELL - 1; ++numChar) {
            setCursor(posX + (WIDTH_CELL - 1), posY + numChar);
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1) + numChar][cell.second * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
        }

// Check 4 corners
    // upper left corner
    if(cellTop && cellLeft && map.grid[cell.first - 1][cell.second - 1] == '$') {
        setCursor(posX, posY);
        cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)][(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
    }
    // upper right corner
    if (cellTop && cellRight && map.grid[cell.first - 1][cell.second + 1] == '$') {
        setCursor(posX + (WIDTH_CELL - 1), posY);
        cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)][cell.second * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
    }
    // lower left corner
    if (cellBottom && cellLeft && map.grid[cell.first + 1][cell.second - 1] == '$') {
        setCursor(posX, posY + (HEIGHT_CELL - 1));
        cout << background[cell.first * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)][(cell.second - 1) * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
    }
    // lower right corner
    if (cellBottom && cellRight && map.grid[cell.first + 1][cell.second + 1] == '$') {
        setCursor(posX + (WIDTH_CELL - 1), posY + (HEIGHT_CELL - 1));
        cout << background[cell.first * (HEIGHT_CELL - 1) + (BUFFER_HEIGHT_CELL - 1)][cell.second * (WIDTH_CELL - 1) + (BUFFER_WIDTH_CELL - 1)];
    }

    cout << TEXT_BLACK;
    // Sleep(1000);

    unHighlightCell(cell.first, cell.second);
}

void game_extra::drawGuide() {

}

void game_extra::drawPath(vector<pair<int, int>> path, bool draw) {
    assert(path.size() >= 2);
    int numCell = path.size();
    
    for (int cell = 0; cell + 1 < numCell; ++cell) {
        drawLine(path[cell], path[cell + 1], draw);
    }
    vector<pair<int, int>> vec;
    for (int i = 0; i < numCell - 1; ++i)
        vec.push_back({path[i].first - path[i + 1].first, path[i].second - path[i + 1].second});
    
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

void game_extra::drawLine(pair<int, int> startCell, pair<int, int> endCell, bool draw) {
    if (startCell == endCell)
        return;
    if (startCell.first == endCell.first)
        drawHorizontalLine(startCell.first, startCell.second, endCell.second, draw);
    if (startCell.second == endCell.second)
        drawVerticalLine(startCell.second, startCell.first, endCell.first, draw);
}

void game_extra::drawVerticalLine(int col, int row1, int row2, bool draw) {
    if (row1 > row2)
        swap(row1, row2);
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY1 = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row1 - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    short posY2 = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row2 - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;

    cout << (draw ? TEXT_COLOR[BRIGHT_YELLOW] : TEXT_BLACK);
    if (!draw)
        while (posY1 < posY2 - 1) {
            posY1++;
            setCursor(posX, posY1);
            cout << background[posY1 - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL) + (BUFFER_HEIGHT_CELL - 1)][posX - (upperLeftCorner.X + BUFFER_WIDTH_CELL) + (BUFFER_WIDTH_CELL - 1)];
        }
    else 
        while (posY1 < posY2 - 1) {
            posY1++;
            setCursor(posX, posY1);
            cout << char(179);
        }
    cout << TEXT_BLACK;
}

void game_extra::drawHorizontalLine(int row, int col1, int col2, bool draw) {
    if (col1 > col2)
        swap(col1, col2);
    short posX1 = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col1 - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posX2 = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col2 - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;

    cout << (draw ? TEXT_COLOR[BRIGHT_YELLOW] : TEXT_BLACK);

    if (!draw)
        while (posX1 < posX2 - 1) {
            posX1++;
            setCursor(posX1, posY);
            cout << background[posY - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL) + (BUFFER_HEIGHT_CELL - 1)][posX1 - (upperLeftCorner.X + BUFFER_WIDTH_CELL) + (BUFFER_WIDTH_CELL - 1)];
        }
    else
        while (posX1 < posX2 - 1) {
            posX1++;
            setCursor(posX1, posY);
            cout << char(196);
        }
    cout << TEXT_BLACK;
}

void game_extra::drawTurningPoint(int row, int col, int type, bool draw) {
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    setCursor(posX, posY);

    if (draw) {
        cout << TEXT_COLOR[BRIGHT_YELLOW] << char(turning[type]);
    }
    else {
        cout << TEXT_BLACK;
        cout << background[posY - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL) + (BUFFER_HEIGHT_CELL - 1)][posX - (upperLeftCorner.X + BUFFER_WIDTH_CELL) + (BUFFER_WIDTH_CELL - 1)];
    }
    cout << TEXT_BLACK;
}

void game_extra::moveCell(int direction) {
    playSound(MOVE);
    unHighlightCell(currentPos.first, currentPos.second);
    currentPos.first = ((currentPos.first + dx[direction - 1] + map.ROW - 1) % map.ROW) + 1;
    currentPos.second = ((currentPos.second + dy[direction - 1] + map.COL - 1) % map.COL) + 1;
    highlightCell(currentPos.first, currentPos.second, BACKGROUND_COLOR[CYAN]);
}

void game_extra::highlightCell(int row, int col, string color) {
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
                cout << background[(HEIGHT_CELL - 1) * (row - 1) + (BUFFER_HEIGHT_CELL - 1) + rowCell][(WIDTH_CELL - 1) * (col - 1) + (BUFFER_WIDTH_CELL - 1) + colCell];
            }
                
            posY++;
            setCursor(posX, posY);
        }
    }
    cout << BACKGROUND_COLOR[BLACK] << TEXT_BLACK;
}

void game_extra::unHighlightCell(int row, int col) {
    highlightCell(row, col, BACKGROUND_COLOR[BLACK]);
}

void game_extra::select() {
    if (map.grid[currentPos.first][currentPos.second] == '$') {
        return;
    }
    playSound(CHOOSE);
    if (currentSelect == make_pair(0, 0)) {
        currentSelect = currentPos;
        highlightCell(currentPos.first, currentPos.second, BACKGROUND_COLOR[YELLOW]);
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

        map.deleteMatch(currentSelect, currentPos);
        drawPath(path, false);
        unHighlightCell(currentSelect.first, currentSelect.second);
        unHighlightCell(currentPos.first, currentPos.second);

        for (int col = 1; col <= map.COL; col++) {
            if (map.grid[currentSelect.first][col] != '$') 
                drawCell({currentSelect.first, col}, map.grid[currentSelect.first][col]); // direction access
            else 
                removeCell({currentSelect.first, col});
            if (map.grid[currentPos.first][col] != '$') 
                drawCell({currentPos.first, col}, map.grid[currentPos.first][col]); // direction access
            else 
                removeCell({currentPos.first, col});
        }
        
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

void game_extra::getRespond(pair<int, int> nextSelect) {

}

bool game_extra::moveSuggestion() {
    if (useHint == 0) {
        renderNotificate("NO MORE HINT!!!");
        return false;
    }
    if (applyMagicMatching) {
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

bool game_extra::magicMove() {
    if (!useMagicMatching) {
        renderNotificate("NO MORE MAGIC!!!");
        return false;
    }
    else {
        magicMatch();
        return true;
    }
}

void game_extra::magicMatch() {
    if (applyMagicMatching) {
        renderNotificate("ALREADY USE!!!");
        return;
    }
    renderNotificate("MAGIC MATCHING");
    --useMagicMatching;
    applyMagicMatching = true;
}

void game_extra::helpMenu() {
    clearScreen();
    Sleep(1000);
    HELP_CONTROL();
    Sleep(1000);
    SetConsoleOutputCP(437);
    drawInterface();
}

void game_extra::saveGame() {
    renderNotificate("DISABLE!!!");
}

void game_extra::startGame() {
    clearScreen();
    hideCursor();
    timeStart = time(0);
    playSound(diff + 1);

    drawInterface();

    while(isPlaying) {
        int input = getInputKey();
        switch (input) {
            case ESC: 
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

bool game_extra::finishGame() {
    if (numLeft == 0 && getCurrentTime() >= 0) {
        playSound(diff + 1, true);
        playSound(WIN);
        renderNotificate("YOU WIN!!!");
        Sleep(8000);
        return true;
    }
    if (getCurrentTime() < 0) {
        playSound(diff + 1, true);
        playSound(LOSE);
        renderNotificate("YOU LOSE!!!");
        Sleep(8000);
        return true;
    }
    
    return false;
}

void game_extra::getBackground() {
    ifstream fin;
    background = NULL;
    int height = sizeROW[diff] * (HEIGHT_CELL - 1) + 1 + 2 * (BUFFER_HEIGHT_CELL - 1);
    int width = sizeCOL[diff] * (WIDTH_CELL - 1) + 1 + 2 * (BUFFER_WIDTH_CELL - 1);
    background = new string [height] {};

    fin.open(backGroundImageExtra);

    if (!fin.is_open()) {
        cerr << "error file";
        return;
    }

    int count = 0;
    while (count < height && getline(fin, background[count])) {
        // cerr << background[count] << endl;
        if (background[count].length() < width) {
            int curLength = background[count].length();
            background[count].append(width - curLength, ' ');
        }
        count++;
    }

    while (count < height) {
        background[count].append(width, ' ');
        count++;
    }

    fin.close();
}

void game_extra::updateInfo() {
    renderScore();
    renderTime();
    renderHint();
    renderMagic();
}

void game_extra::renderScore() {
    short infor_PosX = (upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6);
    short infor_PosY = upperLeftCorner.Y;
    setCursor(infor_PosX + 14, infor_PosY + 3);
    cout << TEXT_BLACK << "      ";
    setCursor(infor_PosX + 14, infor_PosY + 3);
    cout << score;

    // setCursor(upperLeftCorner.X + BUFFER_WIDTH_CELL + (map.COL - 1) * (WIDTH_CELL - 1) + 1,
    //           upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (map.ROW - 1) * (HEIGHT_CELL - 1) + 1);
}

void game_extra::renderHint() {
    short infor_PosX = (upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6);
    short infor_PosY = upperLeftCorner.Y;
    setCursor(infor_PosX + 14, infor_PosY + 4);
    cout << TEXT_BLACK << "      ";
    setCursor(infor_PosX + 14, infor_PosY + 4);
    cout << useHint;
}

void game_extra::renderMagic() {
    short infor_PosX = (upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6);
    short infor_PosY = upperLeftCorner.Y;
    setCursor(infor_PosX + 14, infor_PosY + 5);
    cout << TEXT_BLACK << "             ";

    setCursor(infor_PosX + 14, infor_PosY + 5);
    cout << "MAGIC MATCHING";
    setCursor(infor_PosX + 14, infor_PosY + 6);
    cout << useMagicMatching;
}

void game_extra::renderTime() {
    setCursor(103 + map.boardPos.first, 1);
    cout << TEXT_BLACK << "    ";
    setCursor(103 + map.boardPos.first, 1);
    cout << getCurrentTime();
}

void game_extra::renderNotificate(string noti) {
    short infor_PosX = (upperLeftCorner.X + map.COL * (WIDTH_CELL - 1) + 1 + 2 * BUFFER_WIDTH_CELL) + (diff == HARD ? 4 : 6);
    short infor_PosY = upperLeftCorner.Y;
    setCursor(infor_PosX + 3, infor_PosY + 10);
    cout << TEXT_BLACK << "                         ";
    setCursor(infor_PosX + 3, infor_PosY + 10);
    cout << TEXT_COLOR[RED] << noti << TEXT_BLACK;
}