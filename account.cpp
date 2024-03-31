#include "account.h"

record::record(int __score, time_t __time) {
    time = __time;
    score = __score - (int)(__time * 0.25);

    time_t currentTime = time(0);
    timeFinished = *localtime(&currentTime);
}

string record::getTimeFinished() {
    string result = "";
    result += timeFinished.tm_hour + ':' + timeFinished.tm_min + ':' + timeFinished.tm_sec;
    result += '-';
    result += timeFinished.tm_wday + '/' + timeFinished.tm_mon + '/' + timeFinished.tm_year;
    return result;
}

account::account() {
    username = "";
    password = "password";
}

string account::accountInfo(record &resultGame) {
    return username + ';' + to_string(resultGame.score) + ';' + to_string(resultGame.time) + ';' + resultGame.getTimeFinished();
}