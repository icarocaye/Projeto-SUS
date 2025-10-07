#ifndef LISTA
#define LISTA
#include "Pilha.h"
#include "Registro.h"

//Lista encadeada para registro dos pacientes;
typedef struct Lista{
    Registro *topo;
    Registro *inicio;
    int tamanho;
}Lista;

Lista* criarLista();
void apagarLista(Lista* l);

void listaInserir(Registro *registro_paciente,Lista *l);
bool listaRemover(int id, Lista *l);
Paciente *buscarPaciente(int id, Lista *l);
Registro *buscarRegistro(int id, Lista *l);

void listarPacientes(Lista *l);
bool listaVazia(Lista *l);

#endif