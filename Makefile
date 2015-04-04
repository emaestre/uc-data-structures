# Makefile

# Variables
PRINCIPAL = 
EXE =
CC = g++
FLAGS = -g 

# Programa Principal
all: 
	$(CC) $(FLAGS) $(PRINCIPAL) -o $(EXE)

# Borrar los Archivos Objeto y el Ejecutable
clean:
	rm -rf *.o $(EXE) 