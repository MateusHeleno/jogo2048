#include "jogo2048.h"

int main(){
    int n = 4; // tamanho do tabuleiro 
    /*int **tabuleiro;*/
    char escolha; // escolha no menu
    int repetirMenu = 0; // variavel para controlar a repetição do menu
    menuInicial(&escolha); // começando o programa com o menu e pedindo a escolha
    int tabuleiro[4][4];

    for(int i = 0;i<n;i++){
        for (int j = 0;j<n;j++){
            tabuleiro[i][j] = 0;
        }
    }

    tabuleiro[0][0] = 8;tabuleiro[0][1] = 0;tabuleiro[0][2] = 2;tabuleiro[0][3] = 2;
    tabuleiro[1][1] = 4; 
    tabuleiro[2][2] = 8;
    tabuleiro[3][3] = 16;
    

    do{
        switch(escolha){
        case 'R': case 'r': 
            sair(&escolha);
            repetirMenu = 1; //  tenho que colocar esse repetir menu = 0, pra dps da primeira iteração quando ele voltar aqui parar de repetir
            break;
        case 'N': case 'n':
            tamanhoJogo(&n);
            /*tabuleiro = criaMatriz(n);*/
            
            mapa(n,tabuleiro);          
            moveE(n,tabuleiro);
            mapa(n,tabuleiro);
            repetirMenu = 0;
            //liberaMatriz(tabuleiro,n);
            break;
        case 'J': case 'j':
            printf("%c\n",escolha);
            repetirMenu = 0;
            break;
        case 'C': case 'c':
            printf("%c\n",escolha);
            repetirMenu = 0;
            break;
        case 'S': case 's':
            printf("%c\n",escolha);
            repetirMenu = 0;
            break;
        case 'M': case 'm':
            printf("%c\n",escolha);
            repetirMenu = 0; //
            break;
        case 'A': case 'a':
            ajuda();
            menuInicial(&escolha);
            repetirMenu = 1;
            break;
        default:
            printf("\nOpção inválida, por favor escolha as opções listadas abaixo\n");
            menuInicial(&escolha);
            repetirMenu = 1;
            break;
        }
    }while(repetirMenu);

    return 0;
}

