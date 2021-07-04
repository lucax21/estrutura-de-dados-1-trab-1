#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "matriz_esparsa.h"
// #include "matriz.h"

typedef struct elemento_mat_esp
{
	struct nodo dados;
	struct elemento_mat_esp *prox;
} Elem;

struct descritor_mat_esp
{
	struct elemento_mat_esp *inicio;
	struct elemento_mat_esp *fim;
};

Lista_Mat_Esp *cria_matriz_esp()
{
	Lista_Mat_Esp *li = (Lista_Mat_Esp *)malloc(sizeof(Lista_Mat_Esp));
	if (li != NULL)
	{
		li->inicio = NULL;
		li->fim = NULL;
	}
	return li;
}

void libera_matriz_esp(Lista_Mat_Esp *li)
{
	if (li != NULL)
	{
		Elem *no;
		while ((li->inicio) != NULL)
		{
			no = li->inicio;
			li->inicio = li->inicio->prox;
			free(no);
		}
		free(li);
	}
}

bool insere_matriz_esp(Lista_Mat_Esp *li, struct nodo dado)
{
	if (li == NULL)
		return 0;
	Elem *no = (Elem *)malloc(sizeof(Elem));
	if (no == NULL)
		return 0;

	no->dados = dado;
	if (li->inicio == NULL)
	{
		li->inicio = no;
		no->prox = NULL;
		li->fim = no;
	}
	else
	{
		if (dado.dado > li->fim->dados.dado)
		{
			no->prox = NULL;
			li->fim->prox = no;
			li->fim = no;
		}
		else
		{
			Elem *ant, *atual = li->inicio;
			while (atual != NULL && atual->dados.dado < dado.dado)
			{
				ant = atual;
				atual = atual->prox;
			}
			no->prox = ant->prox;
			ant->prox = no;
		}
	}

	return 1;
}

bool remove_matriz_esp(Lista_Mat_Esp *li, int lin, int col)
{
	if (li == NULL)
		return 0;

	Elem *ant, *atual = li->inicio;
	while (atual != NULL && (atual->dados.col != col && atual->dados.lin != lin))
	{
		ant = atual;
		atual = atual->prox;
	}

	if (atual == NULL)
		return 0;

	else if (atual == li->inicio)
	{
		if (li->inicio->prox == NULL)
		{
			li->inicio = NULL;
			li->fim = NULL;
			free(atual);
			return 1;
		}
		else
		{
			li->inicio = atual->prox;
			free(atual);
			return 1;
		}
	}
	else
	{
		if (atual->prox == NULL)
		{
			li->fim = ant;
			ant->prox = NULL;
			free(atual);
			return 1;
		}
		else
		{
			ant->prox = atual->prox;
			free(atual);
			return 1;
		}
	}
}

// void imprime_matriz_esparsa(struct matriz *li)
// {
// 	if (li->mat_esp == NULL)
// 	{
// 		printf("Matriz esparsa vazia\n");
// 	}
// 	else
// 	{
// 		Elem *no = li->mat_esp;
// 		while (no != NULL)
// 		{
// 			printf("matriz esparsa [%d] [%d] = %.2f\n", no->dados.col, no->dados.lin, no->dados.dado);
// 			no = no->prox;
// 		}
// 	}
// }
