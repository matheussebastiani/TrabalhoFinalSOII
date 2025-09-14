CC=g++

# Alvos principais
all: simulador

# Compila MemoriaContigua.cpp
MemoriaContigua.o: classes/Tipo.hpp classes/MemoriaContigua.hpp classes/MemoriaContigua.cpp
	$(CC) -c classes/MemoriaContigua.cpp -o MemoriaContigua.o

# Compila MemoriaPaginada.cpp
MemoriaPaginada.o: classes/Tipo.hpp classes/MemoriaPaginada.hpp classes/MemoriaPaginada.cpp
	$(CC) -c classes/MemoriaPaginada.cpp -o MemoriaPaginada.o

# Gera o executável simulador a partir dos objetos
simulador: main.cpp MemoriaContigua.o MemoriaPaginada.o
	$(CC) main.cpp MemoriaContigua.o MemoriaPaginada.o -o simulador

# Limpeza
clean:
	rm -f *.o simulador