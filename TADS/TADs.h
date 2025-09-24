#include "Pilha.h"
#include "Fila.h"

#ifndef TADS
#define TADS






//Lista servirá para o registro dos pacientes;
typedef struct Lista {
    No *head;
    No *tail;
    int tamanho;
}Lista;




//funções de No

No *NoCriar(Paciente *p, Pilha *hist);
void NoApagar(No *n);






//funcoes de Lista 

Lista *listaCriar();
void listaApagar(Lista *lista);
void adicionar(Lista *l, No *n);
void remover(Lista *l, int id); //remover por id


#endif