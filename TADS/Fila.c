#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Fila.h"

//funções de Fila

/*
Pré-Cond: há memória disponível na heap
Pós-Cond: aloca uma Fila e a inicia com head e tail em NULL e tamanho 0, retornando um ponteiro para ela
*/
Fila *filaCriar() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->head = NULL;
    f->tail = NULL;
    f->tamanho = 0;

    return f;
}

/*
Pré-Cond: f aponta para uma Fila que existe
Pós-Cond: desaloca a Fila da memória
*/
void filaApagar(Fila *f) {
    free(f);
    return;
}

/*
Pré-Cond: f aponta para Fila que existe
Pós-Cond: retorna o tamanho da fila
*/
int filaTamanho(Fila *f) {
    return f->tamanho;
}

/*
Pré-Cond: f aponta para Fila que existe
Pós-Cond: retorna bool que indica se a fila está vazia
*/
bool filaVazia(Fila *f) {
    return (f->head == NULL) ? true : false;
}

/*
Pré-Cond: Fila e Registro existem
Pós-Cond: adiciona um nó no final da Fila e atualiza tail. Se a fila estiver vazia, atualiza também head
*/
void enfileirar(Fila *f, Registro *n) {
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

/*
Pré-Cond: Fila existe e não é vazia
Pós-Cond: retira o primeiro elemento da fila, fazendo ela "andar" e retorna o elemento retirado
*/
bool desenfileirar(Fila *f, Registro *removido) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return false;
    }
    *removido = *(f->head); //guarda o head no buffer

    Registro *aux = f->head;
    f->head = f->head->prox; //avança o head para o próximo item da fila
    RegistroApagar(aux); //apaga o antigo head
    
    return true;
}
