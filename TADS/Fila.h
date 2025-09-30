#ifndef FILA
#define FILA
#include "Registro.h"

//Fila servirá como a fila de espera dos pacientes que se encontram no hospital, usando Registros como Nós
typedef struct Fila {
    struct Registro *head;
    struct Registro *tail;
    int tamanho;
} Fila;

//funções de Fila

Fila *filaCriar();
void filaApagar(Fila *f);

int filaSize(Fila *f);
bool filaVazia(Fila *f);
void enfileirar(Fila *f, struct Registro *n);
Registro desenfileirar(Fila *f);

#endif