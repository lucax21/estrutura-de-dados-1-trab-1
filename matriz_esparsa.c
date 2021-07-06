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
		if (dado_param.lin <= li->inicio->dados.lin)
		{
			if (dado_param.lin < li->inicio->dados.lin)
			{
				no->prox = li->inicio;
				li->inicio = no;
			}
			else
			{
				if (dado_param.col < li->inicio->dados.col)
				{
					no->prox = li->inicio;
					li->inicio = no;
				}
			}
			printf("\n\ntest 1\n\n");
		}

		//insere no fim
		else if (dado_param.lin >= li->fim->dados.lin)
		{
			if (dado_param.lin > li->fim->dados.lin)
			{
				no->prox = NULL;
				li->fim->prox = no;
				li->fim = no;
			}
			else
			{
				if (dado_param.col > li->fim->dados.col)
				{
					no->prox = NULL;
					li->fim->prox = no;
					li->fim = no;
				}
			}
			printf("\n\ntest 2\n\n");
		}
		// insere no meio
		else
		{
			printf("\n\ntest 3\n\n");
			Elem *ant, *atual = li->inicio;
			//&& (atual->dados.lin <= dado_param.lin && atual->dados.col < dado_param.col)
			while (atual != NULL)
			{
				if (atual->dados.lin >= dado_param.lin)
				{
					if (atual->dados.col > dado_param.col)
					{
						break;
					}
					printf("\n\n\nTest6\n\n\n");
				}

				ant = atual;
				atual = atual->prox;
				printf("Test 5\n");
			}
			if (atual == li->inicio)
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

	//remove do inicio
	if (lin == li->inicio->dados.lin && col == li->inicio->dados.col)
	{
		//remove e a lista fica vazia
		if (li->inicio == li->fim)
		{
			free(li->inicio);
			li->inicio = NULL;
			li->fim = NULL;
			return 1;
		}
		//remove e ainda tem elementos
		else
		{
			Elem *aux = li->inicio;
			li->inicio = li->inicio->prox;
			free(aux);
			return 1;
		}
	}

	//remove do meio e fim
	else
	{
		Elem *ant, *atual = li->inicio;
		// && (atual->dados.col != col && atual->dados.lin != lin)
		while (atual != NULL)
		{
			//sai do loop se achar
			if (atual->dados.lin == lin)
			{
				if (atual->dados.col == col)
					break;
			}
			// sai da funcao se passar da linha e col informada
			else if (atual->dados.lin >= lin)
			{
				if (atual->dados.lin > lin)
					return 0;
				else
				{
					if (atual->dados.col > col)
					{
						return 0;
					}
				}
			}

			ant = atual;
			atual = atual->prox;
		}

		// nao achou
		if (atual == NULL)
			return 0;

		// else if (atual == li->inicio)
		// {
		// 	if (li->inicio->prox == NULL)
		// 	{
		// 		li->inicio = NULL;
		// 		li->fim = NULL;
		// 		free(atual);
		// 		return 1;
		// 	}
		// 	else
		// 	{
		// 		li->inicio = atual->prox;
		// 		free(atual);
		// 		return 1;
		// 	}
		// }
		else
		{
			//remove do fim
			if (atual->prox == NULL)
			{
				li->fim = ant;
				ant->prox = NULL;
				free(atual);
				return 1;
			}
			//remove do meio
			else
			{
				ant->prox = atual->prox;
				free(atual);
				return 1;
			}
		}
	}
}

bool check_campo_matriz_esp(Lista_Mat_Esp *li, int lin, int col)
{
	if (li == NULL)
		return 0;

	if (li->inicio == NULL)
		return 0;
	//
	if (lin == li->inicio->dados.lin && col == li->inicio->dados.col)
	{
		//remove e a lista fica vazia
		if (li->inicio == li->fim)
		{
			return 1;
		}
		//remove e ainda tem elementos
		else
		{
			return 1;
		}
	}

	//remove do meio e fim
	else
	{
		Elem *ant, *atual = li->inicio;
		// && (atual->dados.col != col && atual->dados.lin != lin)
		while (atual != NULL)
		{
			//sai do loop se achar
			if (atual->dados.lin == lin)
			{
				if (atual->dados.col == col)
					break;
			}
			// sai da funcao se passar da linha e col informada
			else if (atual->dados.lin >= lin)
			{
				if (atual->dados.lin > lin)
					return 0;
				else
				{
					if (atual->dados.col > col)
					{
						return 0;
					}
				}
			}

			ant = atual;
			atual = atual->prox;
		}

		// nao achou
		if (atual == NULL)
			return 0;

		// else if (atual == li->inicio)
		// {
		// 	if (li->inicio->prox == NULL)
		// 	{
		// 		li->inicio = NULL;
		// 		li->fim = NULL;
		// 		free(atual);
		// 		return 1;
		// 	}
		// 	else
		// 	{
		// 		li->inicio = atual->prox;
		// 		free(atual);
		// 		return 1;
		// 	}
		// }
		else
		{
			//remove do fim
			if (atual->prox == NULL)
			{
				return 1;
			}
			//remove do meio
			else
			{
				return 1;
			}
		}
	}
}

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
	int i = 0;
	for (int j = 0; j < col_tam; j++)
	{
		printf("\ntest 1\n");
		while (no != NULL)
		{
			if (no->dados.lin == i && no->dados.col == i)
			{
				i++;
				break;
			}
			printf("\ntest 2\n");
			no = no->prox;
		}

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
