#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Fila.h"




//funções de Paciente

Paciente *pacienteCriar(char *nome, int id) {
    Paciente *p = (Paciente *)malloc(sizeof(Paciente));
    p->nome = nome;
    p->id = id;

    return p;
}

void pacienteApagar(Paciente *p) {
    free(p);
    return;
}

//funções de No

No *NoCriar(Paciente *p, Pilha *hist) {
    No *n = (No *)malloc(sizeof(No));
    n->paciente = p;
    n->hist = hist;
    n->prox = NULL;

    return n;
}

void NoApagar(No *n) {
    pacienteApagar(n->paciente);
    pilhaApagar(n->hist);
    free(n);

    return;
}


//funções de Fila

Fila *filaCriar() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->head = NULL;
    f->tail = NULL;
    f->tamanho = 0;

    return f;
}

void filaApagar(Fila *f) {
    free(f);
    return;
}

int filatamanho(Fila *f) {
    return f->tamanho;
}

bool filaVazia(Fila *f) {
    return (f->head == NULL) ? true : false;
}

void queue(Fila *f, No *n) {
    //fila vazia
    if (filaVazia(f)) {
        f->head = n;
    }
    //um ou mais elementos
    else {
        f->tail->prox = n;
    }

    f->tail = n;
    (f->tamanho)++;
    return;
}

bool dequeue(Fila *f, No *removido) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return false;
    }
    *removido = *(f->head); //guarda o head no buffer
    No *aux = f->head;
    f->head = f->head->prox; //avança o head para o próximo item da fila
    NoApagar(aux); //apaga o antigo head
    return true;
}
