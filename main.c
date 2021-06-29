#include <stdio.h>
#include "matriz.h"
#include "matriz_esparsa.h"

void add_matriz(Lista_Mat *lm);
void add_dados_matriz_esp(Lista_Mat *lm);

void add_matriz(Lista_Mat *lm)
{
	Matriz mat;
	do
	{
		printf("Informe a quantidade de colunas da matriz.");
		scanf("%d", &mat.col_tam);
		printf("Informe a quantidade de linhas da matriz.");
		scanf("%d", &mat.lin_tam);
	} while (mat.col_tam < 0 || mat.lin_tam < 0);

	if (insere_matriz(lm, mat))
	{
		printf("Matriz adicionado com sucesso.\n");
	}
	else
	{
		printf("Erro ao adicionar metriz.\n");
	}
}

void add_dados_matriz_esp(Lista_Mat *lm)
{
	Matriz mat;
	Matriz_esparsa mat_esp;
	short int opc;

	printf("Qual matriz voce deseja inserir dados(informe o numero)");
	imprime_matrizes(lm);
	scanf("%d", &opc);
	if (busca_matriz(lm, opc, &mat))
	{
		do
		{
			printf("informe coluna do dado: \n");
			scanf("%d", &mat_esp.col);
			printf("informe linha do dado: \n");
			scanf("%d", &mat_esp.lin);
			printf("informe dado: \n");
			scanf("%f", &mat_esp.dado);

			if (mat_esp.lin >= 0 && mat_esp.col >= 0)
			{
				if (insere_matriz_esp(mat.mat_esp, mat_esp))
					printf("Sucesso inserir dados na matriz esparsa.\n");
				else
					printf("Erro ao inserir dados na matriz esparsa.\n");
			}
		} while (mat_esp.lin < 0 || mat_esp.col < 0);
	}
	else
	{
		printf("Matriz nao encontrada.\n");
	}
}

void main()
{
	Lista_Mat *li = NULL;
	Lista_Mat_Esp *li2 = NULL;
	struct matriz mat;
	Matriz_esparsa nod;
	int test;
	short int op;

	li = cria_lista_mat();

	// inicio da area de teste
	test = insere_matriz(li, mat);
	test = insere_matriz(li, mat);
	test = insere_matriz(li, mat);
	test = insere_matriz(li, mat);
	test = insere_matriz(li, mat);
	test = insere_matriz(li, mat);

	li2 = cria_matriz_esp();

	nod.col = 12;
	nod.dado = 13;
	printf("nod %d\n", nod.col);
	test = insere_matriz_esp(li2, nod);

	// check point 1
	printf("busca matriz: %d\n", busca_matriz(li, 1, &mat));
	mat.mat_esp = cria_matriz_esp();
	if (insere_matriz_esp(mat.mat_esp, nod))
	{
		printf("Adicionado com sucesso na matriz esparsa.\n");
	}
	else
	{
		printf("Erro o adicionar na matriz esparsa.\n");
	}
	imprime_matriz_esparsa(mat.mat_esp);
	libera_matriz_esp(mat.mat_esp);

	imprime_matriz_esparsa(li2);
	printf("AAAAAA\n");
	// imprime_matriz_esparsa(li2);

	imprime_matrizes(li);
	// fim da area de test
	do
	{
		printf("0 - Sair\n");
		printf("1 - Adicionar matriz\n");
		printf("2 - Listar matrizes\n");
		printf("3 - Adicionar dados na matriz\n");
		scanf("%d", &op);

		switch (op)
		{
		case 1:
			add_matriz(li);
			break;
		case 2:
			imprime_matrizes(li);
			break;
		case 3:
			add_dados_matriz_esp(li);
			break;
		default:
			break;
		}

	} while (op);

	libera_lista_mat(li);
	libera_matriz_esp(li2);
}
