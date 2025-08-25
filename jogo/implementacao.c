/* Mateus Oliveira Heleno
   25.1.4007 */


#include "jogo2048.h"


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

void retiraEspacos(char *nome){
    int tam = strlen(nome);
    int j = 0; // índice para escrever a nova string

    for (int i = 0; i < tam; i++) {
        if (nome[i] != ' ') {     // só copia se não for espaço
            nome[j] = nome[i];
            j++;
        }
    }
    nome[j] = '\0'; // finaliza a string
}

char tornarMaior(char c)
{
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    
    return c;
}

void maiuscula(char nome[])
{
    int tam = strlen(nome);
    for (int i =0; i < tam;i++){
        nome[i] = tornarMaior(nome[i]);
    }
}

void menuInicial(){
    printf("\n ============= MENU =============\n");
    printf("(R) Sair\n(N) Novo jogo\n(J) Continuar o jogo atual\n");
    printf("(C) Carregar um jogo salvo\n(S) Salvar o jogo atual\n");
    printf("(M) Mostrar Ranking\n(A) Ajuda com as instruções de como jogar\n");
    printf("\nEscolha: ");
}

void comandos(){
    printf("<a, d, s, w>: Move as peças do tabuleiro para esquerda, direita, para baixo ou para cima, respectivamente.\n");
    printf("<u>: Desfazer o último movimento.\n"); 
    printf("<t pos1 pos2>:: Trocar duas peças de posição, ou seja, troca o conteúdo da posição pos1 com o conteúdo da posição pos2.\n");
    printf("Voltar: Volta para o menu inicial.\n\n");
    printf("Escolha: ");
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

    
    char saida[3];
    
    printf("Aperte qualquer tecla para voltar ao menu: ");
    fgets(saida,3,stdin);
}

int sair(){
    char decisao[4];
    int cont = 1;
    do{
        if(cont > 1)
            printf("Digite apenas \"S\" ou \"N\" para fazer sua escolha: ");// a barra invertida \ antes das aspas é para digitar ela no terminal
        else
            printf("\nVocê deseja sair do jogo ?Responda com \"S\" para fechar o jogo e \"N\" para continuar: ");
    
        fgets(decisao,4,stdin);
        retiraN(decisao); //Retira o \n e limpar o buffer
        retiraEspacos(decisao);
        maiuscula(decisao);
        cont++;
    }while(strcmp(decisao, "S") != 0 && strcmp(decisao, "N") != 0); // strcmp retorna 0 se forem iguais
    if(!strcmp(decisao, "S"))
        return 1;
    else 
        return 0; 
}

int tamanhoJogo(){
    int cont = 1;
    char c[7];
    do{
        if (cont > 1)
            printf("\nOpção inválida, por favor escolha novamente");
        printf("\nQual o tamanho do tabuleiro \n");
        printf("– (4) Jogo padrão 4 x 4.\n– (5) Jogo 5 x 5.\n– (6) Jogo 6 x 6.\n\nEscolha: ");
        fgets(c,7,stdin);
        retiraN(c);
        retiraEspacos(c);
        if(strlen(c) != 1)
            c[0] = 0;
        cont++;
    }while( c[0] < '4' || c[0] > '6');

    return (c[0] - '0');
}

int maiorNumero(int n,int **tabuleiro){
    int maior = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tabuleiro[i][j] > maior) {
                maior = tabuleiro[i][j];
            }
        }
    }
    return maior;
}

int quantidadeDigitos(int numero){
    // Se o número for 0  ele tem 1 dígito
    if (numero == 0) {
        return 1;
    }
    
    int digito = 0;
    while (numero > 0) {
        numero = numero / 10;
        digito++;
    }
    return digito;
}

void linhaHorizontal(int n,int digitos){
    printf("   ");
    printf(TAB_ME);
    for(int i = 0;i<n;i++){
        for(int j =0;j <digitos + 2; j++){ 
            printf(TAB_HOR);
        }
        
        if(i < n -1)
            printf(TAB_MM);
    }
       printf(TAB_MD"\n");
}

void numeroCor(int numero) {
    int cor = 0; // Variável para controlar o estilo
    int calculo = numero;
    while (calculo > 1) {
        calculo = calculo / 2;
        cor++;
    }

    
    cor = ((cor - 1) % 11) + 1; // volta ele uma pra adicionar o 1 dps
    

    switch(cor){ 
       
        case (1): 
            printf(PRETO_NO_BRANCO(" %d "),numero);    
            break;
        case (2): 
            printf(BRANCO_NO_AZUL(" %d "),numero);    
            break;
        case (3): 
            printf(PRETO_NO_AMARELO(" %d "),numero);
            break;
        case (4): 
            printf(BRANCO_NO_MAGENTA(" %d "),numero);
            break;
      case (5): 
            printf(PRETO_NO_CIANO(" %d "),numero);
            break;
        case (6): 
            printf(BRANCO_NO_VERMELHO(" %d "),numero);    
            break;
        case (7): 
            printf(PRETO_NO_VERDE(" %d "), numero);  
            break;
        case (8): 
            printf(BRANCO_NO_VERDE(" %d "), numero);  
            break;
        case(9):
            printf(AZUL_NO_BRANCO(" %d "), numero); 
            break;
        case(10):
            printf(AMARELO_NO_AZUL(" %d "), numero); 
            break;
        case(11):
            printf(VERMELHO_NO_AMARELO(" %d "), numero); 
            break;
   }

}

void mapa(Jogo *jogador){
    int n = jogador->n;
    int maior = maiorNumero(n,jogador->tabuleiro);
    int digitos = quantidadeDigitos(maior); // esse um é colocado pelo for

    int espacoE,espacoD;

    if(digitos % 2 == 0){ // descobrindo se os digitos são pares
        espacoE = digitos / 2;
        espacoD = digitos / 2;
    }
    else{
        espacoE = digitos / 2 + 1; //se for impar, colocar mais um espaço na esquerda
        espacoD = digitos / 2 ;
    }

    printf("   "); // espaço de inicio das coordenadas da letra

    for(int i = 0;i<n;i++){
        for(int j = 0; j<espacoE;j++){
        printf(" "); // espaco do lado esquerdo
        }  

        printf(" %d ",i+1); // impressão das coordenadas da linhas

        for(int k = 0; k<espacoD;k++){ //espaco do lado direito
            printf(" "); 
        }
    }
    printf("\n"); //  caindo pra primeira linha da coluna
    
  
    printf("   "); // espaço de inicio das coordenadas da letra
    printf(TAB_AE); // ponta esquerda
    for(int i = 0;i<n;i++){
        for(int j =0;j <digitos + 2; j++){ 
            printf(TAB_HOR); // meio 
        }
        
        if(i < n -1)
            printf(TAB_AM); // se nao for o final ter a junção
    }
    printf(TAB_AD"\n"); // ponta direita 

   ;
    for(int i = 0;i<n;i++){
        printf("%c  ",i+'A'); // a letra da coordena e os espaços
        printf(TAB_VER);// primeira vertical 
        for(int j =0;j <n; j++){
            int digParcial = digitos - quantidadeDigitos(jogador->tabuleiro[i][j]); 
            if(digParcial % 2 == 0){
                espacoE = digParcial / 2;
                espacoD = digParcial / 2;
            }
            else{
                espacoE = digParcial / 2  + 1 ;
                espacoD = digParcial / 2  ;
            }

            for(int k = 0; k < espacoE;k++){
                printf(" "); // espaco do lado esquerdo
            }

            if(jogador->tabuleiro[i][j] == 0)
                printf(("   ")); // se for zero, imprimir espaço
            else 
                numeroCor(jogador->tabuleiro[i][j]);

            
            for(int k = 0; k<espacoD;k++){
                printf(" "); // espaco do lado direito
            }
            
            printf(TAB_VER);

            if(i == 0 && j == n-1){ 
                printf("\tNome: %s",jogador->nome);
                break;
            }
            else if(i == 1 && j == n-1){ 
                printf("\tPontuação: %d",jogador->pontuacao);
                break;
            }
            else if(i == 2 && j == n-1){  
                printf("\tMovimentos para desfazer: %d",jogador->desfazer);  
                break;
            }
            else if(i == 3 && j == n-1){
                printf("\tMovimentos para troca de posição: %d",jogador->troca);
                break;
            }
        }
        
        printf("\n");
        if(i < n-1)
            linhaHorizontal(n,digitos);
        }

    printf("   ");
    printf(TAB_BE);
    for(int i = 0;i<n;i++){
        for(int j =0;j <digitos + 2; j++){ 
            printf(TAB_HOR);
        }
        
        if(i < n -1)
            printf(TAB_BM);
    }
    printf(TAB_BD);

    printf("\n\n");
}

// para os moviemntos de esquerda e direita vou fixar o valor do i e mexer apenas no j lendo a matriz da maneira convencional linha por linha 

void moveE(Jogo *jogador){ 
    //andar para esquerda
    int n = jogador->n;
    int **tabuleiro = jogador->tabuleiro;
    for (int i = 0; i < n; i++) {
        int k = 0; // vai indicar minhas casas
    
        for (int j = 0; j < n; j++) {
            if  (tabuleiro[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                tabuleiro[i][k] = tabuleiro[i][j];  
                k++;
                
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago, e com ctz ela ja vai ter puxado tudo antes
        while (k < n) {
            tabuleiro[i][k] = 0;
            k++;
        }
    }  
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
    
            if(tabuleiro[i][j] != 0 && tabuleiro[i][j] == tabuleiro[i][j+1]) {
                tabuleiro[i][j] = tabuleiro[i][j] * 2;      // Dobra o valor do primeiro bloco
                tabuleiro[i][j+1] = 0;     // Zera o segundo bloco
                jogador->pontuacao += tabuleiro[i][j];
                j++;

                if(tabuleiro[i][j] == 256)
                    (jogador->desfazer)++; 
            
            }   
        }
    }

    // andar para esquerda
    for (int i = 0; i < n; i++) {
        int k = 0; // vai indicar minhas casas
    
        for (int j = 0; j < n; j++) {
            if  (tabuleiro[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                tabuleiro[i][k] = tabuleiro[i][j];  
                k++;
                
            }
        }
        // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            tabuleiro[i][k] = 0;
            k++;
        }
    } 
}

void moveD(Jogo *jogador){ 
    int n = jogador->n;
    int **tabuleiro = jogador->tabuleiro;
    //andar para direita
    for (int i = 0; i < n; i++) {
        int k = n-1; // vai indicar minhas casas
    
        for (int j = n-1; j >= 0; j--) {
            if(tabuleiro[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                tabuleiro[i][k] = tabuleiro[i][j];  
                k--;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k >= 0) {
            tabuleiro[i][k] = 0;
            k--;
            
        }
    }  
    
    for (int i = 0; i < n; i++) {
        for (int j = n-1; j > 0; j--) {
    
            if(tabuleiro[i][j] != 0 && tabuleiro[i][j] == tabuleiro[i][j-1]){
                tabuleiro[i][j] = tabuleiro[i][j] * 2;      // Dobra o valor do primeiro bloco
                tabuleiro[i][j-1] = 0;     // Zera o segundo bloco
                jogador->pontuacao += tabuleiro[i][j] ;           
                j--;
                
                if(tabuleiro[i][j] == 256)
                    (jogador->desfazer)++; 
            
            }


        }
    }

    //andar para direita
    for (int i = 0; i < n; i++) {
        int k = n-1; // vai indicar minhas casas
    
        for (int j = n-1; j >= 0; j--) {
            if(tabuleiro[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                tabuleiro[i][k] = tabuleiro[i][j];  
                k--;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k >= 0) {
            tabuleiro[i][k] = 0;
            k--;
        }
    }

}

// para os moviemntos de cima e baixo vou fixar o valor do j e mexer apenas no i lendo a tabuleiroriz da maneira inversa coluna po coluna, le uma coluna inteira e so dps pula pra próxima
void moveC(Jogo *jogador){ 
    int n = jogador->n;
    int **tabuleiro = jogador->tabuleiro;
    //andar para cima
    for (int j = 0; j < n; j++) { // invertando a ordem do i e j para ler a tabuleiroriz de coluna por coluna
        int k = 0; // vai indicar minhas casas 
    
        for (int i = 0; i < n; i++) {
            if(tabuleiro[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                tabuleiro[k][j] = tabuleiro[i][j];  
                k++;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            tabuleiro[k][j] = 0;
            k++;
        }
    }  
    
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n -1; i++) {
    
            if(tabuleiro[i][j] != 0 && tabuleiro[i][j] == tabuleiro[i+1][j]) {
                tabuleiro[i][j] = tabuleiro[i][j] * 2;      // Dobra o valor do primeiro bloco
                tabuleiro[i+1][j] = 0;     // Zera o segundo bloco
                jogador->pontuacao += tabuleiro[i][j] ;
                i++;

                if(tabuleiro[i][j] == 256)
                    (jogador->desfazer)++; 
                
            
            }
        }
    }

    for (int j = 0; j < n; j++) {
        int k = 0; // vai indicar minhas casas
    
        for (int i = 0; i < n; i++) {
            if(tabuleiro[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                tabuleiro[k][j] = tabuleiro[i][j];  
                k++;
                
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k < n) {
            tabuleiro[k][j] = 0;
            k++;    
        }
    }    
}

void moveB(Jogo *jogador){ 
    int n = jogador->n;
    int **tabuleiro = jogador->tabuleiro;
    //andar para direita
    for (int j = 0; j < n; j++) {
        int k = n-1; // vai indicar minhas casas
    
        for (int i = n-1; i >= 0; i--) {
            if(tabuleiro[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                tabuleiro[k][j] = tabuleiro[i][j];  
                k--;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k >= 0) {
            tabuleiro[k][j] = 0;
            k--;
        }
    }  
    
    for (int j = 0; j < n; j++) {
        for (int i = n-1; i > 0; i--) {
    
            if(tabuleiro[i][j] != 0 && tabuleiro[i][j] == tabuleiro[i-1][j]) {
                tabuleiro[i][j] = tabuleiro[i][j] * 2;      // Dobra o valor do primeiro bloco
                tabuleiro[i-1][j] = 0;     // Zera o segundo bloco
                jogador->pontuacao += tabuleiro[i][j];
                i--;

                if(tabuleiro[i][j] == 256)
                    (jogador->desfazer)++; 
            }
        }
    }

    //andar para direita
    for (int j = 0; j < n; j++) {
        int k = n-1; // vai indicar minhas casas
    
        for (int i = n-1; i >= 0; i--) {
            if(tabuleiro[i][j] != 0) { // sef for diferente de 0, ele vai pra contar no K, se nao for nao importa, pq pode ser puxado
                tabuleiro[k][j] = tabuleiro[i][j];  
                k--;
            }
        }
    // colocar 0 onde vai ta vazia, para ficar vago
        while (k >= 0) {
            tabuleiro[k][j] = 0;
            k--;
        }
    } 

}


int **criaMatriz(int n)
{
   int **matriz;
   matriz = malloc(n * sizeof(int*));
   for (int i = 0; i < n; i++) {
       matriz[i] = malloc(n * sizeof(int));
   }
   return matriz;
}

void liberaMatriz(int n,int **tabuleiro){
    for (int i = 0; i < n; i++){ 
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

void criarArquivoSalvamento(Jogo jogador,char *nome){
    FILE *saida  = fopen(nome,"w");

    if (saida == NULL) {
        // Se não foi possível abrir, informa o erro e encerra a função
        printf("Erro ao criar o arquivo de salvamento");
        return;
    }

    fprintf(saida,"%d %d %d\n",jogador.n,jogador.desfazer,jogador.troca); // escrevendo o tamnho do tabuleiro 
    fprintf(saida, "%d %s\n", jogador.pontuacao, jogador.nome);

    for (int i = 0; i < jogador.n; i++) {
        for (int j = 0; j < jogador.n; j++) {
            fprintf(saida, "%d ", jogador.tabuleiro[i][j]);
        }
    }
    fprintf(saida, "\n");

     for (int i = 0; i < jogador.n; i++) {
        for (int j = 0; j < jogador.n; j++) {
            fprintf(saida, "%d ", jogador.tabuleiroAnterior[i][j]);
        }
    }
    fprintf(saida, "\n");    
    fclose(saida);
}


void copiaTabuleiro(Jogo *jogador){
    int n = jogador->n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                jogador->tabuleiroAnterior[i][j] = jogador->tabuleiro[i][j];
            }
        }
}

void novoNumero(Jogo *jogador){
    int x,y,valor,cont = 0,probabilidade;
    int n = jogador->n;
    int **tabuleiro = jogador->tabuleiro;
    
    switch(n){ // decide a probabilidade de ser um 4
        case 4: 
            probabilidade = 10;
            break;
        case 5:
            probabilidade = 15;
            break;
        case 6:
            probabilidade = 20;
            break;
    }
    for(int i = 0;i<jogador->n;i++){
        for (int j = 0;j<jogador->n;j++){ 
            if(jogador->tabuleiro[i][j] == 0){
                cont = 1;
                break;
            }
        }
        break;
    }
    while(cont) {
        x= rand() % n;//gera uma posição para x
        y= rand() % n;//gera uma posição para y
        valor = (rand() % 100) + 1 ;// vai gerar um valor entre 1 e 10
        
        if(valor > probabilidade)
            valor = 2;
        else 
            valor = 4;

        if(tabuleiro[x][y] == 0){ 
            tabuleiro[x][y] = valor;
            cont = 0;
        }
    }
}

void anteceder(Jogo *jogador){
    for (int i = 0; i < jogador->n; i++) {
        for (int j = 0; j < jogador->n; j++) {
            jogador->tabuleiro[i][j] = jogador->tabuleiroAnterior[i][j]; //pega um valor da posição i j da matriz            
        }
    }    
}

void preencher0(int n, int **tabuleiro){ // coloca zero em todas as posições da matriz
        for(int i = 0;i<n;i++){
            for (int j = 0;j<n;j++){
                tabuleiro[i][j] = 0;
            }
        }
}

int validacaoJogada(Jogo *jogador){  
    int n = jogador->n;    
    for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(jogador->tabuleiroAnterior[i][j] != jogador->tabuleiro[i][j]) {
                    return 1; 
                }
        }
    }
    return 0;
}

void inicializarTabuleiro(Jogo *jogador){
    novoNumero(jogador);
    novoNumero(jogador);
}

int novoJogo(){ 
    Jogo jogador;

    jogador.n = tamanhoJogo(); // fazendo a escolha do tamnho do jogo
    jogador.tabuleiro = criaMatriz(jogador.n);
    jogador.tabuleiroAnterior = criaMatriz(jogador.n); //aloca matriz de tamanho N
    jogador.pontuacao = 0;
    jogador.desfazer = 0;
    jogador.troca = 0;
    
    char nome[27];
    srand(time(NULL));
    

    printf("\nDigite seu nome: ");
    fgets(nome,27,stdin); // pega o nome do usuario
    retiraN(nome);
    strcpy(jogador.nome, nome); 

    
    preencher0(jogador.n,jogador.tabuleiro);// preenche a matriz com 0 para imprimir espaço
    preencher0(jogador.n,jogador.tabuleiroAnterior);
    inicializarTabuleiro(&jogador);// incializa com dois valores aleatórios
   
    

    
    executarJogo(&jogador); 

    return 0;
}

int executarJogo(Jogo *jogador){
    int desfazerRep = 0;
    char instrucao[20];
    char jogar[7] = "S";
    int countTrocado = numTroca(*jogador) - jogador->troca;
    int incorreto,ganhou = 0,movimento;
    
    do{
        jogador->troca = numTroca(*jogador) - countTrocado; 
        mapa(jogador);
        movimento = 0;

        do{
            incorreto = 0;
            comandos();
            fgets(instrucao,20,stdin);
            retiraN(instrucao);
            maiuscula(instrucao);
                        
            printf("\n");
            if(strcmp(instrucao, "VOLTAR") == 0){ 
                criarArquivoSalvamento(*jogador,"paraSalvamento.txt");

                liberaMatriz(jogador->n, jogador->tabuleiroAnterior); 
                liberaMatriz(jogador->n, jogador->tabuleiro);
                return 0;   

            }
            else if(strcmp(instrucao, "A") == 0){    
                copiaTabuleiro(jogador);
                moveE(jogador);
                movimento = 1;
            } 
            else if(strcmp(instrucao, "D") == 0){ 
                copiaTabuleiro(jogador);
                moveD(jogador);
                movimento = 1;
            }
            else if(strcmp(instrucao, "W") == 0){  
                copiaTabuleiro(jogador);
                moveC(jogador);
                movimento = 1;
            }
            else if(strcmp(instrucao, "S") == 0){  
                copiaTabuleiro(jogador);
                moveB(jogador);
                movimento = 1;
            }
            else if(strcmp(instrucao, "U") == 0){ 
                desfazerRep++;
                if(desfazerRep == 1){
                    if(jogador->desfazer > 0){ 
                        
                        int pontuacaoDaJogadaAnterior = diferencaPontuacao(jogador->n, jogador->tabuleiro, jogador->tabuleiroAnterior);

                        anteceder(jogador);            
                        jogador->pontuacao -= pontuacaoDaJogadaAnterior;
                        jogador->desfazer--;

    
                    }
                    else
                        printf("Você não tem movimentos para voltar\n");
                }
                else    
                    printf("Você não pode voltar duas vezes seguidas, favor fazer outro movimento.\n");
                
            }
            else if(instrucao[0] == 'T'){ 
                if(jogador->troca > 0){ 
                    if((troca(jogador, instrucao) == 1)){  //aqui eu ja fiz a troca
                        troca(jogador, instrucao); //aqui eu destroco pra copiar o tabuleiro
                        copiaTabuleiro(jogador);
                        troca(jogador, instrucao);//aqui eu troco dnv
                        countTrocado++; 
                        desfazerRep = 0;                            
                                             
                    }else{      
                        printf("\nCorrija a sintaxe da sua escrita, ela deve obedecer exatamente ao comando!!\n");
                    }
                }
                else{
                    printf("Você não tem movimentos para trocar\n");
                }
            }
            else{    
                printf("\nOpção inválida, por favor escolha novamente dentre os comandos apresentados\n");
                incorreto = 1;
            }
            
        }while(incorreto == 1);

        if(movimento == 1){ 
            if(validacaoJogada(jogador) == 0){ 
                printf("Movimento inválido, nenhuma peça se moveu. Tente uma direção diferente!\n");
            }
            else{
                
                if(jogador->n == 6) 
                    novoNumero(jogador);
                novoNumero(jogador);
                
                desfazerRep = 0;
            }
        }

        if(vitoria(*jogador) && ganhou == 0){ 
            ganhou++;
            printf("Parabéns !! Você venceu, deseja continuar ?\n ");
            printf("Digite 'S' para continuar o jogo, ou outra coisa para sair\nEscolha: ");
            fgets(jogar,7,stdin);
            retiraEspacos(jogar);
            retiraN(jogar);
            maiuscula(jogar);
        }

        if(derrota(*jogador) && jogador->troca ==0 && jogador->desfazer ==0){
            printf("Epa, parece que o tabuleiro está sem movimentos, mas foi um belo jogo\nTente novamente depois");
            strcpy(jogar, "N");
        }   
           
        
    }while(strcmp(jogar,"S") == 0); 
    atualizarRanking(jogador);
    liberaMatriz(jogador->n,jogador->tabuleiroAnterior); 
    liberaMatriz(jogador->n, jogador->tabuleiro);
    return 0;
} 

int troca(Jogo *jogador, char *instrucao){ // vou conferindo camada por camada
    int x,y,numX,numY,valorReservado;
    int n = jogador->n;
    if(instrucao[0] == 'T' && instrucao[1] == ' ')
    { // fazer igual la em baixo
        int j = 2;
        while (instrucao[j] == ' ') {
            j++; // Avança para a proxma letra
        }
        if(instrucao[j] >='A' && instrucao[j] < (('A' + n))){
            x = (instrucao[j] - 'A' );// pois aqui temos que cair em 0 tbm, que seria a posi 1    
            if (instrucao[j +1] >= '1' && instrucao [j +1] <= ('0' + n)){
                numX = (instrucao[j +1] - '1'); 
                if(instrucao[j +2] == ' '){
                    int i = j+3;
                    while (instrucao[i] == ' ') {
                        i++; // Avança para a proxma letra
                    }
                    if(instrucao[i] >= 'A' && instrucao[i] < (('A' + n))){
                        y = (instrucao[i] - 'A' );    
                        if (instrucao[i+1] >= '1' && instrucao [i+1] <= ('0' + n)){
                            numY = (instrucao[i+1] - '1'); 
                            if (jogador->tabuleiro[x][numX] == 0 || jogador->tabuleiro[y][numY] == 0) {
                                printf("\nMovimento de troca inválido: possível casa vazia.\n\n");
                                return 0; // Retorna 0 para indicar que a troca falhou e não continua
                            }
                            else {
                                valorReservado = jogador->tabuleiro[x][numX]; // guardar o valor
                                jogador->tabuleiro[x][numX] = jogador->tabuleiro[y][numY];
                                jogador->tabuleiro[y][numY] = valorReservado;                        
                                return 1; // se retornar 1 é poorque funcionou de maneira correta
                            }
                        }    
                    }         
                }   
            }       
        }   
    }    
    return 0; // houve algum erro de escrita
}

int vitoria(Jogo jogador){
  for (int i = 0; i <jogador.n; i++) {
        for (int j = 0; j < jogador.n; j++) {
            if(jogador.tabuleiro[i][j] == 2048)
                return 1;            
        }
    } 
    return 0; 
}

int derrota(Jogo jogador){
    int n = jogador.n;
    int **tabuleiro = jogador.tabuleiro;

        // confere se tem casa vaziaf
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tabuleiro[i][j] == 0) {
                return 0; // Jogo pode continuar, retorna falso.
            }
        }
    }
    // confere se tem peças iguais pros lados
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) { 
            if (tabuleiro[i][j] == tabuleiro[i][j + 1]) {
                return 0;
            }
        }
    }

    // confere se tem peças iguais pros lados
    for (int i = 0; i < n - 1; i++) { 
        for (int j = 0; j < n; j++) {
            if (tabuleiro[i][j] == tabuleiro[i + 1][j]) {
                return 0;
            }
        }
    }

    
    return 1; 
}


int numTroca(Jogo jogador){
    int troca = 0;
    int n = jogador.n;
    for(int i =0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(jogador.tabuleiro[i][j] >=512)
                troca += jogador.tabuleiro[i][j];
        }
    }

    return (troca / 512);
}

void salvarJogo(){
    char nome[20];
    Jogo jogador;
    printf("Você deseja salvar esse jogo com qual nome: ");
    scanf("%s",nome);
    limpar_buffer();

    copiarArquivoSalvamento(&jogador, nome);
   
    
}

int carregarJogo(Jogo *jogador, char *nomeArquivo) {
    FILE *entrada = fopen(nomeArquivo, "r"); 
    char lixo;
    if (entrada == NULL) {
        printf("\nNenhum jogo salvo com o nome '%s' foi encontrado!\n", nomeArquivo);
        return 0; 
    }

    
    fscanf(entrada, "%d%c%d%c%d%c", &jogador->n,&lixo, &jogador->desfazer,&lixo, &jogador->troca,&lixo);
    fscanf(entrada, "%d%c", &jogador->pontuacao,&lixo);
    fgets(jogador->nome,27,entrada);
    retiraN(jogador->nome);

    jogador->tabuleiro = criaMatriz(jogador->n);
    jogador->tabuleiroAnterior = criaMatriz(jogador->n);

    
    for (int i = 0; i < jogador->n; i++) {
        for (int j = 0; j < jogador->n; j++) {
            fscanf(entrada, "%d", &jogador->tabuleiro[i][j]);
        }
    }

    fscanf(entrada,"%c",&lixo);

    for (int i = 0; i < jogador->n; i++) {
        for (int j = 0; j < jogador->n; j++) {
            fscanf(entrada, "%d", &jogador->tabuleiroAnterior[i][j]);
        }
    }
    
    fclose(entrada);
    printf("\nJogo carregado com sucesso! Bem-vindo de volta, %s!\n", jogador->nome);
    return 1; // Retorna 1 para indicar sucesso
}

void carregarJogoAtual(){
    Jogo jogador;


    if(carregarJogo(&jogador,"paraSalvamento.txt"))
        executarJogo(&jogador);
    else
        printf("Falhar na execução do programa, pedimos mil desculpas e estamos consertando isso.");
    
}

void carregarJogoPronto(){
    Jogo jogador;

    char nome[20];
    printf("Você deseja carregar qual arquivo: ");
    scanf("%s",nome);
    limpar_buffer();

    if(carregarJogo(&jogador,nome))
        executarJogo(&jogador);
    
}

void contarPecas(int n, int** tabuleiro, int* contagem,int tam) {
        
    for (int i = 0; i < tam; i++) {
        contagem[i] = 0; 
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tabuleiro[i][j] > 0) {
                ///descobrindo o expoente,pra alocar nessa posicao do vetor, e ele tem q ser menor que tam, pra nao estrapolar,
                int expoente = (int)log2(tabuleiro[i][j]);
                if (expoente < tam) {
                    contagem[expoente]++;
                }
            }
        }
    }
}

int diferencaPontuacao(int n, int** tabuleiroAtual, int** tabuleiroAnterior) {
    int maior = 0;
    long long somaAtual = 0; 
    long long somaAnterior = 0;

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            somaAtual += tabuleiroAtual[i][j];
            somaAnterior += tabuleiroAnterior[i][j];
            if (tabuleiroAtual[i][j] > maior) 
                maior = tabuleiroAtual[i][j]; // encontrando o maior valor , nao peguei da função pra reutilizar o for
        }
    }

    if (maior == 0) 
        return 0;

    //peguei o somatorio pra saber qual numero foi gerado
    int pecaNova = somaAtual - somaAnterior;
    int expoenteNovo ;
    if (pecaNova > 0) {
        expoenteNovo = (int)log2(pecaNova);
    }

    
    int tam = (int)log2(maior) + 2; // descobri o expoente do maior Numero


    int *contagemAtual = preencherAlocandoVetor0(tam);
    int *contagemAnterior = preencherAlocandoVetor0(tam);
    int *diferencaContagem = preencherAlocandoVetor0(tam);
    int *numFusoes = preencherAlocandoVetor0(tam);

    contarPecas(n, tabuleiroAtual, contagemAtual, tam);
    contarPecas(n, tabuleiroAnterior, contagemAnterior, tam);

    for (int i = 0; i < tam; i++) {
        diferencaContagem[i] = contagemAtual[i] - contagemAnterior[i]; // fazendo a diferença de peca pra cada expoente
    } // pode ser engativa se tiver dois, usar os dois e gerar mais 

    int retirarPeca;
    int pecasConsumidas;
    //comeco do maior, para saber quantas peças eu usei pra fazer ele, e assim pode retirar nas proximas
    for (int i = tam - 2; i >= 2; i--) { // vai até a peça 4 (i=2)
        pecasConsumidas = 2 * numFusoes[i + 1]; // pecas consumidas pra fazer o proximo,primeiro caso sempre vai ser 0
        if(i == expoenteNovo){  // pra saber se foi gerado ou nao
            retirarPeca =  1 ;
        }
        else 
             retirarPeca =  0;
        
        numFusoes[i] = diferencaContagem[i] + pecasConsumidas - retirarPeca; // 
    }


    int pontuacaoDaJogada = 0;
    for (int i = 2; i < tam; i++) {
        if (numFusoes[i] > 0) {
            int valorDaPeca = (int)pow(2, i); // descovre o valor original dela 
            pontuacaoDaJogada += numFusoes[i] * valorDaPeca; // multiplica pela quantidade de vezes q foi feita
        }
    }

    free(contagemAtual);
    free(contagemAnterior);
    free(diferencaContagem);
    free(numFusoes);

    return pontuacaoDaJogada;
}

int* preencherAlocandoVetor0(int tam){
    int *vet;
    vet = (int*)malloc(tam * sizeof(int));
    for (int i = 0; i < tam; i++) {
        vet[i] = 0;
    }
    return vet;
}
void carregarRanking(Ranking rankingsPorTamanho[3][10], int numeroDeEntradasPorTamanho[3]){
    FILE *arquivo = fopen("ranking.dat", "r");
    if (arquivo == NULL) {
        
        for (int i = 0; i < 3; i++) {
            numeroDeEntradasPorTamanho[i] = 0;
        }
        return;
    }

    // Lê a quantidade de scores salvos para cada tamanho de tabuleiro
    fscanf(arquivo, "%d %d %d", &numeroDeEntradasPorTamanho[0], &numeroDeEntradasPorTamanho[1], &numeroDeEntradasPorTamanho[2]);

    // Lê os dados de cada ranking (4x4, 5x5, 6x6)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < numeroDeEntradasPorTamanho[i]; j++) {
            fscanf(arquivo, "%s %d", rankingsPorTamanho[i][j].nome, &rankingsPorTamanho[i][j].pontuacao);
        }
    }

    fclose(arquivo);
}

// Salva os rankings no arquivo "ranking.dat"
void salvarRanking(Ranking rankingsPorTamanho[3][10], int numeroDeEntradasPorTamanho[3]) {
    FILE *arquivo = fopen("ranking.dat", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar o ranking!\n");
        return;
    }

    // Escreve a quantidade de scores para cada tamanho
    fprintf(arquivo, "%d %d %d\n", numeroDeEntradasPorTamanho[0], numeroDeEntradasPorTamanho[1], numeroDeEntradasPorTamanho[2]);

    // Escreve os dados de cada ranking
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < numeroDeEntradasPorTamanho[i]; j++) {
            fprintf(arquivo, "%s %d\n", rankingsPorTamanho[i][j].nome, rankingsPorTamanho[i][j].pontuacao);
        }
    }

    fclose(arquivo);
}

// Atualiza o ranking com a pontuação do jogo finalizado
void atualizarRanking(Jogo *jogador) {
    if (jogador->pontuacao == 0) 
        return; // Não salva jogos com pontuação zero

    Ranking rankingsPorTamanho[3][10];
    int numeroDeEntradasPorTamanho[3];
    carregarRanking(rankingsPorTamanho, numeroDeEntradasPorTamanho);

    // Converte o tamanho do tabuleiro (4, 5, 6) para um índice de vetor (0, 1, 2)
    int indiceDoRanking = jogador->n - 4;

    // Pega a menor pontuação no ranking se ele estiver cheio (10 entradas)
    int menorPontuacaoNoRanking = 0;
    if (numeroDeEntradasPorTamanho[indiceDoRanking] == 10) {
        menorPontuacaoNoRanking = rankingsPorTamanho[indiceDoRanking][9].pontuacao;
    }

    // Verifica se a pontuação do jogador é alta o suficiente para entrar no ranking
    if (numeroDeEntradasPorTamanho[indiceDoRanking] < 10 || jogador->pontuacao > menorPontuacaoNoRanking) {
        Ranking novaEntradaDoRanking;
        strcpy(novaEntradaDoRanking.nome, jogador->nome);
        novaEntradaDoRanking.pontuacao = jogador->pontuacao;

        // Adiciona a nova pontuação na lista
        if (numeroDeEntradasPorTamanho[indiceDoRanking] < 10) {
            // Se a lista não está cheia, adiciona no final e incrementa o contador
            rankingsPorTamanho[indiceDoRanking][numeroDeEntradasPorTamanho[indiceDoRanking]] = novaEntradaDoRanking;
            numeroDeEntradasPorTamanho[indiceDoRanking]++;
        } else {
            // Se a lista está cheia, substitui a última (e menor) pontuação
            rankingsPorTamanho[indiceDoRanking][9] = novaEntradaDoRanking;
        }

        // --- ORDENAÇÃO MANUAL (Bubble Sort em ordem decrescente) ---
        int numeroDeEntradasAtual = numeroDeEntradasPorTamanho[indiceDoRanking];
        for (int i = 0; i < numeroDeEntradasAtual - 1; i++) {
            for (int j = 0; j < numeroDeEntradasAtual - i - 1; j++) {
                if (rankingsPorTamanho[indiceDoRanking][j].pontuacao < rankingsPorTamanho[indiceDoRanking][j + 1].pontuacao) {
                    // Troca as posições se o elemento atual for menor que o próximo
                    Ranking entradaTemporaria = rankingsPorTamanho[indiceDoRanking][j];
                    rankingsPorTamanho[indiceDoRanking][j] = rankingsPorTamanho[indiceDoRanking][j + 1];
                    rankingsPorTamanho[indiceDoRanking][j + 1] = entradaTemporaria;
                }
            }
        }
        // --- FIM DA ORDENAÇÃO ---

        printf("\nParabéns! Você entrou no ranking!\n");
        salvarRanking(rankingsPorTamanho, numeroDeEntradasPorTamanho);
    }
}

// Mostra o ranking para o usuário
void mostrarRanking() {
    Ranking rankingsPorTamanho[3][10];
    int numeroDeEntradasPorTamanho[3];
    carregarRanking(rankingsPorTamanho, numeroDeEntradasPorTamanho);

    char tamanho[5];
    int tamanhoDoRankingEscolhido = 0;

    // Pergunta ao usuário qual ranking ele quer ver
    do {
        printf("\nQual ranking você deseja ver?\n");
        printf("(4) Tabuleiro 4x4\n");
        printf("(5) Tabuleiro 5x5\n");
        printf("(6) Tabuleiro 6x6\n");
        printf("Escolha: ");

        fgets(tamanho,5,stdin);
        retiraN(tamanho);
        retiraEspacos(tamanho);
        if(strlen(tamanho) != 1)
            tamanho[0] = 0;
        
        
        if (strlen(tamanho) == 1 && (tamanho[0] >= '4' && tamanho[0] <= '6')) {
            tamanhoDoRankingEscolhido = tamanho[0] - '0';
        } else {
            tamanhoDoRankingEscolhido = 0; // Marca a escolha como inválida para repetir o loop
        }
        
        if (tamanhoDoRankingEscolhido == 0) {
            printf("\nOpção inválida. Por favor, escolha 4, 5 ou 6.\n");
        }
    } while (tamanhoDoRankingEscolhido == 0);

    int indiceDoRankingEscolhido = tamanhoDoRankingEscolhido - 4;

    printf("\n========= RANKING %dx%d =========\n", tamanhoDoRankingEscolhido, tamanhoDoRankingEscolhido);

    if (numeroDeEntradasPorTamanho[indiceDoRankingEscolhido] == 0) {
        printf("Ainda não há pontuações para este tamanho.\n");
    } else {
        printf("Pos. | Nome do Jogador            | Pontuação\n");
        printf("-----|----------------------------|------------------\n");
        for (int i = 0; i < numeroDeEntradasPorTamanho[indiceDoRankingEscolhido]; i++) {
            printf("%-4d | %-26s | %d\n", i + 1, rankingsPorTamanho[indiceDoRankingEscolhido][i].nome, rankingsPorTamanho[indiceDoRankingEscolhido][i].pontuacao);
        }
    }
    printf("===============================\n");
    
    printf("\nPressione qualquer tecla para voltar ao menu: ");
    char saida[3];
    fgets(saida,3,stdin);
}

void copiarArquivoSalvamento(Jogo *jogador, char *nome) {
    FILE *entrada = fopen("paraSalvamento.txt", "r");
    FILE *destino = fopen(nome, "w");
    char lixo;
    
    if (destino == NULL) {
        printf("Erro: Não foi possível criar o arquivo de destino '%s'\n", nome);
        fclose(entrada);
        return;
    }
    
    fscanf(entrada, "%d%c%d%c%d%c", &jogador->n,&lixo, &jogador->desfazer,&lixo, &jogador->troca,&lixo);
    fscanf(entrada, "%d%c", &jogador->pontuacao,&lixo);
    fgets(jogador->nome,27,entrada);
    retiraN(jogador->nome);

    jogador->tabuleiro = criaMatriz(jogador->n);
    jogador->tabuleiroAnterior = criaMatriz(jogador->n);
    
    for (int i = 0; i < jogador->n; i++) {
        for (int j = 0; j < jogador->n; j++) {
            fscanf(entrada, "%d", &jogador->tabuleiro[i][j]);
        }
    }

    fscanf(entrada,"%c",&lixo);

    for (int i = 0; i < jogador->n; i++) {
        for (int j = 0; j < jogador->n; j++) {
            fscanf(entrada, "%d", &jogador->tabuleiroAnterior[i][j]);
        }
    }

    fclose(destino);
    fclose(entrada);

    criarArquivoSalvamento(*jogador,nome);
    atualizarRanking(jogador);

    liberaMatriz(jogador->n,jogador->tabuleiroAnterior); 
    liberaMatriz(jogador->n, jogador->tabuleiro);

}
