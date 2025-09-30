#ifndef LISTA
#define LISTA
#include <stdio.h>
#include "Registro.h"

//Lista encadeada para registro dos pacientes;

typedef struct Lista{
    Registro *topo;
    Registro *inicio;
    int tamanho;
}Lista;

//funções de Lista

Lista* criarLista();
void apagarLista(Lista* l);

void inserirPaciente(Registro *registro_paciente,Lista *l);
Paciente* apagarPaciente(int id, Lista *l);
Paciente *buscarPaciente(int id, Lista *l);
Registro *buscarRegistro(int id, Lista *l);

void listarPacientes(Lista *l);
bool listaVazia(Lista *l);

#endif