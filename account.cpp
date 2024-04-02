#include "account.h"

record::record(int __score, time_t __timePlayed) {
    timePlayed = __timePlayed;
    score = __score - (int)(timePlayed * 0.25);

    time_t currentTime = time(0);
    timeFinished = *localtime(&currentTime);
}

string record::getTimeFinished() {
    stringstream ss;
    ss << setw(2) << setfill('0') << timeFinished.tm_hour << ':';
    ss << setw(2) << setfill('0') << timeFinished.tm_min << ':';
    ss << setw(2) << setfill('0') << timeFinished.tm_sec << '-';
    ss << setw(2) << setfill('0') << timeFinished.tm_wday << '/';
    ss << setw(2) << setfill('0') << (timeFinished.tm_mon + 1) << '/';
    ss << setw(2) << setfill('0') << (timeFinished.tm_year + 1900);

    string result;
    ss >> result;
    return result;
}

account::account() {
    username = "Tam";
    password = "password";
}

string account::accountInfo(record &resultGame) {
    return username + ';' + to_string(resultGame.score) + ';' + to_string(resultGame.timePlayed) + ';' + resultGame.getTimeFinished();
}

int getIndex(char x) {
    if ('0' <= x && x <= '9')
        return (int)x - '0';
    else if ('a' <= x && x <= 'z')
        return 10 + (int)x - 'a';
    else if ('A' <= x && x <= 'Z')
        return 10 + 26 + (int)x - 'A';
    else
        return -1;
}

string encrypt(string password) {
    long long const MOD = 175126384190389;
    int const BASE = 67;

    long long result = 0;
    for (char ch: password) {
        result = (1LL * result * BASE + getIndex(ch) + 1) % MOD;
    }
    return to_string(result);
}