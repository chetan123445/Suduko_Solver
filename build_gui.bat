@echo off
g++ src/sudoku_gui.cpp -o sudoku_gui.exe -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra -std=c++17
echo Build complete. Run sudoku_gui.exe to start.
