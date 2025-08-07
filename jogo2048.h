#ifndef JOGO2048_H
#define JOGO2048_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

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
void retiraN(char nome[]); // retira o \n do fgets
void menuInicial(char *escolha);
void jogo();
void mapa();
void ajuda();

#endif // JOGO2048_H
