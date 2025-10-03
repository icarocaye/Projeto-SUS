#ifndef REGISTRO
#define REGISTRO
#include <stdio.h>
#include "Paciente.h"
#include "Pilha.h"

/*
Registro contém um Paciente e seu Histórico, representado por uma Pilha,
bem como um ponteiro para o próximo registro na estrutura em que está incluído.
Dessa forma, Registro serve como um Nó tanto para Fila dos pacientes atuais 
quanto para a Lista de todos os pacientes já atendidos.
*/

typedef struct Registro{
    Paciente *paciente;
    Pilha *historico;
    struct Registro *prox;
}Registro;

Registro *criarRegistro(Paciente *paciente, Pilha *historico);
void apagarRegistro(Registro *registro);

#endif