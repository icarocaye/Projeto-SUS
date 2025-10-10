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

OBS: por praticidade, o TAD Paciente foi incluído em [Registro.h](Registro.h), pois é usado somente nele.

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
A Fila foi implementada dinamicamente de forma encadeada, usando o TAD Registro como nó. Por isso, não possui de fato um tamanho máximo, e poderia ser expandida até o esgotamento da memória. No entanto, como a proposta do projeto pede que a fila tenha um tamanho finito, foi definido um tamanho máximo de 150 e uma função filaCheia(), que verifica se esse tamanho foi atingido. Dessa forma, a estutura da fila se configura da seguinte forma:

```c
#define TAMANHO_MAX 150

typedef struct Fila {
    Registro *inicio;
    Registro *fim;
    int tamanho;
} Fila;
```

Como registro é alocado dinamicamente, a fila guarda apenas um ponteiro para o inicio e um para o final da fila, para facilitar a inserção, além do tamanho atual da fila, para controle.  

Sua funções seguem o padrão de uma fila, permitindo a inserção no final da estrutura e a remoção no início. Além disso, foi implementada uma função para buscar um registro na fila por meio de um id informado, bem como uma função para imprimir a fila na tela, do início para o fim, tudo isso para contribuir com a sua integração no sistema final. Também há funções de consulta, a fim de seguir o conceito de evitar o acesso direto à estrutura.

```c
Fila *filaCriar();
void filaApagar(Fila *f);

bool filaCheia(Fila *f);
bool filaVazia(Fila *f);
int filaTamanho(Fila *f);
Registro* fila_inicio(Fila *f);
void enfileirar(Fila *f, Registro *n);
bool desenfileirar(Fila *f);
Registro *filaBuscar(Fila *f, int id);
void mostrar_fila(Fila *f);
```

## Lista
Assim como a Fila, a Lista também foi implementada dinamicamente de forma encadeada, usando o TAD registro como nó. Mas é importante ressaltar: a Fila e a Lista não compartilham o mesmo registro, pois, apesar de apontarem para o mesmo paciente e histórico, não podem compartilhar as ligações entre nós, pois isso faria uma estrutura interferir na outra. Dessa forma, existem sempre dois registros (um da fila e um da lista) que apontam para o mesmo paciente e histórico. Diferentemente de fila, não há tamanho máximo para a Lista, que pode ser tão longa quanto a memória permitir. A estrutura da Lista é a seguinte:

```c
typedef struct Lista{
    Registro *topo;
    Registro *inicio;
    int tamanho;
}Lista;
```

As funções de Lista podem ser conferidas a seguir. Note que, assim como os outros TADs, existem funções de construção e destrução, funções para consulta/impressão de valores e as funcionalidades da estrutura fila, que permite inserir e remover em qualquer posição (nesse caso, só precisamos inserir no fim).

```c
Lista* criarLista();
void apagarLista(Lista* l);

void listaInserir(Registro *registro_paciente,Lista *l);
bool listaRemover(int id, Lista *l);
Paciente *buscarPaciente(int id, Lista *l);
Registro *buscarRegistro(int id, Lista *l);

void listarPacientes(Lista *l);
bool listaVazia(Lista *l);
```

## Saveload (IO)
Por fim, temos o TAD que controla a leitura e a gravação das estruturas em arquivos. No projeto, chamamos esse TAD de Saveload, mas outro nome comum para ele seria IO(input/output). Diferentemente dos outros TADs, ele não possui uma estrutura própria, mas apenas funções para salvar as outras estruturas que já definimos.  

As funções públicas do TAD são apenas essas:

```c
//funções para gravar no arquivo
/*
As funções PRECISAM ser chamadas nessa ordem! Fila só pode ser salva depois de Lista.
Ponteiro para arquivo deve ter sido criado no modo wb.
*/
bool saveLista(FILE *wb, Lista *l);
bool saveFila(FILE *wb, Fila *);

//funções para ler um arquivo
/*
As funções PRECISAM ser chamadas nessa ordem! Fila só pode ser lida depois de Lista.
Ponteiro para arquivo deve ter sido criado no modo rb.
*/
bool lerLista(FILE *rb, Lista *l);
bool lerFila(FILE *rb, Lista *L, Fila *);
```

No entanto, dentro da implementação também foi definida uma função para salvar Paciente e seu histórico, que foi utilizadas internamente nas funções públicas, de forma que essas estruturas ficam incluídas no salvamento e na leitura de Fila e Lista.  

Outro detalhe importante é que, como o registro da fila e o registro da lista apontam para o mesmo paciente, não podemos salvar os registros duas vezes, pois isso acaba duplicando o paciente e o histórico na memória. Para solucionar isso, a função de salvar Lista é que salva cada paciente e seu histórico de forma adjacente na memória. A função de salvar Fila, por sua vez, salva apenas o tamanho da fila, pois na hora de ler, faremos algo semelhante. Para ler do arquivo, a função de ler Lista é quem recolhe cada paciente e seu histórico e insere-os na fila. A função de ler Fila usa apenas o tamanho n da fila e lê os últimos n elementos da lista de pacientes (ela foi construída conforme a ordem de chegada, o que significa que os últimos pacientes são os que estavam na fila!) , criando registros diferentes para eles e inserindo-os na fila.  

**Por esse motivo, é imprescindível que saveLista() e lerLista() sejam sempre chamadas antes de saveFila() e lerFila(), respectivamente.**
