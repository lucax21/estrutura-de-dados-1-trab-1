#include <stdbool.h>

typedef struct matriz{
	int lin_tam, col_tam;
	int id;
	//struct *ms;
}Matriz;

typedef struct descritor Lista;

Lista *cria_lista();

void libera_lista(Lista *li);

bool insere_lista(Lista *li, struct matriz mat);

void imprime_lista(Lista *li);

