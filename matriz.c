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

bool busca_matriz(Lista_Mat *li, int id_mat, struct matriz *mat)
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
