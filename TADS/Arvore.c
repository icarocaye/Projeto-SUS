    #include "Arvore.h"
    #include "Registro.h"
    #include <stdio.h>
    #include <stdlib.h>


    Arvore *criar_arvore()
    {
        Arvore *a = malloc(sizeof(Arvore));

        a->raiz = NULL;
        a->profundidade = -1;

        return a;
    }
    no *criar_no(Registro *reg)
    {
        no *n = malloc(sizeof(no));
        n->altura = 0;
        n->dados = reg;
        n->dir = NULL;
        n->esq = NULL;
        return n;
    }
    int max(int a,int b)
    {

        return a>b?a:b;
    }
    int obter_altura(no* n)
    {
        return n!= NULL?  n->altura : -1;
    }
    int obter_fb(no *raiz)
    {
        if(raiz==NULL) return 0;
        return obter_altura(raiz->esq) - obter_altura(raiz->dir);
    }
    void atualizar_altura(no *n)
    {
        n->altura = 1 + max(obter_altura(n->esq),obter_altura(n->dir));
    }
    void em_ordem(no *raiz)
    {
        if(raiz==NULL)
            return;
        em_ordem(raiz->esq);
        printf("%d",raiz->dados->paciente->id);
        em_ordem(raiz->dir);
    }
    no *rotacionar_direita(no *raiz)
    {
        no *b = raiz->esq;
        raiz->esq = b->dir;
        b->dir = raiz;

        atualizar_altura(raiz);
        atualizar_altura(b);
        return b;
    }
    no *rotacionar_esquerda(no *raiz)
    {
        no *b = raiz->dir;
        raiz->dir = b->esq;
        b->esq = raiz;

        atualizar_altura(raiz);
        atualizar_altura(b);
        return b;

    }
    no *rotacionar_direita_esquerda(no *raiz)
    {
        raiz->dir = rotacionar_direita(raiz->dir);
        return rotacionar_esquerda(raiz);
    }
    no *rotacionar_esquerda_direita(no *raiz)
    {
        raiz->esq = rotacionar_esquerda(raiz->esq);
        return rotacionar_direita(raiz);
    }
    no *balancear(no *raiz)
    {
        atualizar_altura(raiz);
        int fator = obter_fb(raiz);


        if(fator < -1)
        {
            if(obter_fb(raiz->dir)<=0)
                return rotacionar_esquerda(raiz);

            if(obter_fb(raiz->dir) > 0)
                return rotacionar_direita_esquerda(raiz);
        }
        if(fator > 1)
        {
            if(obter_fb(raiz->esq) >= 0)
                return rotacionar_direita(raiz);
            if(obter_fb(raiz->esq) < 0)
                return rotacionar_esquerda_direita(raiz);

        }

        return raiz;

        

    }

    no *inserir_aux(Registro *reg, no *raiz)
    {
        if(raiz==NULL)
        {
            raiz = criar_no(reg);
        }
        int raiz_id = raiz->dados->paciente->id;
        if(reg->paciente->id < raiz_id)
            raiz->esq = inserir_aux(reg,raiz->esq);
        else if(reg->paciente->id > raiz_id)
            raiz->dir = inserir_aux(reg,raiz->dir);
        else
            return raiz;

        return balancear(raiz);
    }

    Registro* buscar(int id, no *raiz)
    {
        if(raiz==NULL)
            return NULL;
        int raiz_id = raiz->dados->paciente->id;
        
        if(id == raiz_id)
            return raiz->dados;

        if(id < raiz_id)
            return buscar(id, raiz->esq);
        else if(id>raiz_id)
            return buscar(id,raiz->dir);
    }

    no* remover_aux(int id, no *raiz)
    {
        if(raiz==NULL)
            return NULL;
        
        int raiz_id = raiz->dados->paciente->id;
        if(id > raiz_id)
            raiz->dir = remover_aux(id, raiz->dir);
        else if(id < raiz_id)
            raiz->esq = remover_aux(id,raiz->esq);
        
        else 
        {
            no *tmp;
            if(raiz->esq == NULL){
                tmp = raiz->dir;
                free(raiz);
                return tmp;
            }else if(raiz->dir ==  NULL){
                tmp = raiz->esq;
                free(raiz);
                return tmp;
            }

            for(tmp = raiz->esq; tmp->esq != NULL; tmp = tmp->dir);
            raiz->dados = tmp->dados;

            raiz->esq = remover_aux(tmp->dados->paciente->id,raiz->esq);
        }
        return balancear(raiz);
    }
    void remover(int id, Arvore *arv){
        arv->raiz = remover_aux(id,arv->raiz);
    }
    bool inserir(Registro *reg, Arvore *arv)
    {
        return ((arv->raiz = inserir_aux(reg,arv->raiz)) != NULL);
    }