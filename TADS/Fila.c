#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Fila.h"
#include "Lista.h"

//funções de Fila
/*
Pré-Cond: há memória disponível na heap
Pós-Cond: aloca uma Fila e a inicia com head e tail em NULL e tamanho 0, retornando um ponteiro para ela
*/
Fila *filaCriar() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
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
int filatamanho(Fila *f) {
    return f->tamanho;
}

/*
Pré-Cond: f aponta para Fila que existe
Pós-Cond: retorna bool que indica se a fila está vazia
*/
bool filaVazia(Fila *f) {
    return (f->inicio == NULL) ? true : false;
}

bool filaCheia(Fila *f)
{
    return f->tamanho == TAMANHO_MAX;
}

/*
Pré-Cond: Fila e Registro existem
Pós-Cond: adiciona um nó no final da Fila e atualiza tail. Se a fila estiver vazia, atualiza também head
*/
void enfileirar(Fila *f, Registro *n) {
    if(filaCheia(f))
    {
        printf("\n!!! FILA CHEIA !!!\n");
    }
    //fila vazia
    if (filaVazia(f)) {
        f->inicio = n;
    }
    //um ou mais elementos
    else {
        f->fim->prox = n;
    }

    f->fim = n;
    (f->tamanho)++;
    return;
}

/*
Pré-Cond: Fila existe e não é vazia
Pós-Cond: retira o primeiro elemento da fila, fazendo ela "andar" e retorna o elemento retirado
*/
bool desenfileirar(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return false;
    }

    
    Registro *aux = f->inicio; 
    f->inicio = f->inicio->prox; //avança o inicio para o próximo item da fila
    RegistroApagar(aux); //apaga o antigo inicio

    return true;
}

Registro *filaBuscar(Fila *f, int id)
{
    Registro *aux = fila_inicio(f);
    while (aux != NULL) {
        if (aux->paciente->id == id) return aux;
        aux = aux->prox;
    }
    return NULL;
}

void mostrar_fila(Fila *f)
{   
    Registro *aux = f->inicio;
    int pos = 1;
    while(aux != NULL )
    {
        printf("\n %d -> (id=%d) -- %s", pos,aux->paciente->id,aux->paciente->nome);
        pos++;
        aux = aux->prox;
    }
}

Registro *fila_inicio(Fila *f)
{   
    return f->inicio;
}