#include "Tipo.hpp"
#include <vector>

class MemoriaContigua {

private:

    std::vector<BlocoMemoria> particoes;
    
    unsigned int algoritmo;
    bool configurouMemoria = false;
    pid_t contador_pids = 0;

public:
    
    MemoriaContigua();
    ~MemoriaContigua();

    pid_t CriaProcesso();
    bool AlocaProcesso();

};




