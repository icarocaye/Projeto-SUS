#ifndef SAVE
#define SAVE
#include <stdio.h>
//Fila.h e Lista.h já incluem todos os outros TADs
#include "Fila.h"
#include "Lista.h"

/*
TRATAMENTO DE ERRO
Em caso de erro, as funções retornam false e exibem uma mensagem de erro na tela, dizendo em qual estrutura 
o erro se deu e o código dele, que segue esse dicionário:
Código 0 - um dos ponteiros recebidos pela função é aponta para NULL e, portanto, não pode ser acessado.
Código 1 - erro ao salvar um int.
Código 2 - erro ao salvar um vetor.
Código 3 - erro ao salvar um ponteiro.
*/

//funções para gravar no arquivo

//serão usadas dentro de saveReg:
bool savePac(FILE *f, Paciente *p);
bool saveHist(FILE *f, Pilha *h);

//será usada dentro de saveFila e saveLista:
bool saveReg(FILE *f,Registro *n);

bool saveFila(FILE *f, Fila *);
bool saveLista(FILE *f, Lista *l);

//funções para ler um arquivo

//serão usadas dentro de lerReg:
bool lerPac(FILE *f, Paciente *p);
bool lerHist(FILE *f, Pilha *h);

//será usada dentro de lerFila e lerLista:
bool lerReg(FILE *f,Registro *n);

bool lerFila(FILE *f, Fila *);
bool lerLista(FILE *f, Lista *l);

#endif