#include "Pilha.h"

#ifndef FILA
#define FILA

#define TAMANHO_MAX 150

typedef struct {
    char *nome;
    int id;
} Paciente;


//Registro conterá 


//Fila servirá como a fila de espera do hospital
typedef struct Fila {
    struct Registro *inicio;
    struct Registro *fim;
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

bool filaCheia(Fila *f);
bool filaVazia(Fila *f);
void enfileirar(Fila *f, struct Registro *n);
bool desenfileirar(Fila *f);
void mostrar_fila(Fila *f);

struct Registro* fila_inicio(Fila *f);

#endif