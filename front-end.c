#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "config.h"

void box(int v,int h,int x)
{
    int i,j;
    for (i=v;i<=v+2;i++)
        for(j=h;j<=h+3;j++)
        {
            gotoxy(i,j);
            if (i==v+1&&(j==h+1||j==h+2))
            {
                if (x<10)
                    printf(" %d",x);
                else if (x==16)
                    printf("  ");
                else
                    printf("%d",x);
                j++;
            }
            else
                printf("*");
        }
}

void draw_box()
{
    uint8_t i, j;
    unsigned char ch;

    top.row = ROW_POS(LENGTH);
    top.col = COL_POS(BREADTH);
    bot.row = top.row + LENGTH - 1;
    bot.col = top.col + BREADTH - 1;

    system("cls");

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

void put_element()
{
    uint8_t i, j;

    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
        {
            gotoxy(top.row + TO_ROW(i), top.col + TO_COL(j));
            if (puzzle[i][j] < 10)
                printf("0%u", puzzle[i][j]);
            else if (puzzle[i][j] == row*col)
                printf(" ");
            else
                printf("%u", puzzle[i][j]);
        }
}

int get_conformation()
{
    int choice;
    unsigned int key;
    char heading[20] = "";
    uint8_t temp_top, temp_bot, mid_point;

    strcpy(heading, "Play ");
    if (row < 10)
        strcat(heading, "0");
    strcat(heading, int_to_string(row));
    strcat(heading, "x");
    if (col < 10)
        strcat(heading, "0");
    strcat(heading, int_to_string(col));
    strcat(heading, " puzzle");

    choice = 0;
    while (1)
    {
        top.row = ROW_POS(7);
        top.col = COL_POS(21);
        bot.row = top.row + 7 - 1;
        bot.col = top.col + 21 - 1;

        system("cls || clear");
        print_box(2, 3, 0, 2);

        gotoxy(top.row + 1, top.col + 2);
        printf(heading);

        top.row += 3;
        bot.row = top.row + 3 - 1;
        mid_point = (top.col + 21/2);
        temp_top = ++top.col;
        temp_bot = --bot.col;

        gotoxy(top.row + 1, (mid_point - top.col + 1 - 4)/2 + top.col);
        printf("Play");
        gotoxy(top.row + 1, (bot.col - mid_point + 1 - 4)/2 + mid_point);
        printf("Back");

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
