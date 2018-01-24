// How to dynamically allocate a 2D array
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include "74hc595_functions.h"
#include <unistd.h>

void dot(int row, int col)
{
     uint8_t row8, col8;
     uint16_t tmp;
     row8 = ~(1 << (8-row));
     col8 = 1 << (8-col);
     tmp = (row8<<8) | col8;
     set16(tmp);
}

int cnt;
void callback(void)
{
    cnt++;
}

int main()
{
    FILE *pf=fopen("data","r+");

    int i, j, flag=0;
    char *matcopy[9];
    

int ret;
ret=init();
if(ret==0) return 0;

    for(i = 0 ; i < 9 ; i++)
    { matcopy[i] = (char*)malloc(255 * sizeof(char));
        fgets(matcopy[i],255,pf);
    }

    for (j=1;j<255;j++)
    {
        if(matcopy[2][j]=='\n') break;
    }
    flag=j;


        for(i = 1; i <9  ; i++){
        
        for(j = 0 ; j < flag ; j++){
        if(matcopy[i][j]==32)
            matcopy[i][j]=0;
        else if(matcopy[i][j]=='o')
            matcopy[i][j]=1;
        else matcopy[i][j]=0;   
         }
  
        }
    

gpioSetTimerFunc(0,50,callback);
while(1)
    for(i=1;i<9;i++)
        for(j=0;j<8;j++)
            if(matcopy[i][(j+cnt)%flag]==1)
                dot(i,j+1);

release();
return 0;
}

