#include "jogo2048.h"

int main(){
    int mat[4][4];
    int n = 4;

    for(int i = 0;i<n;i++){
        for (int j = 0;j<n;j++){
            mat[i][j] = 0;
        }
    }

    mat[3][3] = 8;mat[0][1] = 4;mat[0][2] = 2;mat[0][3] = 2;
    mat[1][1] = 4; 
    mat[2][2] = 4;
    mat[0][0] = 16; 
    //andar para esquerda
    mapa(n,mat);
    moveE(n,mat);
    mapa(n,mat);
    moveD(n,mat);
    mapa(n,mat);
    /*moveC(n,mat);
    mapa(n,mat);*/

    moveB(n,mat);
    mapa(n,mat);
}
