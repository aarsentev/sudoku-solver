#include "sudoku.h"

int solveCell(Cell * cell)
{
    int x;

    for (x = 0; x < SIZE_ROWS; x++)
    {
        if (cell->possible[x] == 0)
        {
            cell->number = x + 1;
            cell->solvable = 0;
            UNSOLVED--;
        }
    }
}
