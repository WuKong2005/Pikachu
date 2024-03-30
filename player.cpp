#include "player.h"

record::record() {
    gamemode = "";
    winGame = false;
    timeUsed = 0;
    score = 0;
    timeFinished = tm{};
}

record::record(bool __winGame, time_t __timeUsed, int __score) {
    winGame = __winGame;
    timeUsed = __timeUsed;
    score = __score;

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

player::player() {
    newPlayer();
}

player::player(string info, string gamemode) {
    
}

void player::newPlayer(string __name) {
    name = __name;
    resultGame = record();
}

void player::saveGame(board map) {
    ofstream out;
    out.open("savegame.txt");

    out << name << ' ';
    

    out.close();
}

string player::playerInfo() {
    return name + ';' + to_string(resultGame.timeUsed) + ';' + to_string(resultGame.score) + ';' + resultGame.getTimeFinished();
}

void player::saveScore() {
    if (!resultGame.winGame) {
        return;
    }

    fstream inp;
    inp.open((resultGame.gamemode + ".txt").c_str());
    if (!inp.is_open()) {
        return;
    }

    vector<player> listScore{*this};
    string line;
    while(getline(inp, line, '\n')) {
        listScore.emplace_back(player(line, resultGame.gamemode));
    }
    inp.close();

    sort(listScore.begin(), listScore.end(), [&](player A, player B) {
        return A.resultGame.score > B.resultGame.score;
    });

    if (listScore.size() > MAX_PLAYER) {
        listScore.pop_back();
    }

    ofstream out;
    out.open((resultGame.gamemode + ".txt").c_str());
    for (player __player: listScore) {
        out << __player.playerInfo() << '\n';
    }
    out.close();
}