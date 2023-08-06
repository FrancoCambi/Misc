#include "board.h"
#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>

/* Creamos un board dado sus datos si son validos. Si no, devuelve NULL */
Board* board_crear(Barco** _barcos, int _cantBarcos, int _cantValidos, int _filas, int _columnas) {

    Board* board = malloc(sizeof(struct _Board));

    board->barcos = _barcos;
    board->cantBarcos = _cantBarcos;
    board->cantValidos = _cantValidos;
    board->filas = _filas;
    board->columnas = _columnas;

    return board;
}

/* Destruye un board. */
void board_destruir(Board* board) {

    for (int i = 0; i < board->cantBarcos; i++)
        if (board->barcos[i])
            barco_destruir(board->barcos[i]);
    free(board->barcos);
    free(board);
}