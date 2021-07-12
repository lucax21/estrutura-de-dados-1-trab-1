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
	no->prox = NULL;
	if (li->inicio == NULL)
	{
		li->inicio = no;
		no->prox = NULL;
		li->fim = no;
		return 1;
	}
	else
	{
		// insere no inicio
		if (dado_param.lin < li->inicio->dados.lin)
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
			// printf("\n\ntest 1\n\n");
		}

		//insere no fim
		else if (dado_param.lin > li->fim->dados.lin)
		{
			if (dado_param.lin > li->fim->dados.lin)
			{
				no->prox = NULL;
				li->fim->prox = no;
				li->fim = no;
			}
			else
			{

				no->prox = NULL;
				li->fim->prox = no;
				li->fim = no;
			}
			// printf("\n\ntest 2\n\n");
		}
		// insere no meio
		else
		{
			// printf("\n\ntest 3\n\n");
			Elem *ant, *atual = li->inicio;
			//&& (atual->dados.lin <= dado_param.lin && atual->dados.col < dado_param.col)
			while (atual != NULL)
			{
				if (atual->dados.lin >= dado_param.lin)
				{
					if (atual->dados.col > dado_param.col)
					{
						// printf("\n\n\nTest7\n\n\n");
						break;
					}
					else if (atual->dados.lin > dado_param.lin)
						break;
				}

				//31 11 40
				// 11
				ant = atual;
				atual = atual->prox;
				// printf("Test 5\n");
			}
			if (atual == li->inicio)
			{
				no->prox = li->inicio;
				li->inicio = no;
				return 1;
			}
			// else if (ant == li->inicio)
			// {
			// 	no->prox = NULL;
			// 	ant->prox = no;
			// 	li->fim = no;
			// 	return 1;
			// }

			// printf("\n\ntest 4  %d \n\n", (atual == NULL));
			no->prox = ant->prox;
			ant->prox = no;
			if (no->prox == NULL)
			{
				li->fim = no;
			}
		}
	}

	return 1;
}

bool remove_matriz_esp(Lista_Mat_Esp *li, int lin, int col)
{
	if (li == NULL || li->inicio == NULL)
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
		if (li->inicio == li->fim)
		{
			return 1;
		}

		else
		{
			return 1;
		}
	}

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
		else
		{

			if (atual->prox == NULL)
			{
				return 1;
			}
			else
			{
				return 1;
			}
		}
	}
}

bool soma_duas_matrizes(Lista_Mat_Esp *l1, Lista_Mat_Esp *l2, Lista_Mat_Esp *l_result, int lin, int col)
{
	if (l1->inicio == NULL || l2->inicio == NULL)
		return 0;
	Elem *no1 = l1->inicio;
	Elem *no2 = l2->inicio;
	int i, j;
	float soma1, soma2, soma3;
	Matriz_esparsa mat_aux;

	// printf("lin %d col %d\n", lin, col);
	for (i = 0; i < lin; i++)
	{
		for (j = 0; j < col; j++)
		{
			soma1 = soma2 = soma3 = 0;

			for (no1 = l1->inicio; no1 != NULL; no1 = no1->prox)
			{
				if ((no1->dados.lin == i) && (no1->dados.col == j))
				{
					soma1 = no1->dados.dado;
					break;
				}
			}
			for (no2 = l2->inicio; no2 != NULL; no2 = no2->prox)
			{
				if ((no2->dados.lin == i) && (no2->dados.col == j))
				{
					soma2 = no2->dados.dado;
					break;
				}
			}
			soma3 = soma1 + soma2;
			mat_aux.lin = i;
			mat_aux.col = j;
			mat_aux.dado = soma3;
			// printf(" i %d j %d Soma1 %f\n", i, j, soma1);
			// printf(" i %d j %d Soma2 %f\n", i, j, soma2);
			// printf(" i %d j %d Soma3 %f\n", i, j, soma3);
			if (soma3)
			{
				if (!check_campo_matriz_esp(l_result, i, j))
				{
					insere_matriz_esp(l_result, mat_aux);
				}
				else
				{
					Elem *no3 = l_result->inicio;
					//no3->dados.lin != i && no3->dados.col != j &&
					while (no3 != NULL)
					{
						if (no3->dados.lin == i && no3->dados.col == j)
							break;
						no3 = no3->prox;
					}
					// printf("XXX %f soma %f\n", no3->dados.dado, soma3);
					no3->dados.dado = soma3;
					// printf("YYY %f soma %f\n", no3->dados.dado, soma3);
				}
			}
			else
			{
				remove_matriz_esp(l_result, i, j);
			}
		}
	}

	return 1;
}

bool sub_duas_matrizes(Lista_Mat_Esp *l1, Lista_Mat_Esp *l2, Lista_Mat_Esp *l_result, int lin, int col)
{
	if (l1->inicio == NULL || l2->inicio == NULL)
		return 0;
	Elem *no1 = l1->inicio;
	Elem *no2 = l2->inicio;
	int i, j;
	float soma1, soma2, soma3;
	Matriz_esparsa mat_esq;

	// printf("lin %d col %d\n", lin, col);
	for (i = 0; i < lin; i++)
	{
		for (j = 0; j < col; j++)
		{
			soma1 = soma2 = soma3 = 0;

			// printf("\ntest1\n");
			for (no1 = l1->inicio; no1 != NULL; no1 = no1->prox)
			{
				if ((no1->dados.lin == i) && (no1->dados.col == j))
				{
					soma1 = no1->dados.dado;
					break;
				}
			}
			for (no2 = l2->inicio; no2 != NULL; no2 = no2->prox)
			{
				if ((no2->dados.lin == i) && (no2->dados.col == j))
				{
					soma2 = no2->dados.dado;
					soma2 = soma2 * -1;
					break;
				}
			}
			// ma - mb = ma + (-mb)
			soma3 = soma1 + soma2;
			mat_esq.lin = i;
			mat_esq.col = j;
			mat_esq.dado = soma3;
			if (soma3 != 0)
			{
				if (!check_campo_matriz_esp(l_result, i, j))
				{
					insere_matriz_esp(l_result, mat_esq);
				}
				// else if ()
				// {
				// }
				else
				{

					Elem *no3 = l_result->inicio;
					while (no3 != NULL)
					{
						if (no3->dados.lin == i && no3->dados.col == j)
							break;

						no3 = no3->prox;
					}
					no3->dados.dado = soma3;
				}
			}
			else
			{
				remove_matriz_esp(l_result, i, j);
			}
		}
	}

	return 1;
}

bool multi_duas_matrizes(Lista_Mat_Esp *l1, Lista_Mat_Esp *l2, Lista_Mat_Esp *l_result, int lin_a, int col_a, int lin_b, int col_b)
{
	if (l1->inicio == NULL || l2->inicio == NULL)
		return 0;

	Elem *no1 = l1->inicio;
	Elem *no2 = l2->inicio;
	float vl_mat1, vl_mat2, result;
	Matriz_esparsa mat_esq;

	Lista_Mat_Esp *aux;

	aux = cria_matriz_esp();
	while (no1 != NULL)
	{
		mat_esq.lin = no1->dados.lin;
		mat_esq.col = no1->dados.col;
		mat_esq.dado = no1->dados.dado;
		insere_matriz_esp(aux, mat_esq);
		no1 = no1->prox;
	}

	for (int i = 0; i < lin_a; i++)
	{
		for (int j = 0; j < col_b; j++)
		{
			result = 0;

			for (int k = 0; k < lin_a; k++)
			{
				vl_mat1 = 0;
				vl_mat2 = 0;
				for (no1 = aux->inicio; no1 != NULL; no1 = no1->prox)
				{
					if ((no1->dados.lin == i) && (no1->dados.col == k))
					{
						vl_mat1 = no1->dados.dado;
						break;
					}
				}
				for (no2 = l2->inicio; no2 != NULL; no2 = no2->prox)
				{
					if ((no2->dados.lin == k) && (no2->dados.col == j))
					{
						vl_mat2 = no2->dados.dado;
						break;
					}
				}
				// printf("XXX a %f b %f r %f\n", vl_mat1, vl_mat2, result);
				result += vl_mat1 * vl_mat2;
				// printf("YYY a %f b %f r %f\n", vl_mat1, vl_mat2, result);
			}
			mat_esq.lin = i;
			mat_esq.col = j;
			mat_esq.dado = result;
			if (result != 0)
			{
				if (!check_campo_matriz_esp(l_result, i, j))
				{
					insere_matriz_esp(l_result, mat_esq);
				}
				else
				{
					Elem *no3 = l_result->inicio;
					while (no3 != NULL)
					{
						if (no3->dados.lin == i && no3->dados.col == j)
							break;
						no3 = no3->prox;
					}
					no3->dados.dado = result;
				}
			}
			else
			{
				remove_matriz_esp(l_result, i, j);
			}
		}
	}

	libera_matriz_esp(aux);
	return 1;
}

bool gera_matriz_transposta(Lista_Mat_Esp *li, Lista_Mat_Esp *l_result)
{
	if (li == NULL || li->inicio == NULL)
		return 0;

	Elem *no1;
	Matriz_esparsa mat;

	no1 = li->inicio;

	while (no1 != NULL)
	{
		mat.col = no1->dados.lin;
		mat.lin = no1->dados.col;
		mat.dado = no1->dados.dado;
		insere_matriz_esp(l_result, mat);
		no1 = no1->prox;
	}

	return 1;
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
				printf(" \t%0.2f ", no->dados.dado);
				no = no->prox;
			}
			else
				printf(" \t%0.2f ", 0.0F);
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

		while (no != NULL)
		{
			// printf("\ntest 1\n");
			if (no->dados.lin == j && no->dados.col == j)
			{
				// printf("\ntest 3\n");
				// no = no->prox;
				break;
			}
			else
			{
				// printf("\ntest 2\n");
				no = no->prox;
			}
		}
		// printf("\ntest 5\n");
		if (no != NULL && no->dados.lin == j && no->dados.col == j)
		{
			// printf("\ntest 4\n");
			printf(" %.2f ", no->dados.dado);
			no = no->prox;
		}
		else
			printf(" 0 ");
	}
	printf("\n");
}
