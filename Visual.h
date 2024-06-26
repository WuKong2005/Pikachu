#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <conio.h>
#include "controller.h"
#include "menu.h"

using namespace std;


// COLOR
enum COLOR {
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  BRIGHT_RED,
  BRIGHT_GREEN,
  BRIGHT_YELLOW,
  BRIGHT_BLUE,
  BLACK
};

// enumerate the frontend
enum frontend {
  MAIN_MENU,
  PLAY_GAME,
  GAME_MODE,
  LOAD_GAME,
  USERNAME,
  LEADERBOARD,
  HELP,
  INFORMATION_INGAME
};

// text color default
const string TEXT_BLACK = "\x1B[0m";
// height of block in menu
const int HeightBlock = 3;
// distance between each block of each Visual
const int distanceBlock = 3;

// text color
const string TEXT_COLOR[11] = {
	"\x1B[31m",
	"\x1B[32m", 
	"\x1B[33;1m", 
	"\x1B[34m",
	"\x1b[35m", 
	"\x1B[36m",
	"\x1B[37m", 
	"\x1B[91m", 
	"\x1B[92m", 
	"\x1B[93;1m", 
	"\x1B[94m"
};

// background color
const string BACKGROUND_COLOR[12] = {
	"\x1B[41m", 
	"\x1B[42m", 
	"\x1B[43;1m", 
	"\x1B[44m",
	"\x1b[45m", 
	"\x1B[46m",
	"\x1B[47m", 
	"\x1B[101m", 
	"\x1B[102m", 
	"\x1B[103;1m", 
	"\x1B[104m"
	"\x1B[40m"
};

// coordinate of the first block (upper left corner) of each Visual
const COORD FIRST_BLOCK[5] {
	{64, 19}, // MAIN_MENU
	{64, 19}, // PLAY_GAME
	{64, 19}, // GAME_MODE
	{64, 19}, // LOAD_GAME
	{58, 10} // USERNAME
};



// number of block of each Visual
const int numBlock[5] = {
    4, // MAIN_MENU
    4, // PLAY_GAME
    4, // GAME_MODE
    4, // LOAD_GAME
	2 // USERNAME
};

const int WidthBlock[5] = {
	19, // MAIN_MENU
	19, // PLAY_GAME
	19, // GAME_MODE
	19, // LOAD_GAME
	32 // USERNAME
};

// move the Arrow according to keyboardInput (UP, DOWN, ESC)
void Visual_moveArrow(int visual, int input);

// intro game
void printLogo();

// print Visual
void printMainMenu();
void printPlayGame();
void printGameMode();
void printLoadGame();
void printLeaderboard();
void printHelp();
void printUsername();

void printInfoInGame(short posX, short posY);
void printHelpInGame(short posX, short posY);
void printFrameBlock(int Visual);

// FRONTEND
const string GAME_LOGO[7] = {
// 0
R"(

	    				    _.----.   
	    				_,-'       `.
	    				\      __    \
	    				 \.    \ \   |
	    				   \    \/   /
	    				    \     ,-'
	    				     \    \
	    				      \    \
	    				       \    \
	    				        \_.-'


							PRESS ANY KEY FROM KEYBOARD TO CONTINUE
						MAKE SURE TO SWITCH TO FULL SCREEN BEFORE PLAYING GAME
    )",
    // 1
    R"(

	    				    _.----.
	    				_,-'       `.
	    				\      __    \
	    				 \.    \ \   |  __
	    				   \    \/   /,' _`.
	    				    \     ,-'/  /   \
	    				     \    \ |   \_/  |
	    				      \    \ \      /
	    				       \    \ `.__,'
	    				        \_.-'


							PRESS ANY KEY FROM KEYBOARD TO CONTINUE 
						MAKE SURE TO SWITCH TO FULL SCREEN BEFORE PLAYING GAME
    )",
    // 2
    R"(

	    				    _.----.        ____ 
	    				_,-'       `.     |    |  /`.
	    				\      __    \    '-.  | /   `.
	    				 \.    \ \   |  __  |  |/    ,'
	    				   \    \/   /,' _`.|      ,'
	    				    \     ,-'/  /   \    ,'
	    				     \    \ |   \_/  |   `-.
	    				      \    \ \      /       `-.
	    				       \    \ `.__,'|  |`-._    `|
	    				        \_.-'       |__|    `-._ |
	    				                                `'

							PRESS ANY KEY FROM KEYBOARD TO CONTINUE
						MAKE SURE TO SWITCH TO FULL SCREEN BEFORE PLAYING GAME
    )",
    // 3
    R"(
	    				                                  ,'\
	    				    _.----.        ____         ,'  _\
	    				_,-'       `.     |    |  /`.   \,-'
	    				\      __    \    '-.  | /   `.  ___
	    				 \.    \ \   |  __  |  |/    ,','_  `.
	    				   \    \/   /,' _`.|      ,' / / / /
	    				    \     ,-'/  /   \    ,'   | \/ / ,`.
	    				     \    \ |   \_/  |   `-.  \    `'  /
	    				      \    \ \      /       `-.`.___,-'
	    				       \    \ `.__,'|  |`-._    `|
	    				        \_.-'       |__|    `-._ |
	    				                                `'

							PRESS ANY KEY FROM KEYBOARD TO CONTINUE
						MAKE SURE TO SWITCH TO FULL SCREEN BEFORE PLAYING GAME
    )",
    // 4
    R"(
	    				                                  ,'\
	    				    _.----.        ____         ,'  _\   ___    ___
	    				_,-'       `.     |    |  /`.   \,-'    |   \  /   |
	    				\      __    \    '-.  | /   `.  ___    |    \/    |
	    				 \.    \ \   |  __  |  |/    ,','_  `.  |          |
	    				   \    \/   /,' _`.|      ,' / / / /   |          
	    				    \     ,-'/  /   \    ,'   | \/ / ,`.|        
	    				     \    \ |   \_/  |   `-.  \    `'  /|  |    |
	    				      \    \ \      /       `-.`.___,-' |  |\  /|
	    				       \    \ `.__,'|  |`-._    `|      |__| \/ |
	    				        \_.-'       |__|    `-._ |              '-.|
	    				                                `'

							PRESS ANY KEY FROM KEYBOARD TO CONTINUE
						MAKE SURE TO SWITCH TO FULL SCREEN BEFORE PLAYING GAME
    )",
    // 5
    R"(
	    				                                  ,'\
	    				    _.----.        ____         ,'  _\   ___    ___
	    				_,-'       `.     |    |  /`.   \,-'    |   \  /   |
	    				\      __    \    '-.  | /   `.  ___    |    \/    |
	    				 \.    \ \   |  __  |  |/    ,','_  `.  |          | __
	    				   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.
	    				    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \
	    				     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  |
	    				      \    \ \      /       `-.`.___,-' |  |\  /| \      /
	    				       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'
	    				        \_.-'       |__|    `-._ |              '-.|
	    				                                `'

							PRESS ANY KEY FROM KEYBOARD TO CONTINUE
						MAKE SURE TO SWITCH TO FULL SCREEN BEFORE PLAYING GAME
    )",
    // 6
    R"(
	    				                                  ,'\
	    				    _.----.        ____         ,'  _\   ___    ___     ____
	    				_,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
	    				\      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
	    				 \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
	    				   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
	    				    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
	    				     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
	    				      \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
	    				       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
	    				        \_.-'       |__|    `-._ |              '-.|     '-.| |   |
	    				                                `'                            '-._|

							PRESS ANY KEY FROM KEYBOARD TO CONTINUE
						MAKE SURE TO SWITCH TO FULL SCREEN BEFORE PLAYING GAME
    )",
};


// stored the visual
const string Visual[7] = {
    // MAIN_MENU
    R"(
				    	                                  ,'\
				    	    _.----.        ____         ,'  _\   ___    ___     ____
				    	_,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
				    	\      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
				    	 \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
				    	   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
				    	    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
				    	     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
				    	      \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
				    	       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
				    	        \_.-'       |__|    `-._ |              '-.|     '-.| |   |
				    	                                `'                            '-._|

							A MATCHING GAME BY 
							TRAN CONG MINH & NGUYEN HOANG MINH TAM

	   ⠀⠀⠀⠀⠀⢠⠋⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                             
	   ⠀⠀⠀⠀⠀⡆⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                       ⠸⣷⣦⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⠀⠀⠀
	   ⠀⠀⠀⠀⢠⠁⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠀⠒⣶⣶⡶⠂                           -------------------                           ⠙⣿⡄⠈⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠔⠊⠉⣿⡿⠁⠀⠀⠀
	   ⠀⠀⠀⠀⢸⢀⠠⠔⠒⠒⠒⠒⠂⠤⣀⠤⠒⠉⠀⠀⠀⢀⡠⠟⠉                            |     PLAY GAME     |                           ⠈⠣⡀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠁⠀⠀⣰⠟⠀⠀⠀⣀⣀
	   ⠀⠀⠀⠀⡸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⣀⠠⠐⠊⠁⠀⠀⠀⠀⠀⠀                          -------------------                              ⠈⠢⣄⠀⡈⠒⠊⠉⠁⠀⠈⠉⠑⠚⠀⠀⣀⠔⢊⣠⠤⠒⠊⠉ ⡜
	   ⠀⠀⠀⢀⢃⣖⢢⠀⠀⠀⠀⠀⣠⢤⣄⠀⠈⡄⠀⠀⣀⠠⠄⠀⠒⠒⠀⠇                          -------------------                               ⠀⠀⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⡔⠊⠁⠀⠀⠀⠀⠀⠀⠇
	   ⠀⠀⠀⡜⠈⠛⠛⠀⣐⠂⠀⠀⠻⠿⠏⠀⠀⡗⠊⠁⠀⠀⠀⠀⠀⠀⡜⠀                         |    LEADERBOARD    |                                ⡇⢠⡤⢄⠀⠀⠀⠀⠀⡠⢤⣄⠀⡇⠀⠀⠀⠀⠀⠀⠀⢰⠀ 
	   ⠀⠀⢰⠉⢱⠀⠱⠞⠁⠉⠒⡖⠀⢀⠔⠢⡄⡇⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀                          -------------------                                ⢀⠇⠹⠿⠟⠀⠀⠤⠀⠀⠻⠿⠟⠀⣇⠀⠀⡀⠠⠄⠒⠊⠁⠀
	   ⠀⠀⠀⢶⠊⠀⠀⢣⠀⠀⢠⠃⠀⠘⢄⣀⢾⠃⠀⡤⠤⠤⠤⠤⠔                             -------------------                                ⢸⣿⣿⡆⠀⠰⠤⠖⠦⠴⠀⢀⣶⣿⣿⠀⠙⢄⠀⠀⠀⠀⠀⠀
	   ⠀⠀⠀⠀⢱⢄⠀⠀⠢⠔⠃⠀⠀⠀⠀⢀⢎⢢⠀⠰⡀⠀⠀⠀⠀⠀⠀⠀                         |       HELP!       |                                ⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⠿⡿⠛⢄⠀⠀⠱⣄⠀⠀⠀⠀
	    ⠀⠀⠀⣌⠀⠁⠂⠀⠀⠀⠀⠀⠐⠈⠁⢸⡤⠓⢀⡇⠀⠀⠀⠀⠀⠀⠀                          -------------------                                 ⢸⠈⠓⠦⠀⣀⣀⣀⠀⡠⠴⠊⠹⡞⣁⠤⠒⠉⠀⠀⠀⠀⠀
	   ⣄⡀⠀⣰⢸⠀⠀⠀⠀⢀⢀⠂⠀⠀⠀⠀⠄⢳⡈⢁⡀⠀⠀⠀⠀⠀⠀⠀                          -------------------                                ⣠⠃⠀⠀⠀⠀⡌⠉⠉⡤⠀⠀⠀⠀⢻⠿⠆⠀⠀⠀⠀⠀
	   ⢿⣷⠁⠀⠈⡄⠀⠀⠀⠈⡞⠀⠀⠀⠀⡰⠉⠀⢈⠻⠿⠀⠀⠀⠀⠀⠀⠀                         |     EXIT GAME     |                              ⠰⠁⡀⠀⠀⠀⠀⢸⠀⢰⠃⠀⠀⠀⢠⠀⢣⠀⠀
	   ⡇⠈⡆⠀⠀⠱⡀⠀⠀⠀⡇⠀⠀⠀⢠⠁⠀⠀⠈⢀⠇⠀⠀⠀⠀⠀⠀⠀                          -------------------                             ⢶⣗⠧⡀⢳⠀⠀⠀⠀⢸⣀⣸⠀⠀⠀⢀⡜⠀⣸⢤⣶
	   ⠘⡄⢀⠀⠀⠀⠱⡀⠀⠀⠁⠀⠀⡠⠁⠀⠀⢰⠀⡜⠀⠀⠀⠀⠀⠀⠀⠀                                                                          ⠈⠻⣿⣦⣈⣧⡀⠀⠀⢸⣿⣿⠀⠀⢀⣼⡀⣨⣿⡿⠁
	   ⠀⠈⠉⠉⠉⠀⠐⠛⠶⠒⠣⠦⠤⠗⠒⠒⠒⠚⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                            ⠈⠻⠿⠿⠓⠄⠤⠘⠉⠙⠤⢀⠾⠿⣿⠟⠋
    )",

    // PLAY_GAME 
    R"(
				    	                                  ,'\
				    	    _.----.        ____         ,'  _\   ___    ___     ____
				    	_,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
				    	\      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
				    	 \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
				    	   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
				    	    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
				    	     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
				    	      \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
				    	       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
				    	        \_.-'       |__|    `-._ |              '-.|     '-.| |   |
				    	                                `'                            '-._|

							A MATCHING GAME BY 
							TRAN CONG MINH & NGUYEN HOANG MINH TAM

	   ⠀⠀⠀⠀⠀⢠⠋⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                             
	   ⠀⠀⠀⠀⠀⡆⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                       ⠸⣷⣦⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⠀⠀⠀
	   ⠀⠀⠀⠀⢠⠁⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠀⠒⣶⣶⡶⠂                           -------------------                           ⠙⣿⡄⠈⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠔⠊⠉⣿⡿⠁⠀⠀⠀
	   ⠀⠀⠀⠀⢸⢀⠠⠔⠒⠒⠒⠒⠂⠤⣀⠤⠒⠉⠀⠀⠀⢀⡠⠟⠉                            |     NEW  GAME     |                           ⠈⠣⡀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠁⠀⠀⣰⠟⠀⠀⠀⣀⣀
	   ⠀⠀⠀⠀⡸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⣀⠠⠐⠊⠁⠀⠀⠀⠀⠀⠀                          -------------------                              ⠈⠢⣄⠀⡈⠒⠊⠉⠁⠀⠈⠉⠑⠚⠀⠀⣀⠔⢊⣠⠤⠒⠊⠉ ⡜
	   ⠀⠀⠀⢀⢃⣖⢢⠀⠀⠀⠀⠀⣠⢤⣄⠀⠈⡄⠀⠀⣀⠠⠄⠀⠒⠒⠀⠇                          -------------------                               ⠀⠀⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⡔⠊⠁⠀⠀⠀⠀⠀⠀⠇
	   ⠀⠀⠀⡜⠈⠛⠛⠀⣐⠂⠀⠀⠻⠿⠏⠀⠀⡗⠊⠁⠀⠀⠀⠀⠀⠀⡜⠀                         |     LOAD GAME     |                                ⡇⢠⡤⢄⠀⠀⠀⠀⠀⡠⢤⣄⠀⡇⠀⠀⠀⠀⠀⠀⠀⢰⠀ 
	   ⠀⠀⢰⠉⢱⠀⠱⠞⠁⠉⠒⡖⠀⢀⠔⠢⡄⡇⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀                          -------------------                                ⢀⠇⠹⠿⠟⠀⠀⠤⠀⠀⠻⠿⠟⠀⣇⠀⠀⡀⠠⠄⠒⠊⠁⠀
	   ⠀⠀⠀⢶⠊⠀⠀⢣⠀⠀⢠⠃⠀⠘⢄⣀⢾⠃⠀⡤⠤⠤⠤⠤⠔                             -------------------                                ⢸⣿⣿⡆⠀⠰⠤⠖⠦⠴⠀⢀⣶⣿⣿⠀⠙⢄⠀⠀⠀⠀⠀⠀
	   ⠀⠀⠀⠀⢱⢄⠀⠀⠢⠔⠃⠀⠀⠀⠀⢀⢎⢢⠀⠰⡀⠀⠀⠀⠀⠀⠀⠀                         |       EXTRA       |                                ⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⠿⡿⠛⢄⠀⠀⠱⣄⠀⠀⠀⠀
	    ⠀⠀⠀⣌⠀⠁⠂⠀⠀⠀⠀⠀⠐⠈⠁⢸⡤⠓⢀⡇⠀⠀⠀⠀⠀⠀⠀                          -------------------                                 ⢸⠈⠓⠦⠀⣀⣀⣀⠀⡠⠴⠊⠹⡞⣁⠤⠒⠉⠀⠀⠀⠀⠀
	   ⣄⡀⠀⣰⢸⠀⠀⠀⠀⢀⢀⠂⠀⠀⠀⠀⠄⢳⡈⢁⡀⠀⠀⠀⠀⠀⠀⠀                          -------------------                                ⣠⠃⠀⠀⠀⠀⡌⠉⠉⡤⠀⠀⠀⠀⢻⠿⠆⠀⠀⠀⠀⠀
	   ⢿⣷⠁⠀⠈⡄⠀⠀⠀⠈⡞⠀⠀⠀⠀⡰⠉⠀⢈⠻⠿⠀⠀⠀⠀⠀⠀⠀                         |      GO BACK      |                              ⠰⠁⡀⠀⠀⠀⠀⢸⠀⢰⠃⠀⠀⠀⢠⠀⢣⠀⠀
	   ⡇⠈⡆⠀⠀⠱⡀⠀⠀⠀⡇⠀⠀⠀⢠⠁⠀⠀⠈⢀⠇⠀⠀⠀⠀⠀⠀⠀                          -------------------                             ⢶⣗⠧⡀⢳⠀⠀⠀⠀⢸⣀⣸⠀⠀⠀⢀⡜⠀⣸⢤⣶
	   ⠘⡄⢀⠀⠀⠀⠱⡀⠀⠀⠁⠀⠀⡠⠁⠀⠀⢰⠀⡜⠀⠀⠀⠀⠀⠀⠀⠀                                                                          ⠈⠻⣿⣦⣈⣧⡀⠀⠀⢸⣿⣿⠀⠀⢀⣼⡀⣨⣿⡿⠁
	   ⠀⠈⠉⠉⠉⠀⠐⠛⠶⠒⠣⠦⠤⠗⠒⠒⠒⠚⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                            ⠈⠻⠿⠿⠓⠄⠤⠘⠉⠙⠤⢀⠾⠿⣿⠟⠋
    )",

    //GAME_MODE
    R"(
				    	                                  ,'\
				    	    _.----.        ____         ,'  _\   ___    ___     ____
				    	_,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
				    	\      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
				    	 \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
				    	   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
				    	    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
				    	     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
				    	      \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
				    	       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
				    	        \_.-'       |__|    `-._ |              '-.|     '-.| |   |
				    	                                `'                            '-._|
	
							A MATCHING GAME BY 
							TRAN CONG MINH & NGUYEN HOANG MINH TAM

	   ⠀⠀⠀⠀⠀⢠⠋⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                             
	   ⠀⠀⠀⠀⠀⡆⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                       ⠸⣷⣦⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⠀⠀⠀
	   ⠀⠀⠀⠀⢠⠁⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠀⠒⣶⣶⡶⠂                           -------------------                           ⠙⣿⡄⠈⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠔⠊⠉⣿⡿⠁⠀⠀⠀
	   ⠀⠀⠀⠀⢸⢀⠠⠔⠒⠒⠒⠒⠂⠤⣀⠤⠒⠉⠀⠀⠀⢀⡠⠟⠉                            |       EASY!       |                           ⠈⠣⡀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠁⠀⠀⣰⠟⠀⠀⠀⣀⣀
	   ⠀⠀⠀⠀⡸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⣀⠠⠐⠊⠁⠀⠀⠀⠀⠀⠀                          -------------------                              ⠈⠢⣄⠀⡈⠒⠊⠉⠁⠀⠈⠉⠑⠚⠀⠀⣀⠔⢊⣠⠤⠒⠊⠉ ⡜
	   ⠀⠀⠀⢀⢃⣖⢢⠀⠀⠀⠀⠀⣠⢤⣄⠀⠈⡄⠀⠀⣀⠠⠄⠀⠒⠒⠀⠇                          -------------------                               ⠀⠀⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⡔⠊⠁⠀⠀⠀⠀⠀⠀⠇
	   ⠀⠀⠀⡜⠈⠛⠛⠀⣐⠂⠀⠀⠻⠿⠏⠀⠀⡗⠊⠁⠀⠀⠀⠀⠀⠀⡜⠀                         |      MEDIUM!      |                                ⡇⢠⡤⢄⠀⠀⠀⠀⠀⡠⢤⣄⠀⡇⠀⠀⠀⠀⠀⠀⠀⢰⠀ 
	   ⠀⠀⢰⠉⢱⠀⠱⠞⠁⠉⠒⡖⠀⢀⠔⠢⡄⡇⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀                          -------------------                                ⢀⠇⠹⠿⠟⠀⠀⠤⠀⠀⠻⠿⠟⠀⣇⠀⠀⡀⠠⠄⠒⠊⠁⠀
	   ⠀⠀⠀⢶⠊⠀⠀⢣⠀⠀⢠⠃⠀⠘⢄⣀⢾⠃⠀⡤⠤⠤⠤⠤⠔                             -------------------                                ⢸⣿⣿⡆⠀⠰⠤⠖⠦⠴⠀⢀⣶⣿⣿⠀⠙⢄⠀⠀⠀⠀⠀⠀
	   ⠀⠀⠀⠀⢱⢄⠀⠀⠢⠔⠃⠀⠀⠀⠀⢀⢎⢢⠀⠰⡀⠀⠀⠀⠀⠀⠀⠀                         |       HARD!       |                                ⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⠿⡿⠛⢄⠀⠀⠱⣄⠀⠀⠀⠀
	    ⠀⠀⠀⣌⠀⠁⠂⠀⠀⠀⠀⠀⠐⠈⠁⢸⡤⠓⢀⡇⠀⠀⠀⠀⠀⠀⠀                          -------------------                                 ⢸⠈⠓⠦⠀⣀⣀⣀⠀⡠⠴⠊⠹⡞⣁⠤⠒⠉⠀⠀⠀⠀⠀
	   ⣄⡀⠀⣰⢸⠀⠀⠀⠀⢀⢀⠂⠀⠀⠀⠀⠄⢳⡈⢁⡀⠀⠀⠀⠀⠀⠀⠀                          -------------------                                ⣠⠃⠀⠀⠀⠀⡌⠉⠉⡤⠀⠀⠀⠀⢻⠿⠆⠀⠀⠀⠀⠀
	   ⢿⣷⠁⠀⠈⡄⠀⠀⠀⠈⡞⠀⠀⠀⠀⡰⠉⠀⢈⠻⠿⠀⠀⠀⠀⠀⠀⠀                         |      GO BACK      |                              ⠰⠁⡀⠀⠀⠀⠀⢸⠀⢰⠃⠀⠀⠀⢠⠀⢣⠀⠀
	   ⡇⠈⡆⠀⠀⠱⡀⠀⠀⠀⡇⠀⠀⠀⢠⠁⠀⠀⠈⢀⠇⠀⠀⠀⠀⠀⠀⠀                          -------------------                             ⢶⣗⠧⡀⢳⠀⠀⠀⠀⢸⣀⣸⠀⠀⠀⢀⡜⠀⣸⢤⣶
	   ⠘⡄⢀⠀⠀⠀⠱⡀⠀⠀⠁⠀⠀⡠⠁⠀⠀⢰⠀⡜⠀⠀⠀⠀⠀⠀⠀⠀                                                                          ⠈⠻⣿⣦⣈⣧⡀⠀⠀⢸⣿⣿⠀⠀⢀⣼⡀⣨⣿⡿⠁
	   ⠀⠈⠉⠉⠉⠀⠐⠛⠶⠒⠣⠦⠤⠗⠒⠒⠒⠚⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                            ⠈⠻⠿⠿⠓⠄⠤⠘⠉⠙⠤⢀⠾⠿⣿⠟⠋
    )",

	// LOAD_GAME
    R"(
				    	                                  ,'\
				    	    _.----.        ____         ,'  _\   ___    ___     ____
				    	_,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
				    	\      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
				    	 \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
				    	   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
				    	    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
				    	     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
				    	      \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
				    	       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
				    	        \_.-'       |__|    `-._ |              '-.|     '-.| |   |
				    	                                `'                            '-._|
    
							A MATCHING GAME BY 
							TRAN CONG MINH & NGUYEN HOANG MINH TAM

	   ⠀⠀⠀⠀⠀⢠⠋⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                             
	   ⠀⠀⠀⠀⠀⡆⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                       ⠸⣷⣦⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⠀⠀⠀
	   ⠀⠀⠀⠀⢠⠁⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠀⠒⣶⣶⡶⠂                           -------------------                           ⠙⣿⡄⠈⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠔⠊⠉⣿⡿⠁⠀⠀⠀
	   ⠀⠀⠀⠀⢸⢀⠠⠔⠒⠒⠒⠒⠂⠤⣀⠤⠒⠉⠀⠀⠀⢀⡠⠟⠉                            |    SAVE FILE 0    |                           ⠈⠣⡀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠁⠀⠀⣰⠟⠀⠀⠀⣀⣀
	   ⠀⠀⠀⠀⡸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⣀⠠⠐⠊⠁⠀⠀⠀⠀⠀⠀                          -------------------                              ⠈⠢⣄⠀⡈⠒⠊⠉⠁⠀⠈⠉⠑⠚⠀⠀⣀⠔⢊⣠⠤⠒⠊⠉ ⡜
	   ⠀⠀⠀⢀⢃⣖⢢⠀⠀⠀⠀⠀⣠⢤⣄⠀⠈⡄⠀⠀⣀⠠⠄⠀⠒⠒⠀⠇                          -------------------                               ⠀⠀⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⡔⠊⠁⠀⠀⠀⠀⠀⠀⠇
	   ⠀⠀⠀⡜⠈⠛⠛⠀⣐⠂⠀⠀⠻⠿⠏⠀⠀⡗⠊⠁⠀⠀⠀⠀⠀⠀⡜⠀                         |    SAVE FILE 1    |                                ⡇⢠⡤⢄⠀⠀⠀⠀⠀⡠⢤⣄⠀⡇⠀⠀⠀⠀⠀⠀⠀⢰⠀ 
	   ⠀⠀⢰⠉⢱⠀⠱⠞⠁⠉⠒⡖⠀⢀⠔⠢⡄⡇⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀                          -------------------                                ⢀⠇⠹⠿⠟⠀⠀⠤⠀⠀⠻⠿⠟⠀⣇⠀⠀⡀⠠⠄⠒⠊⠁⠀
	   ⠀⠀⠀⢶⠊⠀⠀⢣⠀⠀⢠⠃⠀⠘⢄⣀⢾⠃⠀⡤⠤⠤⠤⠤⠔                             -------------------                                ⢸⣿⣿⡆⠀⠰⠤⠖⠦⠴⠀⢀⣶⣿⣿⠀⠙⢄⠀⠀⠀⠀⠀⠀
	   ⠀⠀⠀⠀⢱⢄⠀⠀⠢⠔⠃⠀⠀⠀⠀⢀⢎⢢⠀⠰⡀⠀⠀⠀⠀⠀⠀⠀                         |    SAVE FILE 2    |                                ⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⠿⡿⠛⢄⠀⠀⠱⣄⠀⠀⠀⠀
	    ⠀⠀⠀⣌⠀⠁⠂⠀⠀⠀⠀⠀⠐⠈⠁⢸⡤⠓⢀⡇⠀⠀⠀⠀⠀⠀⠀                          -------------------                                 ⢸⠈⠓⠦⠀⣀⣀⣀⠀⡠⠴⠊⠹⡞⣁⠤⠒⠉⠀⠀⠀⠀⠀
	   ⣄⡀⠀⣰⢸⠀⠀⠀⠀⢀⢀⠂⠀⠀⠀⠀⠄⢳⡈⢁⡀⠀⠀⠀⠀⠀⠀⠀                          -------------------                                ⣠⠃⠀⠀⠀⠀⡌⠉⠉⡤⠀⠀⠀⠀⢻⠿⠆⠀⠀⠀⠀⠀
	   ⢿⣷⠁⠀⠈⡄⠀⠀⠀⠈⡞⠀⠀⠀⠀⡰⠉⠀⢈⠻⠿⠀⠀⠀⠀⠀⠀⠀                         |      GO BACK      |                              ⠰⠁⡀⠀⠀⠀⠀⢸⠀⢰⠃⠀⠀⠀⢠⠀⢣⠀⠀
	   ⡇⠈⡆⠀⠀⠱⡀⠀⠀⠀⡇⠀⠀⠀⢠⠁⠀⠀⠈⢀⠇⠀⠀⠀⠀⠀⠀⠀                          -------------------                             ⢶⣗⠧⡀⢳⠀⠀⠀⠀⢸⣀⣸⠀⠀⠀⢀⡜⠀⣸⢤⣶
	   ⠘⡄⢀⠀⠀⠀⠱⡀⠀⠀⠁⠀⠀⡠⠁⠀⠀⢰⠀⡜⠀⠀⠀⠀⠀⠀⠀⠀                                                                          ⠈⠻⣿⣦⣈⣧⡀⠀⠀⢸⣿⣿⠀⠀⢀⣼⡀⣨⣿⡿⠁
	   ⠀⠈⠉⠉⠉⠀⠐⠛⠶⠒⠣⠦⠤⠗⠒⠒⠒⠚⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                            ⠈⠻⠿⠿⠓⠄⠤⠘⠉⠙⠤⢀⠾⠿⣿⠟⠋
    )",

	// USERNAME
    R"(
                    
                    
                    
                    
                    
				        PLEASE ENTER YOUR USERNAME AND PASSWORD (AT LEAST 5 AND AT MOST 30 CHARACTERS)
				                        USERNAME DOES NOT CONTAIN ';' CHARACTER
				                    PASSWORD MUST CONTAIN ONLY ALPHABETS AND DIGITS

				                           --------------------------------
				                USERNAME: |                                |
				                           --------------------------------
				                           --------------------------------
				                PASSWORD: |                                |
				                           -------------------------------- 

				                         IF YOU WANNA GO BACK, PRESS ESC KEY
    )",

	// LEADERBOARD
    R"(
	                                                                                                                                 
	      DIFFICULTY       NO.                  USERNAME                      SCORE          TIME(S)                 DATE             
	                                                                                                                             
	                        1                                                                                                          
	                        2                                                                                                         
	         EASY           3                                                                                                         
	                        4                                                                                                         
	                        5                                                                                                         
	                                                                                                                              
	                        1                                                                                                         
	                        2                                                                                                         
	        MEDIUM          3                                                                                                         
	                        4                                                                                                         
	                        5                                                                                                         
	                                                                                                                              
	                        1                                                                                                         
	                        2                                                                                                         
	         HARD           3                                                                                                         
	                        4                                                                                                         
	                        5                                                                                                         
	                                                                                                                              
	)",

	// HELP
	R"( 		 ----------------------------------------------------------------------------------------------------------
		|                  |          UP:   W, w, up arrow                     LEFT:  A, a, left arrow             |
		|      MOVES:      |                                                                                       |
		|                  |          DOWN: S, s, down arrow                   RIGHT: D, d, right arrow            |
		 ---------------------------------------------------------------------------------------------------------- 
		|                  |          P: Save game                             H: Get hint (move suggestion)       |
		|   SPECIAL KEYS   |                            C: Open Help in game                                       |
		|                  |          M: Toggle music                          G: Magic moves                      |
		 ---------------------------------------------------------------------------------------------------------- 
		|                  |   - There are two types of magic moves: Hidden Cell and Magic Matching                |
		|                  |                                                                                       |
		|                  |	 + Hidden Cell: you are allowed to temporary erase a cell from the board. Once you |
		|                  |       made a move, it will be restored back.                                          |
		|                  |                                                                                       |
		|   MAGIC MOVES    |     + Magic matching: Some certain matching you made now is consider valid, but it is |
		|                  |	   only allowed for you next move.                                                 |
		|                  |                                                                                       |
		|                  |   - In one game, it's allowed only one of the two types of magic moves, and it will   |
		|                  |     be selected RANDOMLY!!. And player can know which type of magic moves at the      |
		|                  |     small board on the right of the main board.                                       |
		|                  |                                                                                       |
		 ---------------------------------------------------------------------------------------------------------- 
		|                  |   - The Matching Game (also known as the Pikachu Puzzle Game) includes a board of     |
		|                  |   mutiple cells, each of which presents a figure.                                     |
		|                  |                                                                                       |
		|      RULES:      |   - The player's task is to finds and matches all pairs of cell that contain the same |
		|                  |   figure and connect each other in some particular pattern (I, L, U, Z).              |
		|                  |                                                                                       |
		|                  |   - A legal match will make the two cells disappear. And the game ends when all the   |
		|                  |   matching pairs are found (the board is empty).                                      |
		 ----------------------------------------------------------------------------------------------------------
		|                  |          - I Matching: +1                         - L Mathching: +2                   |
		|     SCORING:     |          - Z or U Matching: +3                    - Magic matching: +4                |
		|                  |          - Move suggestion: -2                    - Not Matched: -2                   |
		 ----------------------------------------------------------------------------------------------------------
		|                  |                - Tran Cong Minh - 23127007 - 23CLC05 - HCMUS                          |
		|    DEVELOPERS    |                                                                                       |
		|                  |                - Nguyen Hoang Minh Tam - 23127017 - 23CLC05 - HCMUS                   |
		 ----------------------------------------------------------------------------------------------------------

    )"
};