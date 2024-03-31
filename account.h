#pragma once

#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include "board.h"

using namespace std;

int const MAX_PLAYER = 5;

struct record {
    int score;
    time_t time;
    tm timeFinished;

    record(int __score = 0, time_t __time = 0);
    string getTimeFinished();
};

//store infomation of the player account
struct account {
    string username;
    string password;

    account();
    string accountInfo(record &resultGame);
};