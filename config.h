#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <inttypes.h>
#include <stdint.h>

#include <QBASIC_func_C.h>
#include <basic_func.h>

//Max values of row and col for scr_size 30x120
#define MAX_ROW 14
#define MAX_COL 24

//Min values of row and col for any scr_size
#define MIN_ROW 2
#define MIN_COL 2

//To find the centre of the screen to draw the box
#define ROW_POS(length) (scr_size.row - length)/2
#define COL_POS(breadth) (scr_size.col - breadth)/2

//To find the length and breadth of the box depending upon the size of puzzle
#define LENGTH (2*row + 1)
#define BREADTH (5*col + 1)

//To find the screen position of the matrix/puzzle
#define TO_ROW(i) (2*i + 1)
#define TO_COL(j) (5*j + 2)

//extern/global variable declaration
extern struct position_detail scr_size;

extern const uint8_t default_row;
extern const uint8_t default_col;

extern uint8_t row;
extern uint8_t col;

extern uint8_t **puzzle;

#endif // CONFIG_H_INCLUDED
