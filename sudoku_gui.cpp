#include "raylib.h"
#include <vector>
#include <string>

#define N 9

// --- Core Sudoku Solver Logic ---

/* Checks if it's safe to place a number in a given row, col */
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if 'num' is not in current row, current column and current 3x3 subgrid
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

/* A recursive backtracking function to solve Sudoku */
bool solveSudoku(int grid[N][N], int row, int col) {
    // If we have reached the 8th row and 9th column (0-indexed), we are done
    if (row == N - 1 && col == N) {
        return true;
    }

    // If column value becomes 9, we move to next row and column start from 0
    if (col == N) {
        row++;
        col = 0;
    }

    // If the current position of the grid already contains value > 0, we iterate for next column
    if (grid[row][col] > 0) {
        return solveSudoku(grid, row, col + 1);
    }

    for (int num = 1; num <= N; num++) {
        // Check if it is safe to place the num (1-9) in the given row, col
        if (isSafe(grid, row, col, num)) {
            // Assigning the num in the current (row, col) position of the grid
            grid[row][col] = num;

            // Checking for next possibility with next column
            if (solveSudoku(grid, row, col + 1)) {
                return true;
            }
        }

        // Removing the assigned num, since our assumption was wrong, and we go for next assumption
        grid[row][col] = 0;
    }
    return false;
}

// --- GUI Helper for Visualization ---

// Helper to compare raylib Color structs since they don't have a built-in == operator
bool CompareColors(Color c1, Color c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

void DrawVisualizationStep(int grid[N][N], int highlightRow, int highlightCol, Color highlightColor, const char* message) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw Grid and numbers
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            DrawRectangleLines(j * 60, i * 60, 60, 60, LIGHTGRAY);
            if (grid[i][j] != 0) {
                // Highlight the currently changing cell
                Color textColor = (i == highlightRow && j == highlightCol) ? highlightColor : BLACK;
                DrawText(TextFormat("%d", grid[i][j]), j * 60 + 20, i * 60 + 10, 40, textColor);
            }
        }
    }
    // Draw thicker lines for 3x3 subgrids
    for (int i = 0; i <= N; i += 3) {
        DrawLineEx((Vector2){0, (float)i * 60}, (Vector2){540, (float)i * 60}, 4, BLACK);
        DrawLineEx((Vector2){(float)i * 60, 0}, (Vector2){(float)i * 60, 540}, 4, BLACK);
    }

    // Highlight the backtracking cell with a transparent rectangle
    if (CompareColors(highlightColor, RED)) DrawRectangle(highlightCol * 60, highlightRow * 60, 60, 60, ColorAlpha(RED, 0.3f));

    DrawText(message, 10, 550, 20, DARKGRAY);
    DrawText("Press ESC to stop", 550, 550, 20, DARKGRAY);
    EndDrawing();
}

/* A recursive backtracking function to visualize solving Sudoku */
bool solveSudokuVisualize(int grid[N][N], int row, int col, bool* shouldStop) {
    // Base case: If we are done
    if (row == N - 1 && col == N) {
        return true;
    }

    // If column value becomes 9, move to next row
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip already filled cells
    if (grid[row][col] > 0) return solveSudokuVisualize(grid, row, col + 1, shouldStop);

    for (int num = 1; num <= N; num++) {
        // Check for user interruption before trying a new number
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
            *shouldStop = true;
            return false;
        }

        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // --- Visualization ---
            DrawVisualizationStep(grid, row, col, BLUE, "Trying new number...");
            WaitTime(1.0); // Wait for 1 second
            // --- End Visualization ---

            if (solveSudokuVisualize(grid, row, col + 1, shouldStop)) {
                return true;
            }

            // If the recursion was stopped by the user, propagate the stop signal up
            if (*shouldStop) return false;

            grid[row][col] = 0; // Backtrack

            // --- Visualization of backtracking ---
            DrawVisualizationStep(grid, row, col, RED, "Backtracking...");
            WaitTime(1.0); // Wait for 1 second
            // --- End Visualization ---
        }
    }
    return false;
}

// --- GUI Functions ---

void DrawSudokuGrid(int grid[N][N], int initialGrid[N][N], int selectedRow, int selectedCol) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Rectangle cell = { (float)j * 60, (float)i * 60, 60, 60 };
            DrawRectangleLinesEx(cell, 1, LIGHTGRAY);

            if (i == selectedRow && j == selectedCol) {
                DrawRectangleRec(cell, ColorAlpha(SKYBLUE, 0.5f));
            }

            if (grid[i][j] != 0) {
                Color textColor = (initialGrid[i][j] != 0) ? GRAY : BLACK;
                DrawText(TextFormat("%d", grid[i][j]), j * 60 + 20, i * 60 + 10, 40, textColor);
            }
        }
    }

    for (int i = 0; i <= N; i += 3) {
        DrawLineEx((Vector2){0, (float)i * 60}, (Vector2){540, (float)i * 60}, 4, BLACK);
        DrawLineEx((Vector2){(float)i * 60, 0}, (Vector2){(float)i * 60, 540}, 4, BLACK);
    }
}

void DrawUI(const char* status) {
    DrawRectangle(550, 20, 230, 40, LIME);
    DrawText("Solve Instantly", 585, 30, 20, DARKGREEN);

    DrawRectangle(550, 70, 230, 40, SKYBLUE);
    DrawText("Visualize Steps", 580, 80, 20, DARKBLUE);

    DrawRectangle(550, 140, 230, 40, ORANGE);
    DrawText("Lock Puzzle", 600, 150, 20, MAROON);

    DrawRectangle(550, 190, 230, 40, PINK);
    DrawText("Clear Grid", 605, 200, 20, MAROON);

    DrawRectangle(550, 240, 230, 40, RED);
    DrawText("Reset to Default", 575, 250, 20, MAROON);

    DrawText("Status:", 550, 300, 20, DARKGRAY);
    DrawText(status, 550, 330, 20, DARKGRAY);

    DrawText("INSTRUCTIONS:", 550, 380, 20, DARKGRAY);
    DrawText("- Click a cell to select.", 550, 410, 15, GRAY);
    DrawText("- Press 1-9 to set value.", 550, 430, 15, GRAY);
    DrawText("- Press 0, DEL, or", 550, 450, 15, GRAY);
    DrawText("  BACKSPACE to clear.", 550, 470, 15, GRAY);
    DrawText("- 'Lock Puzzle' to set your", 550, 490, 15, GRAY);
    DrawText("  board for solving.", 550, 510, 15, GRAY);
}


int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Sudoku Solver");
    SetExitKey(KEY_NULL); // Allow ESC to be used for stopping visualization

    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // This grid stores the original puzzle for the "Reset" button
    int defaultGrid[N][N];
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) defaultGrid[i][j] = grid[i][j];

    int initialGrid[N][N];
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) initialGrid[i][j] = grid[i][j];

    int selectedRow = -1;
    int selectedCol = -1;
    const char* statusMessage = "Ready. Enter your puzzle.";

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // --- Update ---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int r = mousePos.y / 60;
            int c = mousePos.x / 60;

            if (r < N && c < N) {
                selectedRow = r;
                selectedCol = c;
            } else {
                // Check button clicks
                Rectangle solveButton = {550, 20, 230, 40};
                Rectangle visualizeButton = {550, 70, 230, 40};
                Rectangle lockButton = {550, 140, 230, 40};
                Rectangle clearButton = {550, 190, 230, 40};
                Rectangle resetButton = {550, 240, 230, 40};

                if (CheckCollisionPointRec(mousePos, solveButton)) {
                    if (solveSudoku(grid, 0, 0)) {
                        statusMessage = "Solved successfully!";
                    } else {
                        statusMessage = "No solution exists.";
                    }
                    selectedRow = -1; // Deselect cell
                    selectedCol = -1;
                } else if (CheckCollisionPointRec(mousePos, visualizeButton)) {
                    // Make a copy to visualize on, so we can reset to original if needed
                    int tempGrid[N][N];
                    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) tempGrid[i][j] = grid[i][j];
                    
                    bool visualizationStopped = false;
                    if (solveSudokuVisualize(tempGrid, 0, 0, &visualizationStopped)) {
                         for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) grid[i][j] = tempGrid[i][j];
                        statusMessage = "Visualization complete!";
                    } else if (visualizationStopped) {
                        statusMessage = "Visualization stopped.";
                    } else {
                        statusMessage = "No solution found.";
                    }
                    selectedRow = -1; // Deselect cell
                    selectedCol = -1;
                } else if (CheckCollisionPointRec(mousePos, lockButton)) {
                    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) initialGrid[i][j] = grid[i][j];
                    statusMessage = "Puzzle locked! Ready to solve.";
                    selectedRow = -1;
                    selectedCol = -1;
                } else if (CheckCollisionPointRec(mousePos, clearButton)) {
                    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
                        grid[i][j] = 0;
                        initialGrid[i][j] = 0;
                    }
                    statusMessage = "Grid cleared. Enter puzzle.";
                    selectedRow = -1;
                } else if (CheckCollisionPointRec(mousePos, resetButton)) {
                    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) grid[i][j] = defaultGrid[i][j];
                    statusMessage = "Grid has been reset.";
                    selectedRow = -1; // Deselect cell
                    selectedCol = -1;
                }
            }
        }

        if (selectedRow != -1 && selectedCol != -1) {
            if (initialGrid[selectedRow][selectedCol] == 0) { // Can only edit user-added numbers
                int key = GetKeyPressed();
                if (key >= KEY_ONE && key <= KEY_NINE) {
                    int num = key - '0';
                    int currentVal = grid[selectedRow][selectedCol];
                    grid[selectedRow][selectedCol] = 0; // Temporarily clear for isSafe check

                    if (isSafe(grid, selectedRow, selectedCol, num)) {
                        grid[selectedRow][selectedCol] = num;
                        statusMessage = "Ready. Press 'Lock Puzzle' to set.";
                    } else {
                        grid[selectedRow][selectedCol] = currentVal; // Restore previous value
                        statusMessage = "Invalid move!";
                    }

                } else if (key == KEY_BACKSPACE || key == KEY_DELETE || key == KEY_ZERO) {
                    grid[selectedRow][selectedCol] = 0;
                    statusMessage = "Cell cleared.";
                }
            }
        }

        // --- Draw ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawSudokuGrid(grid, initialGrid, selectedRow, selectedCol);
        DrawUI(statusMessage);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}