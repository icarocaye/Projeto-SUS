#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Saveload.h"

//funções para gravar no arquivo

//serão usadas dentro de saveLista:

/*
Pré-Cond: o Paciente existe, a Pilha existe, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve os dados do Paciente e de seu histórico de forma adjacente no arquivo binário
*/
bool savePac(FILE *fp, Paciente *p, Pilha *h)
{
    if (p == NULL || fp == NULL) {
        printf("Erro ao salvar Paciente!\n");
        return false;
    }
    //salva o paciente
    if (fwrite(&(p->id), sizeof(int), 1, fp) < 1) return false;
    if (fwrite(&(p->nome), sizeof(char), NOME_MAX, fp) < 1) return false;

    // salva o histórico logo em seguida
    if (fwrite(&(h->procedimentos), sizeof(char[MAX]), CAP, fp) < 1) return false;
    if (fwrite(&(h->tamanho), sizeof(int), 1, fp) < 1) return false;

    return true;
}

/*
Pré-Cond: a Lista existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve no arquivo o tamanho da Lista e, depois, usa a função saveReg para salvar cada Nó
*/
bool saveLista(FILE *fp, Lista *L)
{
    if (L == NULL || fp == NULL) {
        printf("Erro ao salvar Lista!\n");
        return false;
    }

    //salvar o tamanho da lista primeiro, para facilitar a leitura
    if (fwrite(&(L->tamanho), sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Lista!\n");
        return false;
    }

    //salvar os nós!
    Registro *aux = L->inicio;
    while (aux != NULL) {
        savePac(fp, aux->paciente, aux->historico);
        aux = aux->prox;
    }

    return true;
}

/*
Pré-Cond: a Fila existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve no arquivo o tamanho da fila e, depois, usa a função saveReg para salvar cada Nó
*/
bool saveFila(FILE *fp, Fila *f)
{
    if (f == NULL || fp == NULL) {
        printf("Erro ao salvar Fila!\n");
        return false;
    }

    //salvar somente o tamanho da fila, que é a úunica coisa que será usada na leitura
    if (fwrite(&(f->tamanho), sizeof(int), 1, fp) < 1) return false;
    return true;
}


//funções para ler um arquivo

//serão usadas dentro de lerLista:
/*
Pré-Cond: o Paciente existe, a Pilha existe, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Lê os dados do Paciente e de seu Histórico de forma adjacente no arquivo binário
*/
bool lerPac(FILE *fp, Paciente *p, Pilha *h)
{
    if (p == NULL || fp == NULL) return false;

    //ler o id do paciente
    if (fread(&(p->id), sizeof(int), 1, fp) < 1) return false;
    if (fread(&(p->nome), sizeof(char), NOME_MAX, fp) < 1) return false;

    //ler o histórico logo em seguida
    if (fread(&(h->procedimentos), sizeof(char[MAX]), CAP, fp) < 1) return false;
    if (fread(&(h->tamanho), sizeof(int), 1, fp) < 1) return false;

    return true;
}

/*
Pré-Cond: a Lista existe e não é NULL, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Lê no arquivo o tamanho da lista e, depois, usa a função lerReg para salvar cada Nó
*/
bool lerLista(FILE *fp, Lista *L)
{
    if (L == NULL || fp == NULL) {
        printf("Erro ao importar Lista!\n");
        return false;
    }

    //ler o tamanho da lista primeiro
    if (fread(&(L->tamanho), sizeof(int), 1, fp) < 1) {
        printf("Erro ao importar Lista!\n");
        return false;
    }

    //ler os nós (paciente + histórico), com base no tamanho da fila!
    for (int i = 0; i < L->tamanho; i++) {
        Paciente *p = pacienteEmBranco();
        Pilha *h = pilhaCriar();

        if (!lerPac(fp, p, h)) {
            printf("Erro ao importar Paciente!\n");
            return false;
        }

        Registro *atual = RegistroCriar(p, h);
        listaInserir(atual, L);
    }

    return true;
}

/*
Pré-Cond: a Fila existe, não é NULL e está vazia, a Lista existe e não é NULL e a função lerLista JÁ FOI CHAMADA o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Lê no arquivo o tamanho n da fila e, depois, anda até os últimos n elementos da lista e lê até o fianl
*/
bool lerFila(FILE *fp, Lista *L, Fila*f)
{
    if (f == NULL || fp == NULL || L == NULL) {
        printf("Erro ao importar Fila!\n");
        return false;
    }
    //ler o tamanho da fila primeiro
    fread(&(f->tamanho), sizeof(int), 1, fp);

    if (f->tamanho > 0 && f->tamanho <= L->tamanho) {
        //caminha até o (tamanho - n)-ésimo registro
        Registro *aux = L->inicio;
        for (int i = 0; i < L->tamanho - f->tamanho; i++)
            aux = aux->prox;

        //adiciona os últimos n registros na fila
        while (aux != NULL) {
            enfileirar(f, aux);
            aux = aux->prox;
        }
    }

    return true;
}
