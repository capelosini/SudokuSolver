#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
// #include <string.h>

// double prob(int game[9][9], int number, int x, int y){
//     int c = 0;
//     for (int i=0; i<9; i++){
//         c+=game[y][i];
//         c+=game[i][x];
//     }
//     c-=number;
//     return 1./((double)c/number);
// }

// probability base
// void fixBlock(int (*game)[9], int bx, int by){
//     double best=0;
//     int bestX=0;
//     int bestY=0;
//     for (int i=by; i<by+3; i++){
//         for (int j=bx; j<bx+3; j++){
//             if (game[i][j]){
//                 double value = prob(game, game[i][j], j, i);
//                 if (value > best){
//                     best=value;
//                     bestX=j;
//                     bestY=i;
//                 }
//             }
//         }
//     }
//     if (best){
//         for (int i=by; i<by+3; i++){
//             for (int j=bx; j<bx+3; j++){
//                 if (i != bestY || j != bestX){
//                     game[i][j]=0;
//                 }
//             }
//         }
//     }
// }

// void choosePos(int (*game)[9], int n){
//     int c=0;
//     for (int i=0; i<9; i++){
//         for (int j=0; j<9; j++){
//             if(c == n && game[i][j]){
//                 game[i][j]=0;
//             }
//             else if (game[i][j]){
//                 c++;
//             }
//         }
//     }
// }

// int findNumbersPosBlocks(int (*game)[9], int number){
//     int changes=0;
//     for(int i=0; i<3; i++){
//         for(int j=0; j<3; j++){
//             int startPosX=3*j;
//             int startPosY=3*i;
//             int count=0;
//             for (int y=startPosY; y<startPosY+3; y++){
//                 for (int x=startPosX; x<startPosX+3; x++){
//                     if (game[y][x] == number){
//                         count++;
//                         // if (count > 1)
//                         //     break;
//                     }
//                 }
//                 if (count > 1)
//                     break;
//             }
//             if (count == 1){
//                 continue;
//             }
//             for (int y=startPosY; y<startPosY+3; y++){
//                 for (int x=startPosX; x<startPosX+3; x++){
//                     if (game[y][x] != 0){
//                         game[y][x]=0;
//                         changes++;
//                     }
//                 }
//             }
//         }
//     }
//     return changes;
// }

// void clearUnknown(int (*game)[9], int number){
//     for(int i=0; i<3; i++){
//         for(int j=0; j<3; j++){
//             int startPosX=3*j;
//             int startPosY=3*i;
//             int s = 0;
//             for (int y=startPosY; y<startPosY+3; y++){
//                 for (int x=startPosX; x<startPosX+3; x++){
//                     s+=game[y][x];
//                 }
//             }
//             if (s != 0 && s != number){
//                 for (int y=startPosY; y<startPosY+3; y++){
//                     for (int x=startPosX; x<startPosX+3; x++){
//                         game[y][x]=0;
//                     }
//                 }
//             }
//         }
//     }
// }

unsigned char isWrong(int game[9][9], int number, int x, int y){
    if (number < 1 || x < 0 || x >= 9 || y < 0 || y>= 9){
        return 1;
    }
    // line search
    for (int i=0; i<9; i++){
        if (game[i][x] == number){
            return 1;
        }
    }
    for (int i=0; i<9; i++){
        if (game[y][i] == number){
            return 1;
        }
    }

    //block search
    int x2=x-(x%3);
    int y2=y-(y%3);

    for (int i=y2; i<y2+3; i++){
        for (int j=x2; j<x2+3; j++){
            if (j==x && i==y)
                continue;
            if (game[i][j] == number){
                return 1;
            }
        }
    }

    return 0;
}

void enumN(int game[9][9], int (*output)[9], int number){
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (game[i][j] != 0 || isWrong(game, number, j, i)){
                output[i][j]=0;
            }else{
                output[i][j]=number;
            }
        }
    }
}

void merge(int (*dest)[9], int values[9][9]){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if (values[i][j] != 0 && dest[i][j] == 0){
                dest[i][j]=values[i][j];
            }
        }
    }
}

void printGame(int game[9][9]){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    for (int i=0; i<9; i++){
        if ((i) % 3 == 0)
            printf("------------------------\n");
        for (int j=0; j<9; j++){
            if (j == 0)
                printf("| ");
            printf("%d ", game[i][j]);
            if ((j+1) % 3 == 0)
                printf("| ");
        }
        printf("\n");
    }
    printf("------------------------\n\n");
}

void findNumbersPos(int (*game)[9], int number){
    // horizontal line
    for (int i=0; i<9; i++){
        unsigned char alr=0;
        for(int j=0; j<9; j++){
            if (game[i][j] == number){
                if (!alr){
                    alr=1;
                }
                else{
                    for (int a=0; a<9; a++){
                        game[i][a]=0;
                    }
                    break;
                }
            }
        }
    }
}

int sumAll(int game[9][9]){
    int s=0;
    for (int j=0; j<9; j++){
        for (int i=0; i<9; i++){
            s+=game[j][i];
        }
    }
    return s;
}

void sleep(){
    double counter = 0;
    while (counter < 100){
        counter+=0.00001;
    }
}

void solve(int (*game)[9]){
    int nGames[9][9][9];
    int lastSum=0;
    int t=0;
    //less zeros
    while (lastSum != 405){
        for (int i=0; i<9; i++){
            enumN(game, nGames[i], i+1);
            findNumbersPos(nGames[i], i+1);
            //while (findNumbersPosBlocks(nGames[i], i+1) != 0);
            merge(game, nGames[i]);
            sleep();
            printGame(game);
        }
        t++;
        printf("\n%d\n", t);

        int s = sumAll(game);
        if (s == lastSum){
            // infinite loop detect
            break;
        } else{
            lastSum=s;
        }
    }
}


// easy
int game[9][9] = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}};

// medium
// int game[9][9] = {
//     {0,0,0,2,6,0,7,0,1},
//     {6,8,0,0,7,0,0,9,0},
//     {1,9,0,0,0,4,5,0,0},
//     {8,2,0,1,0,0,0,4,0},
//     {0,0,4,6,0,2,9,0,0},
//     {0,5,0,0,0,3,0,2,8},
//     {0,0,9,3,0,0,0,7,4},
//     {0,4,0,0,5,0,0,3,6},
//     {7,0,3,0,1,8,0,0,0}
// };

// ultra hard
// int game[9][9] = {
//     {8,0,0,0,0,0,0,0,0},
//     {0,0,3,6,0,0,0,0,0},
//     {0,7,0,0,9,0,2,0,0},
//     {0,5,0,0,0,7,0,0,0},
//     {0,0,0,0,4,5,7,0,0},
//     {0,0,0,1,0,0,0,3,0},
//     {0,0,1,0,0,0,0,6,8},
//     {0,0,8,5,0,0,0,1,0},
//     {0,9,0,0,0,0,4,0,0}
// };

int main(){
    solve(game);
    return 0;
}
