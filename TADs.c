#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TADs.h"

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

//funções de Node

Node *nodeCriar(Paciente *p, Pilha *hist) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->paciente = p;
    n->hist = hist;
    n->prox = NULL;

    return n;
}

void nodeApagar(Node *n) {
    pacienteApagar(n->paciente);
    pilhaApagar(n->hist);
    free(n);

    return;
}

//funções de Pilha (histórico)

Pilha *pilhaCriar(char *proc[MAX]);
void pilhaApagar(Pilha *h);

void empilhar(Pilha *pi, Node *n);
Node desempilhar(Pilha *pi);
int pilhaSize(Pilha *pi);
bool pilhaVazia(Pilha *pi);

//funções de Fila

Fila *filaCriar() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->head = NULL;
    f->tail = NULL;
    f->size = 0;

    return f;
}

void filaApagar(Fila *f) {
    free(f);
    return;
}

int filaSize(Fila *f) {
    return f->size;
}

bool filaVazia(Fila *f) {
    return (head == tail == NULL) ? true : false;
}

void queue(Fila *f, Node *n) {
    //fila vazia
    if (filaVazia(f)) {
        f->head = n;
    }
    //um ou mais elementos
    else {
        f->tail->prox = n;
    }

    f->tail = n;
    (f->size)++;
    return;
}

Node dequeue(Fila *f, Node *n);
