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




void limpar_buffer(); // limpa o buffer
void retiraN(char nome[]); // retira o \n do fgets e se necessário limpa o buffer
void maiuscula(char nome[]); // tranforma tudo da string em maisucula nao pode ter acento
void menuInicial(); // imprime o menu e pede a escolha
void mapa(int n,int **tabuleiro,int pontuacao,int desfeito,int trocado,char *nome); // imprime o tabuleiro
void ajuda(); // mostra as regras
int sair(); // opção de sair do programa
int tamanhoJogo(); // pede ao usuario que decida o tamanhro do tabuleiro
void moveE(int n, int **tabuleiro,int *pontuacao); // move o tabuleiro para a esquerda
void moveD(int n, int **tabuleiro,int *pontuacao); // move o tabuleiro para a direita
void moveC(int n, int **tabuleiro,int *pontuacao); // move o tabuleiro para a cima
void moveB(int n, int **tabuleiro,int *pontuacao); // move o tabuleiro para a baixo
void novoNumero(int n,int **tabuleiro); // gera um numero de acordo com o tamano do tabuleiro
void preencher0(int n,int **tabuleiro); // preenche a função com 0
int **criaMatriz(int n); // cria a matriz com alocação dinâmica
void liberaMatriz(int n,int **tabuleiro); // libera a a matriz que foi alocada
void criarArquivo(int n,int **tabuleiro); // cria aqruivos para voltar e para salvar
int validacaoJogada(int n,int** copiaTabuleiro,int **tabuleiro);// valida se a jogada foi válida
int **copiaTabuleiro(int n,int **tabuleiro);//// copia um tabuleiro no outro
void comandos(); // mostra os comandos possíveis no tabuleiro
void anteceder(int n, int **tabuleiro); // volta uma jogada
int mostrarPontuacao(int n, int **tabuleiro);// mostra a pontuacao do jogador
int numDesfazer(int n,int **tabuleiro); // contabiliza a quantidade de possiveis movimentos de desfazer
int numTroca(int n,int **tabuleiro); // contabiliza a quantidade de possiveis movimentos de troca
void inicializarTabuleiro(int n,int **tabuleiro);
int jogo();
void retiraEspacos(char *nome);
//int troca();

#endif // JOGO2048_H