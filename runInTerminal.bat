@echo off
title Pikachu Matching Game
echo Pikachu is running
g++ main.cpp menu.cpp Visual.cpp controller.cpp game.cpp board.cpp account.cpp game_extra.cpp board_extra.cpp linkedlist_2darray.cpp -o Pikachu.exe -lwinmm -static
echo Done, lets play
Start "" "Pikachu.exe"
