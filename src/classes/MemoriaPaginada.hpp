#ifndef MEMORIA_PAGINADA_HPP
#define MEMORIA_PAGINADA_HPP

/*
    Este arquivo contém a definição da classe MemoriaPaginada, que implementa
    um simulador de memória paginada
    Também contém a lasse base Memoria, que armazena funções e atributos comuns entre os simuladores de memória 
    (como criação de processos, busca de processos e por fim reset da memória)

    Funcionalidades principais:
    - Configurar a memória total e o tamanho dos frames
    - Criar processos com nome e tamanho específico
    - Alocar processos dividindo-os em páginas (frames) na memória físic
    - Remover processos liberando os frames ocupados
    - Exibir o estado da memória física e as tabelas de páginas dos processos
    - Simulador interativo via terminal

    Observação: Essa implementação reaproveita funções da memória contígua,
    como CriaProcesso() e EncontraProcesso(), para evitar duplicação de código
    e para facilitar a implementação
*/


#include "Tipo.hpp"
#include <vector> // ira armazenar as listas de processos, frames e páginas
#include <unordered_map> //mapeia o PID de processos às suas páginas
#include <iostream> 
#include <string> //nome dos processos

// Classe base para funções comuns entre contígua e paginada
class Memoria {
protected:
    std::vector<Processo> processos;   // Lista de processos
    pid_t contador_pids = 0;           // Contador de PIDs
    int opcao;                         // Opção do menu
    bool configurouMemoria = false;    // Flag se a memória foi configurada passando como 0

public:
    virtual void Simulador() = 0;      // Função pura virtual para cada simulador

    // Funções comuns (uso mutuo entre os tipos de alocação se for preciso)
    int PrintMenu();
    pid_t CriaProcesso();
    int EncontraProcesso(pid_t pid);
    void ResetarMemoria();
};

// Classe específica para memória paginada
class MemoriaPaginada : public Memoria {
private:
    unsigned int tamanho_total_memoria;          // Tamanho total da memória em KB
    unsigned int tamanho_frame;                  // Tamanho de cada frame em KB
    unsigned int num_frames;                     // Número de frames disponíveis
    std::vector<int> memoria_fisica;            // Vetor representando frames (-1 livre, PID ocupado)
    std::unordered_map<pid_t, std::vector<int>> tabelas_paginas; // Tabela de páginas de cada processo

public:
    double CalculaFragmentacaoInterna();
    MemoriaPaginada();
    ~MemoriaPaginada();

    void ConfiguraMemoria();                   // Define tamanho total e tamanho do frame
    bool AlocaProcesso(pid_t pid);             // Aloca processo dividindo em páginas
    void RemoveProcesso(pid_t pid);            // Remove processo e libera frames
    void ExibeMemoria();                        // Exibe tabela de páginas e o estado da memória
    void Simulador() override;                  // Simulador principal da memória paginada
};

#endif