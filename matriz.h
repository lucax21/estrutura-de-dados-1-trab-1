#ifndef __MATRIZ__
#define __MATRIZ__

#include <stdbool.h>
#include "matriz_esparsa.h"

typedef struct matriz
{
	int lin_tam, col_tam;
	int id;
	Lista_Mat_Esp *mat_esp;
} Matriz;

typedef struct descritor Lista_Mat;

Lista_Mat *cria_lista_mat();

void libera_lista_mat(Lista_Mat *li);

bool insere_matriz(Lista_Mat *li, struct matriz mat);

bool insere_matriz_fim(Lista_Mat *li, struct matriz mat);

bool vazia_matriz(Lista_Mat *li);

bool remove_matriz(Lista_Mat *li, short int id_mat);

void imprime_matrizes(Lista_Mat *li);

// void imprime_matriz_esp(Matriz *mat);

bool busca_matriz(Lista_Mat *li, short int id_mat, Matriz *mat);

#endif
