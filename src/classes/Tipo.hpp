/*
    Arquivo contendo tipos de dados que poderão ser comuns a ambos os simuladores, como definição de tipo de bloco de memória e processo.
*/

#ifndef TIPO_HPP
#define TIPO_HPP
#define TAMANHO_TOTAL_MEMORIA 1024
#define BLOCO_LIVRE -1


#include <sys/types.h> // pid_t
#include <string>

typedef struct {
    
    std::string nome;       // Fins didáticos
    pid_t PID; 
    unsigned int base;      // Onde o processo se inicia
    unsigned int limite;    // Onde o processo termina
    bool alocado;
    unsigned int tamanho;   // Tamanho em KB

} Processo;

typedef struct {

    bool livre;
    unsigned int tamanho; // tamanho do bloco em KB. Não vai ser < 0
    pid_t PID;            // Guarda o PID do "Processo" que o alocou
    unsigned int base;    // Início do bloco de memória. Não vai ser < 0

} BlocoMemoria;


#endif
