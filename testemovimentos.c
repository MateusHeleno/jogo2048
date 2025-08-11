#include "jogo2048.h"

int main(){
    
    int n;
    int my= 0;

    tamanhoJogo(&n);
    
   
    int **tabuleiro = criaMatriz(n);
    srand(time(NULL));
    
    preencher0(n,tabuleiro);

    tabuleiro[0][0] = 8;tabuleiro[0][1] = 0;tabuleiro[0][2] = 2;tabuleiro[0][3] = 2;
    tabuleiro[1][1] = 4; 
    tabuleiro[2][2] = 8;
    tabuleiro[3][3] = 16;

    char andar;
    do{
        mapa(n,tabuleiro);
        printf("Voce quer andar para qual lado: ");
        scanf("%c",&andar);
        limpar_buffer();
        printf("\n");
        switch(andar){
            case 'a': case 'A':
                moveE(n,tabuleiro);
                break;
            case 'd': case 'D':
                moveD(n,tabuleiro);
                break;
            case 'w': case 'W':
                moveC(n,tabuleiro);
                break;
            case 's': case 'S':
                moveB(n,tabuleiro);
                break;
        }
        novoNumero(n,tabuleiro);
        my++;
    }while( my < 5); //totalmente proisório
    liberaMatriz(n,tabuleiro);
}
