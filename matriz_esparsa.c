#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "matriz_esparsa.h"

typedef struct elemento
{
	struct nodo dados;
	struct elemento *prox;
} Elem;

struct descritor
{
	struct elemento *inicio;
	struct elemento *fim;
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

void imprime_matriz_esparsa(Lista_Mat_Esp *li)
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
			printf("matriz esparsa coluna %d\n", no->dados.col);
			no = no->prox;
		}
	}
}
