#include "jogo2048.h"

int main(){
    int mat[4][4];
    int n = 4;
    /*char h;
    do{
        printf("Digite um número entre 4 e 5: ");
        scanf("%c",&h);
        limpar_buffer();
    }while(h < '4' || h > '6');
    */ //pensando em utlizar essa solução pra o scanf da escolha, onde tem que receber o intteiro

    srand(time(NULL));
    
    preencher0(n,mat);
    
    mat[0][0] = 8;mat[0][1] = 0;mat[0][2] = 2;mat[0][3] = 2;
    mat[1][1] = 4; 
    mat[2][2] = 8;
    mat[3][3] = 16;

    char andar;
    do{
        mapa(n,mat);
        printf("Voce quer andar para qual lado: ");
        scanf("%c",&andar);
        limpar_buffer();
        printf("\n");
        switch(andar){
            case 'a': case 'A':
                moveE(n,mat);
                break;
            case 'd': case 'D':
                moveD(n,mat);
                break;
            case 'w': case 'W':
                moveC(n,mat);
                break;
            case 's': case 'S':
                moveB(n,mat);
                break;
        }
        novoNumero(n,mat);
    }while( n == 4); //totalmente proisório
}
