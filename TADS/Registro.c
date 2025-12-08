#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Registro.h"

//funções de Paciente

Paciente *pacienteEmBranco() {
    Paciente *p = (Paciente *)malloc(sizeof(Paciente));
    return p;
}

Paciente *pacienteCriar(char nome[NOME_MAX], int id) {
  
    Paciente *p = (Paciente *)malloc(sizeof(Paciente));
    if(p == NULL){
        perror("Erro ao alocar paciente!");
        return NULL;
    }
    
    strcpy(p->nome,nome);
    p->id = id;
    p->na_fila = false;
    return p;
}

bool pacienteApagar(Paciente *p) {
    if (p == NULL) return false;
    
    free(p);
    return true;
}

//funções de Registro

Registro *RegistroCriar(Paciente *paciente, Pilha *historico)
{
    Registro *reg = malloc(sizeof(Registro)); 
    if (reg == NULL) {
        perror("Erro ao alocar registro!");
        return NULL;
    }
    reg->paciente = paciente;
    reg->historico = historico;
    reg->prox = NULL;
    return reg;
}

bool RegistroApagar(Registro *n) {
    if (n == NULL) false;

    free(n);
    return true;
}

bool RegistroApagarSemDados(Registro *n) {
    if (n == NULL) return false;
    // Não libera paciente nem historico, apenas o registro
    free(n);
    return true;
}