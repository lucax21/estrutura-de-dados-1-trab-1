#ifndef __MATRIZ_ESPARSA__
#define __MATRIZ_ESPARSA__

#include <stdbool.h>
// #include "matriz.h"

typedef struct nodo
{
	float dado;
	int lin, col;
} Matriz_esparsa;

typedef struct descritor_mat_esp Lista_Mat_Esp;

Lista_Mat_Esp *cria_matriz_esp();

void libera_matriz_esp(Lista_Mat_Esp *li);

bool insere_matriz_esp(Lista_Mat_Esp *li, struct nodo dado_param);

bool remove_matriz_esp(Lista_Mat_Esp *li, int lin, int col);

// struct nodo *test(Lista_Mat_Esp *li);

void imprime_mat_esparsa(Lista_Mat_Esp *li, int lin_tam, int col_tam);

void imprime_mat_esparsa_diagonal(Lista_Mat_Esp *li, int lin_tam, int col_tam);

void test2(Lista_Mat_Esp *li);

#endif
