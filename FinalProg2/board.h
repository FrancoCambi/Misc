#ifndef __BOARD_H__
#define __BOARD_H__

#include "barcos.h"

typedef struct _Board {
    Barco** barcos;
    int cantBarcos, cantValidos, filas, columnas;
}Board;

/* Creamos un board dado sus datos si son validos. Si no, devuelve NULL */
Board* board_crear(Barco** _barcos, int _cantBarcos, int _cantValidos, int _filas, int _columnas);

/* Destruye un board. */
void board_destruir(Board* board);


#endif /* __BOARD_H__ */