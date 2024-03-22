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

// FRONTEND 
string GAME_LOGO[7];
const string MAIN_MENU;
const string INSIDE_PLAY_GAME;
const string INSIDE_NEW_GAME;

// hide the Cursor in Console
void hideCursor();

struct visual 
{
  void printLogo();
};