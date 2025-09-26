#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>

//funcoes registro


Registro *criarRegistro(Paciente *paciente, Pilha *historico)
{
    Registro *reg = malloc(sizeof(Registro)); 
    reg->paciente = paciente;
    reg->historico = historico;
    reg->prox = NULL;
    return reg;
}

//funcoes Lista
Lista* criarLista(){
    Lista* lista = malloc(sizeof(Lista));
   
    lista->inicio = NULL;
    lista->topo = NULL;
    lista->tamanho = 0;
    
    return lista;
}
void apagarLista(Lista *l)
{
    if (l == NULL) return;

    Registro *r = l->inicio;
    while (r != NULL) {
        Registro *prox = r->prox;
        free(r); // aqui você pode decidir se libera também paciente e histórico
        r = prox;
    }
    free(l);
}

//verifica se lista esta vazia
bool listaVazia(Lista *l){
    return l->tamanho == 0;
}
//insere registro de paciente no fim da lista
void inserirPaciente(Registro *registro_paciente, Lista *l){
    if(l== NULL)
        return;
    if(l->inicio == NULL)   
        l->inicio = registro_paciente;
    else
        l->topo->prox = registro_paciente;
    
    l->topo = registro_paciente;
    registro_paciente->prox = NULL;
    l->tamanho++;

}

Paciente *buscarPaciente(int id, Lista *l)
{   
    Registro *r = l->inicio;
    while(r!=NULL && r->paciente->id!=id)
        r=r->prox;

    if(r!=NULL)
        return r->paciente;

    return NULL;
}
Registro *buscarRegistro(int id, Lista *l)
{   
    Registro *r = l->inicio;
    while(r!=NULL && r->paciente->id!=id)
        r=r->prox;

    if(r!=NULL)
        return r;

    return NULL;
}

Paciente* apagarPaciente(int id, Lista *l)
{   
    if (l == NULL || listaVazia(l)) {
        return NULL; // lista vazia
    }

    Registro *r = l->inicio;
    Registro *aux = NULL;

    // procura o registro
    while (r != NULL && r->paciente->id != id) {
        aux = r;
        r = r->prox;
    }

    if (r == NULL) {
        // não encontrado
        return NULL;
    }

    // caso seja o primeiro nó
    if (r == l->inicio) {
        l->inicio = r->prox;
        printf("\nremovido do inicio\n");
    } else {
        aux->prox = r->prox;
        printf("\nremovido do meio\n");
    } 

    // caso seja o último nó
    if (r == l->topo) {
        l->topo = aux;
        printf("\nremovido do topo\n");
    }
    
    Paciente *p = r->paciente; // guarda o paciente
    free(r); // libera o registro
    l->tamanho--;

    return p;
}


void listarPacientes(Lista *l)
{   
    Registro *r = l->inicio;
    while(r!=NULL)
    {
        printf("\n Paciente (id=%d) \n ---------\n nome: %s \n historico: lorem ipsilum lorem ipsilum \n",
        r->paciente->id, r->paciente->nome);\
        
        r=r->prox;
    }

}