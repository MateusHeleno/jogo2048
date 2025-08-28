/* Mateus Oliveira Heleno
   25.1.4007 */

#ifndef IMPLEMENTACAO_H
#define IMPLEMENTACAO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>


typedef struct{
    char nome[27];
    int pontuacao,troca,desfazer,n;
    int **tabuleiro;
    int **tabuleiroAnterior;
}Jogo;

typedef struct {
    char nome[27];
    int pontuacao;
} Ranking;

void limpar_buffer(); // limpa o buffer
void retiraN(char *nome); // retira o \n do fgets e se necessário limpa o buffer
void retiraEspacos(char *nome); /// tira os espaços na string
char tornarMaior(char c); //deixa apenas as letras minusculas em maiúsculas
void maiuscula(char *nome); // tranforma tudo da string em maisucula nao pode ter acento
void menuInicial(); // imprime o menu e pede a escolha
void comandos(); // mostra os comandos possíveis no tabuleiro
void ajuda(); // mostra as regras 
int sair(); // opção de sair do programa

int tamanhoJogo(); // pede ao usuario que decida o tamanhro do tabuleiro
int maiorNumero(int n,int **tabuleiro);// pega o maior número
int quantidadeDigitos(int numero); // cálula a quantidade de digitos do maior número
void linhaHorizontal(int n,int digitos); // faz a linha horizontal do mapa
void numeroCor(int numero);
void mapa(Jogo *jogador); // imprime o tabuleiro
void moveE(Jogo *jogador); // move o tabuleiro para a esquerda
void moveD(Jogo *jogador); // move o tabuleiro para a direita
void moveC(Jogo *jogador); // move o tabuleiro para a cima
void moveB(Jogo *jogador); // move o tabuleiro para a baixo

int **criaMatriz(int n); // cria a matriz com alocação dinâmica
void liberaMatriz(int n,int **tabuleiro); // libera a a matriz que foi alocada
void preencher0(int n, int **tabuleiro); // preenche a função com 0

void inicializarTabuleiro(Jogo *jogador); // função para posicionar os dois primeiros numeros no tabuleiro
void novoNumero(Jogo *jogador); // gera um numero de acordo com o tamano do tabuleiro
void anteceder(Jogo *jogador); // volta uma jogada
void copiaTabuleiro(Jogo *jogador);//// copia um tabuleiro no outro
int validacaoJogada(Jogo *jogador);// valida se a jogada foi válida
int numTroca(Jogo jogador);
int troca(Jogo *jogador,char *instrucao); // confere se a escrita está correta , e faz a mudança das posições
void contarPecas(int n, int** tabuleiro, int* contagem,int tam);
int diferencaPontuacao(int n, int** tabuleiroAtual, int** tabuleiroAnterior);
int* preencherAlocandoVetor0(int tam);

int vitoria(Jogo jogador);
int derrota(Jogo jogador);

int novoJogo(); // funlçao que envovle toda a logica do jogo em si, como movimentos, comandos, tamnho e nome 
int executarJogo(Jogo *jogador);
void salvarJogo();
void copiarArquivoSalvamento(Jogo *jogador, char *nome);
int carregarJogo(Jogo *jogador, char *nomeArquivo);
void carregarJogoAtual();
void carregarJogoPronto(int *jogoIniciado);

void carregarRanking(Ranking rankingsPorTamanho[3][10], int numeroDeEntradasPorTamanho[3]);
void salvarRanking(Ranking rankingsPorTamanho[3][10], int numeroDeEntradasPorTamanho[3]);
void mostrarRanking();
void atualizarRanking(Jogo *jogador);


#define ANSI_RESET            "\x1b[0m"  
#define ANSI_BOLD             "\x1b[1m"  
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"


#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET

#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

#define PRETO_NO_BRANCO(string)     ANSI_COLOR_BLACK  ANSI_BG_COLOR_WHITE   string ANSI_RESET
#define BRANCO_NO_AZUL(string)      ANSI_COLOR_WHITE  ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define PRETO_NO_AMARELO(string)    ANSI_COLOR_BLACK  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BRANCO_NO_MAGENTA(string)   ANSI_COLOR_WHITE  ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define PRETO_NO_CIANO(string)      ANSI_COLOR_BLACK  ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BRANCO_NO_VERMELHO(string)  ANSI_COLOR_WHITE  ANSI_BG_COLOR_RED     string ANSI_RESET
#define PRETO_NO_VERDE(string)      ANSI_COLOR_BLACK  ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BRANCO_NO_VERDE(string)     ANSI_COLOR_WHITE  ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define AZUL_NO_BRANCO(string)      ANSI_COLOR_BLUE   ANSI_BG_COLOR_WHITE   string ANSI_RESET
#define AMARELO_NO_AZUL(string)     ANSI_COLOR_YELLOW ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define VERMELHO_NO_AMARELO(string) ANSI_COLOR_RED    ANSI_BG_COLOR_YELLOW  string ANSI_RESET

#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_AE  "\u250F" // ┏ (alto-esquerda)
#define TAB_ME  "\u2523" // ┣ (meio-esquerda)
#define TAB_BE  "\u2517" // ┗ (baixo-esquerda)
#define TAB_AM  "\u2533" // ┳ (alto-meio)
#define TAB_MM  "\u254B" // ╋ (meio-meio)
#define TAB_BM  "\u253B" // ┻ (baixo - meio)
#define TAB_AD  "\u2513" // ┓ (alto-direita)
#define TAB_MD  "\u252B" // ┫ (meio-direita)
#define TAB_BD  "\u251B" // ┛ (baixo-direita)

#endif // IMPLEMENTACAO_H