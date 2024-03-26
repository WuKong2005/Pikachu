#pragma once

#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int MAX_PLAYER = 5;

struct record {
    string gamemode;
    bool winGame;
    time_t timeUsed;
    int score;
    tm timeFinished;

    record();
    record(bool __winGame, time_t __timeUsed, int __score);
    string getTimeFinished();
};

//store infomation of the player
struct player {
    string name;
    record resultGame;
    player();
    player(string info, string gamemode);

    void newPlayer(string __name = "");

    string playerInfo();
    void saveScore();
};