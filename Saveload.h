#ifndef SAVE
#define SAVE
#include <stdio.h>
#include "Pilha.h"
#include "Fila.h"
#include "Lista.h"

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
bool lerPac(FILE *f, Paciente *p);
bool lerHist(FILE *f, Pilha *h);

//será usada dentro de lerFila e lerLista:
bool lerNo(FILE *f, Node *n);

bool lerFila(FILE *f, Fila *);
bool lerLista(FILE *f, Lista *l);


#endif