/* Mateus Oliveira Heleno
   25.1.4007 */

#ifndef JOGO2048_H
#define JOGO2048_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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
void menuInicial(char *escolha); // imprime o menu e pede a escolha
void jogo(); 
void mapa(int n,int **tabuleiro,int pontuacao); // imprime o tabuleiro
void ajuda(); // mostra as regras
void sair(char *escolha); // opção de sair do programa
int tamanhoJogo(); // pede ao usuario que decida o tamanho do tabuleiro
void moveE(int n, int **tabuleiro,int *pontuacao);
void moveD(int n, int **tabuleiro,int *pontuacao);
void moveC(int n, int **tabuleiro,int *pontuacao);
void moveB(int n, int **tabuleiro,int *pontuacao);
void novoNumero(int n,int **tabuleiro);
void preencher0(int n,int **tabuleiro);
int **criaMatriz(int n);    
void liberaMatriz(int n,int **tabuleiro);
void criarArquivo(int n,int **tabuleiro);
int validacaoJogada(int n,int** copiaTabuleiro,int **tabuleiro);
int **copiaTabuleiro(int n,int **tabuleiro);
void comandos();
void anteceder(int n, int **tabuleiro);
int mostrarPontuacao(int n, int **tabuleiro);
int numDesfazer(int n,int **tabuleiro);
int numTroca(int n,int **tabuleiro);
//int troca();

#endif // JOGO2048_H