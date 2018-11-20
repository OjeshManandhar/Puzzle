#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "config.h"
#include "header.h"

void draw_box()
{
    uint8_t i, j;
    unsigned char ch;

    top.row = ROW_POS(LENGTH);
    top.col = COL_POS(BREADTH);
    bot.row = top.row + LENGTH - 1;
    bot.col = top.col + BREADTH - 1;

    system("cls || clear");

    for (i = 0; i < LENGTH; i++)
        for (j = 0; j < BREADTH; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                    ch = 201;
                else if (j == BREADTH - 1)
                    ch = 187;
                else if (j%5 == 0)
                    ch = 209;
                else
                    ch = 205;
            }
            else if (i == LENGTH - 1)
            {
                if (j == 0)
                    ch = 200;
                else if (j == BREADTH - 1)
                    ch = 188;
                else if (j%5 == 0)
                    ch = 207;
                else
                    ch = 205;
            }
            else if (i%2 == 0)
            {
                if (j == 0)
                    ch = 199;
                else if (j == BREADTH - 1)
                    ch = 182;
                else if (j%5 == 0)
                    ch = 197;
                else
                    ch = 196;
            }
            else
            {
                if ((j == 0) || (j == BREADTH - 1))
                    ch = 186;
                else if (j%5 == 0)
                    ch = 179;
                else
                    ch = ' ';
            }

            gotoxy(top.row + i, top.col + j);
            printf("%c", ch);
        }
}

void put_element(const uint8_t type)
{
    /*
    type:
    1 => display "  "
    2 => display number
    */
    uint8_t i, j;

    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
        {
            gotoxy(top.row + TO_ROW(i), top.col + TO_COL(j));
            if ((puzzle[i][j] == row*col) && (type == 0))
                printf("  ");
            else
                printf("%2u", puzzle[i][j]);
        }
}

int get_conformation(const char *heading, const char *opt)
{
    int choice;
    unsigned int key;
    uint8_t temp_top, temp_bot, mid_point;

    choice = 1;
    while (1)
    {
        top.row = ROW_POS(7);
        top.col = COL_POS(21);
        bot.row = top.row + 7 - 1;
        bot.col = top.col + 21 - 1;

        system("cls || clear");
        print_box(2, 3, 0, 2);

        gotoxy(top.row + 1, COL_POS(strlen(heading)));
        printf(heading);

        top.row += 3;
        bot.row = top.row + 3 - 1;
        mid_point = (top.col + 21/2);
        temp_top = ++top.col;
        temp_bot = --bot.col;

        gotoxy(top.row + 1, (mid_point - top.col + 1 - 4)/2 + top.col);
        printf("Play");
        gotoxy(top.row + 1, (bot.col - mid_point + 1 - 4)/2 + mid_point);
        printf(opt);

        if (choice == 1)
        {
            top.col = temp_top;
            bot.col = mid_point;
            print_box(3, 0, 0, 0);
        }
        else if (choice == 0)
        {
            top.col = mid_point;
            bot.col = temp_bot;
            print_box(3, 0, 0, 0);
        }

        key = get_key();
        if ((key == RIGHT) || (key == LEFT))
        {
            if (choice == 0)
                choice = 1;
            else if (choice == 1)
                choice = 0;
        }
        else if (key == ENTER)
            return choice;
        else if (key == ESC)
            return 0;
    }
}

void ask_size()
{
    char temp[7];

    top.row = ROW_POS(6);
    top.col = COL_POS(25);
    bot.row = top.row + 6 - 1;
    bot.col = top.col + 25 - 1;

    system("cls || clear");
    print_box(2, 3, 0, 2);
    gotoxy(top.row + 1, COL_POS(strlen("SET SIZE")));
    printf("SET SIZE");

    top.row += 3;
    top.col += 2;

    gotoxy(top.row, top.col);
    if (MAX_SCR_ROW <= MAX_ROW)
        printf("Row [%u to %u]: ", MIN_ROW, MAX_SCR_ROW);
    else
        printf("Row [%u to %u]: ", MIN_ROW, MAX_ROW);

    gotoxy(top.row + 1, top.col);
    if (MAX_SCR_COL <= MAX_COL)
        printf("Col [%u to %u]: ", MIN_COL, MAX_SCR_COL);
    else
        printf("Col [%u to %u]: ", MIN_COL, MAX_COL);

    top.col += 15;

    do
    {
        strcpy(temp, "");
        gotoxy(top.row, top.col);
        printf("      ");           //printing 6 spaces to clear the input area

        gotoxy(top.row, top.col);
        get_data(temp);
        row = string_to_int(temp);
    }while ((row < MIN_ROW) || (row > MAX_SCR_ROW) || (row > MAX_ROW));

    do
    {
        strcpy(temp, "");
        gotoxy(top.row + 1, top.col);
        printf("      ");           //printing 6 spaces to clear the input area

        gotoxy(top.row + 1, top.col);
        get_data(temp);
        col = string_to_int(temp);
    }while ((col < MIN_COL) || (col > MAX_SCR_COL) || (col > MAX_COL));
}

void display_logo()
{
    FILE *fp = NULL;
    uint8_t line = 0;
    char data[66] ="";
    struct position_detail size = {0};

    fp = fopen("logo.txt", "r");
    if (fp != NULL)
    {
        get_console_size(&size);
        if ((size.row >= 12) && (size.col >= 65))
        {
            system("color 06");
            //console background = 0 = Black
            //console text = 6 = Yellow

            while(fgets(data, sizeof(data), fp) != NULL)
            {
                gotoxy(ROW_POS(12) + line++, COL_POS(65));
                printf("%s", data);
                delay(150);
            }

            gotoxy(ROW_POS(12)+ 11, COL_POS(strlen("Loading Game")));
            printf("Loading Game");
            gotoxy(ROW_POS(12)+ 12, COL_POS(20));
            loading_animation(20);

            gotoxy(scr_size.row - 1, scr_size.col - 1);
            delay(500);
            system("cls || clear");
            system("color 07");                //reset console colour to normal
            //console background = 0 = Black
            //console text = 7 = White
        }
    }
}

void loading_animation(const uint8_t max)
{
    uint8_t i;

    for (i = 0; i < max; i++)
        printf("%c", 177);
    for (i = 0; i < max; i++)
        printf("\b");

    for (i = 0; i < max; i++)
    {
        printf("%c", 219);

        if (i <= max*33/100)
            delay(150);
        else if ((i > max*33/100) && (i <= max*66/100))
            delay(100);
        else
            delay(50);
    }
}
