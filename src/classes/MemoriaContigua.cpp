/*
Este arquivo contém a implementação das funções da classe 'MemoriaContigua',
definida no arquivo 'MemoriaContigua.hpp'. Ele simula um gerenciador de 
memória contígua, permitindo criar, alocar e remover processos, utilizando 
diferentes algoritmos de alocação de memória.

Funcionalidades principais:

1. PrintMenu()                : Exibe o menu principal do simulador e retorna a opção selecionada pelo usuário
2. ConfiguraMemoria()         : Configura a memória total disponível e define o algoritmo de alocação
3. OrdenaVectorMemoria()      : Ordena os blocos de memória por endereço base para manter consistência.
4. CriaProcesso()             : Cria um novo processo, solicita informações do usuário e adiciona ao vetor de processos
5. EncontraProcesso(pid_t pid): Busca um processo pelo PID e retorna seu índice no vetor de processos
6. InsereOcupadoELivre()      : Atualiza o vetor de blocos após a alocação de um processo em um bloco maior (split).
7. AlocaProcesso(pid_t pid)   : Tenta alocar um processo na memória de acordo com o algoritmo selecionado (First, Best, Worst ou Circular Fit)
8. ExibeMemoria()             : Mostra o estado atual da memória, indicando blocos livres e ocupados
9. RemoveProcesso(pid_t pid)  : Libera o bloco de memória de um processo e junta blocos livres adjacentes
10. SimuladorMemoriaContigua() : Função principal que implementa o loop de interação com o usuário, chamando as funções anteriores

Algoritmos de alocação implementados:

- First Fit    : Aloca no primeiro bloco livre que comporta o processo
- Best Fit     : Aloca no bloco livre de menor tamanho que ainda comporta o prcesso
- Worst Fit    : Aloca no bloco livre de maior tamanho disponível
- Circular Fit : Aloca em blocos livres seguindo a última posição usada, simulando alocação circular

Estrutura de dados:

- particoes : vetor de 'BlocoMemoria', que representa os blocos de memória disponíveis e ocupados
- processos : vetor de 'Processo', que contém todos os processos criados, alocados ou não
- algoritmo : número inteiro que define qual algoritmo de alocação será usado
- configurouMemoria : flag que indica se a memória foi inicializada
- contador_pids      : contador para gerar PIDs únicos para cada processo

*/

#include <iostream>
#include "MemoriaContigua.hpp"
#include <string>
#include <algorithm> // std::sort -> será necessário para manter o vector ordenado
#include <limits>

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
        cout << "Os parâmetros de memória já foram definidos. Não é possível redefini-los no momento." << endl;
        return;
    }

    while (1)
    {

        cout << "Tamanho Total da Memória: 1024KB" << endl;
        cout << "Informe o Algoritmo de alocação (1-First-Fit, 2-Best-Fit, 3-Worst-Fit, 4-Circular-Fit): ";
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

void MemoriaContigua::OrdenaVectorMemoria()
{

    if (particoes.empty())
    {
        cout << "Não foi possível ordenar o vector. O vector particoes está vazio." << endl;
    }

    std::sort(particoes.begin(), particoes.end(),
              [](const BlocoMemoria &a, const BlocoMemoria &b)
              {
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
        cout << "Tamanho inválido para o processo. Por favor, insira um processo com o tamanho dentro do limite estabelecido." << endl;
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

void MemoriaContigua::InsereOcupadoELivre(size_t indiceOcupado, const BlocoMemoria &livre)
{

    particoes.insert(particoes.begin() + (indiceOcupado + 1), livre); // Insere o livre na posição seguinte ao ocupado
}

/*
    bool MemoriaContigua::AlocaProcesso(): tenta efetuar a alocação do processo com base no espaço em memória disponível de acordo com o algoritmo selecionado.
*/

                //Função para exibir de fato a mememoria
void MemoriaContigua::ExibeMemoria() {
    if (particoes.empty()) {
        std::cout << "A memória ainda não foi configurada ou está vazia." << std::endl; //se estiver vazio provoca esse "erro"
        return;
    }

    std::cout << "=== Estado da Memória ===" << std::endl;
    for (size_t i = 0; i < particoes.size(); ++i) {
        const BlocoMemoria& bloco = particoes[i];

        std::cout << "Bloco " << i 
                  << ": Base = " << bloco.base               //mostra o bloco, a base, o amanho e se esta livre ou ocupado, com  PID
                  << ", Tamanho = " << bloco.tamanho << " KB, "
                  << (bloco.livre ? "Livre" : "Ocupado (PID " + std::to_string(bloco.PID) + ")")
                  << std::endl;
    }
    std::cout << "=========================" << std::endl;
}

/*
    Elaboraçao das funcoes relacionadas aos algoritmos (FIRST-FIT, BEST-FIT, WORST-FIT e CIRCULAR-FIT)
                                    (algoritmos de seleção de blocos)
*/

                        //FIRST-FIT
int MemoriaContigua::FirstFit(size_t tamanho) {
    for (size_t i = 0; i < particoes.size(); i++) {
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
                        // BEST FIT
int MemoriaContigua::BestFit(size_t tamanho) {
    int indice = -1;
    size_t menor = std::numeric_limits<size_t>::max(); //uso do numeric_limits ao inves do SIZE_MAX por portabilidade

    for (size_t i = 0; i < particoes.size(); ++i) {
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {
            if (particoes[i].tamanho < menor) {
                menor = particoes[i].tamanho;
                indice = static_cast<int>(i);
            }
        }
    }
    return indice;
}
                        // WORST FIT
int MemoriaContigua::WorstFit(size_t tamanho) {
    int indice = -1;
    size_t maior = 0;

    for (size_t i = 0; i < particoes.size(); ++i) {
        if (particoes[i].livre && particoes[i].tamanho >= tamanho) {
            if (particoes[i].tamanho > maior) {
                maior = particoes[i].tamanho;
                indice = static_cast<int>(i);
            }
        }
    }
    return indice;
}
                        // CIRCULAR FIT
int MemoriaContigua::CircularFit(size_t tamanho) {
    if (particoes.empty()) return -1;

    static size_t ultimaPos = 0;
    size_t n = particoes.size();

    for (size_t i = 0; i < n; ++i) {
        size_t idx = (ultimaPos + i) % n;
        if (particoes[idx].livre && particoes[idx].tamanho >= tamanho) {
            ultimaPos = idx; // guarda a posição para próxima busca
            return static_cast<int>(idx);
        }
    }
    return -1;
}

bool MemoriaContigua::AlocaProcesso(pid_t pid)
{

    if (!configurouMemoria)
    {
        cout << "Necessário configurar a memória antes de alocar um processo." << endl;
        return false;
    }

    int indiceProcessoAlvo = EncontraProcesso(pid);

    if (indiceProcessoAlvo < 0)
    {
        cout << "Processo PID: " << pid << " não encontrado no vector de processos!" << endl;
        return false;
    }

    Processo &ProcessoASerAlocado = processos[static_cast<size_t>(indiceProcessoAlvo)]; // 1. Vector trabalha com size_t para enumerar seus índices
                                                                                        // 2. ProcessoASerAlocado recebe uma referência, ou seja, se mudar ProcessoASerAlocado, mudo o processos[indice]
    if (ProcessoASerAlocado.alocado)
    {
        cout << "O processo PID: " << ProcessoASerAlocado.PID << " já está alocado." << endl;
        return false;
    }

    if (ProcessoASerAlocado.tamanho <= 0)
    {
        cout << "O processo com PID: " << ProcessoASerAlocado.PID << "possui tamanho inválido (" << ProcessoASerAlocado.tamanho << ")." << endl;
        return false;
    }


    // Primeira lógica implementada: First Fit --------------------------> Transformar em função posteriormente o que está entre o incio e o fim
    // INICIO FIRST FIT
    // Lógica FIRST FIT -> Percorre as partições da memória e encontra o PRIMEIRO BLOCO DE MEMÓRIA POSSÍVEL DISPONÍVEL
    // ITERAR DE BLOCO EM BLOCO
    int indiceBloco = -1;

    switch (algoritmo) {
    case 1: //  caso 1 para o First Fit
        indiceBloco = FirstFit(ProcessoASerAlocado.tamanho);
        break;
    case 2: // caso 2 para o Best Fit
        indiceBloco = BestFit(ProcessoASerAlocado.tamanho);
        break;
    case 3: // caso 3 para o Worst Fit
        indiceBloco = WorstFit(ProcessoASerAlocado.tamanho);
        break;
    case 4: // caso 4 para o Circular Fit
        indiceBloco = CircularFit(ProcessoASerAlocado.tamanho);
        break;
    default:
        cout << "Algoritmo inválido!" << endl;
        return false;
}
/**
    for (size_t i = 0; i < particoes.size(); i++)
    { // Vector trabalha com size_t

        BlocoMemoria &Bloco = particoes[i];

        if (Bloco.livre && (Bloco.tamanho >= ProcessoASerAlocado.tamanho))
        {                                      // Encontrou o índice de um bloco que satisfaz nossas necessidades no vector
            indiceBloco = static_cast<int>(i); // Caso não encontre, indiceBloco permanece -1
            break;
        }
    }
*/
    if (indiceBloco < 0)
    { // Não encontrou nenhum espaço livre na memória

        cout << "Não foi possível alocar o processo PID: " << ProcessoASerAlocado.PID << ". Não há região contígua na memória >= "
             << ProcessoASerAlocado.tamanho << "KB." << endl;
        return false;
    }

    BlocoMemoria &BlocoSelecionado = particoes[static_cast<size_t>(indiceBloco)]; // Atribui o bloco encontrado para BlocoSelecionado

    /*
        Agora que um bloco de memória que satisfaça nossas necessidades foi escolhido, dois cenários são possíveis:
            1. O Bloco de memória alocado possui tamanho EXATAMENTE IGUAL ao que o processo necessita;
            2. O bloco de memória alocado possui tamanho MAIOR do que o processo necessita.

        Na situação 1, apenas marcaremos que aquele bloco agora pertence ao PID do processo alocado para ele;
        Na situação 2, teremos que fazer um "split", ou seja, alocar o que o processo precisa, e inserir, logo em seguida do espaço alocado para o processo,
        no vetor, um bloco de memória com a "quantidade de memória" que sobrou.
    */

    if (ProcessoASerAlocado.tamanho == BlocoSelecionado.tamanho)
    { // Aqui, o processo recebe o bloco de memória inteiro

        BlocoSelecionado.livre = false;                 // Alocado
        BlocoSelecionado.PID = ProcessoASerAlocado.PID; // O Bloco pertence àquele processo

        ProcessoASerAlocado.base = BlocoSelecionado.base;
        ProcessoASerAlocado.limite = BlocoSelecionado.base + ProcessoASerAlocado.tamanho - 1; // EndLimite = Base(bloco) + tamanho - 1
        ProcessoASerAlocado.alocado = true;

        // Mostra para o usuário que o processo foi alocado com sucesso
        // e informa a base e o limite do bloco de memória ocupado

        cout << "Processo PID " << ProcessoASerAlocado.PID                    
     << " alocado na memória com base " << ProcessoASerAlocado.base 
     << " e limite " << ProcessoASerAlocado.limite << "." << endl;
    }
    else if (BlocoSelecionado.tamanho > ProcessoASerAlocado.tamanho)
    { // Nesse caso, vamos ter que fazer o "split" (situação 2). Então teremos um bloco de memória OCUPADO pelo processo e o restante do bloco Original LIVRE

        BlocoMemoria AreaOcupada;

        AreaOcupada.livre = false;
        AreaOcupada.base = BlocoSelecionado.base;
        AreaOcupada.tamanho = ProcessoASerAlocado.tamanho;
        AreaOcupada.PID = ProcessoASerAlocado.PID;

        BlocoMemoria AreaRestante;
        AreaRestante.livre = true;
        AreaRestante.base = AreaOcupada.base + ProcessoASerAlocado.tamanho;
        AreaRestante.PID = BLOCO_LIVRE;
        AreaRestante.tamanho = BlocoSelecionado.tamanho - ProcessoASerAlocado.tamanho;

        // Necessário inserir o bloco OCUPADO no lugar do bloco ENCONTRADO no vector e inserir logo após ele a área restante

        particoes[static_cast<size_t>(indiceBloco)] = AreaOcupada; // Substitui o bloco recém encontrado pela área ocupada
        InsereOcupadoELivre(static_cast<size_t>(indiceBloco), AreaRestante);

        ProcessoASerAlocado.base = AreaOcupada.base;
        ProcessoASerAlocado.limite = AreaOcupada.base + ProcessoASerAlocado.tamanho - 1;
        ProcessoASerAlocado.alocado = true;

        // Processo parcialmente alocado em um bloco maior.
        // O bloco original foi dividido, a parte necessária é então alocada para o processo
        // e o restante permanece livre, o usuário recebe feedback sobre a divisão.

        cout << "Processo PID " << ProcessoASerAlocado.PID 
        << " alocado na memória com base " << ProcessoASerAlocado.base 
        << " e limite " << ProcessoASerAlocado.limite << "." << endl;

        cout << "Bloco de memória dividido. Espaço restante: " 
        << AreaRestante.tamanho << " KB livre." << endl;
    }
    return true;
    // FIM FIRST FIT

    // retorna false -> caso impossível. O FLUXO DE EXECUÇÃO NÃO PODE CHEGAR AQUI POR MOTIVO ALGUM
}


/*
    void MemoriaContigua::RemoveProcesso(pid_t pid):
    - Libera o bloco de memória associado ao processo informado
    - Marca o processo como desalocado
    - Junta blocos livres adjacentes para evitar fragmentação externa
*/
void MemoriaContigua::RemoveProcesso(pid_t pid) {
        // Encontra o índice do processo pelo PID
    int idx = EncontraProcesso(pid);
    if (idx < 0) {
        std::cout << " Processo " << pid << " não encontrado!" << std::endl;
        return;
    }

    Processo &proc = processos[static_cast<size_t>(idx)];
    if (!proc.alocado) {
        std::cout << " Processo " << pid << " não está alocado!" << std::endl;
        return;
    }

    bool liberado = false;

    // Procura o bloco de memória que pertence a esse processo
    for (auto &bloco : particoes) {
        if (!bloco.livre && bloco.PID == pid) {
            // Libera o bloco
            bloco.livre = true;
            bloco.PID = BLOCO_LIVRE; // constante usada para os blocos livres
            liberado = true;
            std::cout << " Processo " << pid << " removido da memória." << std::endl;
            break;
        }
    }

    if (!liberado) {
        std::cout << " Bloco do processo " << pid << " não encontrado em particoes!" << std::endl;
        return;
    }

    // Atualiza o status do processo
    proc.alocado = false;
    proc.base = 0;
    proc.limite = 0;

    // Junta blocos livres adjacentes
    for (size_t i = 0; i + 1 < particoes.size();) {
        if (particoes[i].livre && particoes[i + 1].livre) {
            particoes[i].tamanho += particoes[i + 1].tamanho;
            particoes.erase(particoes.begin() + i + 1);
        } else {
            i++;
        }
    }
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
            ConfiguraMemoria();
        break;

        case 2:{
            // Chamar função que cria um processo
            // logo depois chamar a função que mostra o estado da memória intrinsicamente (sugestao do professor)

            pid_t pid = CriaProcesso();     // Cria o processo e retorna o PID
            if (pid > 0) {
                AlocaProcesso(pid);         // Tenta alocar o processo
                ExibeMemoria();             // Mostra a memória atualizada
            }
        break;
    }
        case 3:
            pid_t pid;
            std::cout << "Informe o PID do processo a ser removido: ";
            std::cin >> pid;

            // Chama a função que remove o processo
            RemoveProcesso(pid);

            // Exibe o estado atual da memória depois da remoção para que o usúario veja como está a memória
            ExibeMemoria();
            
        break;

        case 4:
            ExibeMemoria();     // chama a função que exibe a memória
            break;               
        case 5:

            // Chamar função que reseta o simulador de memória contígua

            particoes.clear();                  // da clear nas particoes e
            processos.clear();                  // nos processos e por fim
            configurouMemoria = false;          // reseta o simulador
            contador_pids = 0;
            std::cout << "Simulador resetado!" << std::endl;
            break;

        case 0:

            // Break. Sai do laço e mostra as estatísticas finais
            std::cout << "Saindo do simulador..." << std::endl;
            return;

        default:

            // Avisar operação inválida e continue

            cout << "Operação inválida!" << endl;
            continue;
        }
    }
}
