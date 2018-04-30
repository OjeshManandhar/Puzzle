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

extern struct position_detail scr_size;

extern const uint8_t default_row;
extern const uint8_t default_col;

extern uint8_t row;
extern uint8_t col;

#endif // CONFIG_H_INCLUDED
