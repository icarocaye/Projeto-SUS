#ifndef TADS
#define TADS
#define MAX 101

typedef struct {
    char *nome;
    int id;
} Paciente;

//Pilha será usada para o histórico dos pacientes
//ATENÇÃO: preciso ajustar a Pilha de acordo com os requisitos do pdf (preciso entender melhor o que ele quer dizer tbm kk)
typedef struct Pilha {
    char *procedimentos[MAX]; //vetor de string de até 100 chars
    int size;
} Pilha;

//Node conterá 
typedef struct Node {
    Paciente *paciente;
    Pilha *hist;
    Node *prox;
} Node;

//Fila servirá como a fila de espera do hospital
typedef struct Fila {
    Node *head;
    Node *tail;
    int size;
} Fila;



//funções de Paciente

Paciente *pacienteCriar(char *nome, int id);
void pacienteApagar(Paciente *p);


//funções de Node

Node *nodeCriar(Paciente *p, Pilha *hist);
void nodeApagar(Node *n);


//funções de Pilha

Pilha *pilhaCriar(char *proc[MAX]);
void pilhaApagar(Pilha *pi);

void empilhar(Pilha *pi, Node *n);
Node desempilhar(Pilha *pi);
int pilhaSize(Pilha *pi);
bool pilhaVazia(Pilha *pi);


//funções de Fila

Fila *filaCriar();
void filaApagar(Fila *f);

int filaSize(Fila *f);
bool filaVazia(Fila *f);
void queue(Fila *f, Node *n);
Node dequeue(Fila *f, Node *n);


#endif