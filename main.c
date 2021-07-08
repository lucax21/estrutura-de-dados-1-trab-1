#include <stdio.h>
#include "matriz.h"
#include "matriz_esparsa.h"

void add_matriz(Lista_Mat *lm);
void add_dados_matriz_esp(Lista_Mat *lm);
void rm_matriz(Lista_Mat *lm);
void rm_matriz_esp(Lista_Mat *lm);

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
	Matriz_esparsa aux_mat_esp;
	short int opc;

	printf("Qual matriz voce deseja inserir dados(informe o numero)\n");
	imprime_matrizes(lm);
	scanf("%hd", &opc);
	if (busca_matriz(lm, opc, &mat))
	{
		do
		{
			printf("informe coluna do dado: \n");
			scanf("%d", &aux_mat_esp.col);
			printf("informe linha do dado: \n");
			scanf("%d", &aux_mat_esp.lin);
			printf("informe dado: \n");
			scanf("%f", &aux_mat_esp.dado);

			// printf("HUSHUHDUHAS linha %d coluna d% dado %.2f", aux_mat_esp.lin, aux_mat_esp.col, aux_mat_esp.dado);

			// printf("\n\n\ncheck %d\n\n", check_campo_matriz_esp(mat.mat_esp, aux_mat_esp.lin, aux_mat_esp.col));

			if (aux_mat_esp.lin >= 0 && aux_mat_esp.col >= 0 && aux_mat_esp.dado > 0)
			{
				if (!check_campo_matriz_esp(mat.mat_esp, aux_mat_esp.lin, aux_mat_esp.col))
				{
					if (insere_matriz_esp(mat.mat_esp, aux_mat_esp))
						printf("Sucesso inserir dados na matriz esparsa.\n");
					else
						printf("Erro ao inserir dados na matriz esparsa.\n");
				}
				else
				{
					printf("O campo ja possui dado\n");
				}
			}
			// imprime_matriz_esparsa(mat.mat_esp);
		} while (aux_mat_esp.lin < 0 || aux_mat_esp.col < 0);
	}
	else
	{
		printf("Matriz nao encontrada.\n");
	}
}

void rm_matriz(Lista_Mat *lm)
{
	short int opc;
	imprime_matrizes(lm);
	printf("Escolha o numero da matriz que deseja remover.\n");
	scanf("%hd", &opc);
	if (remove_matriz(lm, opc))
	{
		printf("Removido com sucesso.\n");
	}
	else
	{
		printf("Nao foi possivel remover a matriz.\n");
	}
}

void rm_matriz_esp(Lista_Mat *lm)
{
	int lin, col;
	short int opc;
	Matriz mat;
	imprime_matrizes(lm);
	printf("Escolha a matriz: \n");
	scanf("%hd", &opc);
	if (busca_matriz(lm, opc, &mat))
	{
		imprime_mat_esparsa(mat.mat_esp, mat.lin_tam, mat.col_tam);
		do
		{
			printf("Informe a linha da matriz: \n");
			scanf("%d", &lin);
			printf("Informe a coluna da matriz: \n");
			scanf("%d", &col);

			if ((col >= 0 && col < mat.col_tam) && (lin >= 0 && lin < mat.col_tam))
			// if (1)
			{
				if (remove_matriz_esp(mat.mat_esp, lin, col))
				{
					printf("Sucesso ao remover dado na matriz esparsa.\n");
				}
				else
					printf("Erro ao remover dado na matriz esparsa.\n");
			}
		} while ((col < 0 || col > mat.col_tam) || (lin < 0 || lin > mat.lin_tam));
	}
	else
	{
		printf("Matriz nao encontrado.\n");
	}
}

void imprime_mat_esp(Lista_Mat *lm)
{
	Matriz mat;
	short int opc;

	imprime_matrizes(lm);
	printf("Escolha a matriz: \n");
	scanf("%hd", &opc);
	if (busca_matriz(lm, opc, &mat))
	{

		test2(mat.mat_esp);
		imprime_mat_esparsa(mat.mat_esp, mat.lin_tam, mat.col_tam);
	}
	else
	{
		printf("Matriz nao encontrado.\n");
	}
}

void imprime_mat_esp_diagonal(Lista_Mat *lm)
{
	Matriz mat;
	short int opc;

	imprime_matrizes(lm);
	printf("Escolha a matriz: \n");
	scanf("%hd", &opc);
	if (busca_matriz(lm, opc, &mat))
	{
		imprime_mat_esparsa_diagonal(mat.mat_esp, mat.lin_tam, mat.col_tam);
	}
	else
	{
		printf("Matriz nao encontrado.\n");
	}
}

void operacoes_mat(Lista_Mat *lm)
{
	Matriz mat1, mat2, mat_result;
	short int opc;
	imprime_matrizes(lm);
	printf("Escolha a primeira matriz\n");
	scanf("%hd", &opc);
	if (busca_matriz(lm, opc, &mat1))
	{
	}
	else
	{
		printf("Matriz nao encontrado.\n");
	}
	printf("Escolha a segunda matriz\n");
	scanf("%hd", &opc);
	if (busca_matriz(lm, opc, &mat2))
	{
	}
	else
	{
		printf("Matriz nao encontrado.\n");
	}

	//inicializa mat esparsa
	mat_result.mat_esp = cria_matriz_esp;

	//insere na lista de matrizes a matriz result
	// if (insere_matriz_fim(lm, mat_result))
	// {
	// 	printf("Matriz adicionado com sucesso.\n");
	// }
	// else
	// {
	// 	printf("Erro ao adicionar metriz.\n");
	// }
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

	do
	{
		printf("0 - Sair\n");
		printf("1 - Adicionar matriz\n");
		printf("2 - Listar matrizes\n");
		printf("3 - Adicionar dados na matriz\n");
		printf("4 - Remover matriz.\n");
		printf("5 - Remover dado na matriz esparsa.\n");
		printf("6 - Imprime matriz esparsa.\n");
		printf("7 - Imprime diagonal principal da matriz esparsa.\n");
		scanf("%hd", &op);

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
		case 4:
			rm_matriz(li);
			break;
		case 5:
			rm_matriz_esp(li);
			break;
		case 6:
			imprime_mat_esp(li);
			break;
		case 7:
			imprime_mat_esp_diagonal(li);
			break;
		case 8:

			break;
		default:
			break;
		}

	} while (op);

	libera_lista_mat(li);

	libera_matriz_esp(li2); // apagar isso depois hsauhas
}
