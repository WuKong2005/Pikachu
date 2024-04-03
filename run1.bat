@echo off
title Pikachu Matching Game
echo Pikachu is running
g++ main.cpp menu.cpp Visual.cpp controller.cpp game.cpp board.cpp account.cpp -o pikachu1.exe -lwinmm -static
echo Done, lets play
Start "" "Pikachu.exe"
