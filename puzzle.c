#include "sudoku.h"

Sudoku * createSudoku(Cell *** cells, Grid ** grids)
{
    Sudoku * sudoku;

    sudoku = malloc(sizeof(Sudoku));

    sudoku->cells = cells;
    sudoku->grids = grids;

    return sudoku;
}

Sudoku * setUpPuzzle(int ** puzzle)
{
    Cell *** sudoku;
    Grid ** grids;

    int i, j, x;
    int currentGrid = 0;

    sudoku = (Cell ***)malloc(sizeof(Cell **) * 9);
    grids = createGrids();

     for (i = 0; i < SIZE_ROWS; i++)
    {
        sudoku[i] = (Cell **) malloc(sizeof(Cell*) * 9);


        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            sudoku[i][j] = (Cell*) malloc(sizeof(Cell) * 9);

            sudoku[i][j]->number = puzzle[i][j];

            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            grids[currentGrid]->cells[ grids[currentGrid]->numbers ] = sudoku[i][j];
            sudoku[i][j]->parentGrid = grids[currentGrid];
            grids[currentGrid]->numbers++;

            for (x = 0; x < SIZE_ROWS; x++)
            {
                sudoku[i][j]->possible[x] = 0;
            }

            if (j == 2)
            {
                currentGrid++;
            }
            if (j == 5)
            {
                currentGrid++;
            }
        }

        currentGrid -= 2;

        if (i == 2)
        {
            currentGrid = 3;
        }

        if (i == 5)
        {
            currentGrid = 6;
        }
    }

    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->number != 0)
            {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                updateGrids(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return createSudoku(sudoku, grids);
}

int updateSudoku(Cell *** sudoku, int row, int column)
{
    int x;
    int number  = sudoku[row][column]->number;

    for (x = 0; x < SIZE_ROWS; x++)
    {
        if (sudoku[x][column]->possible[number - 1] == 0)
        {
            sudoku[x][column]->solvable--;
        }
        sudoku[x][column]->possible[number - 1] = 1;
    }

    for (x = 0; x < SIZE_COLUMNS; x++)
    {
        if (sudoku[row][x]->possible[number - 1] == 0)
        {
            sudoku[row][x]->solvable--;
        }
        sudoku[row][x]->possible[number - 1] = 1;
    }

    return 1;
}

int checkPuzzle(Cell *** sudoku, Grid ** grids)
{
    int i, j, x;

    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->solvable == 1)
            {
                solveCell(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateGrids(sudoku, i, j);

                return 1;
            }
        }
    }

    if (gridSingles(sudoku, grids))
    {
        return 1;
    }

    return checkRows(sudoku, grids);
}

int ** createPuzzle()
{
    int ** puzzle;
    int i, j;
    int array[9][9] =
    {
        0, 1, 9,    0, 0, 2,    0, 0, 0,
        4, 7, 0,    6, 9, 0,    0, 0, 1,
        0, 0, 0,    4, 0, 0,    0, 9, 0,

        8, 9, 4,    5, 0, 7,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    2, 0, 1,    9, 5, 8,

        0, 5, 0,    0, 0, 6,    0, 0, 0,
        6, 0, 0,    0, 2, 8,    0, 7, 9,
        0, 0, 0,    1, 0, 0,    8, 6, 0
    };

    puzzle = (int**) malloc(sizeof(int*) * 9);

    for (i = 0; i < SIZE_ROWS; i++){
        puzzle[i] = (int*) malloc(sizeof(int) * 9);

        for (j = 0; j < SIZE_COLUMNS; j++){
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}

void printPuzzle(Cell *** puzzle)
{
    int i, j;
    printf("-------------------------\n");
    for (i = 0; i < SIZE_ROWS; i++)
    {
        printf("|");
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            printf(" %d", puzzle[i][j]->number);
            if ((j + 1) % 3 == 0){
                printf(" |");
            }
        }
        printf("\n");
        if (i % 3 == 2){
            printf("-------------------------\n");
        }
    }
}
