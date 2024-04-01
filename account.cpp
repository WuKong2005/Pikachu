#include "account.h"

record::record(int __score, time_t __timePlayed) {
    timePlayed = __timePlayed;
    score = __score - (int)(timePlayed * 0.25);

    time_t currentTime = time(0);
    timeFinished = *localtime(&currentTime);
}

string record::getTimeFinished() {
    string result = "";
    result += to_string(timeFinished.tm_hour) + ':' + to_string(timeFinished.tm_min) + ':' + to_string(timeFinished.tm_sec);
    result += '-';
    result += to_string(timeFinished.tm_wday) + '/' + to_string(timeFinished.tm_mon + 1) + '/' + to_string(timeFinished.tm_year + 1900);
    return result;
}

account::account() {
    username = "Tam";
    password = "password";
}

string account::accountInfo(record &resultGame) {
    return username + ';' + to_string(resultGame.score) + ';' + to_string(resultGame.timePlayed) + ';' + resultGame.getTimeFinished();
}