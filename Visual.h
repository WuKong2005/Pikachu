#pragma once

#include "header.h"
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
const string GAME_LOGO[7];

enum frontend {
  MAIN_MENU,
  PLAY_GAME,
  GAME_MODE,
  LEADERBOARD,
  HELP
};

const string Visual[5];



// hide the Cursor in Console
void hideCursor();

void printLogo();
void printPlayGame();
void printGameMode();
void printLeaderBoard();
void printHelp();