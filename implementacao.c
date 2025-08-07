#include "jogo2048.h"
void jogo(){
    char escolha;
    menuInicial(&escolha);
    int repetirMenu = 0;

    do{
        switch(escolha){
        case 'R': case 'r': 
            printf("%c\n",escolha);
            repetirMenu = 0;
            break;
        case 'N': case 'n':
            printf("%c\n",escolha);
            repetirMenu = 0;
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
            repetirMenu = 0;
            mapa();
            break;
        case 'A': case 'a':
            ajuda();
            sleep(4); // pausa o programa por 4 segundos , pra dar tempo de dar uma olhada na ajuda e dps voltar a imprimir o menu, ela é da biblioteca unistd.h
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

    mapa();
  
}

void limpar_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void retiraN(char nome[])
{
    int tam = strlen(nome);
    if (nome[tam - 1] == '\n') // remove o \n do fgets
        nome[tam - 1] = '\0'; 
}

void menuInicial(char *escolha){
    printf("\n ============= MENU =============\n");
    printf("(R) Sair\n(N) Novo jogo\n(J) Continuar o jogo atual\n");
    printf("(C) Carregar um jogo salvo\n(S) Salvar o jogo atual\n");
    printf("(M) Mostrar Ranking\n(A) Ajuda com as instruções de como jogar\n");
    printf("\nEscolha: ");
    scanf("%c",escolha);//escolha ja é um endereço de memória
    limpar_buffer();
}

void mapa(){
    int n = 4;
    // linha de cima    
    printf("%s",TAB_TL); // Ponta esquerda
    for(int i = 1;i<n;i++){ // começa do um porque a ponta eu ja coloquei
        printf("%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_TJ); // Meio
    }
    printf("%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_TR); // Ponta direita

    for(int i = 0; i < n;i++){ // impressao da matriz
        printf("%s",TAB_VER); // colocando a parede esquerda
        for(int j = 0; j < n; j++){ 
            printf(" %d %s",5,TAB_VER); // imprimindo o valor e colocando as divisorias
            }

        if (i< n-1 ){  // Controla a impressao só pra imprimir as linhas horizontais do meio 
            printf("\n%s",TAB_ML);  // primeira parede
            for (int j = 0; j <n;j++){ 
                if (j < n-1 ) {  
                    printf("%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_MJ); // impressao das horizontais e das divisorias menos a ultima
                }
                else if ( j  == n-1 )
                   printf("%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_MR); // impressao da ultima parte, porque a parede lateral é diferente 
            }
            
        }
    }

    // linha de baixo  
    printf("\n%s",TAB_BL); // Ponta esquerda
    for(int i = 1;i<n;i++){
        printf("%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_BJ); // Meio
    }
    printf("%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_BR); // Ponta direita

}

void ajuda() {
    printf("\nO jogo2048 clássico é jogado em um tabuleiro de 4 x 4, com peças numéricas que deslizam suavemente\n");
    printf("quando o jogador as move em um dos quatro sentidos disponíveis: para cima, para baixo, à esquerda e à direita.\n");
    printf("A cada movimento, um novo número aparece aleatoriamente em um local vazio no tabuleiro, com valor 2 ou 4.\n");
    printf("As peças (blocos) deslizam o mais longe possível na direção escolhida, até que sejam interrompidas\n");
    printf("por outro bloco ou pela borda do tabuleiro. Se duas peças com o mesmo número colidirem durante o movimento,\n");
    printf("elas se fundem, e a posição resultante recebe o valor da soma das duas peças que colidiram.\n");
    printf("A peça resultante não pode se fundir novamente na mesma jogada. Blocos com pontuações maiores possuem cores diferentes.\n\n");

    printf("Regras:\n");
    printf("- O jogo começa com duas posições aleatórias do tabuleiro preenchidas.\n");
    printf("- A cada jogada, o jogador deve escolher uma direção (cima, baixo, esquerda ou direita).\n");
    printf("- Todas as peças se movem o máximo possível nessa direção, embora algumas possam se mover mais que outras.\n");
    printf("- Duas peças adjacentes (na direção do movimento) com números iguais se combinam em uma única peça contendo a soma desses números.\n");
    printf("- Um movimento é considerado válido quando pelo menos uma peça pode ser movida, seja por deslocamento ou por combinação.\n");
    printf("- Ao final de cada jogada, uma nova peça é gerada aleatoriamente em uma posição vazia do tabuleiro (se houver).\n");
    printf("- Para vencer, o jogador deve formar uma peça com o número 2048.\n");
    printf("- O jogador perde se não houver mais movimentos válidos possíveis.\n");
}