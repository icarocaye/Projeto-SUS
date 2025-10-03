#include <stdio.h>
#include <stdbool.h>
#include "./TADS/Paciente.h"
#include "./TADS/Registro.h"
#include "./TADS/Pilha.h"
#include "./TADS/Fila.h"
#include "./TADS/Lista.h"

bool RegistrarPaciente(Lista *registros, Fila *fila_de_espera, int id, char nome[50])
{
    //verificar se id e unico
    if(buscarPaciente(id, registros)!= NULL){
        printf("\n!!!!ID JA EXISTE!!!!\n");
        return false;
    }
  
    //adicionar paciente na lista
    Paciente *paciente = pacienteCriar(id, nome);
    Pilha *historico = pilhaCriar();
    
    //criar dois registros independentes
    Registro *registro_lista = criarRegistro(paciente, historico);
    Registro *registro_fila = criarRegistro(paciente, historico);

    //inserir os registros na lista e na fila
    inserirPaciente(registro_lista, registros);
    enfileirar(fila_de_espera, registro_fila);

    printf("\n PACIENTE INSERIDO NA FILA DE ESPERA E NOS REGISTROS! \n");
    return true;
}

int main()
{   

    int c;
    Fila *fila_de_espera = filaCriar();
    Lista *registros = criarLista();

    printf("Ola, Bem vindo ao sistema de gerenciamento de saude!!\n");


    do{
        printf(
            "\nOpcoes:\n"
            "================\n"
            "1. Registrar paciente\n"
            "2. Dar alta ao paciente\n"
            "3. Adicionar procedimento ao histórico médico\n"
            "4. Desfazer procedimento do histórico médico\n"
            "5. Chamar paciente para atendimento\n"
            "6. Mostrar fila de espera\n"
            "7. Mostrar histórico do paciente\n"
            "8. Sair\n"
        );
        scanf("%d",&c);
        switch(c){
            //REGISTRAR PACIENTE
            case 1: {

                printf(
                    "REGISTRO DE PACIENTE!\n"
                    "====================\n"
                );
                //entradas

                printf("Entre com o id do paciente: ");
                int id;scanf(" %d",&id);

                printf("Entre com o nome do paciente: ");
                char nome[50];scanf(" %199[^\n]",nome);
                
                RegistrarPaciente(registros, fila_de_espera, id, nome);

                break;
            }

            //DAR ALTA AO PACIENTE
            case 2: {

                break;
            }
            
            //ADICIONAR PROCEDIMENTO AO HISTORICO MEDICO
            case 3: {
                //entradas
                int id;scanf(" %d",&id);
                
                //Busca registro pelo id do paciente
                Registro *busca = buscarRegistro(id,registros);
                if(busca==NULL)
                {
                    //paciente não existe
                    break;
                }
                //Adiciona procedimento
                char procedimento[MAX];scanf(" %99[^\n]",procedimento);
                empilhar(busca->historico, procedimento);

                break;
            }

            //DESFAZER PROCEDIMENTO DO HISTORICO MEDICO
            case 4: {
                //entradas
                int id;scanf(" %d",&id);
                
                //Busca registro pelo id do paciente
                Registro *busca = buscarRegistro(id,registros);
                if(busca==NULL)
                {
                    //paciente não existe
                    break;
                }

                busca->historico;
                //remove procedimento
                desempilhar(busca->historico);

                break;
            }

            //CHAMAR PACIENTE PARA ATENDIMENTO
            case 5: {

                break;
            }

            //MOSTRAR FILA DE ESPERA
            case 6: {
            
                break;
            }

            //MOSTRAR HISTORICO DO PACIENTE
            case 7: {

                break;
            }

            default: {

            break;
            }
        }
    }while(c!=8);

    listarPacientes(registros);
    return 0;
}