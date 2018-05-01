#include <stdio.h>

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
