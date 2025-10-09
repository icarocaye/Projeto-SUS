#ifndef FILA
#define FILA
#include "Pilha.h"
#include "Registro.h"

#define TAMANHO_MAX 150

//Fila servirá como a fila de espera do hospital
typedef struct Fila {
    Registro *inicio;
    Registro *fim;
    int tamanho;
} Fila;

//funções de Fila

Fila *filaCriar();
bool filaApagar(Fila *f);

bool filaCheia(Fila *f);
bool filaVazia(Fila *f);
int filaTamanho(Fila *f);
Registro* fila_inicio(Fila *f);
void enfileirar(Fila *f, Registro *n);
bool desenfileirar(Fila *f);
Registro *filaBuscar(Fila *f, int id);
void mostrar_fila(Fila *f);

#endif