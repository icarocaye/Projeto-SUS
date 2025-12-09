#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#include "TADS/Pilha.h"
#include "TADS/Heap.h"   // Substitui Fila.h (Prioridade)
#include "TADS/Arvore.h" // Substitui Lista.h (Eficiência)
#include "TADS/Registro.h"
#include "TADS/Saveload.h"

// Variável de controle da ordem de chegada
int global_chegada = 0;

// Função auxiliar para limpar buffer
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler prioridade (Regra do P2)
int ler_prioridade() {
    int p;
    do {
        printf("\nNivel de Urgência (1-Emergencia ... 5-Não Urgente): ");
        if (scanf("%d", &p) != 1) {
            limpar_buffer();
            p = -1; 
        }
    } while (p < 1 || p > 5);
    return p;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    // Inicialização das estruturas P2
    Heap *fila_de_espera = criarHeap(150);
    Arvore *cadastro_geral = criar_arvore();

    // Tentar carregar dados salvos
    FILE *arquivo = fopen("hospital.dat", "rb");
    if (arquivo != NULL) {
        printf("Carregando dados anteriores...\n");
        if (lerArvore(arquivo, cadastro_geral) && 
            lerHeap(arquivo, cadastro_geral, fila_de_espera, &global_chegada)) {
            printf("Dados carregados com sucesso!\n");
        } else {
            printf("Erro ao carregar dados. Iniciando sistema vazio.\n");
        }
        fclose(arquivo);
    }

    int opcao;
    int id_temp;
    char nome_temp[NOME_MAX];
    char procedimento_temp[MAX];
    char confirmacao;
    Registro *busca; // Ponteiro auxiliar para operações

    printf("Bem-vindo ao sistema PRONTO SOCORRO SUS V2!\n");

    do {
        printf("\n=============================================\n"
               "MENU:\n"
               "=============================================\n"
               "1. Registrar paciente (Triagem)\n"
               "2. Remover paciente (Do cadastro)\n"
               "3. Adicionar procedimento ao historico\n"
               "4. Desfazer ultimo procedimento\n"
               "5. Chamar paciente (Atendimento)\n"
               "6. Mostrar fila de espera (Prioridade)\n"
               "7. Mostrar historico do paciente\n"
               "8. Listar todos os pacientes\n"
               "9. Sair\n"
               "=============================================\n"
               "Escolha: ");
        
        scanf("%d", &opcao);
        limpar_buffer();

        switch(opcao) {
            
            // --- REGISTRAR PACIENTE (Adaptação P2: Heap + Arvore) ---
            case 1:
                printf("\n--- TRIAGEM ---\n");
                printf("Entre com o ID do paciente: ");
                scanf(" %d", &id_temp);
                limpar_buffer();

                // Busca O(log n) na árvore
                busca = arvore_buscar(id_temp, cadastro_geral->raiz);

                if (busca != NULL) {
                    printf("\n!!!! PACIENTE JA CADASTRADO !!!!\n");
                    printf("Nome: %s\nID: %d\n", busca->paciente->nome, busca->paciente->id);
                    
                    if (busca->paciente->na_fila) {
                        printf("ERRO: Paciente ja esta na fila de espera!\n");
                    } else {
                        printf("Deseja colocar na fila de espera novamente? (S/N): ");
                        scanf(" %c", &confirmacao);
                        limpar_buffer();
                        if (confirmacao == 'S' || confirmacao == 's') {
                            int prio = ler_prioridade();
                            chave *nova_chave = criarChave(prio, global_chegada++, busca->paciente);
                            if (heap_inserir(nova_chave, fila_de_espera)) {
                                busca->paciente->na_fila = true;
                                printf("Paciente reconduzido a fila com sucesso.\n");
                            } else {
                                printf("Erro: Fila cheia!\n");
                            }
                        }
                    }
                } else {
                    // Paciente Novo
                    printf("Entre com o nome do paciente: ");
                    fgets(nome_temp, NOME_MAX, stdin);
                    nome_temp[strcspn(nome_temp, "\n")] = 0; 

                    int prio = ler_prioridade();

                    Paciente *novo_pac = pacienteCriar(nome_temp, id_temp);
                    Pilha *novo_hist = pilhaCriar();
                    Registro *novo_reg = RegistroCriar(novo_pac, novo_hist);

                    // Insere na Árvore (Persistência)
                    arvore_inserir(novo_reg, cadastro_geral);

                    // Insere na Heap (Atendimento)
                    chave *nova_chave = criarChave(prio, global_chegada++, novo_pac);
                    if (heap_inserir(nova_chave, fila_de_espera)) {
                        printf("\nPACIENTE INSERIDO NO SISTEMA E NA FILA!\n");
                    } else {
                        printf("\nErro: Fila cheia! Cadastrado apenas no sistema.\n");
                        novo_pac->na_fila = false;
                    }
                }
                break;

            // --- REMOVER PACIENTE ---
            case 2: 
                printf("Entre com o ID do paciente para remover: ");
                scanf(" %d", &id_temp);
                limpar_buffer();

                busca = arvore_buscar(id_temp, cadastro_geral->raiz);
                
                if (busca == NULL) {
                    printf("\n!!! PACIENTE NAO ENCONTRADO !!!\n");
                } else {
                    // Regra P2: Não pode remover se estiver na fila
                    if (busca->paciente->na_fila) {
                        printf("ERRO: Impossivel remover. Paciente aguardando atendimento (está na fila)!\n");
                    } else {
                        printf("Tem certeza que deseja remover %s? (S/N): ", busca->paciente->nome);
                        scanf(" %c", &confirmacao);
                        limpar_buffer();
                        if(confirmacao == 'S' || confirmacao == 's') {
                            arvore_remover(id_temp, cadastro_geral);
                            printf("\n--- PACIENTE REMOVIDO DOS REGISTROS ---\n");
                        }
                    }
                }
                break;

            // --- ADICIONAR PROCEDIMENTO (Restaurado) ---
            case 3:
                printf("Entre com o ID do paciente: ");
                scanf(" %d", &id_temp);
                limpar_buffer();
                
                busca = arvore_buscar(id_temp, cadastro_geral->raiz);
                
                if(busca == NULL) {
                    printf("\n!!! PACIENTE NAO EXISTE !!!\n");
                } else {
                    printf("Paciente: %s. Digite o procedimento:\n", busca->paciente->nome);
                    fgets(procedimento_temp, MAX, stdin);
                    procedimento_temp[strcspn(procedimento_temp, "\n")] = 0;

                    empilhar(busca->historico, procedimento_temp);
                    printf("ADICIONADO AO HISTORICO.\n");
                }
                break;

            // --- DESFAZER PROCEDIMENTO (Restaurado) ---
            case 4: 
                printf("Entre com o ID do paciente: ");
                scanf(" %d", &id_temp);
                limpar_buffer();
                
                busca = arvore_buscar(id_temp, cadastro_geral->raiz);

                if(busca == NULL) {
                    printf("\n!!! PACIENTE NAO EXISTE !!!\n");
                } else {
                    if(pilhaVazia(busca->historico)) {
                        printf("\n!!! HISTORICO VAZIO !!!\n");
                    } else {
                        printf("Desfazer ultimo procedimento de %s? (S/N): ", busca->paciente->nome);
                        scanf(" %c", &confirmacao);
                        limpar_buffer();
                        if(confirmacao == 'S' || confirmacao == 's') {
                            desempilhar(busca->historico);
                            printf("ULTIMO PROCEDIMENTO REMOVIDO.\n");
                        }
                    }
                }
                break;

            // --- CHAMAR PACIENTE (Heap) ---
            case 5:
                chave atendido = heap_remover(fila_de_espera);
                
                if(atendido.paciente != NULL) {
                    printf("\n*** CHAMANDO PACIENTE ***\n");
                    printf("Nome: %s (ID: %d)\n", atendido.paciente->nome, atendido.paciente->id);
                    
                    // Atualiza flag na árvore
                    atendido.paciente->na_fila = false;
                } else {
                    printf("\n!!! FILA DE ESPERA VAZIA !!!\n");
                }
                break;

            // --- MOSTRAR FILA (Prioridade) ---
            case 6: 
                printf("\n--- FILA DE ESPERA (Por Prioridade) ---\n");
                print_heap(fila_de_espera);
                break;

            // --- MOSTRAR HISTORICO (Restaurado) ---
            case 7:
                printf("Entre com o ID do paciente: ");
                scanf(" %d", &id_temp);
                limpar_buffer();

                busca = arvore_buscar(id_temp, cadastro_geral->raiz);
                
                if(busca == NULL) {
                    printf("\n!!! PACIENTE NAO EXISTE !!!\n");
                } else {
                    printf("\nHISTORICO DE: %s (ID=%d)\n", busca->paciente->nome, busca->paciente->id);
                    if(pilhaVazia(busca->historico)) {
                        printf("(Sem procedimentos registrados)\n");
                    } else {
                        // Acesso direto à pilha (conforme seu código original)
                        for(int i = 0; i < busca->historico->tamanho; i++) {
                             printf("%d -> %s\n", i+1, busca->historico->procedimentos[i]);
                        }
                    }
                }
                break;

            // --- LISTAR TODOS (Arvore In-Order) ---
            case 8:
                printf("\n--- CADASTRO GERAL DO HOSPITAL ---\n");
                em_ordem(cadastro_geral->raiz);
                break;

            case 9:
                printf("Encerrando e salvando dados...\n");
                // Salvar dados
                FILE *arquivo = fopen("hospital.dat", "wb");
                if (arquivo != NULL) {
                    if (saveArvore(arquivo, cadastro_geral) && saveHeap(arquivo, fila_de_espera)) {
                        printf("Dados salvos com sucesso!\n");
                    } else {
                        printf("Erro ao salvar dados!\n");
                    }
                    fclose(arquivo);
                } else {
                    printf("Erro ao criar arquivo de salvamento!\n");
                }
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 9);

    apagarHeap(fila_de_espera);
    apagar_arvore(cadastro_geral);

    return 0;
}
