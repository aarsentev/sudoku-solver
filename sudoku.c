#include "sudoku.h"
int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main(){
    int ** puzzle;
    int progress;

    Sudoku* sudoku;

    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle);

    printPuzzle(sudoku->cells);

    while (UNSOLVED > 0)
    {
        progress = checkPuzzle(sudoku->cells, sudoku->grids);

        if (progress == 0)
        {
            printf("Failed to solve the puzzle!");
            break;
        }
    }

    printf("\n\n");

    printPuzzle(sudoku->cells);

    return 0;
}
