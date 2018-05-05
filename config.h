#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <inttypes.h>
#include <stdint.h>

#include <QBASIC_func_C.h>
#include <basic_func.h>

//Min values of row and col for any scr_size
#define MIN_ROW 2
#define MIN_COL 2

//Max values of row and col for any scr_size
#define MAX_ROW 10
#define MAX_COL 10

//Max values of row and col for a certain scr_size
#define MAX_SCR_ROW ((scr_size.row - 1)/2)
#define MAX_SCR_COL ((scr_size.col - 1)/5)

//To find the centre of the screen to draw the box
#define ROW_POS(length) (scr_size.row - length)/2
#define COL_POS(breadth) (scr_size.col - breadth)/2

//To find the length and breadth of the box depending upon the size of puzzle
#define LENGTH (2*row + 1)
#define BREADTH (5*col + 1)

//To find the screen position of the matrix/puzzle
#define TO_ROW(i) (2*i + 1)
#define TO_COL(j) (5*j + 2)

//Default values for row and col
#define DEFAULT_ROW 4
#define DEFAULT_COL 4

//extern/global variable declaration
extern struct position_detail scr_size;         //console size

extern uint8_t row;         //no of rows in the puzzle
extern uint8_t col;         //no of cols in the puzzle

extern uint8_t **puzzle;            //pointer to store the puzzle matrix/array

#endif // CONFIG_H_INCLUDED
