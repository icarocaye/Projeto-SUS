#include <stdbool.h>

#ifndef PILHA
#define PILHA
#define CAP 10
#define MAX 101


//Pilha será usada para o histórico dos pacientes
typedef struct Pilha {
    char procedimentos[CAP][MAX]; //vetor de 10 strings de até 100 chars
    int tamanho;
} Pilha;

#endif

//funções de Pilha

Pilha *pilhaCriar();
void pilhaApagar(Pilha *h);

void empilhar(Pilha *h, char proc[MAX]);
bool desempilhar(Pilha *h);
int pilhaSize(Pilha *h);
bool pilhaVazia(Pilha *h);
int pilhaTamanho(Pilha *h);