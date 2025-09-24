#include "Fila.h"

#ifndef LISTA
#define LISTA

//Estrutura de registro da lista de pacientes
typedef struct Registro{

    Paciente paciente;
    Pilha historico;

}Registro;

//Lista para registro dos pacientes;
typedef struct Lista{
    Registro *pacientes;
    int inicio;
    int fim;
    int tamanho;
}Lista;

Lista* criarLista();
void apagarLista(Lista* l);

void inserirPaciente(Registro registro_paciente,Lista *l);
void apagarPaciente(int id, Lista *l);
Paciente buscarPaciente(int id, Lista *l);
void listarPacientes(Lista *l);
#endif