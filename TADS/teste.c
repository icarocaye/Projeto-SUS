#include "Lista.h"
#include "Fila.h"
#include "Pilha.h"
#include <stdio.h>

void imprimirLista(Lista *l) {
    Registro *atual = l->inicio;
    printf("Lista: ");
    while (atual != NULL) {
        printf("[%d] -> ", atual->paciente->id);
        atual = atual->prox;
    }
    printf("NULL\n");
}

int main() {
    Lista *l = criarLista();

    for (int i = 1; i <= 3; i++) {
        Paciente *paciente = pacienteCriar("aa",i);
        Pilha *p = pilhaCriar();
        Registro *r = criarRegistro(paciente, p);
        inserirPaciente(r, l);
        Paciente *pa = buscarPaciente(1,l);
        apagarPaciente(1,l);
        listarPacientes(l);
        printf("\nApós inserir %d:\n", i);
        printf("Resultado busca\nid=%d\nnome id=%s \n", pa->id,pa->nome);
        printf("inicio = %p (id=%d)\n", (void*)l->inicio, l->inicio->paciente->id);
        printf("topo   = %p (id=%d)\n", (void*)l->topo, l->topo->paciente->id);
        printf("inicio->prox = %p\n", (void*)l->inicio->prox);
        imprimirLista(l);
    }

    return 0;
}