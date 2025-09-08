#include <iostream>
#include "MemoriaContigua.hpp"
#include <string>
#include <algorithm> // std::sort -> será necessário para manter o vector ordenado

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

/*
    void OrdenaVectorMemoria(); -> Para que a representação da memória seja exibida e alocada de maneira correta dentro do vector particoes,
    é fundamental que o vector esteja ordenado por BlocoMemoria.base. Essa função utilizará o std::sort para ordenar o vector, juntamente com uma função
    lambda que "especializará" o std::sort na operação desejada
*/

void MemoriaContigua::OrdenaVectorMemoria(){

    if(particoes.empty()){
        cout << "Não foi possível ordenar o vector. O vector particoes está vazio." << endl;
    }

    std::sort(particoes.begin(), particoes.end(),
    [](const BlocoMemoria& a, const BlocoMemoria& b){
        return a.base < b.base;
    });

    /*
        Lógica do sort: recebe o início e o final do vector de partições. A função de referência (similar ao qsort do C) recebe duas referencias para BlocosMemoria
        e ordena em ordem CRESCENTE da menor para a maior base. Ou seja, do menor "endereço de memória" para o maior
    */

}

/*
    pid_t MemoriaContigua::CriaProcesso(): Função que tenta criar um processo e o insere em um vector, para posteriormente ser alocado.
*/

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
    int MemoriaContigua::EncontraProcesso(pid_t pid): Percorre o vector de processos para encontrar o processo solicitado.
    Faz uma pesquisa sequencial pelo vector de processos e retorna o índice (fazendo um cast de size_t para inteiro) do vector onde se encontra o processo.
    Caso não encontre, retorna -1
*/

int MemoriaContigua::EncontraProcesso(pid_t pid)
{

    for (size_t i = 0; i < processos.size(); i++)
    {
        if (processos[i].PID == pid)
        {
            return static_cast<int>(i); // Cast de size_t para int (cast do C++ verificado pelo compilador)
        }
    }

    return -1;
}

/*
    void MemoriaContigua::InsereOcupadoELivre(size_t indiceOcupado, const BlocoMemoria& livre) -> Basicamente, após alocar um processo em uma região de memória que estava
    previamente livre, é necessário "atualizar aquele bloco".
    Por exemplo: existe um bloco livre de 100KB e vamos alocar um processo de 80KB.
    É necessário na memória:
        * Inserir o processo de 80KB;
        * Separar o bloco de 20KB que "sobrou"
    Essa função basicamente faz isso no vector. Essa função preserva o ordenamento por base
*/

void MemoriaContigua::InsereOcupadoELivre(size_t indiceOcupado, const BlocoMemoria& livre){

    particoes.insert(particoes.begin() + (indiceOcupado + 1), livre); // Insere o livre na posição seguinte ao ocupado

}


/*
    bool MemoriaContigua::AlocaProcesso(): tenta efetuar a alocação do processo com base no espaço em memória disponível de acordo com o algoritmo selecionado.
*/

bool MemoriaContigua::AlocaProcesso(pid_t pid){

    if(!configurouMemoria){
        cout << "Nencessário configurar a memória antes de alocar um processo." << endl;
        return false;
    }

    int indiceProcessoAlvo = EncontraProcesso(pid);

    if(indiceProcessoAlvo < 0){
        cout << "Processo PID: " << pid << " não encontrado no vector de processos!" << endl;
        return false;
    }

    Processo& ProcessoASerAlocado = processos[static_cast<size_t>(indiceProcessoAlvo)]; //1. Vector trabalha com size_t para enumerar seus índices
                                                                                        //2. ProcessoASerAlocado recebe uma referência, ou seja, se mudar ProcessoASerAlocado, mudo o processos[indice]
    if(ProcessoASerAlocado.alocado){
        cout << "O processo PID: " << ProcessoASerAlocado.PID << " já está alocado." << endl;
        return false;
    }

    if(ProcessoASerAlocado.tamanho <= 0){
        cout << "Processo PID: " << ProcessoASerAlocado.PID << "possui tamanho inválido (" << ProcessoASerAlocado.tamanho << ")." << endl;
        return false;
    }

    // Primeira lógica implementada: First Fit --------------------------> Transformar em função posteriormente o que está entre o incio e o fim
    // INICIO FIRST FIT
    // Lógica FIRST FIT -> Percorre as partições da memória e encontra o PRIMEIRO BLOCO DE MEMÓRIA POSSÍVEL DISPONÍVEL
    // ITERAR DE BLOCO EM BLOCO
    int indiceBloco = -1;

    for(size_t i = 0; i < particoes.size(); i++){ // Vector trabalha com size_t

        BlocoMemoria& Bloco = particoes[i];

        if(Bloco.livre && (Bloco.tamanho >= ProcessoASerAlocado.tamanho)){ // Encontrou o índice de um bloco que satisfaz nossas necessidades no vector
            indiceBloco = static_cast<int>(i);                             // Caso não encontre, indiceBloco permanece -1
            break;
        }

    }

    if(indiceBloco < 0){ // Não encontrou nenhum espaço livre na memória

        cout << "Não foi possível alocar o processo PID: " << ProcessoASerAlocado.PID << ". Não há região contígua na memória >= "
        << ProcessoASerAlocado.tamanho << "KB." << endl;
        return false;
    }

    BlocoMemoria& BlocoSelecionado = particoes[static_cast<size_t>(indiceBloco)]; // Atribui o bloco encontrado para BlocoSelecionado

    /*
        Agora que um bloco de memória que satisfaça nossas necessidades foi escolhido, dois cenários são possíveis:
            1. O Bloco de memória alocado possui tamanho EXATAMENTE IGUAL ao que o processo necessita;
            2. O bloco de memória alocado possui tamanho maior do que o processo necessita.
        
        Na situação 1, apenas marcaremos que aquele bloco agora pertence ao PID do processo alocado para ele;
        Na situação 2, teremos que fazer um "split", ou seja, alocar o que o processo precisa, e inserir, logo em seguida do espaço alocado para o processo,
        no vetor, um bloco de memória com a "quantidade de memória" que sobrou.
    */

    if(ProcessoASerAlocado.tamanho == BlocoSelecionado.tamanho){ // Aqui, o processo recebe o bloco de memória inteiro

        BlocoSelecionado.livre = false; // Alocado
        BlocoSelecionado.PID = ProcessoASerAlocado.PID; // O Bloco pertence àquele processo
        
        ProcessoASerAlocado.base = BlocoSelecionado.base;
        ProcessoASerAlocado.limite = BlocoSelecionado.base + ProcessoASerAlocado.tamanho - 1; // EndLimite = Base(bloco) + tamanho - 1
        ProcessoASerAlocado.alocado = true;

        // Printa e retorna True

    } else if(BlocoSelecionado.tamanho > ProcessoASerAlocado.tamanho){ // Nesse caso, vamos ter que fazer o "split" (situação 2). Então teremos um bloco de memória OCUPADO pelo processo e o restante do bloco Original LIVRE

        BlocoMemoria AreaOcupada;

        AreaOcupada.livre = false;
        AreaOcupada.base  = BlocoSelecionado.base;
        AreaOcupada.tamanho = ProcessoASerAlocado.tamanho;
        AreaOcupada.PID = ProcessoASerAlocado.PID; 

        BlocoMemoria AreaRestante;
        AreaRestante.livre = true;
        AreaRestante.base = AreaOcupada.base + ProcessoASerAlocado.tamanho;
        AreaRestante.PID = BLOCO_LIVRE;
        AreaRestante.tamanho = BlocoSelecionado.tamanho - ProcessoASerAlocado.tamanho;

        // Necessário inserir o bloco Ocupado no lugar do bloco ENCONTRADO no vector e inserir logo após ele a área restante

        particoes[static_cast<size_t>(indiceBloco)] = AreaOcupada; // Substitui o bloco recém encontrado pela área ocupada
        InsereOcupadoELivre(static_cast<size_t>(indiceBloco), AreaRestante);

        ProcessoASerAlocado.base = AreaOcupada.base;
        ProcessoASerAlocado.limite = AreaOcupada.base + ProcessoASerAlocado.tamanho - 1;
        ProcessoASerAlocado.alocado = true;

        // Printa e retorna True
    }

    // FIM FIRST FIT

    //retorna false -> caso impossível. O FLUXO DE EXECUÇÃO NÃO PODE CHEGAR AQUI POR MOTIVO ALGUM

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
