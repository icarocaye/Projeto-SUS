#ifndef SAVE
#define SAVE
#include <stdio.h>
//Arvore.h e Heap.h já incluem todos os outros TADs
#include "Arvore.h"
#include "Heap.h"

//funções para gravar no arquivo
/*
As funções PRECISAM ser chamadas nessa ordem! Fila só pode ser salva depois de Lista.
Ponteiro para arquivo deve ter sido criado no modo wb.
*/
bool saveArvore(FILE *wb, Arvore *a);
bool saveHeap(FILE *wb, Heap *h);

//funções para ler um arquivo
/*
As funções PRECISAM ser chamadas nessa ordem! Fila só pode ser lida depois de Lista.
Ponteiro para arquivo deve ter sido criado no modo rb.
*/
bool lerArvore(FILE *rb, Arvore *l);
bool lerHeap(FILE *rb, Arvore *a, Heap *h, int *global_chegada);

#endif