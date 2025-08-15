/* Mateus Oliveira Heleno
   25.1.4007 */

#include "jogo2048.h"

int main(){
    
    int n;
    
    int my = 0;
    int desfazer = 0,countDesfeito = 0;
    int countTrocado = 0;
    n = tamanhoJogo();
    int pontuacao =0;
   
    int **tabuleiro = criaMatriz(n);
    srand(time(NULL));
    
    preencher0(n,tabuleiro);
    char escolha;

    tabuleiro[0][1] = 512;

    novoNumero(n,tabuleiro);
    novoNumero(n,tabuleiro);

    char instrucao[20];
    criarArquivo(n,tabuleiro);
    do{
        int **copiaTab;
        int incorreto;
        int desfeito = numDesfazer(n,tabuleiro) - countDesfeito;
        int trocado = numTroca(n,tabuleiro) - countTrocado;

        mapa(n,tabuleiro,pontuacao,desfeito,trocado);
        
        
        
        comandos();
        int movimento = 0;
        do{
            incorreto = 0;
            printf("Escolha: ");
            fgets(instrucao,20,stdin);
            retiraN(instrucao);
            maiuscula(instrucao);
            printf("%s",instrucao);
            printf("\n");
            if(strcmp(instrucao, "VOLTAR") == 0){ 
                menuInicial(&escolha);
            }
            else if(strcmp(instrucao, "A") == 0){    
                copiaTab = copiaTabuleiro(n,tabuleiro);
                
                moveE(n,tabuleiro,&pontuacao);
                
                
                movimento = 1;
            } 
            else if(strcmp(instrucao, "D") == 0){ 
                copiaTab = copiaTabuleiro(n,tabuleiro);
                
                moveD(n,tabuleiro,&pontuacao);
                
                
                movimento = 1;
            }
            else if(strcmp(instrucao, "W") == 0){  
                copiaTab  = copiaTabuleiro(n,tabuleiro);
                
                moveC(n,tabuleiro,&pontuacao);
                
                
                movimento = 1;
            }
            else if(strcmp(instrucao, "S") == 0){  
                copiaTab = copiaTabuleiro(n,tabuleiro);
                
                moveB(n,tabuleiro,&pontuacao);
                
                
                movimento = 1;
            }
            else if(strcmp(instrucao, "U") == 0){ 
                desfazer++;
                if(desfazer == 1){
                    if(desfeito > 0){ 
                        anteceder(n,tabuleiro);
                        countDesfeito++;
                    }
                    else
                        printf("Você não tem mais movimentos para voltar\n");
                }
                else    
                    printf("Você não pode voltar duas vezes seguidas, favor fazer outro movimento.\n");
                
            }
            else if(strcmp(instrucao,"T POS1, POS2") == 0){ //pensando em usar sscanf
    
                    if(trocado > 0){ 
                        printf("%s\n",instrucao);
                        countTrocado++;
                    }
                    else
                        printf("Você não tem mais movimentos para trocar\n");
                    
            }
            else{    
                printf("\nOpção inválida, por favor escolha novamente dentre os comandos apresentados\n");
                incorreto = 1;
            }
        }while(incorreto == 1);

        if(movimento == 1){ 
            if(validacaoJogada(n,copiaTab,tabuleiro) == 0){ 
                printf("Movimento inválido,nenhuma peça se moveu. Tente uma direção diferente!;\n");
                if(desfazer == 1)
                    desfazer = 0;
            }
            else{
                criarArquivo(n,copiaTab); // vai salvar a matriz q ele copiou antes do movimento, entao nao da pra usar no salvamento, pois n tem o ultimo movimento
                novoNumero(n,tabuleiro);
                desfazer =0; // como entrou em número, sabe que ele nao repetiu o desfazer
            }
            
            liberaMatriz(n,copiaTab);
        }
        
        
        my++;  
    }while( my  > -1); //totalmente proisório
    
    liberaMatriz(n,tabuleiro);
}
