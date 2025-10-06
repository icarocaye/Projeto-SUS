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


void RegistroApagar(Registro *n) {
    pacienteApagar(n->paciente);
    pilhaApagar(n->historico);
    free(n);
    
    return;
}


//funções de Fila

Fila *filaCriar() {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
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
    return (f->inicio == NULL) ? true : false;
}
bool filaCheia(Fila *f)
{
    return f->tamanho == TAMANHO_MAX;
}
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