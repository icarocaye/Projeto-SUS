#include <stdio.h>
#include <stdbool.h>
#include "./TADS/Pilha.h"
#include "./TADS/Fila.h"
#include "./TADS/Lista.h"



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
            case 1:

                printf(
                    "REGISTRO DE PACIENTE!\n"
                    "====================\n"
                );
                //entradas

                printf("Entre com o id do paciente: ");
                int id;scanf("%d",&id);

                //verificar se id e unico
                if(buscarPaciente(id, registros)!= NULL){
                    printf("\n!!!!ID JA EXISTE!!!!\n");
                    break;
                }

                printf("Entre com o nome do paciente: ");
                char nome[200];scanf("%s",nome);

                
               
                //adicionar paciente na lista
                Paciente *paciente = pacienteCriar(nome, id);
                Pilha *historico = pilhaCriar();
                
                Registro *registro_paciente = criarRegistro(paciente, historico);
                inserirPaciente(registro_paciente, registros);

                //adicionar paciente na fila de espera
                enfileirar(fila_de_espera, registro_paciente);

                printf("\n PACIENTE INSERIDO NA FILA DE ESPERA E NOS REGISTROS! \n");

            break;
            //DAR ALTA AO PACIENTE
            case 2: 

            break;
            //ADICIONAR PROCEDIMENTO AO HISTORICO MEDICO
            case 3:

            break;
            //DESFAZER PROCEDIMENTO DO HISTORICO MEDICO
            case 4:

            break;
            //CHAMAR PACIENTE PARA ATENDIMENTO
            case 5:

            break;
            //MOSTRAR FILA DE ESPERA
            case 6: 
            
            break;
            //MOSTRAR HISTORICO DO PACIENTE
            case 7:

            break;
            default:

            break;
        }
    }while(c!=8);

    listarPacientes(registros);
    return 0;
}