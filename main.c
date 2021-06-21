#include <stdio.h>
#include "matriz.h"

void main(){
	Lista *li = NULL;
	struct matriz mat;
	int test;

	li = cria_lista();


	test = insere_lista(li, mat);

	test = insere_lista(li, mat);
	test = insere_lista(li, mat);
	test = insere_lista(li, mat);
	test = insere_lista(li, mat);
	test = insere_lista(li, mat);


	imprime_lista(li);
	libera_lista(li);
}
