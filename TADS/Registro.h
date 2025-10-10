#ifndef REG
#define REG
#include "Pilha.h"
#define NOME_MAX 120

typedef struct {
    int id;
    char nome[NOME_MAX];
} Paciente;

//Estrutura de registro da lista/fila de pacientes

typedef struct Registro{
    Paciente *paciente;
    Pilha *historico;
    struct Registro *prox;
}Registro;


//funções de Paciente
Paciente *pacienteEmBranco();
Paciente *pacienteCriar(char nome[NOME_MAX], int id);
bool pacienteApagar(Paciente *p);

//funções de Registro

Registro *RegistroCriar(Paciente *p, Pilha *hist);
bool RegistroApagar(struct Registro *n);

#endif