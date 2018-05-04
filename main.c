#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "config.h"
#include "header.h"

//-----extern values-----
struct position_detail scr_size = {30, 120};

uint8_t row = 0;
uint8_t col = 0;

uint8_t **puzzle = NULL;
//-----------------------

void play();

int main()
{
    unsigned int i, choice;
    char **main_menu_items = NULL;

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
                play();
                (void)get_key();
            }
            break;
        case 2:
            printf("Set size");
            (void)get_key();
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
