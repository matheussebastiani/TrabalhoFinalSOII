
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
    bool AlocaProcesso(pid_t pid);
    int EncontraProcesso(pid_t pid);
    void InsereOcupadoELivre(size_t indiceOcupado, const BlocoMemoria& livre); // Os índices de vector são do tipo size_t
    void SimuladorMemoriaContigua();
    int PrintMenu();
    void ConfiguraMemoria();
    void OrdenaVectorMemoria();

};



#endif
