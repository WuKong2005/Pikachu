#pragma once

#include "header.h";
#include <conio.h>

// COLOR
enum COLOR {
  RED,
  GREEN,
  YELLOW,
  BLUE
};
const string TEXT_BLACK = "\x1B[0m";

// FRONTEND 
string GAME_LOGO[7];
const string MAIN_MENU;
const string PLAY_GAME;
const string GAME_MODE;
const string LEADERBOARD;
const string HELP;

// hide the Cursor in Console
void hideCursor();

struct visual 
{
  void printLogo();
  void printPlayGame();
  void printGameMode();
  void printLeaderBoard();
  void printHelp();
};