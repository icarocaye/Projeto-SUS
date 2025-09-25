#include "Lista.h"
#include <stdlib.h>


//funcoes registro


//funcoes Lista

Lista* criarLista(){
    Lista* lista = malloc(sizeof(Lista));
   

    lista->phead = NULL;
    lista->ptail = NULL;

    lista->tamanho = 0;
    
    return lista;
}
void apagarLista(Lista *l)
{
    free(l);
}

//insere registro de paciente no fim da lista
void inserirPaciente(Registro registro_paciente, Lista *l){
    

}

bool listaCheia(Lista *l){

}