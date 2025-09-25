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
    //PROBLEMA: Nome do paciente está sendo tratado de forma dinâmica, seria melhor definir um tamanho fixo!, ou adicionar uma variável para guardar o tamanho do nome!!
}

bool saveHist(FILE *fp, Pilha *h)
{
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
bool saveNo(FILE *fp, Node *n)
{
    if (savePac(fp, n->paciente) == false)
        return false;
    if (saveHist(fp, n->hist) == false)
        return false;

    if (fwrite(n->prox, sizeof(Node *), 1, fp) < 1) {
        printf("Erro ao salvar Nó!");
        return false;
    }

    return true;
}

bool saveFila(FILE *fp, Fila *l)
{
    //salvar o tamanho da fila primeiro, para facilitar a leitura
    if (fwrite(l->size, sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila!");
        return false;
    }
    //salvar os nós!
    while (l->head != NULL) {
        saveNo(fp, l->head);
        l->head = l->head->prox;
    }

    return true;
}


//funções para ler um arquivo

//serão usadas dentro de lerNo:
Paciente lerPac(FILE *fp);
Pilha lerHist(FILE *fp);

//será usada dentro de lerFila:
Node lerNo(FILE *fp);

Fila lerFila(FILE *fp);