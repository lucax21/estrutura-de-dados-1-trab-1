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

bool insere_matriz_esp(Lista_Mat_Esp *li, Matriz_esparsa dado_param);

bool remove_matriz_esp(Lista_Mat_Esp *li, int lin, int col);

bool check_campo_matriz_esp(Lista_Mat_Esp *li, int lin, int col);

bool soma_duas_matrizes(Lista_Mat_Esp *l1, Lista_Mat_Esp *l2, Lista_Mat_Esp *l_result, int lin, int col);

bool sub_duas_matrizes(Lista_Mat_Esp *l1, Lista_Mat_Esp *l2, Lista_Mat_Esp *l_result, int lin, int col);

bool multi_duas_matrizes(Lista_Mat_Esp *l1, Lista_Mat_Esp *l2, Lista_Mat_Esp *l_result, int lin_a, int col_a, int lin_b, int col_b);

bool gera_matriz_transposta(Lista_Mat_Esp *li, Lista_Mat_Esp *l_result);

// struct nodo *test(Lista_Mat_Esp *li);

void imprime_mat_esparsa(Lista_Mat_Esp *li, int lin_tam, int col_tam);

void imprime_mat_esparsa_diagonal(Lista_Mat_Esp *li, int lin_tam, int col_tam);

void test2(Lista_Mat_Esp *li);

#endif
