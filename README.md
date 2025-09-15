# TrabalhoFinalSOII

Repositório para armazenar e documentar o trabalho final da disciplina de Sistemas Operacionais II

## Integrantes 
- Gustavo Luiz Rosset - 198100
- Matheus Sebastiani Silva - 198204

# Simulador de Gerência de Memória

## Descrição do Projeto
Este projeto é um **Simulador de Gerência de Memória**, desenvolvido como trabalho final da disciplina de Sistemas Operacionais II.  
O simulador permite estudar e testar diferentes algoritmos de alocação de memória, observar como processos são armazenados, removidos e organizados na memória, e calcular a fragmentação nos dois esquemas:
O simulador possui **duas modalidades**:
1. **Alocação Contígua**
2. **Paginação**

O usuário interage com o simulador através de um menu no terminal, podendo criar processos, alocá-los, removê-los e visualizar o estado da memória.

## Linguagem e Interface
- Linguagem de programação: **C++17**  
- Interface: **Terminal / Console** (CLI), com menus interativos para manipulação da memória e processos.

## Bibliotecas utilizadas
O projeto utiliza bibliotecas padrão do C++, não foi necessário a instalação de bibliotecas externas:

<iostream>: para entrada e saída no console (cin, cout), usado para criar menus interativos e mostrar informações da memória.

<limits>: para verificar limites de tipos de dados e limpar entradas inválidas do usuário, evitando erros de leitura.

<cmath>: para cálculos matemáticos, como o ceil() usado para calcular o número de páginas necessárias para cada processo.

<vector>: para armazenar dinamicamente listas de processos, partições e páginas de memória.

<string>: para armazenar nomes dos processos.

<algorithm>: para ordenação de vetores de partições na memória contígua (por exemplo, função sort()).


## Funcionalidades

### Alocação Contígua
- Escolha entre os algoritmos:
  - **First-Fit**: Aloca no primeiro bloco disponível suficiente.
  - **Best-Fit**: Aloca no menor bloco suficiente.
  - **Worst-Fit**: Aloca no maior bloco disponível.
  - **Circular-Fit**: Aloca no próximo bloco disponível circularmente.
- Criação de processos com tamanho e nome personalizados.
- Remoção de processos da memória.
- Visualização do estado atual da memória, mostrando blocos ocupados e livres.
- Reset completo da memória e dos processos.
- Cálculo de Fragmentação Interna:
    O simulador calcula o espaço desperdiçado dentro de cada partição ocupada e exibe a porcentagem de fragmentação interna em relação à memória total.

### Paginação
- Simulação de memória paginada.
- Criação e alocação de processos em páginas.
- Remoção de processos e atualização das páginas livres.
- Visualização do estado atual da memória paginada.
- Cálculo de Fragmentação Interna:
    Para cada processo, o simulador calcula o espaço desperdiçado na última página alocada e exibe a porcentagem de fragmentação interna em relação à memória total.

---

## Estrutura de Arquivos

/project-root
│
├── main.cpp # Ponto de entrada do programa
├── classes/
│ ├── MemoriaContigua.hpp # Declaração da classe de alocação contígua
│ ├── MemoriaContigua.cpp # Implementação das funções da alocação contígua
│ ├── MemoriaPaginada.hpp # Declaração da classe de paginação
│ └── MemoriaPaginada.cpp # Implementação das funções de paginação
└── README.md # Este arquivo

## Decisões de Projeto e Arquitetura
- Separação das funcionalidades em **duas classes principais**: `MemoriaContigua` e `MemoriaPaginada`.  
- Cada classe possui métodos próprios para criar/remover processos, alocar memória e exibir o estado atual.  
- Menu interativo no console, facilitando a interação do usuário sem necessidade de interface gráfica complexa.  
- Estrutura modular permite fácil manutenção e extensão dos algoritmos de alocação.

## Principais Classes e Funções

### **MemoriaContigua**
Classe que simula a alocação contígua de memória.

**Atributos principais:**
- `particoes`: vetor que armazena blocos de memória (`BlocoMemoria`), indicando se estão livres ou ocupados.
- `processos`: vetor que mantém os processos criados.
- `algoritmo`: inteiro que define qual algoritmo de alocação será usado.
- `contador_pids`: contador para gerar IDs únicos de processos.

**Funções principais:**
- `PrintMenu()`: Exibe o menu principal do simulador contíguo.
- `ConfiguraMemoria()`: Inicializa a memória com tamanho fixo (1024 KB) e define o algoritmo de alocação.
- `CriaProcesso()`: Cria um novo processo com nome e tamanho, retornando seu PID.
- `AlocaProcesso(pid_t pid)`: Tenta alocar um processo na memória usando o algoritmo definido.
- `RemoveProcesso(pid_t pid)`: Remove o processo da memória, liberando blocos ocupados.
- `ExibeMemoria()`: Mostra a memória atual, indicando blocos livres e ocupados.
- `OrdenaVectorMemoria()`: Ordena o vetor de blocos por endereço base.
- `CalculaFragmentaçãoExterna()`: Calcula a fragmentação externa para memória contígua
- `ExibeProcesso()`: Exibe a lista de processos alocados e não alocados com o endereço de base e limite para os que estão alocados na memória
- Algoritmos de alocação:
  - `FirstFit(size_t tamanho)`
  - `BestFit(size_t tamanho)`
  - `WorstFit(size_t tamanho)`
  - `CircularFit(size_t tamanho)`
- `SimuladorMemoriaContigua()`: Função principal que controla a interface e execução do simulador contíguo.

## Exemplo de uso
Escolha o modo de alocação:
1. Alocação Contígua
2. Paginação
1

== Menu Principal - Memória Contígua ==
1. Definir Parâmetros da Memória
2. Adicionar Processo
3. Remover Processo
4. Exibir Memória
5. Resetar
0. Sair
Escolha uma opção: 1

Informe o tamanho total da memória (KB): 1024
Escolha o algoritmo de alocação (1-FirstFit, 2-BestFit, 3-WorstFit, 4-CircularFit): 2

Escolha uma opção: 2
Informe o nome do processo: P1
Informe o tamanho do processo (KB): 200

Escolha uma opção: 2
Informe o nome do processo: P2
Informe o tamanho do processo (KB): 300

Escolha uma opção: 4
=== Estado da Memória ===
Bloco 0: PID 1, Tamanho 200 KB
Bloco 1: PID 2, Tamanho 300 KB
Bloco 2: LIVRE, Tamanho 524 KB

Fragmentação interna: 0 KB (0.0%)

## O conteúdo dos exemplos acima pode variar 

---

### **MemoriaPaginada**
Classe que simula a alocação de memória paginada.

**Atributos principais:**
- Vetores de páginas e processos, controlando quais páginas estão ocupadas.
- Constantes definindo tamanho de página e memória total.

**Funções principais:**
- `CriaProcesso()`: Cria um processo e define suas páginas.
- `AlocaProcesso(pid_t pid)`: Aloca as páginas necessárias para um processo.
- `RemoveProcesso(pid_t pid)`: Libera as páginas ocupadas pelo processo.
- `ExibeMemoria()`: Mostra o estado atual da memória paginada.
- `Simulador()`: Função principal que controla o menu e execução da simulação de paginação.
- `CalculaFragmentacaoInterna()`: Calcula a fragmentação interna no modo de paginação

## Exemplo de uso
Escolha o modo de alocação:
1. Alocação Contígua
2. Paginação
2

== Menu Principal - Paginação ==
1. Definir Parâmetros da Memória
2. Adicionar Processo
3. Remover Processo
4. Exibir Tabelas de Páginas
5. Resetar
0. Sair
Escolha uma opção: 1

Informe o tamanho total da memória (KB): 1024
Informe o tamanho do frame (KB): 128

Escolha uma opção: 2
Informe o nome do processo: P1
Informe o tamanho do processo (KB): 200

Escolha uma opção: 2
Informe o nome do processo: P2
Informe o tamanho do processo (KB): 300

Escolha uma opção: 4
=== Estado da Memória Física ===
Frame 0: PID 1
Frame 1: PID 1
Frame 2: PID 2
Frame 3: PID 2
Frame 4: PID 2
Frame 5: LIVRE
Frame 6: LIVRE
Frame 7: LIVRE

=== Tabelas de Páginas ===
PID 1: 0 1
PID 2: 2 3 4

Fragmentação interna (última página de cada processo):
P1: 56 KB
P2: 32 KB
Total: 88 KB (8.59%)

## O conteúdo dos exemplos acima pode variar 

---

## Como rodar o projeto

- Para conseguir "rodar" o simulador, é importante e aconselhado que seja feito no terminal de um sistema operacional linux (a nível de facilidade e compatibilidade)e que esteja com a pate de compilador g++ 
 atualizada para o uso correto do simulador, vale lembrar também que é preciso ter um conhecimento leve de como clonar repositórios de projetos do github, caso não tenha o conhecimento, abaixo estarão instrucoes gerais de como fazer esse processo:

 ## Intrucões para o uso do GITHUB
- Criar uma conta no GitHub
- Acesse: https://github.com
- Clique em Sign up (ou Cadastrar-se).
- Preencha:
- Nome de usuário 
- E-mail
- Senha
- Siga as instruções de verificação do e-mail.
- Agora você tem uma conta no GitHub.

- Instale o git em seu computador com um SO linux:
- Utilize os comandos abaixo no terminal:
    sudo apt update
    sudo apt install git
- No terminal, configure seu nome e e-mail (eles aparecem nos commits):
- Utilize os comandos:
    git config --global user.name "Seu Nome"
    git config --global user.email "seu-email@exemplo.com"
- Após esses passos acima clone o repositório, compile e rode o simulador a partir dos comandos abaixo:

# Clonar o repositório
git clone https://github.com/matheussebastiani/TrabalhoFinalSOII.git

# Entrar na pasta do projeto
cd TrabalhoFinalSOII

# Compilar os arquivos C++
g++ -std=c++17 main.cpp classes/MemoriaContigua.cpp classes/MemoriaPaginada.cpp -o simulador ou com o uso do Makefile presente na pasta

# Executar o simulador
./simulador

# CASO NÃO CONSIGA RODAR O SIMULADOR, REPITA OS PROCESSOS ACIMA NOVAMENTE COM ATENÇÃO








