#include "main.h"
#include "board.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Cantidad de argumentos invalida.");
        exit(EXIT_FAILURE);
    }

    char* nombreEntrada = argv[1];
    Board* boardEntrada = entrada_board(nombreEntrada);
    salida_board(boardEntrada);

    board_destruir(boardEntrada);
    return 0;
}