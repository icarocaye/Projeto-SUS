#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Fila.h"
#include "Lista.h"



//funções de Paciente

Paciente *pacienteCriar(char *nome, int id) {
    Paciente *p = (Paciente *)malloc(sizeof(Paciente));
    if(p == NULL){
        perror("Erro ao alocar paciente");
        exit(1);
    }
    p->nome = malloc(strlen(nome)+1);
    if(p->nome == NULL)
    {
        perror("Erro ao alocar nome do paciente");
        exit(1);
    }
    strcpy(p->nome,nome);
    p->id = id;

    return p;
}

void pacienteApagar(Paciente *p) {
    free(p);
    return;
}

//funções de Registro

Registro *RegistroCriar(Paciente *p, Pilha *hist) {
    Registro *n = (Registro *)malloc(sizeof(Registro));
    n->paciente = p;
    n->historico = hist;
    n->prox = NULL;

    return n;
}

void RegistroApagar(Registro *n) {
    pacienteApagar(n->paciente);
    pilhaApagar(n->historico);
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

bool desenfileirar(Fila *f, Registro *removido) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return false;
    }
    *removido = *(f->head); //guarda o head Registro buffer
    Registro *aux = f->head;
    f->head = f->head->prox; //avança o head para o próximo item da fila
    RegistroApagar(aux); //apaga o antigo head
    return true;
}
