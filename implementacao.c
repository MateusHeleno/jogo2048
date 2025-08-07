#include "jogo2048.h"
void jogo(){
    char escolha;
    menuInicial(&escolha);
    int repetirMenu = 0;

    do{
        switch(escolha){
        case 'N': case 'n': // probabilidade de ser usado maior
            printf("%c\n",escolha);
            repetirMenu = 0;
            break;
        case 'R': case 'r':
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
        case 'A': case 'a':
            printf("%c\n",escolha);
            repetirMenu = 0;
            mapa();
            break;
        case 'M': case 'm':
            printf("%c\n",escolha);
            repetirMenu = 0;
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

    int n;
    scanf("%d",&n);
    // linha de cima    
    printf("%s",TAB_TL); // Ponta esquerda
    for(int i = 1;i<n;i++){
        printf("%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_TJ); // Meio
    }
    printf("%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_TR); // Ponta direita

    for(int i = 0; i < n;i++){
        printf("%s",TAB_VER);
        for(int j = 0; j < n; j++){
            printf(" %d %s",5,TAB_VER);
            }

        
        if (i<n-1){  // Controla a impressao só pra imprimir as linhas do meio
            printf("\n%s",TAB_ML);  // primeira parede
            for (int j = 0; j <n;j++){ 
                if (j < n-1) {  
                    printf("%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_MJ); // paredes do meio ao final
                }
                else if ( j  == n-1)
                   printf("%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_MR);
            }
            
        }
    }
    

    // linha de cima    
    printf("\n%s",TAB_BL); // Ponta esquerda
    for(int i = 1;i<n;i++){
        printf("%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_BJ); // Meio
    }
    printf("%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_BR); // Ponta direita

}