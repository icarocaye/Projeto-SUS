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

chave* criarChave(int p, Paciente *pac)
{
    chave* chave = malloc(sizeof(chave));
    if(chave==NULL)
        return NULL;
    chave->prioridade = p;
    chave->paciente = pac;
    return chave;
}

int maiorFilho(int r, chave* c, int pos)
{
    int fe = 2*r +1;
    int fd = 2*r +2;
    if(fd<pos)
    {
        return c[fe].prioridade> c[fd].prioridade ? fe : fd;
    }
    return fe;
}
bool esta_cheia(Heap* h)
{
    return h->pos==h->max;
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
    
    if(h->chaves[pai].prioridade < h->chaves[n].prioridade)
    {
        troca(h,pai,n);
        organizar_heap_cima(pai,h);
    }
   
}   
void organizar_heap_baixo(int r,Heap *h)
{   
   
    if((2*r + 1)<h->pos)
    {
        int mf = maiorFilho(r,h->chaves, h->pos);
        if(h->chaves[r].prioridade < h->chaves[mf].prioridade)
        {
            troca(h,mf,r);
            organizar_heap_baixo(mf,h);
        }
    }
   
}
bool inserir(chave c, Heap *h)
{
    if(esta_cheia(h))
        return false;

    h->chaves[h->pos] = c;
    
    organizar_heap_cima(h->pos,h);
    h->pos++;
    return true;            
    
    
}
chave topo(Heap *h){
    return h->chaves[0];
}

bool remover(Heap *h)
{
    if(esta_vazia(h))
        return false;

    h->pos--;
    h->chaves[0] = h->chaves[h->pos];

    if(h->pos>0)
        organizar_heap_baixo(0,h);
    return true;
    
}
void print(Heap *h)
{
    for(int i = 0; i<h->pos; i++)
    {
        printf("%d",h->chaves[i].prioridade);
    }
}
