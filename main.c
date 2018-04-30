#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include <QBASIC_func_C.h>
#include <basic_func.h>

void box(int,int,int);

int main()
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
            exit(1);
        }
    }while (1);
    return 0;
}

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
