/*
    Arquivo contendo tipos de dados que poderão ser comuns a ambos os simuladores, como definição de tipo de bloco de memória e processo.
*/

#include <sys/types.h> // pid_t
#include <string>

typedef struct {
    
    std::string nome;       // Fins didáticos
    pid_t PID; 
    unsigned int base;      // Onde o processo se inicia
    unsigned int limite;    // Onde o processo termina

} Processo;

typedef struct {

    bool livre;
    unsigned int tamanho; // tamanho do bloco em KB. Não vai ser < 0
    pid_t PID;            // Guarda o PID do "Processo" que o alocou
    unsigned int base;    // Início do bloco de memória. Não vai ser < 0

} BlocoMemoria;




