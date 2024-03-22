#include "board.h"

//Constructor
board::board() {
    ROW = COL = 0;
    grid = NULL;
    flood = NULL;
}

//Create a board specific for its difficult
board::board(int difficult) {
    ROW = sizeROW[difficult];
    COL = sizeCOL[difficult];

    //Add a boundary of the initial board
    //Allowed an efficient and clear implementation
    grid = new char*[ROW + 2];
    flood = new array<int, 3>*[ROW + 2];

    for (int r = 0; r < ROW + 2; r++) {
        grid[r] = new char[COL + 2]{};
        flood[r] = new array<int, 3>[COL + 2]{};    
    }

    //Consider the boundary as deleted cell
    for (int r = 0; r < ROW + 2; r++) 
        grid[r][0] = grid[r][COL + 1] = '$';
    for (int c = 0; c < COL + 2; c++)
        grid[0][c] = grid[ROW + 1][c] = '$';
}

//Deallocate dynamically memory used
board::~board() {
    for (int r = 0; r < ROW + 2; r++) 
    {
        delete [] grid[r];
        delete [] flood[r];
    }
    delete [] grid;
    delete [] flood;
}

//Load a saved board
bool board::readSaveFile(string pathSaveFile) {
    ifstream inp;
    inp.open(pathSaveFile.c_str());
    
    //Failed to open saved game 
    if (!inp.is_open()) {
        return false;
    }

    //Create a buffer to read the size of board, current timeCheck, all character and relative information of each cell
    //The extra size used to check the valid of input as well
    int maxSize = sizeROW[2] * sizeCOL[2] * 4 + 3 + 1;
    int* buffer = new int[maxSize]{}; 
    int __size = 0;
    while(true) {
        int x;
        inp >> x;
        if (x == 0) 
            break;

        buffer[__size] = x;
        __size++;
        if (__size == maxSize)
            break;
    }

    //Check valid size of board
    int curRow = buffer[0], curCol = buffer[1], curTimeCheck = buffer[2];
    bool found = false;
    for (int difficult = 0; difficult < 3; difficult++) 
        if (curRow == sizeROW[difficult] && curCol == sizeCOL[difficult]) 
            found = true;
    if (!found)
        return false;
    
    //Check amount of integer read
    if (__size != maxSize - 1) 
        return false;
    
    //Check valid information of each cell
    bool valid = true;
    for (int i = 3; i < __size; i += 4) {
        if (buffer[i] != (int)'$' && (buffer[i] < (int)'A' || (int)'Z' < buffer[i])) valid = false;
        if (buffer[i + 1] > curTimeCheck) valid = false;
    }

    //Return the valid of this saved game
    return valid;
}

//Initialize board
void board::initializeBoard() {
    //Initialize amount of pairs for each character
    int frequent[ALPHABET]{};
    
    //Execute ROW * COL / 2 times, for each time, choose randomly a character then increase its frequency by 1
    for (int time = 0; time < ROW * COL / 2; time++) 
        frequent[rand() % ALPHABET]++;
    
    //Multiply each character's frequency by 2
    for (int c = 0; c < ALPHABET; c++)
        frequent[c] <<= 1;
    assert(accumulate(frequent, frequent + ALPHABET, 0) == ROW * COL);

    //Assign them to the board
    int lastCharacter = 0;
    for (int r = 1; r <= ROW; r++) 
    {
        for (int c = 1; c <= COL; c++)
        {
            while(!frequent[lastCharacter])
                lastCharacter++;
            grid[r][c] = char(lastCharacter + 'A');
            --frequent[lastCharacter];
        }
    }

    //And finally shuffle them until we can guarantee a valid move exist
    do {
        shuffleBoard();
    } while(!automatic_check());
}

//Shuffle the board when needed (no valid move left or player want to do it)
void board::shuffleBoard() {
    //Count number of cells left
    int valid_cell = 0;
    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            valid_cell += (grid[r][c] != '$');
        }
    }

    //Put all of them in an temporary array with size of exact amount of valid cells left
    char* arrayCell = new char[valid_cell];
    int index = 0;
    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            if (grid[r][c] != '$') {
                arrayCell[index] = grid[r][c];
                ++index;
            }
        }
    }

    //Shuffle them, them put them back to the board
    random_shuffle(arrayCell, arrayCell + valid_cell);
    index = 0;
    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            if (grid[r][c] != '$') {
                grid[r][c] = arrayCell[index];
                ++index;
            }
        }
    }

    //Deallocate that temporary array
    delete [] arrayCell;
}

//Check valid move from the player, started from startCell and ended at endCell
//Flag "magic" allow more possible moves
bool board::checkMatch(pair<int, int> startCell, pair<int, int> endCell, bool magic, bool* found) {
    //Assume startCell and endCell are two different cells
    int r1 = startCell.first, c1 = startCell.second;
    int r2 = endCell.first, c2 = startCell.second;

    //If the character from these 2 cells are different then the match is invalid
    if (grid[r1][c1] != grid[r2][c2]) return false;

    //Focus on this character
    char aimCharacter = grid[r1][c1]; 

    //Indicate a new checking attempt
    ++timeCheck;

    //Two queues to store nodes while BFS
    queue<array<int, 3>> prevQ, curQ;

    //Add initial nodes to queue and mark it (visited node)
    prevQ.push({r1, c1, -1});
    flood[r1][c1][0] = timeCheck;
    flood[r1][c1][1] = -1;
    flood[r1][c1][2] = -1;

    for (int numStep = 0; numStep <= 2 + magic; numStep++) {
        while(!prevQ.empty()) {
            //C++17
            //Dequeue a node from previous layer
            //Each node is a state consists of row index, column index of the cell and vector index used to reach that cell
            auto &[curR, curC, curD] = prevQ.front();
            prevQ.pop();

            //Iterate all possible moves
            for (int dir = 0; dir < 4; dir++) {
                //Only allowed to visit nodes with direction perpendicular to this state's vector  
                if (curD != -1) {
                    if (dir == curD) continue;
                    if (abs(dir - curD) == 2) continue;
                }
                
                //Start from this cell, keep moving with that direction until certain conditions are satisfied
                int newR = curR;
                int newC = curC;
                while(true) {
                    newR += dx[dir], newC += dy[dir];
                    //Out of bounds
                    if (0 > newR || newR >= ROW + 2 || 0 > newC || newC >= COL + 2) 
                        break;

                    //Visited cell
                    if (flood[newR][newC][0] == timeCheck) 
                        break;

                    //This cell is not deleted yet but it has a different character from the character we focused on
                    if (grid[newR][newC] != '$' && grid[newR][newC] != aimCharacter) 
                        break;
                    
                    //This cell is deleted, or this cell is not deleted yet and it has the same character as the character we focused on
                    //We can visit this cell
                    if ((grid[newR][newC] == '$') || (grid[newR][newC] != '$' && grid[newR][newC] == aimCharacter)) {
                        flood[newR][newC][0] = timeCheck;
                        flood[newR][newC][1] = curR;
                        flood[newR][newC][2] = curC;
                        
                        //If this cell is deleted, then we can add this state to current layer
                        //otherwise, we know that a valid move exist (so we can check if the board has some valid moves or not)
                        if (grid[newR][newC] == '$')
                            curQ.push({newR, newC, dir});
                        else
                            *found = true;
                    }

                    //Reach a non-deleted cell
                    if (grid[newR][newC] != '$')
                        break;
                }
            }
        }

        //Move to the next layer
        prevQ.swap(curQ);
    }

    //If we can reach endCell in this attempt, then this move is valid
    return (flood[r2][c2][0] == timeCheck);
}

//Remove(delete) a cell from the board
void board::deleteCell(pair<int, int> cell) {
    grid[cell.first][cell.second] = '$';
}

//Remove(delete) a match from the board
void board::deleteMatch(pair<int, int> startCell, pair<int, int> endCell) {
    deleteCell(startCell);
    deleteCell(endCell);
}

//Check the existence of a valid move
bool board::automatic_check() {
    bool found = false;

    //Start from each non-deleted cell
    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            if (grid[r][c] != '$') {
                //Iterate any other non-deleted cell and check
                for (int other_r = 1; other_r <= ROW; other_r++) {
                    for (int other_c = 1; other_c <= COL; other_c++) {
                        if (grid[other_r][other_c] != '$') {
                            //Exist a valid path between these two
                            if (checkMatch(make_pair(r, c), make_pair(other_r, other_c), false, &found)) {
                                return true;
                            }
                            //or from the start cell to some other cells
                            if (found) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    //No valid move exist
    return false;
}

//To save the board to a text file
//For debug and save/load game
void board::importBoard() {
    ofstream out;
    out.open("board.txt");

    //Size of the board and data of each cell
    out << ROW << ' ' << COL << ' ' << timeCheck << ' ';
    for (int r = 1; r <= ROW; r++) 
        for (int c = 1; c <= COL; c++) 
            out << grid[r][c] << ' ' << flood[r][c][0] << ' ' << flood[r][c][1] << ' ' << flood[r][c][2];

    out.close();
}

//Vector of cells represent the path between two cells
vector<pair<int, int>> board::getPath(pair<int, int> startCell, pair<int, int> endCell) {
    int curR = endCell.first;
    int curC = endCell.second;
    vector<pair<int, int>> result;
    do
    {
        result.emplace_back(curR, curC);
        tie(curR, curC) = make_tuple(flood[curR][curC][1], flood[curR][curC][2]);
    } while (curR != -1 && curC != -1);
    return result;
}