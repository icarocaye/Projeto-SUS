# Projeto SUS
O projeto faz parte da disciplina de Algoritmos e Estruturas de Dados I, e consiste na elaboração de um sistema simples de atendimento médico por meio de tipos abstratos de dados (TADs).

## Funcionalidades do Sistema
O sistema consiste em dois armazenamentos principais: uma Lista com todos os pacientes que deram entrada no hospital e um Fila com os pacientes que entraram e ainda não foram atendidos. Para implementar essas estruturas, construímos um TAD de registro, que pode representar tanto um item da Lista quanto um item da Fila. Esse registro, por sua vez, aponta para o TAD Paciente (composto por id único e nome) e para o seu histórico de procedimentos, implementado como uma Pilha de strings e que pode ser manipulado. Mais informações sobre os TADs e suas implementações estão contidas em [Tipos Abstrados de Dados](TADS/README.md).  

Além disso, o sistema conta com as seguintes funcionalidades, que são acessíveis por meio do menu de main.c e ordenadas pelos mesmos índices deste documento:  

1. Registrar um novo paciente  
    - Entradas: id único e nome.  
    - Resultado: cria um novo paciente e insere ele, num registro, na Fila e, em outro registro, na Lista.  
  
2. Dar alta ao paciente;  
    /O que significa dar alta ao paciente? Adicionar descrição/
   
3. Adicionar procedimento ao histórico médico;
    - Entradas: id do paciente que receberá o procedimento e o procedimento.  
    - Resultado: insere o procedimento no topo do histórico médico (uma pilha) se ele não estiver cheio.  

4. Desfazer procedimento do histórico médico;  
    - Entrada: id do paciente que terá o último procedimento removido.  
    - Resultado: remove o procedimento mais recente do histórico, contido no topo da pilha.  

5. Chamar paciente para atendimento;
    - Adicionar descrição

6. Mostrar fila de espera;
    - Entrada: nenhuma.
    - Resultado: imprime na tela o nome e o id de cada paciente presente na fila atual, segundo a sua ordem.

7. Mostrar histórico do paciente;
    - Entrada: id do paciente em questão.
    - Resultado: imprime na tela todos os procedimentos contidos no histórico, (decidir de vai ser do mais antigo pro mais recente ou do mais recente pro mais antigo!!!).

8. Sair do menu;
