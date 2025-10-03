#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Saveload.h"

/*
TRATAMENTO DE ERRO
Em caso de erro, as funções retornam false e exibem uma mensagem de erro na tela, dizendo em qual estrutura 
o erro se deu e o código dele, que segue esse dicionário:
Código 0 - um dos ponteiros recebidos pela função é aponta para NULL e, portanto, não pode ser acessado.
Código 1 - erro ao salvar um int.
Código 2 - erro ao salvar um vetor.
Código 3 - erro ao salvar um ponteiro.
*/

//funções para gravar no arquivo

//serão usadas dentro de saveNo:

/*
Pré-Cond: o Paciente existe, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve os dados do Paciente de forma adjacente no arquivo binário
*/
bool savePac(FILE *fp, Paciente *p)
{
    if (p == NULL || fp == NULL) {
        printf("Erro ao salvar Paciente! Código 0");
        return false;
    }
    //salva o id do paciente
    if (fwrite(&(p->id), sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Paciente! Código 1");
        return false;
    }
    //salva o nome do paciente com, no máximo, 49 caracteres (e 1 de parada)
    if (fwrite(&(p->nome), sizeof(char[50]), 1, fp) < 1) {
        printf("Erro ao salvar Paciente! Código 2");
        return false;
    }

    return true;
}

/*
Pré-Cond: a Pilha existe, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve os dados da Pilha de forma adjacente no arquivo binário
*/
bool saveHist(FILE *fp, Pilha *h)
{
    if (h == NULL || fp == NULL) {
        printf("Erro ao salvar histórico! Código 0");
        return false;
    }
    //salva os 10 procedimentos, cada um sendo um vetor de 101 chars, no arquivo f
    if (fwrite(&(h->procedimentos), sizeof(char[MAX]), CAP, fp) < CAP) {
        printf("Erro ao salvar histórico! Código 2");
        return false;
    }
    //salva o tamanho usado do histórico
    if (fwrite(&(h->tamanho), sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar histórico! Código 1");
        return false;
    }

    return true;
}

//será usada dentro de saveFila:
/*
Pré-Cond: o Nó existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: usa as funções anteriores para salvar o Paciente e o Histórico do Nó e, depois, salva o ponteiro para o próximo Nó
*/
bool saveReg(FILE *fp, Registro *n)
{  
    if (n == NULL || fp == NULL) {
        printf("Erro ao salvar Nó! Código 0");
        return false;
    }
    //salvar o Paciente e o Histórico
    if (savePac(fp, n->paciente) == false)
        return false;
    if (saveHist(fp, n->historico) == false)
        return false;
    //salvar o ponteiro para o próximo Nó
    if (fwrite(&(n->prox), sizeof(Registro *), 1, fp) < 1) {
        printf("Erro ao salvar Nó! Código 3");
        return false;
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
        printf("Erro ao salvar Fila! Código 0");
        return false;
    }
    //salvar o tamanho da fila primeiro, para facilitar a leitura
    if (fwrite(&(f->tamanho), sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila! Còdigo 1");
        return false;
    }
    //salvar os nós!
    Registro *aux = f->head;
    while (aux != NULL) {
        saveReg(fp, aux);
        aux = aux->prox;
    }

    return true;
}

//saveLista é quase igual ao saveFila
/*
Pré-Cond: a Lista existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve no arquivo o tamanho da Lista e, depois, usa a função saveReg para salvar cada Nó
*/
bool saveLista(FILE *fp, Lista *L)
{
    if (L == NULL || fp == NULL) {
        printf("Erro ao salvar Lista! Código 0");
        return false;
    }
    //salvar o tamanho da lista primeiro, para facilitar a leitura
    if (fwrite(&(L->tamanho), sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila! Código 1");
        return false;
    }
    //salvar os nós!
    Registro *aux = L->inicio;
    while (aux != NULL) {
        saveReg(fp, aux);
        aux = aux->prox;
    }

    return true;
}

//funções para ler um arquivo

//serão usadas dentro de lerNo:
/*
Pré-Cond: o Paciente existe, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Lê os dados do Paciente de forma adjacente no arquivo binário
*/
bool lerPac(FILE *fp, Paciente *p)
{
    if (p == NULL || fp == NULL) {
        printf("Erro ao importar paciente! Código 0");
        return false;
    }
    //ler o id do paciente
    if (fread(&(p->id), sizeof(int), 1, fp) < 1) {
        printf("Erro ao importar paciente! Código 1");
        return false;
    }
    //ler o nome do paciente
    if (fread(&(p->nome), sizeof(char[50]), 1, fp) < 1) {
        printf("Erro ao importar paciente! Código 2");
        return false;
    }

    return true;
}

/*
Pré-Cond: a Pilha existe, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Lê os dados da Pilha de forma adjacente no arquivo binário
*/
bool lerHist(FILE *fp, Pilha *h)
{
    if (h == NULL || fp == NULL) {
        printf("Erro ao importar histórico! Código 0");
        return false;
    }
    //lê os 10 procedimentos, cada um sendo um vetor de 101 chars, no arquivo f
    if (fread(&(h->procedimentos), sizeof(char[MAX]), CAP, fp) < CAP) {
        printf("Erro ao importar histórico! Código 2");
        return false;
    }
    if (fread(&(h->tamanho), sizeof(int), 1, fp) < 1) {
        printf("Erro ao importar histórico! Código 1");
        return false;
    }

    return true;
}

//será usada dentro de lerFila:
/*
Pré-Cond: o Nó existe e não é NULL, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: usa as funções anteriores para ler o Paciente e o Histórico do Nó (Registro) e, depois, lê o ponteiro para o próximo Nó
*/
bool lerReg(FILE *fp, Registro *n)
{
    if (n == NULL || fp == NULL) {
        printf("Erro ao importar Nó! Código 0");
        return false;
    }
    //ler o Paciente e o Histórico
    if (lerPac(fp, n->paciente) == false)
        return false;
    if (lerHist(fp, n->historico) == false)
        return false;
    //ler o ponteiro para o próximo Nó
    if (fread(&(n->prox), sizeof(Registro *), 1, fp) < 1) {
        printf("Erro ao importar Nó! Código 3");
        return false;
    }

    return true;
}

/*
Pré-Cond: a Fila existe e não é NULL, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Lê no arquivo o tamanho da fila e, depois, usa a função lerReg para salvar cada Nó
*/
bool lerFila(FILE *fp, Fila*f)
{
    if (f == NULL || fp == NULL) {
        printf("Erro ao importar Fila! Código 0");
        return false;
    }
    //ler o tamanho da fila primeiro
    if (fread(&(f->tamanho), sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila! Código 1");
        return false;
    }
    //ler os nós, com base no tamanho da fila!
    Registro *aux = f->head;
    for (int i = 0; i < f->tamanho; i++) {
        lerReg(fp, aux);
        aux = aux->prox;
    }

    return true;
}

//assim como nas funções de salvar, a função lerLista é quase igual a lerFila
/*
Pré-Cond: a Lista existe e não é NULL, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Lê no arquivo o tamanho da lista e, depois, usa a função lerReg para salvar cada Nó
*/
bool lerLista(FILE *fp, Lista *L)
{
    if (L == NULL || fp == NULL) {
        printf("Erro ao importar Fila! Código 0");
        return false;
    }
    //ler o tamanho da fila primeiro
    if (fread(&(L->tamanho), sizeof(int), 1, fp) < 1) {
        printf("Erro ao salvar Fila! Código 1");
        return false;
    }
    //ler os nós, com base no tamanho da fila!
    Registro *aux = L->inicio;
    for (int i = 0; i < L->tamanho; i++) {
        lerReg(fp, aux);
        aux = aux->prox;
    }

    return true;
}