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
            if (get_conformation() == 1)
            {
                create_puzzle();
                play();
                (void)get_key();
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
    uint8_t temp, temp_i, temp_j;

    //Creating the puzzle with initial value 0
    puzzle = (uint8_t **)calloc(row, sizeof(uint8_t *));
    for (i = 0; i < row; i++)
        puzzle[i] = (uint8_t *)calloc(col, sizeof(uint8_t));

    //Giving value 1, 2, 3, ...
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            puzzle[i][j] = i*col + j + 1;

    //Shuffling the puzzle
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
}

void play()
{
    int i,j,r,c,x,ch,ir=3,ic=3,moves=0,br;
    int p[4][4]={
                    {1,4,15,7},
                    {8,10,2,11},
                    {14,3,6,13},
                    {12,9,5,16}
                };
    do
    {
        for (i=1,r=0;i<=12;i+=3,r++)
            for(j=1,c=0;j<=19;j+=5,c++)
            {
                x=p[r][c];
                box(i,j,x);
            }
        ch=getkey();
        if (ch==77 && ic>0)
        {
            swap_int(&p[ir][ic],&p[ir][ic-1]);
            ic--;
        }
        else if (ch==75 && ic<3)
        {
            swap_int(&p[ir][ic],&p[ir][ic+1]);
            ic++;
        }
        else if (ch==80 && ir>0)
        {
            swap_int(&p[ir][ic],&p[ir-1][ic]);
            ir--;
        }
        else if (ch==72 && ir<3)
        {
            swap_int(&p[ir][ic],&p[ir+1][ic]);
            ir++;
        }
        moves++;
        for (i=0,br=0,x=1;i<4;i++)
        {
            for(j=0;j<4;j++,x++)
                if (p[i][j]!=x)
                {
                    br=1;
                    break;
                }
            if (br==1)
                break;
        }
        if (br==0)
        {
            system("cls");
            printf("\nYou Win!!!\n\a");
            printf("Your Moves = %d.\n",moves);
            return;
        }
    }while (1);
}
