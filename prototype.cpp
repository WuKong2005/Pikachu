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

int ROW, COL;
//Uppercase character
char** grid;
bool** deleted;
int frequent[ALPHABET]{};
int timeCheck = 0;
array<int, 3>** flood;

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
    deleted = new bool*[ROW + 2];
    flood = new array<int, 3>*[ROW + 2];

    for (int r = 0; r < ROW + 2; r++) 
    {
        grid[r] = new char[COL + 2]{};
        deleted[r] = new bool[COL + 2]{};
        flood[r] = new array<int, 3>[COL + 2]{};    
    }

    for (int r = 0; r < ROW + 2; r++)
        deleted[r][0] = deleted[r][COL + 1] = true;
    for (int c = 0; c < COL + 2; c++)
        deleted[0][c] = deleted[ROW + 1][c] = true;
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
            cout << setw(2) << (deleted[r][c] ? ' ' : grid[r][c]) << ' ';
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
    queue<array<int, 3>> prevQ, curQ;
    prevQ.push({r1, c1, -1});

    flood[r1][c1][0] = timeCheck;
    flood[r1][c1][1] = -1;
    flood[r1][c1][2] = -1;

    for (int numStep = 0; numStep <= 2; numStep++)
    {
        while(!prevQ.empty())
        {
            auto &[r, c, d] = prevQ.front();
            prevQ.pop();

            for (int dir = 0; dir < 4; dir++)
            {
                if (d != -1)
                {
                    if (dir == d) continue;
                    if (abs(dir - d) == 2) continue;
                }
                
                int newR = r;
                int newC = c;
                while(true)
                {
                    newR += dx[dir], newC += dy[dir];
                    if (0 > newR || newR >= ROW + 2 || 0 > newC || newC >= COL + 2) 
                        break;
                    if (flood[newR][newC][0] == timeCheck) 
                        break;
                    if (!deleted[newR][newC] && grid[newR][newC] != C) 
                        break;
                    if (deleted[newR][newC] || (!deleted[newR][newC] && grid[newR][newC] == C))
                    {
                        flood[newR][newC][0] = timeCheck;
                        flood[newR][newC][1] = r;
                        flood[newR][newC][2] = c;
                        if (deleted[newR][newC])
                            curQ.push({newR, newC, dir});
                    }
                    if (!deleted[newR][newC])
                        break;
                }
            }
        }
        prevQ.swap(curQ);
    }

    return (flood[r2][c2][0] == timeCheck);
}

void deleteMatch(int r1, int c1, int r2, int c2)
{
    deleted[r1][c1] = deleted[r2][c2] = true;
}

vector<pair<int, int>> getPath(int r1, int c1, int r2, int c2) {
    int curR = r2, curC = c2;
    vector<pair<int, int>> result;
    do
    {
        result.emplace_back(curR, curC);
        tie(curR, curC) = make_tuple(flood[curR][curC][1], flood[curR][curC][2]);
    } while (curR != -1 && curC != -1);
    return result;
}

void freeResource()
{
    for (int r = 0; r < ROW + 2; r++) 
    {
        delete [] grid[r];
        delete [] deleted[r];
        delete [] flood[r];
    }
    delete [] grid;
    delete [] deleted;
    delete [] flood;
}

void importBoard() {
    ofstream out;
    out.open("board.txt");

    out << ROW << ' ' << COL << '\n';
    for (int r = 1; r <= ROW; r++) {
        for (int c = 1; c <= COL; c++) {
            out << grid[r][c] << ' ' << flood[r][c][0] << ' ' << flood[r][c][1] << ' ' << flood[r][c][2] << ' ';
        }
    }

    out.close();
}

int main()
{
    srand(time(NULL));

    createGrid();

    initializeGrid();

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
        printGrid();
        if (found) {
            vector<pair<int, int>> path = getPath(r1, c1, r2, c2);
            cout << "path:\n";
            for (auto node: path) {
                cout << node.first << ' ' << node.second << "; ";
            }
            cout << '\n';
        }
    }

    freeResource();
}