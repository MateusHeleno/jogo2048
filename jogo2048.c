/* Mateus Oliveira Heleno
   25.1.4007 */

#include "jogo2048.h"

int main(){
    
    char escolha[7]; // escolha no menu
    
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
                jogo();
                break;
            case 'J': case 'j':
                printf("%s\n",escolha);
                break;
            case 'C': case 'c':
                printf("%s\n",escolha);
                break;
            case 'S': case 's':
                printf("%s\n",escolha);
                break;
            case 'M': case 'm':
                printf("%s\n",escolha); // so para salvar os comentarios de uma vez
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

