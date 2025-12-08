#ifndef TREE
#define TREE
#include "Registro.h"


typedef struct no{
    Registro *dados;
    struct no *esq;
    struct no *dir;
    int altura;
    int fb;
}no;

typedef struct Arvore{
    no *raiz;
    int profundidade;
}Arvore;

Arvore *criar_arvore();
bool apagar_arvore(Arvore *avl);

no *criar_no(Registro *reg);
bool apagar_no(no *n);

int obter_fb(no *n);
int obter_altura(no* n);
void atualizar_altura(no *n);
void em_ordem(no *raiz);
no* rotacionar_direita(no *raiz);
no* rotacionar_esquerda(no *raiz);
no* rotacionar_esquerda_direita(no *raiz);
no* rotacionar_direita_esquerda(no *raiz);
bool arvore_inserir(Registro *novo_registro, Arvore *arvore);
Registro *arvore_buscar(int id, no* raiz);
no *balancear(no*raiz);
void arvore_remover(int id, Arvore *arvore);




#endif