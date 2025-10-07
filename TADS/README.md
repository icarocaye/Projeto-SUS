# Estrutura e implementação dos TADs
Este documento tem como intuito apresentar a estrutura e as funcionalidades de cada tipo abstrato de dados (TAD) utilizado neste projeto. Os detalhes sobre a interface do sistema e o funcionamento do programa principal estão contidos em [Projeto SUS](../README.md).  

Apesar de todos os TADs serem acessíveis à main.c (decisão que foi feita para generalizar a aplicação deles no sistema), as estruturas mais utilizadas diretamente são [Histórico (Pilha)](Pilha.h), [Fila](Fila.h) e [Lista](Lista.h). De qualquer forma, vamos descrever cada um dos TADs, começando pelos mais fundamentais, que são incorporados em TADs posteriores, como os que acabaram de ser mencionados.  

## Paciente
Paciente é um dos dois TADs fundamentais do projeto, aqueles que serão incorporados em outros TADs e, portanto, precisam estar em ordem para permitir o funcionamento deles.  

Paciente guarda apenas um id e um nome e tem a seguinte estrutura:  

```c
typedef struct {
    int id;
    char nome[50];
} Paciente;
```

Suas funções são simples, apenas para criar e apagar um paciente  

```c
Paciente *pacienteCriar(int id, char nome[50]);
void pacienteApagar(Paciente *p);
```

OBS: por praticidade, o TAD Paciente foi incluído em [Registro.h](Registro.h), pois é somente usado nele.

## Pilha
Pilha representa o histórico de procedimentos de um paciente. Assim como Paciente, ele também será incroporado nos próximos TADs, no entanto, ele também será acessado diretamente pelo cliente para adicionar e remover procedimentos. A Pilha guarda até 10 procedimentos por meio de um vetor de strings (essencialmente, uma matriz de chars) e a quantidade de procedimentos que contém, sua estrutura é a seguinte:

```c
typedef struct Pilha {
    char procedimentos[CAP][MAX]; //vetor de 10 strings de até 100 chars
    int tamanho;
} Pilha;
```

Suas funções devem permitir a manipulação do histórico seguindo o conceito de uma pilha, permitindo apenas inserir e retirar no fim/topo (empilhar e desempilhar). Além disso, temos funções para criar e apagar e também para consultas.

```c
Pilha *pilhaCriar();
void pilhaApagar(Pilha *h);

void empilhar(Pilha *h, char proc[MAX]);
bool desempilhar(Pilha *h);
bool pilhaVazia(Pilha *h);
int pilhaTamanho(Pilha *h);
```

## Registro (nó)
Registro é o primeiro TAD composto por outros. Ele funciona como nó tanto da Fila quanto da Lista e seu intuito é apontar para um paciente e para um histórico, que passa a ser associado a ele. Sua estrutura também inclui um ponteiro para o próximo registro da estrutura em que estiver inserido:

```c
typedef struct Registro {
    Paciente *paciente;
    Pilha *historico;
    struct Registro *prox;
} Registro;
```

Ele aponta ao invés de armazenar cruamente esses valores pois cada paciente + histórico precisa de dois registros: um para a Fila e outro para a Lista, para que não haja conflito entre as duas estruturas. Nesse caso, como esses dois registros apontam para o mesmo paciente e histórico, não precisamos duplicá-los na memória.  

Por ser usado apenas como um nó, as funções do Registro são simples, somente para criar e apagar.

```c
Registro *criarRegistro(Paciente *paciente, Pilha *historico);
void apagarRegistro(Registro *registro);
```

## Fila

## Lista

## Saveload (IO)
