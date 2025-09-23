#include <stdio.h>
#include <stdbool.h>
#include "TADs.h"

int main()
{   

    int c;

    do{
        scanf("%d",&c);
        switch(c){
            //REGISTRAR PACIENTE
            case 1:
                char nome[200];
                char id[100];
                
                //criar id unico

                //adicionar paciente na lista

                //adicionar paciente na fila
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

    return 0;
}