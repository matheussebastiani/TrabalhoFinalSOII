
# Mockup Trabalho Final Sistemas Operacionais II

## 1. Esboço da Interface principal:

* O Simulador será pensado para que seja utilizado em um Terminal, com alguns comandos que o usuário terá a disposição e deverá inserí-los em seus menus.
* O Simulador será desenvolvido em um ambiente Linux, portanto, algumas estratégias e pensamentos serão considerando um ambiente Linux de execução.

Para excutar o simulador, o usuário terá à disposição:

* O código-fonte com o arquivo Makefile para gerar o arquivo compilado a partir de seu ambiente (considerando que o usuário tenha o compilador gcc/g++);
* O arquivo já compilado para Linux de 64 bits (`x86_64`);
* ~~ O arquivo já compilado para Windows de 64 bits (`x86_64`) ~~.

Para executar o simulador, o usuário deverá digitar o seguinte:

    $ ./simulador

A partir daí, o usuário poderá selecionar qual opção deseja entre as opções disponíveis no menu do programa.

Os dados serão exibidos para o usuário no Terminal quando o mesmo puder e quiser solicitar os dados de estatística.

---

## 2. Fluxo de Interação do Usuário no Modo Alocação Contígua

A ideia inicial, para o simulador, é que logo após o usuário executar o comando:

    $ ./simulador

O simulador passe a executar, apresentando um menu inicial como:

    === Simulador de Gerência de Memória ===
    Escolha o modo de simulação:
        1. Alocação Contígua
        2. Paginação

Para que o usuário selecione o modo de Gerência de Memória que será utilizado. Caso o usuário digite 1, será selecionado o modo `Alocalção Conígua`, e 2 para `Paginação`.

Ao selecionar o Modo 1, o usuário terá as seguintes opções:

    == Menu Principal - Alocação Contígua ==
        1. Definir Parâmetros da Memória
        2. Adicionar Processos
        3. Remover Processos
        4. Exibir Memória
        5. Resetar
        0. Sair

Selecionando a opção 1, o usuário deverá informar:
* Qual o tamanho total da memória (em KB, MB, a ser definido);
* O Algoritmo a ser utilizado (_Worst Fit_, _Best Fit_, _First Fit_ ou _Circular Fit_).

Em uma tela como:

    > 1
    Informe o tamanho total da memória (KB):
    Informe o Algoritmo de alocação (1-FF, 2-BF, 3-WF, 4-CF): 

> Após o usuário definir os parâmetros de memória, esses parâmetros *NÃO PODERÃO MAIS SER ALTERADOS.*

Na opção de adicionar processos, o usuário deverá definir:
* Um nome para o processo a ser criado;
* O quanto o processo ocupará de memória (na mesma unidade do tamanho da memória).

A tela será algo como:
    
    > 2
    Nome do processo:
    Tamanho (KB):

Ao final, uma mensagem confirmando a ação aparecerá, como

> Processo ${nome_processo} adicionado.

O Usuário poderá criar quantos processos desejar, o que implicará diretamente na alocação de memória entre os processos.

Na opção `Remover processos`, o usuário deverá informar o nome do processo a ser removido, como:

    >3
    Informe o processo a ser removido:

Após informar o nome do processo, o programa retornará:

> O processo ${nome_processo} foi removido.

## 3. Detalhe da Visualização de Dados - Alocação Contígua

A opção `4. Exibir Memória`, exibirá o estado atual da memória física, em blocos, ilustrando qual processo está alocado para o respectivo bloco. Supondo que exista um processo P1 na memória ocupando um espaço `x`. Algo como o ilustrado em seguida deverá aparecer:

    > 4
    Memória:
    +-----------------------------------------+
    | P1 | P1 | P1 | P1 | LIVRE | LIVRE | ... |
    +-----------------------------------------+

A opção `5. Resetar` limpará o conteúdo da memória e excluirá todos os processos correntes. Retornando uma mensagem como:

> A memória foi resetada.


O usuário poderá acompanhar como os processos serão alocados e removidos, além de poder visualizar o estado da memória durante a execução dos processos criados.

## 4. Métricas de saída

Ao final da execução, (`0. Sair`), serão exibidas as informações relativas à memória no momento de término da execução.

As informações exibidas serão:
* Processos alocados;
* Porcentagem de memória utilizada;
* Percentual de fragmentação externa.

Como:

    == Resultado Final - Alocação Contígua Dinâmica ==
    Processos alocados: P1, P2, P3 (exemplo)
    Uso da memória: 50 / 100 KB (50.0%)
    Fragmentação externa: 0%

A ideia do cálculo da fragmentação externa é a seguinte:

    Fragmentação = Quantidade em bytes de regiões livres entre processos / Total da memória

Isso inclui também uma região livre entre o início do espaço de endereçamento físico e o primeiro processo alocado (algo que pode vir a acontecer).

---

## Pilha de Tecnologia Proposta

Como a aplicação será feita no terminal, a ideia é utilizar a poderosa linguagem C++ com suas bibliotecas e contêineres refinados para estruturas de dados necessárias durante o desenvolvimento do projeto. Além de oferecer interessantíssimas abstrações provenientes da Orientação a Objetos e a possibilidade de utilizar bibliotecas do bom e velho C. Caso os integrantes da dupla possuam tempo hábil (o que é pouco provável), pode ser pensado em algo utilizando o QT Creator, mas é pouco provável.
