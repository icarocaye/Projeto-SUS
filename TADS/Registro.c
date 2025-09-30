#include <stdio.h>
#include <stdlib.h>
#include "Registro.h"

//funções de Registro

/*
Pré-Cond: p aponta para Paciente e hist aponta para Pilha
Pós-Cond: aloca um Registro (nó) na heap, atribui Paciente e Histórico à ele e retorna um ponteiro para ele
*/
Registro *RegistroCriar(Paciente *p, Pilha *hist) {
    if (p == NULL || hist == NULL) {
        printf("Erro ao alocar registro!");
        return NULL;
    }
    Registro *n = (Registro *)malloc(sizeof(Registro));
    if (n == NULL) {
        printf("Erro ao alocar registro!");
        return NULL;
    }
    n->paciente = p;
    n->historico = hist;
    n->prox = NULL;

    return n;
}

/*
Pré-Cond: n aponta para um Registro
Pós-Cond: apaga o Paciente e a Pilha associados ao Registro e, depois, desaloca também ele
*/
void RegistroApagar(Registro *n) {
    if (n != NULL) {
        pacienteApagar(n->paciente);
        pilhaApagar(n->historico);
        free(n);
    }

    return;
}
