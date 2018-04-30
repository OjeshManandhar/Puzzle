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
