#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <vector>
#include <conio.h>

using namespace std;

// Arrow
const string arrow = ">>>";

// COLOR
enum COLOR {
  RED,
  GREEN,
  YELLOW,
  BLUE
};
const string TEXT_BLACK = "\x1B[0m";
const string TEXT_COLOR[4] = {"\x1B[31m", "\x1B[32m", "\x1B[33;1m", "\x1B[34m"};

// enumerate the frontend
enum frontend {
  MAIN_MENU,
  PLAY_GAME,
  GAME_MODE,
  LOAD_GAME,
  USERNAME,
  LEADERBOARD,
  HELP
};

// hide the Cursor in Console
void hideCursor();

void showCursor();

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
   ⠀⠀⠀⢀⢃⣖⢢⠀⠀⠀⠀⠀⣠⢤⣄⠀⠈⡄⠀⠀⣀⠠⠄⠀⠒⠒⠀⠇                                                                            ⠀⠀⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⡔⠊⠁⠀⠀⠀⠀⠀⠀⠇
   ⠀⠀⠀⡜⠈⠛⠛⠀⣐⠂⠀⠀⠻⠿⠏⠀⠀⡗⠊⠁⠀⠀⠀⠀⠀⠀⡜⠀                          -------------------                                 ⡇⢠⡤⢄⠀⠀⠀⠀⠀⡠⢤⣄⠀⡇⠀⠀⠀⠀⠀⠀⠀⢰⠀ 
   ⠀⠀⢰⠉⢱⠀⠱⠞⠁⠉⠒⡖⠀⢀⠔⠢⡄⡇⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀                         |     LOAD GAME     |                               ⢀⠇⠹⠿⠟⠀⠀⠤⠀⠀⠻⠿⠟⠀⣇⠀⠀⡀⠠⠄⠒⠊⠁⠀
   ⠀⠀⠀⢶⠊⠀⠀⢣⠀⠀⢠⠃⠀⠘⢄⣀⢾⠃⠀⡤⠤⠤⠤⠤⠔                             -------------------                                ⢸⣿⣿⡆⠀⠰⠤⠖⠦⠴⠀⢀⣶⣿⣿⠀⠙⢄⠀⠀⠀⠀⠀⠀
   ⠀⠀⠀⠀⢱⢄⠀⠀⠢⠔⠃⠀⠀⠀⠀⢀⢎⢢⠀⠰⡀⠀⠀⠀⠀⠀⠀⠀                                                                              ⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⠿⡿⠛⢄⠀⠀⠱⣄⠀⠀⠀⠀
    ⠀⠀⠀⣌⠀⠁⠂⠀⠀⠀⠀⠀⠐⠈⠁⢸⡤⠓⢀⡇⠀⠀⠀⠀⠀⠀⠀                          -------------------                                 ⢸⠈⠓⠦⠀⣀⣀⣀⠀⡠⠴⠊⠹⡞⣁⠤⠒⠉⠀⠀⠀⠀⠀
   ⣄⡀⠀⣰⢸⠀⠀⠀⠀⢀⢀⠂⠀⠀⠀⠀⠄⢳⡈⢁⡀⠀⠀⠀⠀⠀⠀⠀                         |      GO BACK      |                               ⣠⠃⠀⠀⠀⠀⡌⠉⠉⡤⠀⠀⠀⠀⢻⠿⠆⠀⠀⠀⠀⠀
   ⢿⣷⠁⠀⠈⡄⠀⠀⠀⠈⡞⠀⠀⠀⠀⡰⠉⠀⢈⠻⠿⠀⠀⠀⠀⠀⠀⠀                          -------------------                               ⠰⠁⡀⠀⠀⠀⠀⢸⠀⢰⠃⠀⠀⠀⢠⠀⢣⠀⠀
   ⡇⠈⡆⠀⠀⠱⡀⠀⠀⠀⡇⠀⠀⠀⢠⠁⠀⠀⠈⢀⠇⠀⠀⠀⠀⠀⠀⠀                                                                          ⢶⣗⠧⡀⢳⠀⠀⠀⠀⢸⣀⣸⠀⠀⠀⢀⡜⠀⣸⢤⣶
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
   ⠀⠀⠀⠀⢸⢀⠠⠔⠒⠒⠒⠒⠂⠤⣀⠤⠒⠉⠀⠀⠀⢀⡠⠟⠉                            |    SAVE FILE 1    |                           ⠈⠣⡀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠁⠀⠀⣰⠟⠀⠀⠀⣀⣀
   ⠀⠀⠀⠀⡸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⣀⠠⠐⠊⠁⠀⠀⠀⠀⠀⠀                          -------------------                              ⠈⠢⣄⠀⡈⠒⠊⠉⠁⠀⠈⠉⠑⠚⠀⠀⣀⠔⢊⣠⠤⠒⠊⠉ ⡜
   ⠀⠀⠀⢀⢃⣖⢢⠀⠀⠀⠀⠀⣠⢤⣄⠀⠈⡄⠀⠀⣀⠠⠄⠀⠒⠒⠀⠇                          -------------------                               ⠀⠀⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⡔⠊⠁⠀⠀⠀⠀⠀⠀⠇
   ⠀⠀⠀⡜⠈⠛⠛⠀⣐⠂⠀⠀⠻⠿⠏⠀⠀⡗⠊⠁⠀⠀⠀⠀⠀⠀⡜⠀                         |    SAVE FILE 2    |                                ⡇⢠⡤⢄⠀⠀⠀⠀⠀⡠⢤⣄⠀⡇⠀⠀⠀⠀⠀⠀⠀⢰⠀ 
   ⠀⠀⢰⠉⢱⠀⠱⠞⠁⠉⠒⡖⠀⢀⠔⠢⡄⡇⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀                          -------------------                                ⢀⠇⠹⠿⠟⠀⠀⠤⠀⠀⠻⠿⠟⠀⣇⠀⠀⡀⠠⠄⠒⠊⠁⠀
   ⠀⠀⠀⢶⠊⠀⠀⢣⠀⠀⢠⠃⠀⠘⢄⣀⢾⠃⠀⡤⠤⠤⠤⠤⠔                             -------------------                                ⢸⣿⣿⡆⠀⠰⠤⠖⠦⠴⠀⢀⣶⣿⣿⠀⠙⢄⠀⠀⠀⠀⠀⠀
   ⠀⠀⠀⠀⢱⢄⠀⠀⠢⠔⠃⠀⠀⠀⠀⢀⢎⢢⠀⠰⡀⠀⠀⠀⠀⠀⠀⠀                         |    SAVE FILE 3    |                                ⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⠿⡿⠛⢄⠀⠀⠱⣄⠀⠀⠀⠀
    ⠀⠀⠀⣌⠀⠁⠂⠀⠀⠀⠀⠀⠐⠈⠁⢸⡤⠓⢀⡇⠀⠀⠀⠀⠀⠀⠀                          -------------------                                 ⢸⠈⠓⠦⠀⣀⣀⣀⠀⡠⠴⠊⠹⡞⣁⠤⠒⠉⠀⠀⠀⠀⠀
   ⣄⡀⠀⣰⢸⠀⠀⠀⠀⢀⢀⠂⠀⠀⠀⠀⠄⢳⡈⢁⡀⠀⠀⠀⠀⠀⠀⠀                          -------------------                                ⣠⠃⠀⠀⠀⠀⡌⠉⠉⡤⠀⠀⠀⠀⢻⠿⠆⠀⠀⠀⠀⠀
   ⢿⣷⠁⠀⠈⡄⠀⠀⠀⠈⡞⠀⠀⠀⠀⡰⠉⠀⢈⠻⠿⠀⠀⠀⠀⠀⠀⠀                         |      GO BACK      |                              ⠰⠁⡀⠀⠀⠀⠀⢸⠀⢰⠃⠀⠀⠀⢠⠀⢣⠀⠀
   ⡇⠈⡆⠀⠀⠱⡀⠀⠀⠀⡇⠀⠀⠀⢠⠁⠀⠀⠈⢀⠇⠀⠀⠀⠀⠀⠀⠀                          -------------------                             ⢶⣗⠧⡀⢳⠀⠀⠀⠀⢸⣀⣸⠀⠀⠀⢀⡜⠀⣸⢤⣶
   ⠘⡄⢀⠀⠀⠀⠱⡀⠀⠀⠁⠀⠀⡠⠁⠀⠀⢰⠀⡜⠀⠀⠀⠀⠀⠀⠀⠀                                                                          ⠈⠻⣿⣦⣈⣧⡀⠀⠀⢸⣿⣿⠀⠀⢀⣼⡀⣨⣿⡿⠁
   ⠀⠈⠉⠉⠉⠀⠐⠛⠶⠒⠣⠦⠤⠗⠒⠒⠒⠚⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                                            ⠈⠻⠿⠿⠓⠄⠤⠘⠉⠙⠤⢀⠾⠿⣿⠟⠋
    )",

	// USERNAME
    R"(
                    
                    
                    
                    
                    
                    PLEASE ENTER YOUR USERNAME (AT LEAST 5 AND AT MOST 30 CHARACTERS)

                                   --------------------------------
                        USERNAME: |                                |
                                   -------------------------------- 

                                IF YOU WANNA GO BACK, PRESS ESC KEY
    )",

	// LEADERBOARD
    R"(
	 -------------------- ----- ---------------------------------------- --------------- --------------- ----------------------------
	|     DIFFICULTY     | NO. |                USERNAME                |    TIME(s)    |     SCORE     |            DATE            |
	 -------------------- ----- ---------------------------------------- --------------- --------------- ----------------------------
	|                    |  1  |                                        |               |               |                            | 
	|                    |  2  |                                        |               |               |                            |
	|        EASY        |  3  |                                        |               |               |                            |
	|                    |  4  |                                        |               |               |                            |
	|                    |  5  |                                        |               |               |                            |
	 -------------------- ----- ---------------------------------------- --------------- --------------- ----------------------------
	|                    |  1  |                                        |               |               |                            |
	|                    |  2  |                                        |               |               |                            |
	|       MEDIUM       |  3  |                                        |               |               |                            |
	|                    |  4  |                                        |               |               |                            |
	|                    |  5  |                                        |               |               |                            |
	 -------------------- ----- ---------------------------------------- --------------- --------------- ----------------------------
	|                    |  1  |                                        |               |               |                            |
	|                    |  2  |                                        |               |               |                            |
	|        HARD        |  3  |                                        |               |               |                            |
	|                    |  4  |                                        |               |               |                            |
	|                    |  5  |                                        |               |               |                            |
	 -------------------- ----- ---------------------------------------- --------------- --------------- ----------------------------
	)",

	// HELP
	R"(
		 ----------------------------------------------------------------------------------------------------------
		|                  |          UP:   W, w, up arrow                     LEFT:  A, a, left arrow             |
		|      MOVES:      |                                                                                       |
		|                  |          DOWN: S, s, down arrow                   RIGHT: D, d, right arrow            |
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
		|                  |                                                                                       |
		|     SCORING:     |                                                                                       |
		|                  |                                                                                       |
		----------------------------------------------------------------------------------------------------------
		|                  |                - Tran Cong Minh - 23127007 - 23CLC05 - HCMUS                          |
		|    DEVELOPERS    |                                                                                       |
		|                  |                - Nguyen Hoang Minh Tam - 23127017 - 23CLC05 - HCMUS                   |
		----------------------------------------------------------------------------------------------------------

							PRESS ANY KEY TO GO BACK ! 
    )"
};