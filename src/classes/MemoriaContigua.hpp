
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

public:
    
    MemoriaContigua();
    ~MemoriaContigua();

    pid_t CriaProcesso();
    bool AlocaProcesso();
    void SimuladorMemoriaContigua();
    int PrintMenu();
    void ConfiguraMemoria();

};



#endif
