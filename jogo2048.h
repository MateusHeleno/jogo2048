#ifndef JOGO2048_H
#define JOGO2048_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void limpar_buffer(); // limpa o buffer
void retiraN(char nome[]); // retira o \n do fgets
void menuInicial(char *escolha);
void jogo();
#endif // JOGO2048_H
