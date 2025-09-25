#include "Lista.h"
#include <stdlib.h>


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
   
    lista->inicio = 0;
    lista->topo = NULL;
    lista->tamanho = 0;
    
    return lista;
}
void apagarLista(Lista *l)
{
    free(l);
}

//verifica se lista esta vazia
bool listaVazia(Lista *l){
    return l->tamanho == 0;
}
//insere registro de paciente no fim da lista
void inserirPaciente(Registro *registro_paciente, Lista *l){
    
    if(listaVazia(l))
    {   
        l->inicio = registro_paciente;
        l->topo = registro_paciente;
    }else{

        l->topo->prox = registro_paciente;
        l->topo = registro_paciente;
    }

    l->tamanho++;

}

Paciente buscarPaciente(int id, Lista *l)
{      
    if(inicio->paciente->id == id )
        return inicio->paciente;
    Registro*aux=inicio;
    while(aux!=null)
    {   
        if(aux->paciente->id==id)
            return aux;
        aux=aux->prox;
    }
    return NULL;
}
void apagarPaciente(int id, Lista *l)
{
    
}
