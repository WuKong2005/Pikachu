#include "board_extra.h"

//Create a board specific for its difficult
board_extra::board_extra(int difficult) {
    ROW = 7;
    COL = 12;
    suggestPair = array<int, 4>{};

    //Add a boundary of the initial board
    //Allowed an efficient and clear implementation
    grid.init2DArray(ROW + 2, COL + 2);
    flood = new array<int, 3>**[ROW + 2];

    for (int r = 0; r < ROW + 2; r++) {
        flood[r] = new array<int, 3>*[COL + 2]{};
        for (int c = 0; c < COL + 2; c++)
            flood[r][c] = new array<int, 3>[2]{};    
    }
}

//Deallocate dynamically memory used
board_extra::~board_extra() {
    if (flood == NULL)
        return;
    for (int r = 0; r < ROW + 2; r++) {
        delete [] flood[r];
        flood[r] = NULL;
    }
    delete [] flood;
    flood = NULL;
}

//Initialize board
void board_extra::initializeBoard() {
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
    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            while(!frequent[lastCharacter])
                lastCharacter++;
            grid[r][c] = char(lastCharacter + 'A');
            --frequent[lastCharacter];
        }
    }

    // And finally shuffle them until we can guarantee a valid move exist
    do {
        shuffleBoard();
    } while(!automaticCheck());
}

//Shuffle the board when needed (no valid move left or player want to do it)
void board_extra::shuffleBoard() {
    //Count number of cells left
    int valid_cell = 0;
    for (int r = 1; r <= ROW; r++) 
        for (int c = 1; c <= COL; c++) 
            valid_cell += (grid[r][c] != '$');
    
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

char board_extra::getChar(pair<int, int> cell) {
    return grid[cell.first][cell.second];
}

void board_extra::assignCell(pair<int, int> cell, char c) {
    grid[cell.first][cell.second] = c;
}

//Check valid move from the player, started from startCell and ended at endCell
//Flag "magic" allow more possible moves
bool board_extra::checkMatch(pair<int, int> startCell, pair<int, int> endCell, bool magic, bool* found) {
    if (startCell == endCell) 
        return false;
    //Assume startCell and endCell are two different cells
    int r1 = startCell.first, c1 = startCell.second;
    int r2 = endCell.first, c2 = endCell.second;

    //If the character from these 2 cells are different then the match is invalid
    if (grid[r1][c1] != grid[r2][c2]) return false;

    //Focus on this character
    char aimCharacter = grid[r1][c1]; 

    //Indicate a new checking attempt
    ++timeCheck;

    //Two queues to store nodes while BFS
    queue<array<int, 4>> prevQ, curQ;
    
    //Add initial nodes to queue and mark it (visited node)
    prevQ.push({r1, c1, 0, -1});
    prevQ.push({r1, c1, 1, -1});
    for (int type = 0; type < 2; type++) {
        flood[r1][c1][type][0] = timeCheck;
        flood[r1][c1][type][1] = -1;
        flood[r1][c1][type][2] = -1;
    }

    for (int numStep = 0; numStep <= 2 + magic; numStep++) {
        while(!prevQ.empty()) {
            //Dequeue a node from previous layer
            //Each node is a state consists of row index, column index of the cell and vector index used to reach that cell
            int curR = prevQ.front()[0];
            int curC = prevQ.front()[1];
            int curType = prevQ.front()[2];
            int curD = prevQ.front()[3];

            prevQ.pop();

            //Iterate all possible moves
            for (int dir = 0; dir < 4; dir++) {
                //Only allowed to visit nodes with direction perpendicular to this state's vector  
                if (curType == ((dir == 0) || (dir == 2))) 
                    continue;
                
                //Start from this cell, keep moving with that direction until certain conditions are satisfied
                int newR = curR;
                int newC = curC;
                bool newType = (dir == 0 || dir == 2); //vertical
                while(true) {
                    newR += dx[dir], newC += dy[dir];
                    //Out of bounds
                    if (0 > newR || newR >= ROW + 2 || 0 > newC || newC >= COL + 2) 
                        break;

                    //Visited cell
                    if (flood[newR][newC][newType][0] == timeCheck) 
                        break;

                    //This cell is not deleted yet but it has a different character from the character we focused on
                    if (grid[newR][newC] != '$' && grid[newR][newC] != aimCharacter) 
                        break;
                    //This cell is deleted, or this cell is not deleted yet and it has the same character as the character we focused on
                    //We can visit this cell
                    if ((grid[newR][newC] == '$') || (grid[newR][newC] != '$' && grid[newR][newC] == aimCharacter)) {
                        flood[newR][newC][newType][0] = timeCheck;
                        flood[newR][newC][newType][1] = curR;
                        flood[newR][newC][newType][2] = curC;
                        
                        //If this cell is deleted, then we can add this state to current layer
                        //otherwise, we know that a valid move exist (so we can check if the board has some valid moves or not)
                        if (grid[newR][newC] == '$')
                            curQ.push({newR, newC, newType, dir});
                        else {
                            if (found != NULL)
                                *found = true;
                            //A valid move exist
                            suggestPair = {r1, c1, newR, newC};
                        }
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
    return (flood[r2][c2][0][0] == timeCheck || flood[r2][c2][1][0] == timeCheck);
}

//Vector of cells represent the path between two cells
vector<pair<int, int>> board_extra::getPath(pair<int, int> startCell, pair<int, int> endCell) {
    int endR = endCell.first;
    int endC = endCell.second;
    vector<pair<int, int>> result;

    for (int T = 0; T < 2; T++) {
        if (flood[endR][endC][T][0] == timeCheck) {
            vector<pair<int, int>> validPath;
            int curR = endR, curC = endC, type = T;
            do {
                validPath.emplace_back(curR, curC);
                tie(curR, curC, type) = make_tuple(flood[curR][curC][type][1], flood[curR][curC][type][2], type ^ 1);
            } while (curR != -1 && curC != -1);
            if (result.empty() || (result.size() > validPath.size()))
                result = validPath;
        }
    }

    // cerr << result.size() << '\n';
    return result;
}

//Determine the type of path between two cells
int board_extra::getTypePath(vector<pair<int, int>> path) {
    assert(path.size() >= 2);
    //5 cells <=> MAGIC MATCHING
    if (path.size() == 5) {
        return MAGIC_MATCHING;
    }
    //2 cells <=> I matching, 3 cells <=> L matching
    if (path.size() <= 3)
        return path.size() - 2;
    else {
        //4 cells <=> Z matching or U matching
        //3 segments and the middle segment is perpendicular to the first and last segment 
        bool type = (path[1].first == path[2].first);
        if (type) {
            //The middle segment is a horizontal segment
            //The row index of the start cell and last cell are both in one side of the middle segment <=> U matching
            //otherwise, Z matching
            return 2 + ((path[0].first - path[1].first) * (path[3].first - path[2].first) > 0);
        }
        else {
            //The middle segment is a vertical segment
            //Similar to the horizontal case
            return 2 + ((path[0].second - path[1].second) * (path[3].second - path[2].second) > 0);
        }
    }
}

//Remove(delete) a cell from the board
void board_extra::deleteCell(pair<int, int> cell) {
    grid[cell.first][cell.second] = '$';
    // removeCell(cell);
}

//Remove(delete) a match from the board
void board_extra::deleteMatch(pair<int, int> startCell, pair<int, int> endCell) {
    if (startCell.first != endCell.first) {
        grid[startCell.first].deleteNode(startCell.second);
        grid[startCell.first].addEnd('$');

        grid[endCell.first].deleteNode(endCell.second);
        grid[endCell.first].addEnd('$');
    }
    else {
        if (startCell.second > endCell.second) 
            swap(startCell, endCell);
        grid[startCell.first].deleteNode(endCell.second);
        grid[startCell.first].deleteNode(startCell.second);
        grid[endCell.first].addEnd('$');
        grid[endCell.first].addEnd('$');
    }
}

//Check the existence of a valid move
bool board_extra::automaticCheck() {
    bool found = false;
    suggestPair = {-1, -1, -1, -1};

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
                                assert(found);
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
    assert(suggestPair[0] == -1);
    return false;
}

//Store possible move while execute the automaticCheck()
//And return array of -1 if no valid move exists
array<int, 4> board_extra::suggestMove() {
    return suggestPair;
}