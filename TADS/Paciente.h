#ifndef PACIENTE
#define PACIENTE
#include <stdio.h>

/*
Paciente guarda apenas o id e o nome da pessoa em questão, e é um dos 
componentes do Registro, que é melhor explicado em Registro.h.
O nome é atualmente limitado em até 50 caracteres, incluindo '\0' e, por ser 
estático, exige funções da biblioteca string.h para sua manipulação
*/

typedef struct {
    int id;
    char nome[50];
} Paciente;

//funções de Paciente

Paciente *pacienteCriar(int id, char nome[50]);
void pacienteApagar(Paciente *p);

#endif