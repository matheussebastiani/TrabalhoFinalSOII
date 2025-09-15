/*
    Implementação da classe MemoriaPaginada e da classe base Memoria.

    Funcionalidades implementadas:
    1. Funções comuns da classe base Memoria:
        - PrintMenu(): Exibe opções do menu e retorna a escolha do usuario
        - CriaProcesso(): Cria e armazena um processo com PID único
        - EncontraProcesso(): Busca um processo pelo PID
        - ResetarMemoria(): Limpa a memória e reinicia o contador de PIDs

    2. Funções da classe MemoriaPaginada:
        - ConfiguraMemoria(): Define tamanho total da memória e tamanho dos frames
        - AlocaProcesso(): Aloca um processo na memória física dividindo em páginas
        - RemoveProcesso(): Remove processo liberando os frames ocupados
        - ExibeMemoria(): Mostra o estado da memória e as tabelas de páginas
        - Simulador(): Loop principal interativo com menu para o usuário

    Observação:
    - A memória física é representada como um vetor de inteiros, onde cada
      posição é um frame (-1 livre ou PID do processo alocado)
    - As tabelas de páginas são armazenadas em um unordered_map, mapeando o PID
      para os frames que vao ucpuar
*/

#include "MemoriaPaginada.hpp"
#include <iostream>
#include <limits> //verificar se os valores são validos
#include <cmath> //cálculos matemáticos

using namespace std;


  // Funções comuns da classe base Memoria (INTERAÇÃO COM O USÚARIO)

int Memoria::PrintMenu() {
    cout << "Escolha uma opção: "; //função que cria o início da interação com o usúario
    cin >> opcao;
    return opcao;
}

pid_t Memoria::CriaProcesso() {
    Processo novo;
    cout << "Informe o nome do processo: ";
    cin >> novo.nome;                              //função que vai criar os processos

    cout << "Informe o tamanho do processo (KB): ";
    cin >> novo.tamanho;

    if (novo.tamanho <= 0) {
        cout << "Tamanho inválido!" << endl;
        return -1;
    }

    novo.PID = ++contador_pids;
    novo.alocado = false;
    novo.base = 0;
    novo.limite = 0;

    processos.push_back(novo);

    cout << "Processo " << novo.PID << " criado com sucesso (tamanho: " << novo.tamanho << " KB)." << endl;

    return novo.PID;
}

int Memoria::EncontraProcesso(pid_t pid) {
    for (size_t i = 0; i < processos.size(); i++) { //função que encontra processos
        if (processos[i].PID == pid)
            return static_cast<int>(i);
    }
    return -1;
}

void Memoria::ResetarMemoria() {
    processos.clear();            //função que irá resetar a memória
    contador_pids = 0;
    configurouMemoria = false;
    cout << "Memória resetada." << endl;
}

//MemoriaPaginada

MemoriaPaginada::MemoriaPaginada() : tamanho_total_memoria(0), tamanho_frame(0), num_frames(0) {}

MemoriaPaginada::~MemoriaPaginada() {}

//Configuração da memória 

void MemoriaPaginada::ConfiguraMemoria() {
    if (configurouMemoria) {
        cout << "Memória já configurada!" << endl;
        return;
    }                                                       //configuração da memória feita de acordo com as intenções do usuário

    cout << "Informe o tamanho total da memória (KB): ";
    cin >> tamanho_total_memoria;

    cout << "Informe o tamanho do frame (KB): ";
    cin >> tamanho_frame;

    if (tamanho_total_memoria <= 0 || tamanho_frame <= 0 || tamanho_frame > tamanho_total_memoria) {
        cout << "Valores inválidos!" << endl;
        return;
    }

    num_frames = tamanho_total_memoria / tamanho_frame;
    memoria_fisica.assign(num_frames, -1); // Inicializa todos os frames como livres (-1)
    configurouMemoria = true;

    cout << "Memória configurada com " << num_frames << " frames de " << tamanho_frame << " KB." << endl;
}

//Aloca processo em páginas

bool MemoriaPaginada::AlocaProcesso(pid_t pid) {
    int idx = EncontraProcesso(pid);
    if (idx < 0) {
        cout << "Processo não encontrado!" << endl;
        return false;
    }

    Processo &proc = processos[idx];

    if (proc.alocado) {
        cout << "Processo já alocado!" << endl;
        return false;
    }

    int num_paginas = static_cast<int>(ceil((double)proc.tamanho / tamanho_frame));
    vector<int> paginas_alocadas;

    for (size_t i = 0; i < memoria_fisica.size() && paginas_alocadas.size() < num_paginas; i++) {
        if (memoria_fisica[i] == -1) { // frame livre
            memoria_fisica[i] = proc.PID;
            paginas_alocadas.push_back(static_cast<int>(i));
        }
    }

    if (paginas_alocadas.size() < num_paginas) {
        //se nao houverem frames o bastante, desfaz a alocação e mostra uma mensagem de erro
        for (int f : paginas_alocadas) memoria_fisica[f] = -1;
        cout << "Falha ao alocar o processo " << proc.PID << ": memória insuficiente!" << endl;
        return false;
    }

    tabelas_paginas[proc.PID] = paginas_alocadas;
    proc.alocado = true;

    cout << "Processo " << proc.PID << " alocado com " << num_paginas << " páginas." << endl;
    return true;
}

//Remove processo

void MemoriaPaginada::RemoveProcesso(pid_t pid) {
    int idx = EncontraProcesso(pid);
    if (idx < 0) {
        cout << "O processo não foi encontrado!" << endl;
        return;
    }

    Processo &proc = processos[idx];
    if (!proc.alocado) {
        cout << "O processo não está alocado!" << endl;  //função que vai remover processos alocados e informar caso o processo nao esteja alocado
        return;
    }

    for (int frame : tabelas_paginas[proc.PID]) {
        memoria_fisica[frame] = -1;
    }

    tabelas_paginas.erase(proc.PID);
    proc.alocado = false;

    cout << "Processo " << proc.PID << "  foi removido da memória." << endl;
}

//Exibe o estado da memória

void MemoriaPaginada::ExibeMemoria() {
    cout << "=== Estado da Memória Física ===" << endl;
    for (size_t i = 0; i < memoria_fisica.size(); i++) {
        cout << "Frame " << i << " com o processo: ";
        if (memoria_fisica[i] == -1)
            cout << "LIVRE";
        else
            cout << "PID " << memoria_fisica[i];     //exibe como está a memória no momento
        cout << endl;
    }

    cout << "\n=== Tabelas de Páginas ===" << endl;
    for (auto &entry : tabelas_paginas) {
        cout << "PID do processo: " << entry.first << " Frame: ";
        for (int f : entry.second) cout << f << " ";
        cout << endl;
    }
}
double MemoriaPaginada::CalculaFragmentacaoInterna() {    //função que calcula a fragmentaçao interna (posterioermente irá mostrar ao usuário)
    int desperdicio_total = 0;

    for (auto &proc : processos) {
        if (proc.alocado) {
            int resto = proc.tamanho % tamanho_frame;
            if (resto > 0)
                desperdicio_total += (tamanho_frame - resto);
        }
    }

    return (desperdicio_total * 100.0) / tamanho_total_memoria; // porcentagem
}

//Simulador principal

void MemoriaPaginada::Simulador() {
    while (true) {
        cout << "== Menu Principal - Paginação ==" << endl;       //inicia o simulador de memoria paginada (Interface de Usuário)
        cout << "\t 1. Definir Parâmetros da Memória" << endl;
        cout << "\t 2. Adicionar Processo" << endl;
        cout << "\t 3. Remover Processo" << endl;
        cout << "\t 4. Exibir Tabelas de Páginas" << endl;
        cout << "\t 5. Resetar" << endl;
        cout << "\t 0. Sair" << endl;
        PrintMenu();                                               

        switch (opcao) {
            case 1:
                ConfiguraMemoria();
                break;
            case 2: {
                pid_t pid = CriaProcesso();
                if (pid > 0) AlocaProcesso(pid);
                break;
            }
            case 3: {
                /*
                cout << "Informe o PID do processo a remover: ";
                pid_t pid;
                cin >> pid;
                RemoveProcesso(pid);
                break;
                */
                pid_t pid;
                cout << "Informe o PID do processo a remover: ";
                if (!(cin >> pid)) {                  // Verifica se o input é válido
                    cin.clear();                      // Limpa erro de cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta entrada inválida
                    cout << "Entrada inválida!" << endl;
                } else {
                    // Verifica se o PID existe de fato antes de remover
                    int idx = EncontraProcesso(pid);
                    if (idx < 0) {
                        cout << "O processo PID " << pid << " não foi encontrado!" << endl;
                    } else if (!processos[idx].alocado) {
                        cout << "O processo PID " << pid << " não está alocado!" << endl;
                    } else {
                        RemoveProcesso(pid); // Chama a função para remover
                    }
                }
                break;
            
            }
            case 4:
                ExibeMemoria();    //chama a função que ira exibir a memória no simulador
                cout << "Fragmentação Interna (Paginação): "
                << CalculaFragmentacaoInterna() << "%" << endl;  //exibe a porcentagem de FRAGMENTAÇÃO EXTERNA (paginação)
                break;
            case 5:
                ResetarMemoria();
                memoria_fisica.assign(num_frames, -1);  //chama a função que vai dar um reset na memória
                tabelas_paginas.clear();
                break;
            case 0:
                cout << "Saindo do simulador..." << endl;   //sai do simulador
                return;
            default:
                cout << "Opção inválida!" << endl; //caso não caia em nenhum case retorna que a opção foi inválida
        }
    }
}
/*a funçao do simulador principal é semelhante a da memoria contigua*/