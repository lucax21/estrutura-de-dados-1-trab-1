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

bool insere_matriz_esp(Lista_Mat_Esp *li, Matriz_esparsa dado_param)
{
	if (li == NULL)
		return 0;
	Elem *no = (Elem *)malloc(sizeof(Elem));
	if (no == NULL)
		return 0;

	no->dados = dado_param;
	if (li->inicio == NULL)
	{
		li->inicio = no;
		no->prox = NULL;
		li->fim = no;
	}
	else
	{
		// insere no inicio
		if ((dado_param.lin <= li->inicio->dados.lin) && (dado_param.col < li->inicio->dados.col))
		{
			printf("\n\ntest 1\n\n");
			no->prox = li->inicio;
			li->inicio = no;
		}
		//
		// else if (dado_param.lin == li->inicio->dados.lin && dado_param.col < li->inicio->dados.col)
		// {
		// 	no->prox = li->inicio;
		// 	li->inicio = no;
		// }
		// else if(dado_param.lin == li->inicio->dados.lin && dado_param.col > li->inicio->dados.col){
		// 	if(li->inicio->prox == li->fim){
		// 		// aux = li->fim
		// 	}
		// 	no->prox = li->inicio->prox;
		// 	li->inicio->prox = no;
		// 	//ver se ele eh ultimo ou esta no meio

		// }

		//insere no fim
		else if (dado_param.lin >= li->fim->dados.lin && dado_param.col > li->fim->dados.col)
		{
			printf("\n\ntest 2\n\n");
			no->prox = NULL;
			li->fim->prox = no;
			li->fim = no;
		}
		//
		else
		{
			printf("\n\ntest 3\n\n");
			Elem *ant, *atual = li->inicio;
			//
			while (atual != NULL && atual->dados.lin <= dado_param.lin && atual->dados.col < dado_param.col)
			{
				//if(atual->dados.lin )
				ant = atual;
				atual = atual->prox;
				printf("Test 5\n");
			}
			if(atual == li->inicio)
			{
				no->prox = li->inicio;
				li->inicio = no;
				return 1;
			}
			printf("\n\ntest 4  %d \n\n", (atual == NULL));
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

// struct nodo *test(Lista_Mat_Esp *li)
// {
// 	struct nodo *aux = li->inicio->dados;
// 	return aux;
// }

void imprime_mat_esparsa(Lista_Mat_Esp *li, int lin_tam, int col_tam)
{

	// printf("XXX %d %d \n", lin_tam, col_tam);
	Elem *no = li->inicio;
	for (int i = 0; i < lin_tam; i++)
	{
		for (int j = 0; j < col_tam; j++)
		{

			if (no != NULL && no->dados.lin == i && no->dados.col == j)
			{
				printf(" %.2f ", no->dados.dado);
				no = no->prox;
			}
			else
				printf(" 0 ");
		}
		printf("\n");
	}
}

void test2(Lista_Mat_Esp *li)
{
	Elem *no = li->inicio;
	while (no != NULL)
	{
		printf("l %d c %d d %f \n", no->dados.lin, no->dados.col, no->dados.dado);
		no = no->prox;
	}
	printf("\n");
}

void imprime_mat_esparsa_diagonal(Lista_Mat_Esp *li, int lin_tam, int col_tam)
{
	Elem *no = li->inicio;
	for (int j = 0; j < col_tam; j++)
	{
		if (no != NULL && no->dados.lin == j && no->dados.col == j)
		{
			printf(" %.2f ", no->dados.dado);
			no = no->prox;
		}
		else
			printf(" 0 ");
	}
	printf("\n");
}
