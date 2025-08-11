#ifndef JOGO2048_H
#define JOGO2048_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)




void limpar_buffer(); // limpa o buffer
void retiraN(char nome[]); // retira o \n do fgets e se necessário limpa o buffer
void maiuscula(char nome[]); // tranforma tudo da string em maisucula nao pode ter acento
void menuInicial(char *escolha); // imprime o menu e pede a escolha
void jogo(); 
void mapa(int n,int **tabuleiro); // imprime o tabuleiro
void ajuda(); // mostra as regras
void sair(char *escolha); // opção de sair do programa
void tamanhoJogo(int *n); // pede ao usuario que decida o tamanho do tabuleiro
void moveE(int n, int **tabuleiro);
void moveD(int n, int **tabuleiro);
void moveC(int n, int **tabuleiro);
void moveB(int n, int **tabuleiro);
void novoNumero(int n,int **tabuleiro);
void preencher0(int n,int **tabuleiro);
int **criaMatriz(int n);    
void liberaMatriz(int n,int **tabuleiro);
#endif // JOGO2048_H
