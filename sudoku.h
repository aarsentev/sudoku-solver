#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>

extern int UNSOLVED;
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;

typedef struct Sudoku{
    struct Cell *** cells;
    struct Grid ** grids;

} Sudoku;

typedef struct Grid
{
    struct Cell ** cells;
    int numbers;
    int possible[9];
    int solvable;
    struct Grid * next;
} Grid;

typedef struct Cell
{
    int row;
    int column;
    int number;
    int possible[9];
    /*
        [0][0][0][0][0][0][0][0][0]
        [9][8][7][6][5][4][3][2][1]
    */
    int solvable;
    Grid * parentGrid;
} Cell;



// Function declarations by file

// Defined in puzzle.c
Sudoku * createSudoku(Cell *** cells, Grid ** grids);
Sudoku * setUpPuzzle(int ** puzzle);
void printPuzzle(Cell *** puzzle);

// Defined in reader.c
int ** readPuzzleFromFile(char * filename);
void freePuzzle(int ** puzzle, int rows);

// Defined in cell.c
int solveCell(Cell * cell);

// Defined in grid.c
Grid ** createGrids();
int gridSingles(Cell *** sudoku, Grid ** grids);
int updateGrids(Cell *** sudoku, int row, int column);

// Defined in row.c
int checkRows(Cell *** sudoku, Grid ** grids);

// Defined in sudoku.c
int ** createPuzzle();
int updateSudoku(Cell *** sudoku, int row, int column);
int checkPuzzle(Cell *** sudoku, Grid ** grids);

#endif
