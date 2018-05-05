#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
//#include <time.h>

#include "config.h"
#include "header.h"

//-----extern values-----
struct position_detail scr_size = {30, 120};        //MAX 255 as uint8_t is used

uint8_t row = 0;
uint8_t col = 0;

uint8_t **puzzle = NULL;
//-----------------------

int main()
{
    unsigned int i, choice;
    char **main_menu_items = NULL;
    char heading[20] = "";
    char detail[20] = "";

    adjust_console_size(scr_size);

    main_menu_items = get_2D_char_array(4, 10);
    strcpy(main_menu_items[0], "MAIN MENU");
    strcpy(main_menu_items[1], "Play");
    strcpy(main_menu_items[2], "Set size");
    strcpy(main_menu_items[3], "Exit");

    choice = 1;
    do
    {
        choice = display_menu(main_menu_items, 4, choice);

        system("cls || clear");
        switch (choice)
        {
        case 1:
            if ((row == 0) && (col == 0))
            {
                row = DEFAULT_ROW;
                col = DEFAULT_COL;
            }

            /*
            strcpy(heading, "Play ");
            if (row < 10)
                strcat(heading, "0");
            strcat(heading, int_to_string(row));
            strcat(heading, "x");
            if (col < 10)
                strcat(heading, "0");
            strcat(heading, int_to_string(col));
            strcat(heading, " puzzle");
            */
            sprintf(heading, "Play %ux%u puzzle", row, col);
            if (get_conformation(heading, "Back") == 1)
            {
                create_puzzle();
                play();
            }
            break;
        case 2:
            row = col = 0;

            ask_size();

            sprintf(detail, "Size set to %ux%u", row, col);
            print_detail(detail, NULL);
            break;
        case 3:
            for (i = 0; i < 4; i++)
                free(main_menu_items[i]);
            free(main_menu_items);
            break;
        }
    }while (choice != 3);

    return 0;
}

void get_data(char *data)
{
    uint8_t count = 0;
    char ch;

    while(1)
    {
        fseek(stdin, 0, SEEK_END);
        ch = getch();
        if (ch == '\b' && count != 0)
        {
            printf("\b \b");
            data[count] = 0;
            count--;
        }
        else if (ch == '\b' && count == 0)
            continue;
        else if (count < 1 && ch =='\r')            //1 = min character in input
            continue;
        else if (ch == '\r')
        {
            data[count] = 0;
            break;
        }
        else if (count == 6)                        //6 = max character in input
            continue;
        else if ((ch >= '0') && (ch <= '9'))
        {
            data[count] = ch;
            count++;
            putchar(ch);
        }
        else
            continue;
    }
}

void create_puzzle()
{
    uint8_t i, j;
    uint8_t temp;
    //unsigned int temp_i, temp_j;
    unsigned int key, moves;

    //Creating the puzzle with initial value 0
    puzzle = (uint8_t **)calloc(row, sizeof(uint8_t *));
    for (i = 0; i < row; i++)
        puzzle[i] = (uint8_t *)calloc(col, sizeof(uint8_t));

    //Giving value 1, 2, 3, ...
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            puzzle[i][j] = i*col + j + 1;

    /*
    //Shuffling the puzzle
    //This method could sometime lead to a unsolvable puzzle
    srand(time(0));
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
        {
            temp_i = rand()%row;
            temp_j = rand()%col;

            temp = puzzle[i][j];
            puzzle[i][j] = puzzle[temp_i][temp_j];
            puzzle[temp_i][temp_j] = temp;
        }

    //Making the last element row*col to display it blank at start
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            if (puzzle[i][j] == row*col)
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[row - 1][col - 1];
                puzzle[row - 1][col - 1] = temp;

                break;
            }
    */

    //New method of shuffling puzzle
    srand(time(0));
    i = row - 1;
    j = col - 1;
    for (moves = 0; moves < 1000; moves++)
    {
        key = rand()%4;
        if (key == 0)
            key = UP;
        else if (key == 1)
            key = DOWN;
        else if (key == 2)
            key = RIGHT;
        else if (key == 3)
            key = LEFT;

        switch (key)
        {
        case UP:
            if (i < (row - 1))
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[i + 1][j];
                puzzle[i + 1][j] = temp;

                i++;
            }
            break;
        case DOWN:
            if (i > 0)
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[i - 1][j];
                puzzle[i - 1][j] = temp;

                i--;
            }
            break;
        case LEFT:
            if (j < (row - 1))
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[i][j + 1];
                puzzle[i][j + 1] = temp;

                j++;
            }
            break;
        case RIGHT:
            if (j > 0)
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[i][j - 1];
                puzzle[i][j - 1] = temp;

                j--;
            }
            break;
        }
    }
}

void play()
{
    uint8_t flag, finish;
    uint8_t i, j;
    uint8_t temp, temp_i, temp_j;
    unsigned int key, moves;
    char message[15] = "";
    char heading[] = "Sure to Quit";

    flag = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            if (puzzle[i][j] == row*col)
            {
                flag = 1;
                break;
            }
        if (flag == 1)
            break;
    }

    moves = 0;

    draw_box();
    while (1)
    {
        put_element(0);

        key = get_key();
        switch (key)
        {
        case UP:
            if (i < (row - 1))
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[i + 1][j];
                puzzle[i + 1][j] = temp;

                i++;
                moves++;
            }
            break;
        case DOWN:
            if (i > 0)
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[i - 1][j];
                puzzle[i - 1][j] = temp;

                i--;
                moves++;
            }
            break;
        case LEFT:
            if (j < (row - 1))
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[i][j + 1];
                puzzle[i][j + 1] = temp;

                j++;
                moves++;
            }
            break;
        case RIGHT:
            if (j > 0)
            {
                temp = puzzle[i][j];
                puzzle[i][j] = puzzle[i][j - 1];
                puzzle[i][j - 1] = temp;

                j--;
                moves++;
            }
            break;
        case ESC:
            if (get_conformation(heading, "Quit") == 0)
                return;
            else
                draw_box();
            break;
        }

        finish = 1;
        for (temp_i = 0; temp_i < row; temp_i++)
            for (temp_j = 0; temp_j < col; temp_j++)
                if (puzzle[temp_i][temp_j] != (temp_i*col + temp_j + 1))
                {
                    finish = 0;
                    break;
                }

        if (finish == 1)
        {
            put_element(1);
            (void)get_key();

            sprintf(message, "Moves = %u", moves);
            print_detail("Puzzle Solved", message);
            break;
        }
    }
}
