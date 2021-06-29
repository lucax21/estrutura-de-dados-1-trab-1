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

void imprime_matrizes(Lista_Mat *li);

bool busca_matriz(Lista_Mat *li, int id_mat, Matriz *mat);

#endif
