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

bool insere_matriz_esp(Lista_Mat_Esp *li, struct nodo dado);

bool remove_matriz_esp(Lista_Mat_Esp *li, int lin, int col);

// void imprime_matriz_esparsa(Matriz li);

#endif
