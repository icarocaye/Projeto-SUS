#include "Fila.h"

#ifndef LISTA
#define LISTA

//Estrutura de registro da lista de pacientes
typedef struct Registro{

    Paciente *paciente;
    Pilha *historico;
    struct Registro *prox;
}Registro;

//Lista encadeada para registro dos pacientes;
typedef struct Lista{
    Registro *topo;
    Registro *inicio;
    int tamanho;
}Lista;

Registro *criarRegistro(Paciente *paciente, Pilha *historico);
Registro apagarRegistro(Registro *registro);

Lista* criarLista();
void apagarLista(Lista* l);

void inserirPaciente(Registro *registro_paciente,Lista *l);
void apagarPaciente(int id, Lista *l);
Paciente buscarPaciente(int id, Lista *l);
void listarPacientes(Lista *l);
bool listaVazia(Lista *l);

#endif