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
  LOAD_GAME,
  LEADERBOARD,
  HELP
};

const string Visual[6];


// hide the Cursor in Console
void hideCursor();

// intro game
void printLogo();

// print Visual
void printMainMenu();
void printPlayGame();
void printGameMode();
void printLoadGame();
void printLeaderboard();
void printHelp();