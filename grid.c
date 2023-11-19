#include "sudoku.h"

int gridSingles(Cell *** sudoku, Grid ** grids)
{
    int i, j, x;
    int count;
    int temp;

    /* Loop through grids */
    for (i = 0; i < 9; i++)
    {
        /* Loop through possible array */
        for (j = 0; j < 9; j++)
        {
            count = 0;

            /* Loop through cells */

            for (x = 0; x < 9; x++)
            {
                if (grids[i]->cells[x]->number != 0)
                    continue;

                if (grids[i]->cells[x]->possible[j] == 0)
                {
                    count++;
                    temp = x;
                }

                if (count >= 2)
                {
                    break;
                }
            }

            if (count == 1)
            {
                grids[i]->cells[temp]->number = j + 1;
                UNSOLVED--;
                grids[i]->cells[temp]->solvable = 0;

                updateSudoku(sudoku, grids[i]->cells[temp]->row, grids[i]->cells[temp]->column);

                return 1;
            }
        }
    }
    return 0;
}

Grid ** createGrids()
{
    int x, y;
    Grid ** grids;

    grids = malloc(sizeof(Grid*) * 9);

    for (x = 0; x < 9; x++)
    {
        grids[x] = malloc(sizeof(Grid));
        grids[x]->cells = malloc(sizeof(Cell*) * 9);
        grids[x]-> numbers = 0;
        grids[x]->solvable = 9;

        for (y = 0; y < 9; y++)
        {
            grids[x]->possible[y] = 0;
        }
    }

    return grids;
}

int updateGrids(Cell *** sudoku, int row, int column)
{
    int x;
    int number = sudoku[row][column]->number;
    Grid * grid;
    grid = sudoku[row][column]->parentGrid;

    for (x = 0; x < 9; x++)
    {
        if (grid->cells[x]->possible[number - 1] == 0)
        {
            grid->cells[x]->solvable--;
            grid->cells[x]->possible[number - 1] = 1;
        }
    }
}
