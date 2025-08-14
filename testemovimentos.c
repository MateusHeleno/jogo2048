#include "jogo2048.h"

int main(){
    
    int n;
    
    int my = 0;
    tamanhoJogo(&n);
    
   
    int **tabuleiro = criaMatriz(n);
    srand(time(NULL));
    
    preencher0(n,tabuleiro);
    char escolha;

    tabuleiro[0][0] = 8;tabuleiro[0][1] = 0;tabuleiro[0][2] = 2;tabuleiro[0][3] = 2;
    tabuleiro[1][1] = 4; 
    tabuleiro[2][2] = 8;
    tabuleiro[3][3] = 16;

    char instrucao[10];
    criarArquivo(n,tabuleiro);
    do{
        int **copiaTab;
        int incorreto;
        mapa(n,tabuleiro);
        
        novoNumero(n,tabuleiro);
        
        comandos();
        int movimento = 0;
        do{
            incorreto = 0;
            printf("Escolha: ");
            fgets(instrucao,10,stdin);
            retiraN(instrucao);
            maiuscula(instrucao);
            
            printf("\n");
            if(strcmp(instrucao, "VOLTAR") == 0){ 
                menuInicial(&escolha);
            }
            else if(strcmp(instrucao, "A") == 0){    
                copiaTab = copiaTabuleiro(n,tabuleiro);
                criarArquivo(n,tabuleiro);
                moveE(n,tabuleiro);
                
                
                movimento = 1;
            } 
            else if(strcmp(instrucao, "D") == 0){ 
                copiaTab = copiaTabuleiro(n,tabuleiro);
                criarArquivo(n,tabuleiro);
                moveD(n,tabuleiro);
                
                
                movimento = 1;
            }
            else if(strcmp(instrucao, "W") == 0){  
                copiaTab  = copiaTabuleiro(n,tabuleiro);
                criarArquivo(n,tabuleiro);
                moveC(n,tabuleiro);
                
                
                movimento = 1;
            }
            else if(strcmp(instrucao, "S") == 0){  
                copiaTab = copiaTabuleiro(n,tabuleiro);
                criarArquivo(n,tabuleiro);
                moveB(n,tabuleiro);
                
                
                movimento = 1;
            }
            else if(strcmp(instrucao, "U") == 0){ 
                //colcoar confição para quantos antenceder
                anteceder(n,tabuleiro);
                
            }
            else if(strcmp(instrucao, "T") == 0){ 
                printf("%s",instrucao);
                
            }
            else{    
                printf("\nOpção inválida, por favor escolha novamente dentre os comandos apresentados\n");
                incorreto = 1;
            }
        }while(incorreto == 1);

        if(movimento == 1){ 
            if(validacao(n,copiaTab,tabuleiro) == 0){ 
                printf("Movimento inválido,nenhuma peça se moveu. Tente uma direção diferente!;\n");
            }
            else{ 
                novoNumero(n,tabuleiro);
            }
            liberaMatriz(n,copiaTab);
        }
        
        
        my++;  
    }while( my  > -1); //totalmente proisório
    
    liberaMatriz(n,tabuleiro);
}
