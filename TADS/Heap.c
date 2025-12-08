#include "Heap.h" 
#include "Registro.h"
#include <stdlib.h>
#include <stdio.h>
Heap *criarHeap(int n){
    Heap* h = malloc(sizeof(Heap));
    if(h==NULL) return NULL;
    h->chaves = malloc(n*sizeof(chave));
    if(h->chaves == NULL)
    {
        free(h);
        return NULL;
    }
    
    h->pos = 0;
    h->max = n;
    return h;
}

chave *criarChave(int p, int c, Paciente *pac)
{
    chave* chave = malloc(sizeof(chave));
    if(chave==NULL)
        return NULL;
    chave->prioridade = p;
    chave->chegada = c;
    chave->paciente = pac;
    return chave;
}

bool apagarChave(chave *c)
{
    free(c);
    return true;
}

bool apagarHeap(Heap *h)
{
    if (h == NULL) return false;
    free(h->chaves);
    free(h);
    return true;
}

int menorFilho(int r, chave* c, int pos)
{
    int fe = 2*r +1;
    int fd = 2*r +2;
    if (fd < pos) {
        if (c[fe].prioridade == c[fd].prioridade) {
            return c[fe].chegada < c[fd].chegada ? fe : fd;
        }
        else
        {
            return c[fe].prioridade < c[fd].prioridade ? fe : fd;
        }
    }
    return fe;
}
bool esta_cheia(Heap* h)
{
    return h->pos == h->max;
}
bool esta_vazia(Heap *h)
{
    return h->pos == 0;
}
void troca(Heap* h, int a,int b)
{
    chave tmp = h->chaves[a];
    h->chaves[a] = h->chaves[b];
    h->chaves[b] = tmp;
}
void organizar_heap_cima(int n,Heap *h)
{   
    if(n==0)
        return;
    int pai = (n-1)/2;
    
        bool deve_trocar = false;
    
    if(h->chaves[pai].prioridade > h->chaves[n].prioridade) {
        // Filho tem maior prioridade (número menor)
        deve_trocar = true;
    } 
    else if(h->chaves[pai].prioridade == h->chaves[n].prioridade) {
        // Mesma prioridade: verificar ordem de chegada
        if(h->chaves[pai].chegada > h->chaves[n].chegada) {
            deve_trocar = true;
        }
    }
    
    if(deve_trocar) {
        troca(h, pai, n);
        organizar_heap_cima(pai, h);
    }
    return;
}

void organizar_heap_baixo(int r,Heap *h)
{   
   
    if((2*r + 1)<h->pos)
    {
        int mf = menorFilho(r,h->chaves, h->pos);
        bool deve_trocar = false;
    
        if(h->chaves[r].prioridade > h->chaves[mf].prioridade) {
            // Filho tem maior prioridade (número menor)
            deve_trocar = true;
        }
        else if(h->chaves[r].prioridade == h->chaves[mf].prioridade) {
            // Mesma prioridade: verificar ordem de chegada
            if(h->chaves[r].chegada > h->chaves[mf].chegada) {
                deve_trocar = true;
            }
        }
        
        if(deve_trocar) {
            troca(h, mf, r);
            organizar_heap_baixo(mf, h);
        }
    }
   
}
bool heap_inserir(chave *c, Heap *h)
{
    if(esta_cheia(h))
        return false;

    h->chaves[h->pos] = *c;
    c->paciente->na_fila = true;
    
    organizar_heap_cima(h->pos,h);
    h->pos++;
    return true;
    
    
}
chave topo(Heap *h){
    return h->chaves[0];
}

Paciente *heap_remover(Heap *h)
{
    if(esta_vazia(h))
        return NULL;
    Paciente *removido = h->chaves[0].paciente;
    h->pos--;
    h->chaves[0] = h->chaves[h->pos];

    if(h->pos>0)
        organizar_heap_baixo(0,h);
    return removido;
    
}
void print_heap(Heap *h)
{
    for(int i = 0; i<h->pos; i++)
    {
        printf("\nPrioridade: %d\nNome: %s\nID: %d\n",h->chaves[i].prioridade, h->chaves[i].paciente->nome, h->chaves[i].paciente->id);
    }
}
