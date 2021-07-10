#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "matriz.h"
#include "matriz_esparsa.h"

typedef struct elemento
{
	struct matriz dados;
	struct elemento *prox;
} Elem;

struct descritor
{
	struct elemento *inicio;
	struct elemento *final;
};

Lista_Mat *cria_lista_mat()
{
	Lista_Mat *li = (Lista_Mat *)malloc(sizeof(Lista_Mat));
	if (li != NULL)
	{
		li->inicio = NULL;
		li->final = NULL;
	}

	return li;
}

void libera_lista_mat(Lista_Mat *li)
{
	if (li != NULL)
	{
		Elem *no;
		while ((li->inicio) != NULL)
		{
			no = li->inicio;
			li->inicio = li->inicio->prox;
			libera_matriz_esp(no->dados.mat_esp);
			free(no);
		}
		free(li);
	}
}

bool vazia_matriz(Lista_Mat *li)
{
	if (li == NULL)
		return 1;
	return 0;
}

bool insere_matriz(Lista_Mat *li, struct matriz mat)
{
	if (li == NULL)
		return 0;
	Elem *no = (Elem *)malloc(sizeof(Elem));
	if (no == NULL)
		return 0;

	int ult_id;
	no->dados = mat;
	no->prox = NULL;

	no->dados.mat_esp = cria_matriz_esp();

	if (li->inicio == NULL)
	{
		no->dados.id = 1;
		li->inicio = no;
	}
	else
	{
		ult_id = li->final->dados.id;
		ult_id++;
		no->dados.id = ult_id;
		li->final->prox = no;
	}
	li->final = no;

	return 1;
}

bool insere_matriz_fim(Lista_Mat *li, struct matriz mat)
{
	if (li == NULL)
		return 0;

	Elem *no = (Elem *)malloc(sizeof(Elem));
	if (no == NULL)
		return 0;

	int id_aux;

	no->dados = mat;
	id_aux = li->final->dados.id;
	id_aux++;

	no->dados.id = id_aux;

	no->prox = NULL;
	li->final->prox = no;
	li->final = no;

	return 1;
}

bool remove_matriz(Lista_Mat *li, short int id_mat)
{
	if (li == NULL)
		return 0;

	Elem *ant, *atual = li->inicio;
	while (atual != NULL && atual->dados.id != id_mat)
	{
		ant = atual;
		atual = atual->prox;
	}
	//nao achou o elemento
	if (atual == NULL)
		return 0;

	else if (atual == li->inicio)
	{
		if (li->inicio->prox == NULL)
		{
			li->inicio = NULL;
			li->final = NULL;
			libera_matriz_esp(atual->dados.mat_esp);
			free(atual);
			return 1;
		}
		else
		{
			li->inicio = atual->prox;
			libera_matriz_esp(atual->dados.mat_esp);
			free(atual);
			return 1;
		}
	}
	else
	{
		if (atual->prox == NULL)
		{
			li->final = ant;
			ant->prox = NULL;
			libera_matriz_esp(atual->dados.mat_esp);
			free(atual);
			return 1;
		}
		else
		{
			ant->prox = atual->prox;
			libera_matriz_esp(atual->dados.mat_esp);
			free(atual);
			return 1;
		}
	}
}

void imprime_matrizes(Lista_Mat *li)
{
	if (li == NULL || li->inicio == NULL)
	{
		printf("lista vazia\n");
	}
	else
	{
		Elem *no = li->inicio;
		while (no != NULL)
		{
			printf("matriz id: %d\n", no->dados.id);
			no = no->prox;
		}
	}
}

// void imprime_matriz_esp(Matriz *mat)
// {
// 	// struct elemento_mat_esp *no = mat->mat_esp;

// 	struct elemento_mat_esp *aux = test1(mat->mat_esp);

// 	printf("");

// 	for (int i = 0; i < mat->lin_tam; i++)
// 	{
// 		for (int j = 0; j < mat->col_tam; j++)
// 		{
// 			// if (false)
// 			{
// 				printf(" %d ");
// 				// no = no->inicio->prox;
// 			}
// 			//else
// 			printf(" 0 ");
// 		}
// 		printf("\n");
// 	}
// 	// }
// }

bool busca_matriz(Lista_Mat *li, short int id_mat, struct matriz *mat)
{
	if (li == NULL)
		return 0;

	if (li->final->dados.id == id_mat)
	{
		*mat = li->final->dados;
		return 1;
	}
	else
	{
		Elem *no = li->inicio;
		while (no != li->final && no->dados.id != id_mat)
		{
			no = no->prox;
		}
		if (no == li->final)
			return 0;
		else
		{
			*mat = no->dados;
			return 1;
		}
	}
}
