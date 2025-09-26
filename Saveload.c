#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Saveload.h"

//funções para gravar no arquivo

//serão usadas dentro de saveNo:

/*
Pré-Cond: o Paciente existe, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve os dados do Paciente de forma adjacente no arquivo binário
*/
bool savePac(FILE *fp, Paciente *p)
{
    if (p == NULL) {
        printf("Erro ao salvar Paciente!");
        return false;
    }
    //PROBLEMA: Nome do paciente está sendo tratado de forma dinâmica, seria melhor definir um tamanho fixo!, ou adicionar uma variável para guardar o tamanho do nome!!
}

/*
Pré-Cond: a Pilha existe, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve os dados da Pilha de forma adjacente no arquivo binário
*/
bool saveHist(FILE *fp, Pilha *h)
{
    if (h == NULL) {
        printf("Erro ao salvar histórico!");
        return false;
    }
    //salva os 10 procedimentos, cada um sendo um vetor de 101 chars, no arquivo f
    if (fwrite(h->procedimentos, sizeof(char[MAX]), CAP, fp) < CAP) {
        printf("Erro ao salvar histórico!");
        return false;
    }
    if (fwrite(h->size, sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar histórico!");
        return false;
    }

    return true;
}

//será usada dentro de saveFila:
/*
Pré-Cond: o Nó existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: usa as funções anteriores para salvar o Paciente e o Histórico do Nó e, depois, salva o ponteiro para o próximo Nó
*/
bool saveNo(FILE *fp, No *n)
{  
    if (n == NULL) {
        printf("Erro ao salvar Nó!");
        return false;
    }
    //salvar o Paciente e o Histórico
    if (savePac(fp, n->paciente) == false)
        return false;
    if (saveHist(fp, n->hist) == false)
        return false;
    //salvar o ponteiro para o próximo Nó
    if (fwrite(n->prox, sizeof(No *), 1, fp) < 1) {
        printf("Erro ao salvar Nó!");
        return false;
    }

    return true;
}

/*
Pré-Cond: a Fila existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve no arquivo o tamanho da fila e, depois, usa a função saveNo para salvar cada Nó
*/
bool saveFila(FILE *fp, Fila *f)
{
    if (f == NULL) {
        printf("Erro ao salvar Fila!");
        return false;
    }
    //salvar o tamanho da fila primeiro, para facilitar a leitura
    if (fwrite(f->size, sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila!");
        return false;
    }
    //salvar os nós!
    No *aux = f->head;
    while (f->head != NULL) {
        saveNo(fp, aux);
        aux = aux->prox;
    }

    return true;
}

//saveLista é quase igual ao saveFila
/*
Pré-Cond: a Lista existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve no arquivo o tamanho da Lista e, depois, usa a função saveNo para salvar cada Nó
*/
bool saveLista(FILE *fp, Lista *L)
{
    //salvar o tamanho da lista primeiro, para facilitar a leitura
    if (fwrite(L->size, sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila!");
        return false;
    }
    //salvar os nós!
    No *aux = L->head;
    while (L->head != NULL) {
        saveNo(fp, aux);
        aux = aux->prox;
    }

    return true;
}

//funções para ler um arquivo

//serão usadas dentro de lerNo:
bool lerPac(FILE *fp, Paciente *p)
{
    //FAZER DEPOIS DE DESENVOLVER savePac
}

bool lerHist(FILE *fp, Pilha *h)
{
    if (h == NULL) {
        printf("Erro ao importar histórico!");
        return false;
    }
    //lê os 10 procedimentos, cada um sendo um vetor de 101 chars, no arquivo f
    if (fread(h->procedimentos, sizeof(char[MAX]), CAP, fp) < CAP) {
        printf("Erro ao importar histórico!");
        return false;
    }
    if (fread(h->size, sizeof(int), 1, fp) < 1) {
        printf("Erro ao importar histórico!");
        return false;
    }

    return true;
}

//será usada dentro de lerFila:
bool lerNo(FILE *fp, No *n)
{
    if (n == NULL) {
        printf("Erro ao importar Nó!");
        return false;
    }
    //ler o Paciente e o Histórico
    if (lerPac(fp, n->paciente) == false)
        return false;
    if (lerHist(fp, n->hist) == false)
        return false;
    //ler o ponteiro para o próximo Nó
    if (fread(n->prox, sizeof(No *), 1, fp) < 1) {
        printf("Erro ao importar Nó!");
        return false;
    }

    return true;
}

bool lerFila(FILE *fp, Fila*f)
{
    if (f == NULL) {
        printf("Erro ao importar Fila!");
        return false;
    }
    //ler o tamanho da fila primeiro
    if (fread(f->size, sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila!");
        return false;
    }
    //ler os nós, com base no tamanho da fila!
    No *aux = f->head;
    for (int i = 0; i < f->size; i++) {
        lerNo(fp, aux);
        aux = aux->prox;
    }

    return true;
}

//assim como as funções de salvar, a função lerLista é quase igual a lerFila
bool lerLista(FILE *fp, Lista *L)
{
    if (L == NULL) {
        printf("Erro ao importar Fila!");
        return false;
    }
    //ler o tamanho da fila primeiro
    if (fread(L->size, sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila!");
        return false;
    }
    //ler os nós, com base no tamanho da fila!
    No *aux = L->head;
    for (int i = 0; i < L->size; i++) {
        lerNo(fp, aux);
        aux = aux->prox;
    }

    return true;
}