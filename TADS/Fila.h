#include "Pilha.h"
#ifndef FILA
#define FILA

typedef struct {
    int id;
    char nome[50];
} Paciente;

//Registro servirá como Nó, tanto de Lista como de Fila
typedef struct No {
    Paciente paciente;
    Pilha historico;
    struct No *prox;
} Registro;


//Fila servirá como a fila de espera do hospital
typedef struct Fila {
    struct Registro *head;
    struct Registro *tail;
    int tamanho;
} Fila;

//funções de Paciente

Paciente *pacienteCriar(char *nome, int id);
void pacienteApagar(Paciente *p);

//funções de Registro

struct Registro *RegistroCriar(Paciente *p, Pilha *hist);
void RegistroApagar(struct Registro *n);

//funções de Fila

Fila *filaCriar();
void filaApagar(Fila *f);

int filaSize(Fila *f);
bool filaVazia(Fila *f);
void enfileirar(Fila *f, struct Registro *n);
bool desenfileirar(Fila *f, struct Registro *removido);

#endif