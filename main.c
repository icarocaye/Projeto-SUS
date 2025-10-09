#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./TADS/Pilha.h"
#include "./TADS/Fila.h"
#include "./TADS/Lista.h"
#include "./TADS/Saveload.h"


int main()
{   

    int c;
    Fila *fila_de_espera = filaCriar();
    Lista *registros = criarLista();

    //INSERIR LEITURA DE ARQUIVO COM FUNÇÕES DE SAVELOAD.H AQUI
    

    printf("Olá, Bem-vindo ao sistema de gerenciamento de saúde!!\n");
    
   
    do{
        //variaveis que serao utilizadas nos casos abaixo
        int id; //id paciente
        char nome[NOME_MAX]; //nome paciente
        char procedimento[MAX]; //procedimento historico
        Paciente *paciente; // variavel para armazenar paciente;
        Registro *busca; //variavel para armazenar registro;
        char prosseguir; 


        printf(
            "\nMENU:\n"
            "=============================================\n"
            "1. Registrar paciente\n"
            "2. Registrar óbito de paciente\n"
            "3. Adicionar procedimento ao histórico médico\n"
            "4. Desfazer procedimento do histórico médico\n"
            "5. Chamar paciente para atendimento\n"
            "6. Mostrar fila de espera\n"
            "7. Mostrar histórico do paciente\n"
            "8. Mostrar lista de pacientes\n"
            "9. Sair\n"
            "=============================================\n"
        );
        scanf("%d",&c);

        switch(c){

          
            //REGISTRAR PACIENTE
            case 1:

                printf(
                    "====================\n"
                    "REGISTRO DE PACIENTE!\n"
                    "====================\n"
                );
                //entradas

                printf("Entre com o id do paciente: ");
                scanf(" %d",&id);

                //verificar se id e unico
                if(buscarPaciente(id, registros)!= NULL){
                    printf("\n!!!!ID JA EXISTE!!!!\n");
                    break;
                }

                printf("Entre com o nome do paciente: ");
                scanf(" %120[^\n]",nome);

              
                //adicionar paciente na lista
                Paciente *novo_paciente = pacienteCriar(nome, id);
                Pilha *historico = pilhaCriar();
                
                Registro *registro_lista = RegistroCriar(novo_paciente, historico);
                listaInserir(registro_lista, registros);

                //adicionar paciente na fila de espera
                Registro *registro_fila = RegistroCriar(novo_paciente, historico);
                enfileirar(fila_de_espera, registro_fila);

                printf("\n PACIENTE INSERIDO NA FILA DE ESPERA E NOS REGISTROS! \n");

            break;

            //DAR ALTA AO PACIENTE
            case 2: 
                
                printf("Entre com o id do paciente que deseja declarar óbito: ");
                scanf(" %d", &id);

                //verificar se paciente está na lista
                paciente = buscarPaciente(id,registros);
                if(paciente == NULL)
                {
                    printf("\n\n !!! PACIENTE NÃO ENCONTRADO !!! \n\n");
                    break;
                }
                
                //verificar se paciente esta na fila 
                if (filaBuscar(fila_de_espera, id) != NULL)
                {
                    printf("ERRO: Impossível remover paciente, pois ele ainda não foi atendido!");
                    break;
                }

                printf("Remover paciente (ID = %d) -> %s (S/N)\n", paciente->id, paciente->nome);
                do {
                    scanf(" %c", &prosseguir);
                } while(prosseguir != 'N' && prosseguir != 'n' && prosseguir != 'S' && prosseguir != 's' );

                listaRemover(id,registros);

                printf("\n\n --- PACIENTE REMOVIDO DOS REGISTROS --- \n\n");

            break;

            //ADICIONAR PROCEDIMENTO AO HISTORICO MEDICO
            case 3:
            //entradas
                printf("Entre com o id do paciente: ");
                scanf(" %d",&id);
                
                //Busca registro pelo id do paciente
                busca = buscarRegistro(id,registros);
                if(busca == NULL)
                {
                    printf("\n\n !!! PACIENTE NÃO EXISTE !!! \n\n");
                    break;
                }
                
                paciente = busca->paciente;
                printf("Paciente (id = %d) --> %s encontrado, entre com o procedimento\n a ser adicionado no histórico\n(MÁXIMO DE 100 CARACTÉRES)\n: "
                ,paciente->id, paciente->nome);
                //Adiciona procedimento
                scanf(" %101[^\n]",procedimento);

                //se fila estiver cheia empilhar não empilha
                empilhar(busca->historico,procedimento);

                printf("ADICIONADO AO HISTÓRICO");

            break;

            //DESFAZER PROCEDIMENTO DO HISTORICO MEDICO
            case 4: 
                printf("O último procedimento do histórico do paciente será removido\n ");
               
                //entradas
                printf("Entre com o id do paciente: ");
                scanf(" %d", &id);
                
                //Busca registro pelo id do paciente
                busca = buscarRegistro(id,registros);

                if(busca == NULL)
                {
                    printf("\n\n !!! PACIENTE NÃO EXISTE !!! \n\n");
                    break;
                }

                if(pilhaVazia(busca->historico))
                {
                    printf("\n !!! HISTÓRICO VAZIO !!!\n");
                    break;
                }
                
                paciente = busca->paciente;
                printf("Paciente (id=%d) --> %s encontrado. Tem certeza que deseja remover o último procedimento do histórico?\n ",
                paciente->id, paciente->nome);
                printf("\nÚltimo procedimento: ( %s ) [S/N]\n ",busca->historico->procedimentos[busca->historico->tamanho - 1]);
             
                 
                do {
                    scanf(" %c", &prosseguir);
                } while(prosseguir != 'N' && prosseguir != 'n' && prosseguir != 'S' && prosseguir != 's' );

                if(prosseguir == 'S' || prosseguir == 's') {
                    if (desempilhar(busca->historico))
                        printf("\nREMOVIDO DO HISTÓRICO DO PACIENTE\n");
                    else
                        printf("Histórico vazio!\n"); 
                } 
            
               
            break;

            //CHAMAR PACIENTE PARA ATENDIMENTO
            case 5:

                if(filaVazia(fila_de_espera)){
                    printf("\n\n !!! FILA DE ESPERA VAZIA !!! \n\n");
                    break;
                }
                paciente = fila_inicio(fila_de_espera)->paciente;
                printf("Chamar Paciente: (ID= %d) -> %s para atendimento ? (S/N) \n ",paciente->id,paciente->nome);

                do{
                    scanf(" %c", &prosseguir);
                }while(prosseguir != 'N' && prosseguir != 'n' && prosseguir != 'S' && prosseguir != 's' );

                desenfileirar(fila_de_espera);  
                
            break;

            //MOSTRAR FILA DE ESPERA
            case 6: 

                printf("\n\n--- FILA DE ESPERA ---\n");
                mostrar_fila(fila_de_espera);
                printf("\n\n");
            break;
            //MOSTRAR HISTORICO DO PACIENTE

            case 7:
                printf("Entre com o id do paciente que deseja consultar o histórico: ");
                scanf(" %d",&id);

                busca = buscarRegistro(id,registros);
                if(busca == NULL)
                {
                    printf("\n\n !!! PACIENTE NÃO EXISTE !!! \n\n");
                    break;
                }
                if(pilhaVazia(busca->historico))
                {
                    printf("\n !!! HISTÓRICO VAZIO !!!\n");
                    break;
                }
                printf("\nHISTÓRICO (ID=%d) -- %s\n\n", busca->paciente->id, busca->paciente->nome);

                for(int i = 0; i<busca->historico->tamanho; i++)
                {
                    char *procedimento = busca->historico->procedimentos[i];
                    printf("%d -> %s \n", i+1, procedimento);
                }
                printf("\n");

            break;

            //MOSTRAR LISTA
            case 8:
                listarPacientes(registros);
            default:

            break;
        }
    } while(c!=9);

    listarPacientes(registros);

    //INSERIR GRAVAÇÃO EM ARQUIVO COM FUNÇÕES DE SAVELOAD.H AQUI
    
    filaApagar(fila_de_espera);
    apagarLista(registros);
    
    printf("Saindo do sistema... Volte sempre!\n");
    return 0;
}