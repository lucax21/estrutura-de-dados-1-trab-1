#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "matriz.h"

typedef struct elemento{
	struct matriz dados; 
	struct elemento *prox;
}Elem;

struct descritor{
	struct elemento *inicio;
	struct elemento *final;
};

Lista *cria_lista(){
	Lista *li = (Lista*)malloc(sizeof(Lista));
	if(li != NULL){
		li->inicio = NULL;
		li->final = NULL;
	}
		
	return li;
}

void libera_lista(Lista *li){
	if(li != NULL){
		Elem *no;
		while((li->inicio) != NULL){
			no = li->inicio;
			li->inicio = li->inicio->prox;
			free(no);
		}
		free(li);
	}
}

bool insere_lista(Lista *li, struct matriz mat){
	if(li == NULL)
		return 0;
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) 
		return 0;

	int ult_id;
	no->dados = mat;
	no->prox = NULL;
	if(li->inicio == NULL){
		no->dados.id = 1;
		li->inicio = no;
	}
	else {
		ult_id = li->final->dados.id;
		ult_id++;
		no->dados.id = ult_id;
		li->final->prox = no;
	}
	li->final = no;

	return 1;
}

void imprime_lista(Lista *li){
	if(li == NULL || li->inicio == NULL){
		printf("lista vazia\n");
	}
	else {
		Elem *no = li->inicio;
		while(no != NULL){
			printf("matriz %d\n", no->dados.id);
			no = no->prox;
		}
	}
}
