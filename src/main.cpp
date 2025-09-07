#include <iostream>




int main(){

    int option;

    std::cout << "=== Simulador de Gerência de Memória ===" << std::endl;
    std::cout << "Escolha o modo de alocação:" << std::endl;
    std::cout << "\t1. Alocação Contígua." << std::endl;
    std::cout << "\t2. Paginação." << std::endl;

    std::cout << "Digite sua escolha (1/2): ";
    
    std::cin >> option;

    std::cout << option;

    switch(option){

        case 1:
            // Chama função-membro que realiza a simulação de alocação contígua
            break;
        
        case 2:
            // Chama função-membro que realiza a simulação de paginação
            break;

        default:
            std::cout << "Opção inválida!" << std::endl;
            exit(EXIT_FAILURE);
    }

}



