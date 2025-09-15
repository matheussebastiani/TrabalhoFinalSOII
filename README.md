# TrabalhoFinalSOII

Repositório para armazenar e documentar o trabalho final da disciplina de Sistemas Operacionais II

# Simulador de Gerência de Memória

## Descrição
Este projeto é um simulador de gerenciamento de memória inspirado em sistemas operacionais.  
Permite estudar e testar diferentes algoritmos de alocação de memória e entender como processos são armazenados, removidos e organizados na memória.

O simulador possui **duas modalidades**:
1. **Alocação Contígua**
2. **Paginação**

O usuário interage com o simulador através de um menu no terminal, podendo criar processos, alocá-los, removê-los e visualizar o estado da memória.

---

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
- Algoritmos de alocação:
  - `FirstFit(size_t tamanho)`
  - `BestFit(size_t tamanho)`
  - `WorstFit(size_t tamanho)`
  - `CircularFit(size_t tamanho)`
- `SimuladorMemoriaContigua()`: Função principal que controla a interface e execução do simulador contíguo.

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

---

## Como rodar o projeto

Clone o repositório, compile e rode o simulador:

```bash
# Clonar o repositório
git clone https://github.com/matheussebastiani/TrabalhoFinalSOII.git

# Entrar na pasta do projeto
cd TrabalhoFinalSOII

# Compilar os arquivos C++
g++ -std=c++17 main.cpp classes/MemoriaContigua.cpp classes/MemoriaPaginada.cpp -o simulador ou com o uso do Makefile 

# Executar o simulador
./simulador








