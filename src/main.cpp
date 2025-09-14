/*
Arquivo principal do programa (main.cpp). Este arquivo é responsável por iniciar a execução
do simulador de gerenciamento de memória, permitindo ao usuário escolher entre
dois modos de alocação, além de configurar a memória e processos a serem alocados, os modos de alocação presentes são:

1. Alocação Contígua
2. Paginação

Funcionalidade:

- Solicita ao usuário que escolha o modo de alocação
- Cria o objeto do simulador correspondente ao modo escolhido
- Chama a função-membro do simulador para executar o menu interativo
- Caso o usuário selecione uma opção inválida, exibe mensagem de erro e encerra
  a execução

Classes utilizadas:

- MemoriaContigua  : Simula a alocação de processos em memória contígua,
                     incluindo criação, alocação, remoção de processos e
                     exibição do estado da memória
- MemoriaPaginada  : Simula a alocação de memória utilizando paginação, com
                     gerenciamento de páginas e processos

Estrutura do código:

1. Exibe mensagem inicial com o título do simulador
2. Solicita ao usuário que escolha entre alocação contígua ou paginação
3. Lê a opção do usuário
4. Cria o objeto do simulador correspondente à escolha
5. Chama a função-membro que executa o menu interativo do simulador
6. Caso a opção seja inválida, exibe mensagem de erro e encerra o programa

*/

#include <iostream>
#include "classes/MemoriaContigua.hpp"
#include "classes/MemoriaPaginada.hpp"



int main(){

    int option;

    std::cout << "=== Simulador de Gerência de Memória ===" << std::endl;
    std::cout << "Escolha o modo de alocação:" << std::endl;
    std::cout << "\t1. Alocação Contígua." << std::endl;
    std::cout << "\t2. Paginação." << std::endl;

    std::cout << "Digite sua escolha (1/2): ";
    
    std::cin >> option;

    std::cout << option;

    MemoriaContigua simulador;

    switch(option){

        case 1:{
            // Chama função-membro que realiza a simulação de alocação contígua
            MemoriaContigua simulador;          // Cria objeto do simulador
            simulador.SimuladorMemoriaContigua(); // Chama o menu interno do simulador de alocação contigua
            break;
        }
        case 2:{
            // Chama função-membro que realiza a simulação de paginação
            MemoriaPaginada simuladorPaginada; //Cria o objeto do simulador
            simuladorPaginada.Simulador();   //Chama o menu interno do simulador de paginação
            break;
        }
        default:
            std::cout << "Opção inválida!" << std::endl;  //Caso não caia em nenhum dos cases, retorna que a opção foi inválida
            exit(EXIT_FAILURE);
    }

}



