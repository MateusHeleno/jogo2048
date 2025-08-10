#include "jogo2048.h"

typedef struct{
    char nome[20];
    int rank,troca,desfazer;
    int tabuleiro[4][4];
}Jogo;


/*void jogo(){
    int n; // tamanho do tabuleiro 
    char escolha; // escolha no menu
    int repetirMenu = 0; // variavel para controlar a repetição do menu
    menuInicial(&escolha); // começando o programa com o menu e pedindo a escolha

    do{
        switch(escolha){
        case 'R': case 'r': 
            sair(&escolha);
            repetirMenu = 1; //  tenho que colocar esse repetir menu = 0, pra dps da primeira iteração quando ele voltar aqui parar de repetir
            break;
        case 'N': case 'n':
            tamanhoJogo(&n);
            mapa(n);
            printf("%d",n);
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
}*/

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
    else 
        limpar_buffer();
}

void maiuscula(char nome[]){
    int tam = strlen(nome);
    for (int i =0; i < tam;i++){
        nome[i] = toupper(nome[i]);
    }
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

void mapa(int n,int mat[4][4]){
    // teste
    Jogo total[10];
    
    for(int i = 0;i<n;i++){
        for (int j = 0;j<n;j++){
            total[0].tabuleiro[i][j] = mat[i][j];
        }
    }
   // até aqui 

    // linha de cima 
    printf("%s",TAB_TL); // Ponta esquerda
    for(int i = 1;i<n;i++){ // começa do um porque a ponta eu ja coloquei
        printf("%s%s%s%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_TJ); // Meio
    }
    printf("%s%s%s%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_TR); // Ponta direita

    for(int i = 0; i < n;i++){ // impressao da matriz
        printf("%s",TAB_VER); // colocando a parede esquerda
        for(int j = 0; j < n; j++){ 
            if (mat[i][j] == 0)
                printf("      %s",TAB_VER); // imprimindo o valor e colocando as divisorias
            else if(mat[i][j] < 10)
                printf("  %d   %s",total[0].tabuleiro[i][j],TAB_VER);
            else if(mat[i][j] < 100)
                printf("  %d  %s",total[0].tabuleiro[i][j],TAB_VER);
            else if(mat[i][j] < 1000) 
                printf(" %d  %s",total[0].tabuleiro[i][j],TAB_VER);
            else  
                printf(" %d %s",total[0].tabuleiro[i][j],TAB_VER);
        }

        if (i< n-1 ){  // Controla a impressao só pra imprimir as linhas horizontais do meio 
            printf("\n%s",TAB_ML);  // primeira parede
            for (int j = 0; j <n;j++){ 
                if (j < n-1 ) {  
                    printf("%s%s%s%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_MJ); // impressao das horizontais e das divisorias menos a ultima
                }
                else if ( j  == n-1 )
                   printf("%s%s%s%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_MR); // impressao da ultima parte, porque a parede lateral é diferente 
            }
            
        }
    }

    // linha de baixo  
    printf("\n%s",TAB_BL); // Ponta esquerda
    for(int i = 1;i<n;i++){
        printf("%s%s%s%s%s%s%s",TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_BJ); // Meio
    }
    printf("%s%s%s%s%s%s%s\n",TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_HOR,TAB_BR); // Ponta direita

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
    printf("- O jogador perde se não houver mais movimentos válidos possíveis.\n\n");

    char saida[3]; // Esperado a resposta OK
    int cont = 1;
    do{
        if(cont > 1)
            printf("Apenas a palavra OK sai do código, se quiser realmente sair digite novamente: ");
        else
            printf("Digite OK para voltar ao menu : ");
            
        fgets(saida,3,stdin);
        retiraN(saida);//Retira o \n e limpar o buffer
        maiuscula(saida);
        cont++;
    }while(strcmp(saida,"OK"));
}

void sair(char *escolha){
    char decisao[12];
    int cont = 1;
    do{
        if(cont > 1)
            printf("Digite apenas \"Continuar\" ou \"Sair\" para fazer sua escolha: ");// a barra invertida \ antes das aspas é para digitar ela no terminal
        else
            printf("\nVocê deseja sair do jogo ?Responda com \"Continuar\" para ficar e \"Sair\" para fechar o jogo: ");
    
        fgets(decisao,12,stdin);
        retiraN(decisao); //Retira o \n e limpar o buffer
        maiuscula(decisao);
        cont++;
    }while(strcmp(decisao, "CONTINUAR") != 0 && strcmp(decisao, "SAIR") != 0); // strcmp retorna 0 se forem iguais
    if(!strcmp(decisao, "SAIR"))
        exit(0);
    else 
        menuInicial(escolha);    
}

void tamanhoJogo(int *n){
    int cont = 1;
    do{
        if (cont > 1)
            printf("\nOpção inválida, por favor escolha novamente");
        printf("\n– (4) Jogo padrão 4 x 4.\n– (5) Jogo 5 x 5.\n– (6) Jogo 6 x 6.\nEscolha: ");
        scanf("%d",n);
        cont++;
    }while( *n < 4 || *n > 6);

}

/*int ** criaMatriz(int n){
    int **matriz;
    matriz = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(n * sizeof(int));
    }
    return matriz;
}

void liberaMatriz(int **matriz, int n){
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
 }*/  
 

// para os moviemntos de esquerda e direita vou fixar o valor do i e mexer apenas no j lendo a matriz da maneira convencional linha por linha 
void moveE(int n, int mat[4][4]){ 
    //andar para esquerda
    for (int i = 0; i < n; i++) {
        int k = 0; // vai indicar minhas casas
    
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                mat[i][k] = mat[i][j];  
                k++;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            mat[i][k] = 0;
            k++;
        }
    }  
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
    
            if (mat[i][j] != 0 && mat[i][j] == mat[i][j+1]) {
                    mat[i][j] = mat[i][j] * 2;      // Dobra o valor do primeiro bloco
                    mat[i][j+1] = 0;     // Zera o segundo bloco

            }
        }
    }

    // andar para esquerda
    for (int i = 0; i < n; i++) {
        int k = 0; // vai indicar minhas casas
    
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                mat[i][k] = mat[i][j];  
                k++;
            }
        }
        // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            mat[i][k] = 0;
            k++;
        }
    } 
}

void moveD(int n, int mat[4][4]){ 
    //andar para direita
    for (int i = 0; i < n; i++) {
        int k = n-1; // vai indicar minhas casas
    
        for (int j = n-1; j >= 0; j--) {
            if (mat[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                mat[i][k] = mat[i][j];  
                k--;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k >= 0) {
            mat[i][k] = 0;
            k--;
        }
    }  
    
    for (int i = 0; i < n; i++) {
        for (int j = n-1; j > 0; j--) {
    
            if (mat[i][j] != 0 && mat[i][j] == mat[i][j-1]) {
                    mat[i][j] = mat[i][j] * 2;      // Dobra o valor do primeiro bloco
                    mat[i][j-1] = 0;     // Zera o segundo bloco

            }
        }
    }

    //andar para direita
    for (int i = 0; i < n; i++) {
        int k = n-1; // vai indicar minhas casas
    
        for (int j = n-1; j >= 0; j--) {
            if (mat[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                mat[i][k] = mat[i][j];  
                k--;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k >= 0) {
            mat[i][k] = 0;
            k--;
        }
    }

}

// para os moviemntos de cima e baixo vou fixar o valor do j e mexer apenas no i lendo a matriz da maneira inversa coluna po coluna, le uma coluna inteira e so dps pula pra próxima

void moveC(int n, int mat[4][4]){ 
    //andar para esquerda
    for (int i = 0; i < n; i++) {
        int k = 0; // vai indicar minhas casas
    
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                mat[k][j] = mat[i][j];  
                k++;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            mat[i][k] = 0;
            k++;
        }
    }  
    
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n ; j++) {
    
            if (mat[i][j] != 0 && mat[i][j] == mat[i][j+1]) {
                    mat[i][j] = mat[i][j] * 2;      // Dobra o valor do primeiro bloco
                    mat[i+1][j] = 0;     // Zera o segundo bloco

            }
        }
    }

    // andar para esquerda
    for (int i = 0; i < n; i++) {
        int k = 0; // vai indicar minhas casas
    
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                mat[k][j] = mat[i][j];  
                k++;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            mat[i][k] = 0;
            k++;
        }
    }   
}


