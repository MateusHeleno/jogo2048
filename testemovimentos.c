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

    char instrucao[10];
    criarArquivo(n,tabuleiro);
    do{
        mapa(n,tabuleiro);
        comandos();
        do{
            int incorreto = 0;
            printf("Escolha: ");
            fgets(instrucao,10,stdin);
            retiraN(instrucao);
            maiuscula(instrucao);
            
            printf("\n");
            if(strcmp(instrucao, "VOLTAR") == 0)
                moveE(n,tabuleiro);
            else if(strcmp(instrucao, "A") == 0)   
                moveE(n,tabuleiro);   
            else if(strcmp(instrucao, "D") == 0)
                moveD(n,tabuleiro);
            else if(strcmp(instrucao, "W") == 0) 
                moveC(n,tabuleiro);
            else if(strcmp(instrucao, "S") == 0) 
                moveB(n,tabuleiro);
            else if(strcmp(instrucao, "U") == 0) 
                printf("%s",instrucao);
            else if(strcmp(instrucao, "T") == 0) 
                printf("%s",instrucao);
            else{    
                printf("\nOpção inválida, por favor escolha novamente dentre os comandos apresentados\n");
                incorreto = 1;
            }
        }while(incorreto == 1);


        if(validacao(n,tabuleiro) == 0) 
            printf("Movimento inválido,nenhuma peça se moveu. Tente uma direção diferente!;\n");
        else{ 
            novoNumero(n,tabuleiro);
            criarArquivo(n,tabuleiro);
        }
        my++;  
    }while( my  > -1); //totalmente proisório
    
    liberaMatriz(n,tabuleiro);
}
