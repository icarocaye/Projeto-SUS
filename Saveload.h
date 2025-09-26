#ifndef SAVE
#define SAVE
#include <stdio.h>
#include "TADs.h"

//funções para gravar no arquivo

//serão usadas dentro de saveNo:
bool savePac(FILE *f, Paciente *p);
bool saveHist(FILE *f, Pilha *h);

//será usada dentro de saveFila e saveLista:
bool saveNo(FILE *f, Node *n);

bool saveFila(FILE *f, Fila *);
bool saveLista(FILE *f, Lista *l);

//funções para ler um arquivo

//serão usadas dentro de lerNo:
Paciente lerPac(FILE *f);
Pilha lerHist(FILE *f);

//será usada dentro de lerFila e lerLista:
Node lerNo(FILE *f);

Fila lerFila(FILE *f);
Lista lerLista(FILE *f);


#endif