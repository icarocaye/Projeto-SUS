#include <stdio.h>
#include <stdlib.h>
#include "Paciente.h"

//funções de Paciente

/*
Pré-Cond: nome tem até 50 chars
Pós-Cond: aloca um Paciente na heap, passa os atributos dados para ele e retorna um ponteiro para ele
*/
Paciente *pacienteCriar(int id, char nome[50]) {
    Paciente *p = (Paciente *)malloc(sizeof(Paciente));
    if(p == NULL){
        perror("Erro ao alocar paciente");
        return NULL;
    }
    p->id = id;
    strcpy(p->nome,nome);

    return p;
}

/*
Pré-Cond: p aponta para Paciente
Pós-Cond: desaloca Paciente da memória
*/
void pacienteApagar(Paciente *p) {
    if (p != NULL)
        free(p);
    return;
}