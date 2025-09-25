#include "Pilha.h"
#ifndef FILA
#define FILA

typedef struct {
    char *nome;
    int id;
} Paciente;



//No conterá 
typedef struct No {
    Paciente *paciente;
    Pilha *hist;
    struct No *prox;
} No;

//Fila servirá como a fila de espera do hospital
typedef struct Fila {
    No *head;
    No *tail;
    int tamanho;
} Fila;

//funções de Paciente

Paciente *pacienteCriar(char *nome, int id);
void pacienteApagar(Paciente *p);

//funções de No

No *NoCriar(Paciente *p, Pilha *hist);
void NoApagar(No *n);

//funções de Fila

Fila *filaCriar();
void filaApagar(Fila *f);

int filaSize(Fila *f);
bool filaVazia(Fila *f);
void enfileirar(Fila *f, No *n);
bool desenfileirar(Fila *f, No *removido);

#endif