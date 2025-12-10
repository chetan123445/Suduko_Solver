#  Sudoku Solver GUI

A feature-rich Sudoku solver application built in C++ with the [Raylib](https://www.raylib.com/) library. This application not only solves any valid Sudoku puzzle instantly but also provides a step-by-step visualization of the backtracking algorithm, making it an excellent tool for learning.

https://drive.google.com/drive/folders/1ieKug6m1zBxKURkNi6z8EnIAgUkCXSCC?usp=drive_link

---

## ✨ Features

- **Interactive GUI**: A clean and simple graphical user interface for entering and viewing Sudoku puzzles.
- **Instant Solver**: Solves any valid puzzle almost instantly using a recursive backtracking algorithm.
- **Step-by-Step Visualization**: Watch the algorithm work in real-time!
  - Each number placement and backtracking step is shown with a 1-second delay.
  - The current cell being processed is highlighted.
  - You can stop the visualization at any time by pressing the `ESCAPE` key.
- **Custom Puzzle Creation**:
  - Start with a blank grid using the "Clear Grid" button.
  - Enter your own numbers to create a custom puzzle.
  - The application provides real-time validation to prevent invalid moves.
- **Puzzle Locking**: Use the "Lock Puzzle" button to set your custom numbers as the base puzzle, turning them gray and making them uneditable.
- **Multiple Controls**: Easily reset the grid to the default puzzle or clear it completely.

---

## 🚀 Getting Started

Follow these instructions to compile and run the application on your local machine.

### Prerequisites

- A C++ compiler that supports C++17 (like MinGW g++ on Windows).
- The **Raylib** library files.

### Compilation

1.  **File Structure**: Ensure your project directory is set up correctly. The necessary Raylib files should be placed in `include` and `lib` folders relative to the source code:
    ```
    Suduko_Solver/
    ├── include/
    │   └── raylib.h
    ├── lib/
    │   └── libraylib.a  (or other raylib library file)
    └── sudoku_gui.cpp
    ```

2.  **Compile Command**: Open a terminal (like Git Bash or PowerShell) in the `Sudoku_Solver` directory and run the following command:

    ```bash
    g++ sudoku_gui.cpp -o sudoku_gui.exe -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra -std=c++17
    ```
    This will create an executable file named `sudoku_gui.exe`.

### Running the Application

After successful compilation, run the program from the same terminal:

```bash
./sudoku_gui.exe
```

---

## 📖 How to Use the Application

1.  **Select a Cell**: Click on any cell in the 9x9 grid to select it. The selected cell will be highlighted.

2.  **Enter a Number**:
    - Press any number key from `1` to `9` to place a value in the selected cell.
    - The application will prevent you from making an invalid move (e.g., placing a number that already exists in the same row, column, or 3x3 box).
    - To clear a cell, press `0`, `DELETE`, or `BACKSPACE`.

3.  **Use the Control Buttons**:
    - **Solve Instantly**: Immediately fills the grid with the correct solution.
    - **Visualize Steps**: Starts the step-by-step visualization of the solving process. Press `ESC` to stop at any time.
    - **Lock Puzzle**: Finalizes the numbers you've entered, turning them into the official puzzle to be solved.
    - **Clear Grid**: Empties the entire grid, allowing you to create a new puzzle from scratch.
    - **Reset to Default**: Reverts the grid to the original hard-coded puzzle.

---

## 🧠 Core Logic: Backtracking

The solver is based on a recursive backtracking algorithm, a common and effective method for solving constraint-satisfaction problems like Sudoku.

1.  **Find an Empty Cell**: The algorithm scans the grid for an empty cell.
2.  **Try Numbers**: It tries to place a valid number (from 1 to 9) in that empty cell. A number is valid if it doesn't already exist in the current row, column, or 3x3 sub-grid.
3.  **Recurse**: If a valid number is found, it's placed in the cell, and the algorithm recursively calls itself to solve the rest of the puzzle.
4.  **Backtrack**: If the recursive call fails to find a solution (i.e., it reaches a dead end), it means the number placed was incorrect. The algorithm then "backtracks" by undoing the choice (resetting the cell to 0) and tries the next valid number.
5.  **Solution**: If the algorithm successfully fills the entire grid, a solution has been found. If it tries all numbers in the first empty cell and none lead to a solution, the puzzle is unsolvable.
