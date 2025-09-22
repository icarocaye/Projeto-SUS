#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

Pilha *pilhaCriar() {
    Pilha *h = (Pilha *)malloc(sizeof(Pilha));
    memset(h->procedimentos, 0, sizeof(h->procedimentos)); //garantir que o vetor começa zerado, possivelmente desenecessário, talvez retire depois
    h->size = 0;

    return h;
}

void pilhaApagar(Pilha *h) {
    free(h);
    return;
}

void empilhar(Pilha *h, char proc[MAX]) {
    if (pilhaSize(h) >= CAP)
        printf("Histórico cheio!\n");
    else {
        strcpy(h->procedimentos[pilhaSize(h)], proc);
        h->size++;
    }
    return;
}

bool desempilhar(Pilha *h, char *removido[MAX]) {
    if (pilhaVazia(h)) {
        printf("Histórico já está vazio!\n");
        return false;
    }
    strcpy(*removido, h->procedimentos[pilhaSize(h)-1]); //copia o último elemento da pilha para o buffer
    h->size--; //diminui o tamanho, vai sobrescrever a string desempilhada
    return true;
}

int pilhaSize(Pilha *h) {
    return h->size;
}

bool pilhaVazia(Pilha *h) {
    return (pilhaSize(h) == 0) ? true : false;
}

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
    return (f->head == NULL) ? true : false;
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

bool dequeue(Fila *f, Node *removido) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return false;
    }
    *removido = *(f->head); //guarda o head no buffer
    Node *aux = f->head;
    f->head = f->head->prox; //avança o head para o próximo item da fila
    nodeApagar(aux); //apaga o antigo head
    return true;
}
