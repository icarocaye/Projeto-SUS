#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>

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
void listaInserir(Registro *registro_paciente, Lista *l){
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
    if(listaVazia(l))
        return NULL;

    Registro *r = l->inicio;
    while(r!=NULL && r->paciente->id!=id)
        r=r->prox;

    if(r!=NULL)
        return r->paciente;

    return NULL;
}
Registro *buscarRegistro(int id, Lista *l)
{   
    if(listaVazia(l))
        return NULL;
        
    Registro *r = l->inicio;
    while(r!=NULL && r->paciente->id!=id)
        r=r->prox;

    if(r!=NULL)
        return r;

    return NULL;
}

bool listaRemover(int id, Lista *l)
{   
    if (l == NULL || listaVazia(l)) {
        return false; // lista vazia
    }

    Registro *r = l->inicio;
    Registro *aux = NULL;

    // procura o nó anterior ao registro
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
    } else {
        aux->prox = r->prox;
   
    } 

    // caso seja o último nó
    if (r == l->topo) {
        l->topo = aux;
    }
    
    pacienteApagar(r->paciente);
    pilhaApagar(r->historico);
    free(r); // libera o registro
    l->tamanho--;

    return true;
}


void listarPacientes(Lista *l)
{   
    Registro *r = l->inicio;
    while(r!=NULL)
    {
        printf("\nPaciente (id=%d) \n ---------\n nome: %s  \n",
        r->paciente->id, r->paciente->nome);\
        Pilha *hist = r->historico;
        if(hist->tamanho>0){
            printf("\nhistórico:\n");
            
            for(int i = 0;i<hist->tamanho;i++){
                printf(" %d -- %s \n",i+1,hist->procedimentos[i]);
            }
        }else
            printf("Paciente sem histórico");
        r=r->prox;
    }

}