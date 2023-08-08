#include "barcos.h"
#include<stdlib.h>
#include<stddef.h>

/* Crea un barco dados sus datos y los datos del board */
Barco* barco_crear(int _supFila, int _supCol, int _orientacion, int _longitud, int boardFilas, int boardCol) {

    // Chequeamos que los datos pasados sean los de un barco valido dentro de nuestro board
    // Si no, devolvemos NULL
    if (_supFila > boardFilas || _supFila <= 0 || _supCol > boardCol || _supCol <= 0 || 
                (_orientacion != 1 && _orientacion != 0) || _longitud > 4 || _longitud < 2) 
        return NULL;
    
    
    // Si los datos estan bien, devolvemos el barco creado
    Barco* barco = malloc(sizeof(struct _Barco));

    barco->supFila = _supFila;
    barco->supCol = _supCol;
    barco->orientacion = _orientacion;
    barco->longitud = _longitud;

    return barco;
}

/* Destruye un barco. */
void barco_destruir(Barco* barco) {
    if (barco)
        free(barco);
}