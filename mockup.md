
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

> [!WARNING]
> Após o usuário definir os parâmetros de memória, esses parâmetros NÃO PODERÃO MAIS SER ALTERADOS.

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

## 2.1. Fluxo de interação do Usuário no modo Paginação
Caso o usuário selecione a opção 2 (Paginação), o simulador apresentará o seguinte MENU:

== Menu Principal - Paginação ==
    1. Definir Parâmetros da Memória
    2. Adicionar Processos
    3. Remover Processos
    4. Exibir Tabelas de Páginas
    5. Resetar
    0. Sair

> [!IMPORTANT]
>Na opção 1, o usuário deverá informar:

- O tamanho total da memória (em KB ou MB, conforme definido);
- O tamanho da moldura (frame), que será utilizado para dividir a memória.

> 1  
Informe o tamanho total da memória (KB):  
Informe o tamanho da moldura (KB):  

Esses parâmetros, uma vez definidos, **não poderão mais ser alterados**.

Na opção de adicionar processos, o usuário deverá fornecer:

- Nome do processo;  
- Tamanho do processo (em KB).  

O simulador irá automaticamente dividir o processo em páginas e alocá-las em molduras disponíveis.

> 2  
Nome do processo:  
Tamanho (KB):  

Mensagem de confirmação:  

Processo ${nome_processo} adicionado.  

Na opção de remover processos, o usuário deverá informar o nome do processo, e o simulador liberará as molduras utilizadas.

> 3  
Informe o processo a ser removido:  
O processo ${nome_processo} foi removido.  

---

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

## 3.1. Detalhe da Visualização de Dados - Paginação
Na opção 4 (Exibir Tabelas de Páginas), o simulador exibirá:

- A tabela de páginas de cada processo, indicando quais páginas estão mapeadas em quais molduras;  
- O estado atual da memória física, mostrando o conteúdo de cada moldura.

Exemplo simplificado:

> 4  
Tabela de Páginas - Processo P1  
Página | Moldura  
0      | 2  
1      | 5  
2      | 6  

Memória Física:  
+-----------------------------------------+  
| P1(p0) | LIVRE | P1(p1) | P1(p2) | LIVRE | ... |  
+-----------------------------------------+  

A opção 5 (Resetar) limpará a memória e todas as tabelas de páginas.  

---

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

>[!NOTE]
>Isso inclui também uma região livre entre o início do espaço de endereçamento físico e o primeiro processo alocado (algo que pode vir a acontecer).

---
## 4.1. Métricas de Saída - Paginação
Ao finalizar (0. Sair), serão exibidas estatísticas relacionadas à memória, como:

- Processos alocados e número de páginas de cada um;  
- Porcentagem de memória utilizada;  
- Percentual de fragmentação interna (causada pelo último frame de cada processo não totalmente ocupado).  

Exemplo:  

== Resultado Final - Paginação ==  
Processos alocados: P1 (3 páginas), P2 (5 páginas)  
Uso da memória: 68 / 100 KB (68.0%)  
Fragmentação interna: 4 KB  

## Pilha de Tecnologia Proposta

Como a aplicação será feita no terminal, a ideia é utilizar a poderosa linguagem C++ com suas bibliotecas e contêineres refinados para estruturas de dados necessárias durante o desenvolvimento do projeto. Além de oferecer interessantíssimas abstrações provenientes da Orientação a Objetos e a possibilidade de utilizar bibliotecas do bom e velho C. Caso os integrantes da dupla possuam tempo hábil (o que é pouco provável), pode ser pensado em algo utilizando o QT Creator, mas é pouco provável.

