/*
Este arquivo define a classe 'MemoriaContigua', responsável por simular um 
sistema de gerenciamento de memória contígua para processos em um ambiente 
de sistema operacional.

A classe permite:
- Criar processos e armazená-los em um vetor de processos
- Alocar processos em memória usando diferentes algoritmos:
    * First Fit
    * Best Fit
    * Worst Fit
    * Circular Fit
- Remover processos da memória.
- Exibir o estado atual da memória e das partições
- Configurar parâmetros iniciais da memória e ordenar os blocos
- Simular interativamente o gerenciamento de memória contígua via menu

Estrutura interna:

- particoes: vetor que representa os blocos de memória, livres ou ocupados
- processos: vetor de processos criados
- algoritmo: define qual algoritmo de alocação será utilizado
- configurouMemoria: flag que indica se a memória já foi configurada
- contador_pids: contador para gerar PIDs únicos para cada processo

Funções principais:

- CriaProcesso()           : Cria um processo e adiciona ao vetor de processos
- AlocaProcesso(pid_t pid) : Tenta alocar um processo em memória
- RemoveProcesso(pid_t pid): Remove um processo da memória
- ExibeMemoria()           : Mostra o estado atual da memória e partições
- SimuladorMemoriaContigua(): Loop principal para interação do usuário
- ConfiguraMemoria()       : Configura os parâmetros iniciais da memória
- PrintMenu()              : Exibe o menu de operações
- OrdenaVectorMemoria()    : Ordena os blocos de memória por endereço base
*/

#ifndef MEMORIA_CONTIGUA_HPP
#define MEMORIA_CONTIGUA_HPP

#include "Tipo.hpp"
#include <vector>
#include <unordered_map>

class MemoriaContigua {

private:

    std::vector<BlocoMemoria> particoes;
    std::vector<Processo> processos;

    unsigned int algoritmo;
    bool configurouMemoria = false;
    pid_t contador_pids = 0;
    int opcao;
    int FirstFit(size_t tamanho);
    int BestFit(size_t tamanho);
    int WorstFit(size_t tamanho);
    int CircularFit(size_t tamanho);

public:
    
    //MemoriaContigua();
   // ~MemoriaContigua();


    pid_t CriaProcesso();
    bool AlocaProcesso(pid_t pid);
    int EncontraProcesso(pid_t pid);
    void InsereOcupadoELivre(size_t indiceOcupado, const BlocoMemoria& livre); // Os índices de vector são do tipo size_t
    void SimuladorMemoriaContigua();
    int PrintMenu();
    void ConfiguraMemoria();
    void OrdenaVectorMemoria();
    void ExibeMemoria();
    void RemoveProcesso(pid_t pid);
    float CalculaFragmentacaoExterna();
    void ExibeProcessos();

};



#endif
