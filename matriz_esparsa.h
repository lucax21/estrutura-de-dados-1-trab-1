#ifndef __MATRIZ_ESPARSA__
#define __MATRIZ_ESPARSA__

#include <stdbool.h>

typedef struct nodo
{
	float dado;
	int lin, col;
} Matriz_esparsa;

typedef struct descritor Lista_Mat_Esp;

Lista_Mat_Esp *cria_matriz_esp();

void libera_matriz_esp(Lista_Mat_Esp *li);

bool insere_matriz_esp(Lista_Mat_Esp *li, struct nodo dado);

void imprime_matriz_esparsa(Lista_Mat_Esp *li);

#endif
