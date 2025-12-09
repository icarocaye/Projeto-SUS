#ifndef HEAP
#define HEAP

#include "Registro.h"

typedef struct chave{
    int prioridade;
    int chegada;
    Paciente* paciente;
}chave;

typedef struct Heap{

    chave* chaves;
    int pos;
    int max;

}Heap;

Heap* criarHeap(int n);
bool apagarHeap(Heap *h);

chave* criarChave(int prioridade, int chegada, Paciente *paciente);
bool apagarChave(chave *c);

int maiorFilho(int r, chave* chaves, int pos);
bool heap_inserir(chave *p, Heap *heap);
chave heap_remover(Heap *heap);
chave proximo(Heap *heap);
bool esta_cheia(Heap *heap);
bool esta_vazia(Heap *heap);
void troca(Heap *heap,int i, int j);
chave topo(Heap *heap);
void organizar_heap_cima(int pos, Heap *heap);
void organizar_heap_baixo(int pos, Heap *heap);

void print_heap(Heap *h);

#endif