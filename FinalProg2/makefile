# Compilador y opciones de compilación
CC = gcc
CFLAGS = -Wall -Wextra -g

# Regla para construir ambos ejecutables
all: programa

# Objeto 1: programa
programa: main.c barcos.c board.c utils.c
	$(CC) $(CFLAGS) main.c barcos.c board.c utils.c

# Regla para limpiar (borrar) los ejecutables y archivos objeto
clean:
	rm -f programa tests
