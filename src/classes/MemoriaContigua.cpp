#include <iostream>
#include "MemoriaContigua.hpp"
#include <string>

using namespace std;

// Apenas printa o menu e retorna a opção selecionada. Limpa a função principal do simulador

int MemoriaContigua::PrintMenu()
{

    cout << "== Menu Principal - Alocação Contígua ==" << endl;
    cout << "\t 1. Definir Parâmetros da Memória" << endl;
    cout << "\t 2. Adicionar Processos" << endl;
    cout << "\t 3. Remover Processos" << endl;
    cout << "\t 4. Exibir Memória" << endl;
    cout << "\t 5. Resetar" << endl;
    cout << "\t 0. Sair" << endl;
    cout << "Escolha uma opção: ";
    cin >> opcao;

    return opcao;
}

/*
    void MemoriaContigua::ConfiguraMemoria(): Função que realiza a configuração inicial do espaço de memória simulado.
*/

void MemoriaContigua::ConfiguraMemoria()
{

    if (configurouMemoria)
    {
        cout << "Os parâmetros de memória já foram definidos. Não é mais possível redefini-los" << endl;
        return;
    }

    while (1)
    {

        cout << "Tamanho Total da Memória: 1024KB" << endl;
        cout << "Informe o Algoritmo de alocação (1-FF, 2-BF, 3-WF, 4-CF): ";
        cin >> algoritmo;

        if (algoritmo < 1 || algoritmo > 4)
        {
            cout << "Opção inválida! Selecione um número entre 1 e 4!" << endl;
            continue;
        }
        else
        {

            // Inicializa a memória como um bloco único de 1024KB

            particoes.clear(); // Limpa o vector
            contador_pids = 0; // Seta o contador de PIDs como 0

            // Criação do bloco inicial de 1024KB

            BlocoMemoria bloco;

            bloco.base = 0;
            bloco.tamanho = TAMANHO_TOTAL_MEMORIA;
            bloco.livre = true;
            bloco.PID = BLOCO_LIVRE;
            particoes.push_back(bloco);

            configurouMemoria = true;

            cout << "Memória configurada com 1024KB e algoritmo de alocação " << algoritmo << "." << endl;

            break;
        }
    }
}

pid_t MemoriaContigua::CriaProcesso()
{

    if (!configurouMemoria)
    {

        cout << "Operação inválida. Não é possível criar um processo antes de definir os parâmetros de memória." << endl;
        return -1;
    }

    Processo NovoProcesso;

    cout << "Informe o apelido do processo: ";
    cin >> NovoProcesso.nome;

    cout << "Informe o tamanho do processo (KB): ";
    cin >> NovoProcesso.tamanho;

    if (NovoProcesso.tamanho <= 0 || NovoProcesso.tamanho > TAMANHO_TOTAL_MEMORIA)
    { // Permite apenas valores entre 1KB e 1024KB
        cout << "Tamanho inválido para o processo. Por favor, tente novamente." << endl;
        return -1;
    }

    NovoProcesso.alocado = false; // Deverá ser alocado posteriormente. Não cabe a essa função fazer isso.
    NovoProcesso.base = 0;
    NovoProcesso.limite = 0;
    NovoProcesso.PID = ++contador_pids;

    processos.push_back(NovoProcesso); // Adiciona o novo processo ao vector de processos. Poderá ser utilizado como uma "fila" de processos não alocados posteriormente

    cout << "Processo PID: " << NovoProcesso.PID << " ocupando " << NovoProcesso.tamanho << " KB criado com sucesso." << endl;
    cout << "Processo PID: " << NovoProcesso.PID << " ainda não alocado." << endl;

    return NovoProcesso.PID;
}

/*
    void MemoriaContigua::SimuladorMemoriaContigua(); -> Função principal do simulador. Será responsável por fazer a interface com o usuário e chamar outras
    funções para efetuar as solicitações necessárias.
*/
void MemoriaContigua::SimuladorMemoriaContigua()
{

    while (1)
    {

        PrintMenu();

        switch (opcao)
        {

        case 1:

            // Chamar função de definição de parâmetros de memória

        case 2:

            // Chamar função que cria um processo
            // logo depois chamar a função que mostra o estado da memória intrinsicamente (sugestao do professor)
        case 3:

            // Chamar função que remove um processo

        case 4:

            // Chamar função que exibe o estado atual da memória

        case 5:

            // Chamar função que reseta o simulador de memória contígua

        case 0:

            // Break. Sai do laço e mostra as estatísticas finais

        default:

            // Avisar operação inválida e continue

            cout << "Operação inválida!" << endl;
            continue;
        }
    }
}
