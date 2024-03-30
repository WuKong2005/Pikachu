#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <queue>
#include <array>
#include <iomanip>
#include <assert.h>
#include <numeric>
#include <fstream>

using namespace std;

int const ALPHABET = 26;
//4 vectors represent 4 moves in the board
int const dx[] = {1, 0, -1, 0};
int const dy[] = {0, 1, 0, -1};

int const sizeROW[] = {4, 6, 9};
int const sizeCOL[] = {6, 9, 16};

int ROW, COL;
//Uppercase character
char** grid;
int frequent[ALPHABET]{};
int timeCheck = 0;
array<int, 3>*** flood;

void createGrid();

void initializeGrid();

void shuffleGrid();

void printGrid();

bool validMatch(int r1, int c1, int r2, int c2);

void deleteMatch(int r1, int c1, int r2, int c2);

void freeResource();

void createGrid()
{
    ROW = 9;
    COL = 16;

    grid = new char*[ROW + 2];
    flood = new array<int, 3>**[ROW + 2];

    for (int r = 0; r < ROW + 2; r++) 
    {
        grid[r] = new char[COL + 2]{};
        flood[r] = new array<int, 3>*[COL + 2]{};
        for (int c = 0; c < COL + 2; c++)
            flood[r][c] = new array<int, 3>[2]{};    
    }

    for (int r = 0; r < ROW + 2; r++)
        grid[r][0] = grid[r][COL + 1] = '$';
    for (int c = 0; c < COL + 2; c++)
        grid[0][c] = grid[ROW + 1][c] = '$';
}

void initializeGrid()
{
    int totalCharacter = (ROW * COL) / 2;
    int minimumFrequency = max(totalCharacter / ALPHABET - 1, 0);
    totalCharacter -= minimumFrequency * ALPHABET;
    for (int c = 0; c < ALPHABET - 1; c++)
    {
        frequent[c] = (rand() % totalCharacter);
        totalCharacter -= frequent[c];
        frequent[c] += minimumFrequency;
    }
    frequent[ALPHABET - 1] = totalCharacter + minimumFrequency;

    for (int c = 0; c < ALPHABET; c++)
        frequent[c] <<= 1;

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

    shuffleGrid();
}

void shuffleGrid()
{
    char* arrayGrid = new char[ROW * COL];
    for (int r = 0; r < ROW; r++)
        for (int c = 0; c < COL; c++) 
            arrayGrid[r * COL + c] = grid[r + 1][c + 1];

    random_shuffle(arrayGrid, arrayGrid + ROW * COL);
    for (int r = 0; r < ROW; r++)
        for (int c = 0; c < COL; c++)
            grid[r + 1][c + 1] = arrayGrid[r * COL + c];

    delete [] arrayGrid;
}

void printGrid()
{
    cout << "   " << " |";
    for (int c = 1; c <= COL; c++)
    {
        cout << ' ';
        cout << setw(2) << c << ' ';
        cout << "|";
    }
    cout << '\n';
    for (int c = 1; c <= COL * 5 + 5; c++)
        cout << "-";
    cout << '\n';
    
    for (int r = 1; r <= ROW; r++)
    {
        cout << "  " << r << " |";
        for (int c = 1; c <= COL; c++)
        {
            cout << ' ';
            cout << setw(2) << (grid[r][c] == '$' ? ' ' : grid[r][c]) << ' ';
            cout << "|";
        }
        cout << '\n';
        for (int c = 1; c <= COL * 5 + 5; c++)
            cout << "-";
        cout << '\n';
    }
}

bool validMatch(int r1, int c1, int r2, int c2)
{
    if (r1 == r2 && c1 == c2) return false;
    if (grid[r1][c1] != grid[r2][c2]) return false;
    char C = grid[r1][c1]; 
    ++timeCheck;
    queue<array<int, 4>> prevQ, curQ;
    prevQ.push({r1, c1, 0, -1});
    prevQ.push({r1, c1, 1, -1});

    for (int type = 0; type < 2; type++) {
        flood[r1][c1][type][0] = timeCheck;
        flood[r1][c1][type][1] = -1;
        flood[r1][c1][type][2] = -1;
    }

    for (int numStep = 0; numStep <= 2; numStep++)
    {
        while(!prevQ.empty())
        {
            int r = prevQ.front()[0];
            int c = prevQ.front()[1];
            int type = prevQ.front()[2];
            int d = prevQ.front()[3];
            prevQ.pop();

            for (int dir = 0; dir < 4; dir++)
            {
                if (type == ((dir == 0) || (dir == 2))) 
                    continue;
                
                int newR = r;
                int newC = c;
                bool newType = (dir == 0 || dir == 2); //vertical
                assert(newType ^ type == true);
                while(true)
                {
                    newR += dx[dir], newC += dy[dir];
                    if (0 > newR || newR >= ROW + 2 || 0 > newC || newC >= COL + 2) 
                        break;
                    if (flood[newR][newC][newType][0] == timeCheck) 
                        break;
                    if (grid[newR][newC] != '$' && grid[newR][newC] != C) 
                        break;
                    if (grid[newR][newC] == '$' || (grid[newR][newC] != '$' && grid[newR][newC] == C))
                    {
                        flood[newR][newC][newType][0] = timeCheck;
                        flood[newR][newC][newType][1] = r;
                        flood[newR][newC][newType][2] = c;
                        if (grid[newR][newC] == '$')
                            curQ.push({newR, newC, newType, dir});
                    }
                    if (grid[newR][newC] != '$')
                        break;
                }
            }
        }
        prevQ.swap(curQ);
    }

    return (flood[r2][c2][0][0] == timeCheck || flood[r2][c2][1][0] == timeCheck);
}

void deleteMatch(int r1, int c1, int r2, int c2)
{
    grid[r1][c1] = grid[r2][c2] = '$';
}

vector<pair<int, int>> getPath(int r1, int c1, int r2, int c2) {
    vector<pair<int, int>> result;

    for (int T = 0; T < 2; T++) {
        if (flood[r2][c2][T][0] == timeCheck) {
            vector<pair<int, int>> validPath;
            int curR = r2, curC = c2, type = T;
            do
            {
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

void freeResource()
{
    for (int r = 0; r < ROW + 2; r++) 
    {
        delete [] grid[r];
        delete [] flood[r];
    }
    delete [] grid;
    delete [] flood;
}

void importBoard() {
    ofstream out;
    out.open("board.txt");

    out << ROW << ' ' << COL << ' ' << timeCheck << '\n';
    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            out << grid[r][c] << ' ' << flood[r][c][0][0]  << ' ' << flood[r][c][1][0] << ' ';
        }
    }

    out.close();
}

string* readBoard(string pathSaveFile) {
    ifstream inp;
    inp.open(pathSaveFile.c_str());
    
    //Failed to open saved game 
    if (!inp.is_open()) {
        return NULL;
    }

    //Create a buffer to read the size of board, current timeCheck, all character and relative information of each cell
    //The extra size used to check the valid of input as well
    int maxSize = sizeROW[2] * sizeCOL[2] * 3 + 3 + 1;
    string* buffer = new string[maxSize]{}; 
    int __size = 0;
    while(true) {
        string x;
        inp >> x;
        if (x.empty()) 
            break;

        buffer[__size] = x;
        __size++;
        if (__size == maxSize)
            break;
    }

    cerr << __size << '\n';
    for (int i = 0; i < __size; i++)
        cerr << buffer[i] << ' ';
    cout << '\n';

    auto validNumber = [&](string x) ->bool {
        for (char digit: x) {
            if (digit < '0' || digit > '9') {
                return false;
            }
        }
        return true;
    };

    //Check valid size of board and timeCheck
    if (!validNumber(buffer[0]) || !validNumber(buffer[1]) || !validNumber(buffer[2])) {
        delete [] buffer;
        return NULL;
    }

    int curRow = stoi(buffer[0]), curCol = stoi(buffer[1]), curTimeCheck = stoi(buffer[2]);
    // bool found = false;
    // for (int difficult = 0; difficult < 3; difficult++) 
    //     if (curRow == sizeROW[difficult] && curCol == sizeCOL[difficult]) 
    //         found = true;
    // if (!found) {
    //     delete [] buffer;
    //     return NULL;
    // }
    
    //Check amount of integer read
    if (__size != curRow * curCol * 3 + 3) {
        delete [] buffer;
        return NULL;
    }
    
    // //Check valid information of each cell
    bool valid = true;
    for (int i = 3; i < __size; i += 3) {
        if (buffer[i].size() > 1) valid = false;
        if (buffer[i][0] != '$' && (buffer[i][0] < 'A' || 'Z' < buffer[i][0])) valid = false;
        if (!validNumber(buffer[i + 1])) valid = false;
        else if (stoi(buffer[i + 1]) > curTimeCheck) valid = false;
        if (!validNumber(buffer[i + 2])) valid = false;
        else if (stoi(buffer[i + 2]) > curTimeCheck) valid = false;
    }

    //Return the valid of this saved game
    if (!valid) {
        delete [] buffer;
        return NULL;
    }
    else
        return buffer;
}

void loadBoard(string* &buffer) {
    ROW = stoi(buffer[0]);
    COL = stoi(buffer[1]);
    timeCheck = stoi(buffer[2]);

    cerr << ROW << ' ' << COL << ' ' << timeCheck << '\n';

    grid = new char*[ROW + 2];
    flood = new array<int, 3>**[ROW + 2];

    for (int r = 0; r < ROW + 2; r++) 
    {
        grid[r] = new char[COL + 2]{};
        flood[r] = new array<int, 3>*[COL + 2]{};
        for (int c = 0; c < COL + 2; c++)
            flood[r][c] = new array<int, 3>[2]{};    
    }

    for (int r = 0; r < ROW + 2; r++)
        grid[r][0] = grid[r][COL + 1] = '$';
    for (int c = 0; c < COL + 2; c++)
        grid[0][c] = grid[ROW + 1][c] = '$';
    
    int idBuffer = 3;
    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            cout << buffer[idBuffer] << ' ' << buffer[idBuffer + 1] << '\n';
            grid[r][c] = buffer[idBuffer][0];
            flood[r][c][0][0] = stoi(buffer[idBuffer + 1]);
            flood[r][c][1][0] = stoi(buffer[idBuffer + 2]);
            idBuffer += 3;
            cout << grid[r][c] << ' ' << flood[r][c][0][0] << ' ' << flood[r][c][0][1] << ' ' << flood[r][c][0][2] << ' ' << flood[r][c][1][0] << ' ' << flood[r][c][1][1] << ' ' << flood[r][c][1][2] << '\n';
        }
    }

    delete [] buffer;
}

int getTypePath(vector<pair<int, int>> path) {
    assert(path.size() >= 2);
    if (path.size() <= 3)
        return path.size() - 2;
    else {
        bool type = (path[1].first == path[2].first);
        if (type) {
            //horizontal
            return 2 + ((path[0].first - path[1].first) * (path[3].first - path[2].first) > 0);
        }
        else {
            //vertical
            return 2 + ((path[0].second - path[1].second) * (path[3].second - path[2].second) > 0);
        }
    }
}

int main()
{
    srand(time(NULL));

    // string* buffer = readBoard("board.txt");
    // loadBoard(buffer);
    // printGrid();

    createGrid();

    initializeGrid();

    cout << "\033[2J" << "\033[1;1H";

    printGrid();

    while(true)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        if (r1 == 0 && r2 == 0 && c1 == 0 && c2 == 0) break;

        if (r1 == -1 && r2 == -1 && c1 == -1 && c2 == -1) {
            importBoard();
            continue;
        }
        if (r1 < 1 || r1 > ROW || r2 < 1 || r2 > ROW) continue;
        if (c1 < 1 || c1 > COL || c2 < 1 || c2 > COL) continue;
        bool found = false;
        if (validMatch(r1, c1, r2, c2)) {
            deleteMatch(r1, c1, r2, c2);
            found = true;
        }
        
        //https://student.cs.uwaterloo.ca/~cs452/terminal.html
        cout << "\033[2J" << "\033[1;1H";
        system("cls");
        printGrid();
        if (found) {
            vector<pair<int, int>> path = getPath(r1, c1, r2, c2);
            cout << "path:\n";
            for (auto node: path) {
                cout << node.first << ' ' << node.second << "; ";
            }
            cout << '\n';
            cout << "type: " << getTypePath(path) << '\n';
        }
    }

    freeResource();
}