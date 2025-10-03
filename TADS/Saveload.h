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

bool saveFila(FILE *f, Fila *);
bool saveLista(FILE *f, Lista *l);

//funções para ler um arquivo

bool lerFila(FILE *f, Fila *);
bool lerLista(FILE *f, Lista *l);

#endif