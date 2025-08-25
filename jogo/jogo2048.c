/* Mateus Oliveira Heleno
   25.1.4007 */

#include "jogo2048.h"

int main(){
    
    char escolha[7]; // escolha no menu
    
    int jogoIniciado = 0;
    while(1){ 
        menuInicial(); // começando o programa com o menu e pedindo a escolha
        fgets(escolha,7,stdin);
        retiraN(escolha);
        retiraEspacos(escolha);
        maiuscula(escolha);
        
        if(strlen(escolha) != 1) // se ela tiver tamanho maior que 1 ela escreve algo incorreto na posicao 1
            escolha[0] = 0;

        

        switch(escolha[0]){
            case 'R': case 'r': 
                if(sair() == 1){ 
                    printf("\nEspero que tenha gostado da experiência,volte sempre !!\nSaindo do jogo...\n");
                    return 0;
                }                
                break;
            case 'N': case 'n':
                novoJogo();
                jogoIniciado = 1;
                break;
            case 'J': case 'j':
                if(jogoIniciado)
                    carregarJogoAtual();
                else
                    printf("\nVocê nao tem nenhum jogo iniciado para continuar\n");
                   
                break;
            case 'C': case 'c':
                carregarJogoPronto();
                break;
            case 'S': case 's':
                if(jogoIniciado)
                    salvarJogo();
                else
                    printf("\nVocê nao tem nenhum jogo iniciado para salvar\n");
                break;
            case 'M': case 'm':
                mostrarRanking();
                break;
            case 'A': case 'a':
                ajuda();
                break;
            default:
                printf("\nOpção inválida, por favor escolha as opções listadas abaixo\n");
                break;
            }
    }

    return 0;
}

