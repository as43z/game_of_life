#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_HEIGHT 50
#define MATRIX_WIDTH 50



void initTablero(int tablero[MATRIX_WIDTH][MATRIX_HEIGHT]){
    int x, y;
    
    //zeroed
    for(y = 0; y < MATRIX_HEIGHT; y++){
        for(x = 0; x < MATRIX_WIDTH; x++){
            tablero[x][y] = 0;
        }
    }
}

int godPerform(int tablero[MATRIX_WIDTH][MATRIX_HEIGHT], int x, int y){
    int i = 0, j = 0, sumTotal = 0;
    for(j = y-1; j < y+2; j++){
        for(i = x-1; i < x+2; i++){
            // we cannot count rows at j = -1,
            // columns at i = -1, rows at j = 10
            // and columns at i = 10
            if(!((j < 0)||(i < 0)||(j > MATRIX_HEIGHT-1)||(i > MATRIX_HEIGHT-1))){
                if(tablero[i][j] == 1)
                    sumTotal++;
            }
        }
    }
    //don't count yourself
    if(tablero[x][y] == 1)
        sumTotal--;

    if(tablero[x][y]==1){
        if((sumTotal > 3)||(sumTotal < 2)){
            return 0;
        } else {
            return 1;
        }
    } else {
        if(sumTotal == 3){
            return 1;
        } else {
            return 0;
        }
    }
}

void gameTick(int tablero[MATRIX_WIDTH][MATRIX_HEIGHT]){
    int buff[MATRIX_WIDTH][MATRIX_HEIGHT];
    initTablero(buff);

    int x, y;
    for(y = 0; y < MATRIX_HEIGHT; y++){
        for(x = 0; x < MATRIX_WIDTH; x++){
            buff[x][y] = godPerform(tablero, x, y);
        }
    }

    memcpy(tablero, buff, MATRIX_HEIGHT*MATRIX_WIDTH*sizeof(int));
}



void printTablero(int tablero[MATRIX_WIDTH][MATRIX_HEIGHT]){
    int x, y;
    char cID = ' ';

    //for every matrix position
    for(y = 0; y < MATRIX_HEIGHT; y++){
        printf("row %i) ", (y));
        for(x = 0; x < MATRIX_WIDTH; x++){
            //check wether a position is active
            //or not. 1 is active, 0 is not active
            if(tablero[x][y] == 1){
                cID = '#';
            } else {
                cID = '-';
            }

            printf("%c ", cID);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    int tablero[MATRIX_WIDTH][MATRIX_HEIGHT];

    initTablero(tablero);

    /* design a pattern */
    tablero[4][3] = 1;
    tablero[5][4] = 1;
    tablero[5][5] = 1;
    tablero[4][5] = 1;
    tablero[3][5] = 1;

    int iteration = 0;
    while(1){
        printf("iteration %i)\n", iteration);

        printTablero(tablero);
        getchar();

        gameTick(tablero);
        iteration++;
        system("@cls||clear");
    }

    return 0;
}
