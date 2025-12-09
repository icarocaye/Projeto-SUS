#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Saveload.h"
#include "Arvore.h"
#include "Heap.h"

//funções para gravar no arquivo

//serão usadas dentro de saveLista:

/*
Pré-Cond: o Paciente existe, a Pilha existe, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve os dados do Paciente e de seu histórico de forma adjacente no arquivo binário
*/
bool savePaciente(FILE *fp, Paciente *p, Pilha *h)
{
    if (p == NULL || fp == NULL) {
        printf("Erro ao salvar Paciente!\n");
        return false;
    }
    //salva o paciente
    if (fwrite(&(p->id), sizeof(int), 1, fp) < 1) return false;
    if (fwrite(&(p->nome), sizeof(char), NOME_MAX, fp) < 1) return false;
    if (fwrite(&(p->na_fila), sizeof(bool), 1, fp) < 1) return false;

    // salva o histórico logo em seguida
    if (fwrite(&(h->procedimentos), sizeof(char[MAX]), CAP, fp) < 1) return false;
    if (fwrite(&(h->tamanho), sizeof(int), 1, fp) < 1) return false;

    return true;
}

/*
Pré-Cond: o Paciente existe, a Pilha existe, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Lê os dados do Paciente e de seu Histórico de forma adjacente no arquivo binário
*/
bool lerPaciente(FILE *fp, Paciente *p, Pilha *h)
{
    if (p == NULL || fp == NULL) return false;

    //ler o id do paciente
    if (fread(&(p->id), sizeof(int), 1, fp) < 1) return false;
    if (fread(&(p->nome), sizeof(char), NOME_MAX, fp) < 1) return false;
    if (fread(&(p->na_fila), sizeof(bool), 1, fp) < 1) return false;

    //ler o histórico logo em seguida
    if (fread(&(h->procedimentos), sizeof(char[MAX]), CAP, fp) < 1) return false;
    if (fread(&(h->tamanho), sizeof(int), 1, fp) < 1) return false;

    return true;
}

// Função auxiliar recursiva para salvar a árvore em pré-ordem
/*
Pré-Cond: a AVL existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve no arquivo recursivamente em pré-ordem a AVL e marca os nós nulos com o sentinela -1
*/
bool saveArvoreRec(FILE *fp, no *raiz)
{
    if (raiz == NULL) {
        // Marca que chegou em um nó NULL (usa -1 como sentinela)
        int sentinela = -1;
        if (fwrite(&sentinela, sizeof(int), 1, fp) < 1) return false;
        return true;
    }
    
    // Salva o paciente e histórico do nó atual
    if (!savePaciente(fp, raiz->dados->paciente, raiz->dados->historico))
        return false;
    
    // Recursão: subárvore esquerda e direita
    if (!saveArvoreRec(fp, raiz->esq)) return false;
    if (!saveArvoreRec(fp, raiz->dir)) return false;
    
    return true;
}

// Função auxiliar recursiva para ler a árvore em pré-ordem
/*
Pré-Cond: a AVL existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Lê no arquivo recursivamente em pré-ordem a AVL identificando os nós nulos com o sentinela -1
*/
no* lerArvoreRec(FILE *fp)
{
    int id;
    if (fread(&id, sizeof(int), 1, fp) < 1) return NULL;
    
    // Se encontrou sentinela, retorna NULL
    if (id == -1) return NULL;
    
    // Caso contrário, id é válido. Reposiciona para ler o paciente completo
    fseek(fp, -sizeof(int), SEEK_CUR);
    
    // Cria novo paciente e histórico
    Paciente *p = pacienteEmBranco();
    Pilha *h = pilhaCriar();
    
    if (!lerPaciente(fp, p, h)) {
        pacienteApagar(p);
        pilhaApagar(h);
        return NULL;
    }
    
    // Cria o registro e o nó
    Registro *reg = RegistroCriar(p, h);
    no *n = criar_no(reg);
    
    // Recursão: reconstrói subárvores
    n->esq = lerArvoreRec(fp);
    n->dir = lerArvoreRec(fp);
    
    // Atualiza altura e balanceia
    atualizar_altura(n);
    
    return n;
}

/*
Pré-Cond: a Árvore existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve a árvore no arquivo usando percurso em pré-ordem
*/
bool saveArvore(FILE *fp, Arvore *arv)
{
    if (arv == NULL || fp == NULL) {
        printf("Erro ao salvar Árvore!\n");
        return false;
    }
    
    return saveArvoreRec(fp, arv->raiz);
}

/*
Pré-Cond: a Heap existe e não é NULL, o ponteiro para arquivo foi criado no modo wb
Pós-Cond: Escreve a heap no arquivo (tamanho + array de chaves)
*/
bool saveHeap(FILE *fp, Heap *h)
{
    if (h == NULL || fp == NULL) {
        printf("Erro ao salvar Heap!\n");
        return false;
    }

    // Salva o tamanho atual da heap
    if (fwrite(&(h->pos), sizeof(int), 1, fp) < 1) return false;
    
    // Salva cada chave (prioridade, chegada, ID do paciente)
    for (int i = 0; i < h->pos; i++) {
        if (fwrite(&(h->chaves[i].prioridade), sizeof(int), 1, fp) < 1) return false;
        if (fwrite(&(h->chaves[i].chegada), sizeof(int), 1, fp) < 1) return false;
        
        // Salva apenas o ID do paciente (não o ponteiro)
        int id = h->chaves[i].paciente->id;
        if (fwrite(&id, sizeof(int), 1, fp) < 1) return false;
    }

    return true;
}


//funções para ler um arquivo


/*
Pré-Cond: a Árvore existe e está vazia, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Reconstrói a árvore a partir do arquivo
*/
bool lerArvore(FILE *fp, Arvore *arv)
{
    if (arv == NULL || fp == NULL) {
        printf("Erro ao importar Árvore!\n");
        return false;
    }

    arv->raiz = lerArvoreRec(fp);
    
    return true;
}

/*
Pré-Cond: a Heap existe e está vazia, a Árvore JÁ FOI CARREGADA, o ponteiro para arquivo foi criado no modo rb
Pós-Cond: Reconstrói a heap usando os IDs salvos para buscar os pacientes na árvore
*/
bool lerHeap(FILE *fp, Arvore *arv, Heap *h, int *global_chegada)
{
    if (h == NULL || arv == NULL || fp == NULL) {
        printf("Erro ao importar Heap!\n");
        return false;
    }
    
    // Lê o tamanho da heap
    int n;
    if (fread(&n, sizeof(int), 1, fp) < 1) {
        // Arquivo vazio ou fim de arquivo - heap vazia é aceitável
        return true;
    }
    
    // Lê cada chave e reconstrói
    for (int i = 0; i < n; i++) {
        int prioridade, chegada, id;
        
        if (fread(&prioridade, sizeof(int), 1, fp) < 1) return false;
        if (fread(&chegada, sizeof(int), 1, fp) < 1) return false;
        if (fread(&id, sizeof(int), 1, fp) < 1) return false;
        
        // Busca o paciente na árvore pelo ID
        Registro *reg = arvore_buscar(id, arv->raiz);
        if (reg == NULL) {
            printf("Erro: Paciente ID %d na heap não encontrado na árvore!\n", id);
            return false;
        }
        
        // Cria a chave e insere na heap
        chave *nova_chave = criarChave(prioridade, chegada, reg->paciente);
        if (!heap_inserir(nova_chave, h)) {
            printf("Erro ao inserir paciente na heap!\n");
            free(nova_chave);
            return false;
        }
        
        free(nova_chave); // A heap faz uma cópia, pode liberar
        
        // Atualiza o global_chegada para o maior valor
        if (chegada >= *global_chegada) {
            *global_chegada = chegada + 1;
        }
    }

    return true;
}
