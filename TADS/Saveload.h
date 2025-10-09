#ifndef SAVE
#define SAVE
#include <stdio.h>
//Fila.h e Lista.h já incluem todos os outros TADs
#include "Fila.h"
#include "Lista.h"

//funções para gravar no arquivo
/*
As funções PRECISAM ser chamadas nessa ordem! Fila só pode ser salva depois de Lista.
Ponteiro para arquivo deve ter sido criado no modo wb.
*/
bool saveLista(FILE *wb, Lista *l);
bool saveFila(FILE *wb, Fila *);

//funções para ler um arquivo
/*
As funções PRECISAM ser chamadas nessa ordem! Fila só pode ser lida depois de Lista.
Ponteiro para arquivo deve ter sido criado no modo rb.
*/
bool lerLista(FILE *rb, Lista *l);
bool lerFila(FILE *rb, Lista *L, Fila *);

#endif