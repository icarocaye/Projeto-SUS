# Projeto SUS
O projeto faz parte da disciplina de Algoritmos e Estruturas de Dados I, e consiste na elaboração de um sistema simples de atendimento médico por meio de tipos abstratos de dados (TADs).

## Funcionalidades do Sistema
O sistema consiste em dois armazenamentos principais: uma Lista com todos os pacientes que deram entrada no hospital e um Fila com os pacientes que entraram e ainda não foram atendidos. Para implementar essas estruturas, construímos um TAD de registro, que pode representar tanto um item da Lista quanto um item da Fila. Esse registro, por sua vez, aponta para o TAD Paciente (composto por id único e nome) e para o seu histórico de procedimentos, implementado como uma Pilha de strings e que pode ser manipulado. Mais informações sobre os TADs e suas implementações estão contidas em [Tipos Abstrados de Dados](TADS/README.md).  

Além disso, o sistema conta com as seguintes funcionalidades, que são acessíveis pelo próprio terminal, definidas em [main.c](main.c) e ordenadas pelos mesmos índices deste documento:  

1. Registrar um novo paciente  
    - Entradas: id único e nome.  
    - Resultado: se não houver outro paciente com esse id, cria um novo paciente e insere ele, num registro, na Fila e, em outro registro, na Lista.  
  
2. Registrar óbito de paciente   
    - Entrada: id do paciente a ser removido.
    - Resultado: remove o paciente da Lista de registros. Se o paciente ainda estiver na fila, não é possível fazer isso, pois seria necessário violar a ordem da fila caso ele esteja no meio dela.
   
3. Adicionar procedimento ao histórico médico  
    - Entradas: id do paciente que receberá o procedimento e o procedimento.  
    - Resultado: insere o procedimento no topo do histórico médico (uma pilha) se ele não estiver cheio.  

4. Desfazer procedimento do histórico médico  
    - Entrada: id do paciente que terá o último procedimento removido.  
    - Resultado: remove o procedimento mais recente do histórico, contido no topo da pilha.  

5. Chamar paciente para atendimento  
    - Entrada: nenhuma.
    - Resultado: chama o primeiro paciente da fila de espera para atendimento, efetivamente removendo-o da Fila.

6. Mostrar fila de espera  
    - Entrada: nenhuma.
    - Resultado: imprime na tela o nome e o id de cada paciente presente na fila atual, segundo a sua ordem.

7. Mostrar histórico do paciente  
    - Entrada: id do paciente em questão.
    - Resultado: imprime na tela todos os procedimentos contidos no histórico, do mais antigo para o mais recente.

8. Mostrar lista de pacientes  
    - Entrada: nenhuma.
    - Resultado: imprime na tela a lista de todos os pacientes não falecidos que já deram entrada no sistema.

9. Sair do menu  

Os requisitos do projeto e descrição mais detalhada das ações podem ser encontrados no [PDF de definição do projeto](proj1VersaoAtualizada.pdf)  

## Como rodar
Abaixo seguem as instruções de como compilar e executar o código do projeto:  
