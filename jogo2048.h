/* Mateus Oliveira Heleno
   25.1.4007 */

#ifndef JOGO2048_H
#define JOGO2048_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


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

typedef struct{
    char nome[27];
    int pontuacao,troca,desfazer;
    int **tabuleiro;
    int n;
}Jogo;



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
int maiorNumero(Jogo *jogador);// pega o maior número
int quantidadeDigitos(int numero); // cálula a quantidade de digitos do maior número
void linhaHorizontal(int n,int digitos); // faz a linha horizontal do mapa
void mapa(Jogo *jogador); // imprime o tabuleiro
void moveE(Jogo *jogador); // move o tabuleiro para a esquerda
void moveD(Jogo *jogador); // move o tabuleiro para a direita
void moveC(Jogo *jogador); // move o tabuleiro para a cima
void moveB(Jogo *jogador); // move o tabuleiro para a baixo

int **criaMatriz(int n); // cria a matriz com alocação dinâmica
void liberaMatriz(int n,int **tabuleiro); // libera a a matriz que foi alocada
void criarArquivo(int n,int **tabuleiro,char *nome); // cria aqruivos para voltar e para salvar

void novoNumero(Jogo *jogador); // gera um numero de acordo com o tamano do tabuleiro
void anteceder(Jogo *jogador); // volta uma jogada
void preencher0(Jogo *jogador); // preenche a função com 0

int validacaoJogada(Jogo *jogador,int** copiaTabuleiro);// valida se a jogada foi válida
int **copiaTabuleiro(Jogo *jogador);//// copia um tabuleiro no outro

int mostrarPontuacao(Jogo *jogador);// mostra a pontuacao do jogador
int numDesfazer(Jogo *jogador); // contabiliza a quantidade de possiveis movimentos de desfazer
int numTroca(Jogo *jogador); // contabiliza a quantidade de possiveis movimentos de troca
void inicializarTabuleiro(Jogo *jogador); // função para posicionar os dois primeiros numeros no tabuleiro
int jogo(); // funlçao que envovle toda a logica do jogo em si, como movimentos, comandos, tamnho e nome 
int troca(Jogo *jogador,char *instrucao); // confere se a escrita está correta , e faz a mudança das posições

#endif // JOGO2048_H