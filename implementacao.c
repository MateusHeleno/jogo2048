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
    printf("<t pos1, pos2>:: Trocar duas peças de posição, ou seja, troca o conteúdo da posição pos1 com o conteúdo da posição pos2.\n");
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
            printf("\nVocê deseja sair do jogo ?Responda com \"S\" para ficar e \"N\" para fechar o jogo: ");
    
        fgets(decisao,4,stdin);
        retiraN(decisao); //Retira o \n e limpar o buffer
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

int maiorNumero(Jogo *jogador){
    int maior = 0;
    int n = jogador->n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (jogador->tabuleiro[i][j] > maior) {
                maior = jogador->tabuleiro[i][j];
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

void mapa(Jogo *jogador){
    int n = jogador->n;
    int maior = maiorNumero(jogador);
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
                printf("   "); // se for zero, imprimir espaço
            else 
                printf(" %d ",jogador->tabuleiro[i][j]); // imprimindo o número

            
            for(int k = 0; k<espacoD;k++){
                printf(" "); // espaco do lado direito
            }
            
            printf(TAB_VER);

            /*if(i == 0 && j == n-1){ 
                printf("\tNome: %s",jogador->nome);
                break;
            }
            else if(i == 1 && j == n-1){ 
                printf("\tPontuação: %d",pontuacao);
                break;
            }
            else if(i == 2 && j == n-1){  
                printf("\tMovimentos para desfazer: %d",desfeito);  
                break;
            }
            else if(i == 3 && j == n-1){
                printf("\tMovimentos para troca de posição: %d",trocado);
                break;
            }*/
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

void criarArquivo(int n,int **tabuleiro,char *nome){
    FILE *saida  = fopen(nome,"wb");
    fwrite(&n,sizeof(int),1,saida); // escrevendo o tamnho do tabuleiro 
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fwrite(&tabuleiro[i][j], sizeof(int), 1, saida); // aloca cada linha manualmente
        }
    }
    
    fclose(saida);
}

int **copiaTabuleiro(Jogo *jogador){
    int n = jogador->n;
    int **copiaTabuleiro = criaMatriz(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                copiaTabuleiro[i][j] = jogador->tabuleiro[i][j];
            }
        }
    return copiaTabuleiro;
}


void novoNumero(Jogo *jogador){
    int x,y,valor,cont = 1,probabilidade;
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
    FILE *entrada = fopen("paraValidacao.dat","rb");
    int nA;
    fread(&nA, sizeof(int), 1, entrada);

    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < nA; j++) {
            fread(&jogador->tabuleiro[i][j], sizeof(int), 1, entrada); //pega um valor da posição i j da matriz            
        }
    }


    
    fclose(entrada);

}

void preencher0(Jogo *jogador){ // coloca zero em todas as posições da matriz
        for(int i = 0;i<jogador->n;i++){
            for (int j = 0;j<jogador->n;j++){
                jogador->tabuleiro[i][j] = 0;
            }
        }
}


int validacaoJogada(Jogo *jogador,int** copiaTabuleiro){  
    int n = jogador->n;    
    for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(copiaTabuleiro[i][j] != jogador->tabuleiro[i][j]) {
                    return 1; 
                }
        }
    }
    return 0;
}

int mostraPontuacao(Jogo *jogador){
    int ranking = 0;
    int n = jogador->n;
    for(int i =0;i<n;i++){
        for(int j = 0;j<n;j++){
            ranking += jogador->tabuleiro[i][j];
        }
    }
    return ranking;
}

int numDesfazer(Jogo *jogador){
    int n = jogador->n;
    int desfazer = 0;
    for(int i =0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(jogador->tabuleiro[i][j] >=512)
                desfazer += jogador->tabuleiro[i][j];
        }
    }

    return (desfazer / 512);
}

int numTroca(Jogo *jogador){
    int troca = 0;
    int n = jogador->n;
    for(int i =0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(jogador->tabuleiro[i][j] >=256)
                troca += jogador->tabuleiro[i][j];
        }
    }

    return (troca / 256);
}

void inicializarTabuleiro(Jogo *jogador){
    novoNumero(jogador);
    novoNumero(jogador);
}

int jogo(){ 
    Jogo jogador;

    jogador.n = tamanhoJogo(); // fazendo a escolha do tamnho do jogo
    jogador.tabuleiro = criaMatriz(jogador.n);// aloca a matriz com o tamanho de N
    jogador.pontuacao = 0;
    jogador.troca = 0;
    jogador.desfazer = 0;

    int desfazerRep = 0;
    int countDesfeito = 0;
    int countTrocado = 0;
    int jogadas = 0;
    char instrucao[20],nome[27];
    srand(time(NULL));
    

    printf("\nDigite seu nome: ");
    fgets(nome,27,stdin); // pega o nome do usuario
    retiraN(nome);
    strcpy(jogador.nome, nome); 

    
    preencher0(&jogador);// preenche a matriz com 0 para imprimir espaço
    inicializarTabuleiro(&jogador);// incializa com dois valores aleatórios

    do{
        int **copiaTab;
        int incorreto;
        int desfeito = numDesfazer(&jogador) - countDesfeito;// calcula quantidade de desfazer totais - as que ele usou
        int trocado = numTroca(&jogador) - countTrocado;// calcula quantidade de troca totais - as que ele usou

        mapa(&jogador);
        
        
        int movimento = 0;
        do{
            incorreto = 0;
            comandos();
            fgets(instrucao,20,stdin);
            retiraN(instrucao);
            maiuscula(instrucao);
                        
            printf("\n");
            if(strcmp(instrucao, "VOLTAR") == 0){ 
                // salvar arquivo antes de sair criarArquivo(n,tabuleiro)
                criarArquivo(jogador.n,jogador.tabuleiro,"paraSalvamento.dat");
                liberaMatriz(jogador.n,jogador.tabuleiro);
                return 0;   

            }
            else if(strcmp(instrucao, "A") == 0){    
                copiaTab  = copiaTabuleiro(&jogador);
                
                moveE(&jogador);
                
                movimento = 1;
                
            } 
            else if(strcmp(instrucao, "D") == 0){ 
                copiaTab  = copiaTabuleiro(&jogador);
                
                moveD(&jogador);
                                
                movimento = 1; //  indica que a opção feita foi de um movimento
            }
            else if(strcmp(instrucao, "W") == 0){  
                copiaTab  = copiaTabuleiro(&jogador);
                
                moveC(&jogador);
    
                movimento = 1;
            }
            else if(strcmp(instrucao, "S") == 0){  
                copiaTab  = copiaTabuleiro(&jogador);
                
                moveB(&jogador);
                
                movimento = 1;
            }
            else if(strcmp(instrucao, "U") == 0){ 
                desfazerRep++; // controla se ta tentando desfazer de forma seguida
                if(desfazerRep == 1){
                    if(desfeito > 0){  //  se nao tiver movimentos de desfazer, ele apita um erro 
                        anteceder(&jogador); // ele volta o movimento e a nova peça
                        countDesfeito++; // ele aumenta o contador de quantidades de vezes q ja desfez
                    }
                    else
                        printf("Você não tem mais movimentos para voltar\n");
                }
                else    
                    printf("Você não pode voltar duas vezes seguidas, favor fazer outro movimento.\n");
                
            }
            else if(instrucao[0] == 'T'){ 
                
                    if(trocado > 0){ 
                        if(troca(&jogador, instrucao) == 1){ // comando ja sendp executado aqui
                            printf("%s",instrucao);
                            countTrocado++ ;
                        }else{ 
                            printf("%s",instrucao);
                            printf("\nCorriga a sintaxe da sua esrita, ela deve obedecer exatamente ao comando!!\n");
                        }
                    }
                    else{
                        printf("Você não tem mais movimentos para trocar\n");
                        printf("%s",instrucao);
                    }
               
                    
            }
            else{    
                printf("\nOpção inválida, por favor escolha novamente dentre os comandos apresentados\n");
                
            }
            
        }while(incorreto == 1);

        if(movimento == 1){ 
            if(validacaoJogada(&jogador, copiaTab) == 0){ 
                printf("Movimento inválido,nenhuma peça se moveu. Tente uma direção diferente!\n");
            }
            else{
                criarArquivo(jogador.n,copiaTab,"paraValidacao.dat"); // vai salvar a matriz q ele copiou antes do movimento, entao nao da pra usar no salvamento, pois n tem o ultimo movimento
                jogadas++;
                novoNumero(&jogador);
                desfazerRep =0; // como entrou em número, sabe que ele nao repetiu o desfazer
            }
            liberaMatriz(jogador.n,copiaTab); // aloquei a matriz no copia tab, e aqui eu livrei
        }
           
    }while(1); 
}

int troca(Jogo *jogador, char *instrucao){ // vou conferindo camada por camada
    int x,y,numX,numY,valorReservado;
    int n = jogador->n;
    if(instrucao[0] == 'T' && instrucao[1] == ' '){
        if(instrucao[2] >='A' && instrucao[2] < (('A' + n))){
            x = (instrucao[2] - 'A' );// pois aqui temos que cair em 0 tbm, que seria a posi 1    
            if (instrucao[3] >= '1' && instrucao [3] <= ('0' + n)){
                numX = (instrucao[3] - '1'); 
                if(instrucao[4] == ',' && instrucao[5] == ' '){
                    if(instrucao[6] >= 'A' && instrucao[6] < (('A' + n))){
                        y = (instrucao[6] - 'A' );    
                        if (instrucao[7] >= '1' && instrucao [7] <= ('0' + n)){
                            numY = (instrucao[7] - '1'); 
                            valorReservado = jogador->tabuleiro[x][numX];
                            jogador->tabuleiro[x][numX] = jogador->tabuleiro[y][numY];
                            jogador->tabuleiro[y][numY] = valorReservado;                        
                            return 1; // se retornar 1 é poorque funcionou de maneira correta
                        }    
                    }         
                }   
            }       
        }   
    }    
    return 0; // houve allgum erro de escrita
}

/*void continuarJogo(){
    FILE *entrada  = fopen(paraSalvamento,"rb");
    fread(&nA, sizeof(int), 1, entrada);

    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < nA; j++) {
            fread(&tabuleiro[i][j], sizeof(int), 1, entrada); //pega um valor da posição i j da matriz            
        }
    }


}

*/