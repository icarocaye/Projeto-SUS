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
        printf("\n=== Inserindo paciente %d ===\n", i);

        Paciente *paciente = pacienteCriar("aa", i);
        Pilha *p = pilhaCriar();
        Registro *r = criarRegistro(paciente, p);
        inserirPaciente(r, l);

        imprimirLista(l);

        // Buscar paciente recém-inserido
        Paciente *pa = buscarPaciente(i, l);
        if (pa != NULL) {
            printf("Busca OK: id=%d nome=%s\n", pa->id, pa->nome);
        } else {
            printf("Paciente %d não encontrado!\n", i);
        }

        // Agora remover o primeiro paciente (id=1)
        if (i == 3) { // só remove no final pra testar a lista cheia
            printf("\n--- Removendo paciente 1 ---\n");
            Paciente *removido = apagarPaciente(1, l);
            if (removido != NULL) {
                printf("Removido: id=%d nome=%s\n", removido->id, removido->nome);
            } else {
                printf("Paciente 1 não estava na lista\n");
            }
            imprimirLista(l);
        }

        // Debug do estado interno
        if (l->inicio != NULL) {
            printf("inicio = %p (id=%d)\n", (void*)l->inicio, l->inicio->paciente->id);
            printf("inicio->prox = %p\n", (void*)l->inicio->prox);
        } else {
            printf("inicio = NULL\n");
        }

        if (l->topo != NULL) {
            printf("topo   = %p (id=%d)\n", (void*)l->topo, l->topo->paciente->id);
        } else {
            printf("topo = NULL\n");
        }
    }

    return 0;
}
