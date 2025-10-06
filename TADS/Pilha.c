#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Pilha.h"

//funções de Pilha (histórico)

Pilha *pilhaCriar() {
    Pilha *h = (Pilha *)malloc(sizeof(Pilha));
    memset(h->procedimentos, 0, sizeof(h->procedimentos)); //garantir que o vetor começa zerado, possivelmente desenecessário, talvez retire depois
    h->tamanho = 0;

    return h;
}

void pilhaApagar(Pilha *h) {
    free(h);
    return;
}

void empilhar(Pilha *h, char proc[MAX]) {
    if (pilhaTamanho(h) >= CAP)
        printf("Histórico cheio!\n");
    else {
        strcpy(h->procedimentos[pilhaTamanho(h)], proc);
        h->tamanho++;
    }
    return;
}

char *desempilhar(Pilha *h) {
    if (pilhaVazia(h)) {
        printf("Histórico já está vazio!\n");
        return false;
    }
    char *topo = h->procedimentos[h->tamanho - 1];
    char *aux = malloc(strlen(topo)+1);

    strcpy(aux,topo);
    strcpy(h->procedimentos[h->tamanho - 1],"");

    h->tamanho--; //diminui o tamanho, vai sobrescrever a string desempilhada
    return aux;
}

int pilhaTamanho(Pilha *h) {
    return h->tamanho;
}

bool pilhaVazia(Pilha *h) {
    return (pilhaTamanho(h) == 0) ? true : false;
}