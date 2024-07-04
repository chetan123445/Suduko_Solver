                             Program Explanation
--> Functions

1: isSafe Function:

-->This function checks if it's safe to place a number in a specific cell of
   the Sudoku grid.   
-->It ensures the number does not already exist in the current row, column,
   or the 3x3 sub-grid.
-->It returns 1 if it's safe to place the number, otherwise it returns 0.

2: Solve Function:

-->This function uses a backtracking approach to solve the Sudoku puzzle.
-->It recursively tries to fill the grid with valid numbers.
-->It handles moving to the next cell, skipping pre-filled cells, and 
   backtracking when necessary.
-->The function returns 1 if the puzzle is successfully solved, otherwise it
   returns 0. 

3: main Function:

-->The main function handles user input and output.
-->It reads the Sudoku puzzle from the user.
-->It displays the entered puzzle.
-->It calls the Solve function to solve the puzzle.
-->It displays the solved puzzle if a solution exists, otherwise it prints 
   message indicating "no solution exists".

4:Flow of the Program

1:Input:The user is prompted to enter the Sudoku puzzle row by row. The 
        input is read into a 2D array grid.

2:Display Input:The entered Sudoku puzzle is displayed in a formatted    
                manner.

3:Solve the Puzzle:The Solve function is called to solve the puzzle using a 
                   backtracking algorithm.

4:Output:If a solution exists, the solved Sudoku puzzle is displayed in a 
         formatted manner.
         If no solution exists, a message indicating that no solution exists
         is printed. 