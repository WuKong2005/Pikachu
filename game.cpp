#include "game.h"

game::game() {
    
}

game::~game() {
    if (!background)
        delete [] background;
}

game::game(int difficult) {
    map.~board();
    new (&map) board(difficult);
    numLeft = map.ROW * map.COL;
    isPlaying = true;
    diff = difficult;
    upperLeftCorner = {7, 4};
    currentPos = {1, 1};
    
    ifstream fin;
    int height = sizeROW[difficult] * (HEIGHT_CELL - 1) + 1;
    background = new string [height];

    fin.open(backGroundImage[difficult].c_str());
    int count = 0;
    while (count < height && getline(fin, background[count]))
        count++;
    fin.close();
}

void game::drawInterface() {
    
}

void game::drawBoard() {
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
    for (int row = 1; row <= map.ROW; ++row)
        for (int col = 1; col <= map.COL; ++col)
            if (map.grid[row][col] != '$') {
                drawCell({row, col}, map.grid[row][col]); // direction access
                Sleep(1);
            }
    cout << TEXT_BLACK;
}

void game::drawCell(pair<int, int> cell, char key) {
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
    cout << key;
}

void game::removeCell(pair<int, int> cell) {
    if (map.grid[cell.first][cell.second] != '$')
        return;
    
    highlightCell(cell.first, cell.second, BACKGROUND_COLOR[YELLOW]);

    // set Cursor to coordinate of upperLeftCorner of cell
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (cell.second - 1) * (WIDTH_CELL - 1);
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (cell.first - 1) * (HEIGHT_CELL - 1);

    // cout << BACKGROUND_COLOR[YELLOW];
    // check and delete top side
    if (map.grid[cell.first - 1][cell.second] == '$') {
        setCursor(posX, posY);
        for (int numChar = 0; numChar < WIDTH_CELL; ++numChar)    
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1)][(cell.second - 1) * (WIDTH_CELL - 1) + numChar];
    }
    //check and delete bottom side
    if (map.grid[cell.first + 1][cell.second] == '$') {
        setCursor(posX, posY + (HEIGHT_CELL - 1));
        for (int numChar = 0; numChar < WIDTH_CELL; ++numChar)
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL - 1][(cell.second - 1) * (WIDTH_CELL - 1) + numChar];
    }
    //check and delete left side
    if (map.grid[cell.first][cell.second - 1] == '$')
        for (int numChar = 0; numChar < HEIGHT_CELL; ++numChar) {
            setCursor(posX, posY + numChar);
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + numChar][(cell.second - 1) * (WIDTH_CELL - 1)];
        }
    // check and delete right side
    if (map.grid[cell.first][cell.second + 1] == '$')
        for (int numChar = 0; numChar < HEIGHT_CELL; ++numChar) {
            setCursor(posX + (WIDTH_CELL - 1), posY + numChar);
            cout << background[(cell.first - 1) * (HEIGHT_CELL - 1) + numChar][(cell.second - 1) * (WIDTH_CELL - 1)];
        }
    cout << TEXT_BLACK;
    Sleep(1000);

    unHighlightCell(cell.first, cell.second);
}

void game::drawGuide() {

}

void game::drawPath(pair<int, int> startCell, pair<int, int> endCell, vector<pair<int, int>> path) {

}

void game::drawLine(pair<int, int> startCell, pair<int, int> endCell) {
    if (startCell == endCell)
        return;
    else if (startCell.first == endCell.first)
        drawHorizontalLine(startCell.first, startCell.second, endCell.second);
    else if (startCell.second == endCell.second)
        drawVerticalLine(startCell.second, startCell.first, endCell.first);
    else
        return;
}

void game::deleteLine(pair<int, int> startCell, pair<int, int> endCell) {
    if (startCell == endCell)
        return;
    else if (startCell.first == endCell.first)
        deleteHorizontalLine(startCell.first, startCell.second, endCell.second);
    else if (startCell.second == endCell.second)
        deleteVerticalLine(startCell.second, startCell.first, endCell.first);
    else
        return;
}

void game::drawVerticalLine(int col, int row1, int row2) {
    if (row1 > row2)
        swap(row1, row2);
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY1 = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row1 - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    short posY2 = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row2 - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;

    cout << TEXT_COLOR[BRIGHT_YELLOW];
    while (posY1 < posY2 - 1) {
        posY1++;
        setCursor(posX, posY1);
        cout << char(179);
    }
    cout << TEXT_BLACK;
}

void game::deleteVerticalLine(int col, int row1, int row2) {
    if (row1 > row2)
        swap(row1, row2);
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY1 = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row1 - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    short posY2 = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row2 - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    cout << TEXT_BLACK;
    while (posY1 < posY2 - 1) {
        posY1++;
        setCursor(posX, posY1);
        cout << background[posY1 - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL)][posX - (upperLeftCorner.X + BUFFER_WIDTH_CELL)];
    }
}

void game::drawHorizontalLine(int row, int col1, int col2) {
    if (col1 > col2)
        swap(col1, col2);
    short posX1 = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col1 - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posX2 = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col2 - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;

    cout << TEXT_COLOR[BRIGHT_YELLOW];
    while (posX1 < posX2 - 1) {
        posX1++;
        setCursor(posX1, posY);
        cout << char(196);
    }
    cout << TEXT_BLACK;
}

void game::deleteHorizontalLine(int row, int col1, int col2) {
    if (col1 > col2)
        swap(col1, col2);
    short posX1 = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col1 - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posX2 = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col2 - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;

    cout << TEXT_BLACK;
    while (posX1 < posX2 - 1) {
        posX1++;
        setCursor(posX1, posY);
        cout << background[posY - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL)][posX1 - (upperLeftCorner.X + BUFFER_WIDTH_CELL)];
    }
}

void game::drawTurningPoint(int row, int col, int type) {
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    setCursor(posX, posY);

    cout << TEXT_COLOR[BRIGHT_YELLOW];
    cout << char(turning[type]);
    cout << TEXT_BLACK;
}

void game::deleteTurningPoint(int row, int col) {
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + WIDTH_CELL / 2;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + HEIGHT_CELL / 2;
    setCursor(posX, posY);

    cout << background[posY - (upperLeftCorner.Y + BUFFER_HEIGHT_CELL)][posX - (upperLeftCorner.X + BUFFER_WIDTH_CELL)];
}

void game::moveCell(int direction) {
    switch (direction) {
        case UP:
            unHighlightCell(currentPos.first, currentPos.second);
            if (currentPos.first == 1)
                currentPos.first = map.ROW;
            else
                currentPos.first--;
            break;
            
        case DOWN:
            unHighlightCell(currentPos.first, currentPos.second);
            if (currentPos.first == map.ROW)
                currentPos.first = 1;
            else
                currentPos.first++;
            break;
        
        case LEFT:
            unHighlightCell(currentPos.first, currentPos.second);
            if (currentPos.second == 1)
                currentPos.second = map.COL;
            else
                currentPos.second--;
            break;
            
        case RIGHT:
            unHighlightCell(currentPos.first, currentPos.second);
            if (currentPos.second == map.COL)
                currentPos.second = 1;
            else
                currentPos.second++;
            break;
        
        case ENTER:
            select();
            return;
        
        default:
            return;
    }
    highlightCell(currentPos.first, currentPos.second, BACKGROUND_COLOR[CYAN]);
}

void game::highlightCell(int row, int col, string color) {
    short posX = upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + 1;
    short posY = upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + 1;
    setCursor(posX, posY);
    cout << color;

    if (map.grid[row][col] != '$') // if Cell isn't deleted
        for (int rowCell = 1; rowCell <= HEIGHT_CELL - 2; ++rowCell) {
            if (rowCell != HEIGHT_CELL / 2)
                for (int colCell = 1; colCell <= WIDTH_CELL - 2; ++colCell)
                    cout << " ";
            else
                for (int colCell = 1; colCell <= WIDTH_CELL - 2; ++colCell)
                    if (colCell != WIDTH_CELL / 2)
                        cout << " ";
                    else
                        cout << TEXT_COLOR[WHITE] << 'A' << color;
            setCursor(upperLeftCorner.X + BUFFER_WIDTH_CELL + (col - 1) * (WIDTH_CELL - 1) + 1,
                      upperLeftCorner.Y + BUFFER_HEIGHT_CELL + (row - 1) * (HEIGHT_CELL - 1) + 1 + rowCell);
        }
    else // if Cell is deleted --> draw Background
        for (int rowCell = 1; rowCell <= HEIGHT_CELL - 2; ++rowCell) {
            for (int colCell = 1; colCell <= WIDTH_CELL - 2; ++colCell)
                cout << background[(HEIGHT_CELL - 1) * (row - 1) + rowCell][(WIDTH_CELL - 1) * (col - 1) + colCell];
            posY++;
            setCursor(posX, posY);
        }
    cout << BACKGROUND_COLOR[BLACK] << TEXT_BLACK;
}

void game::unHighlightCell(int row, int col) {
    highlightCell(row, col, BACKGROUND_COLOR[BLACK]);
}

void game::select() {
    if (currentSelect.first == 0 && currentSelect.second == 0) {
        currentSelect.first = currentPos.second;
        currentSelect.second = currentPos.first;
        highlightCell(currentPos.second, currentPos.first, BACKGROUND_COLOR[YELLOW]);
    }
    else if (currentSelect.first == currentPos.second && currentSelect.second == currentPos.first) {
        unHighlightCell(currentPos.second, currentPos.first);
        currentSelect.first = 0;
        currentSelect.second = 0;
    }
    else; // check matching
} 

void game::getRespond(pair<int, int> nextSelect) {

}

void game::startGame() {

}

void game::finishGame() {
    
}