#ifndef __UTILS_H__
#define __UTILS_H__

#include "board.h"
#include "barcos.h"
#include<stdio.h>
#include<stdlib.h>

/* Libera toda la memoria de una matriz de enteros. */
void destruir_matriz(int** matriz, int filas);

/* Libera toda la memoria de un array de barcos */
void destruir_arreglo_barcos(Barco** barcos, int cantBarcos);

/* Devuelve un numero random en el intervalo [min, max]*/
int random_intervalo(int min, int max);

/* Recibe un nombre de archivo de entrada y devuelve un Board con todos los datos
que el archivo da. */
Board* entrada_board(char* nombreEntrada);

/* Intenta insertar un barco en la matriz que guarda las posiciones ya ocupadas por un barco. 
En caso de no poderlo insentar devuelve NULL.
Si todo salio bien, devuelve el mismo barco pasado como agumento. */
Barco* insertar_barco_matriz(Barco* barco, int** matriz, int  filas, int columnas);

/* Recibe el board con los datos del archivo de entrada y selecciona una cantidad random de 
barcos y los escribe en el archivo de salida. */
void salida_board(Board* boardEntrada);


#endif /* __UTILS_H__ */