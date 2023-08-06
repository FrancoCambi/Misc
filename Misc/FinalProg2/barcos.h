#ifndef __BARCOS_H__
#define __BARCOS_H__

typedef struct _Barco {

    int supFila, supCol, orientacion, longitud;

}Barco;

/* Crea un barco dados sus datos y los datos del board */
Barco* barco_crear(int _supFila, int _supCol, int _orientacion, int _longitud, int boardFilas, int boardCol);

/* Destruye un barco. */
void barco_destruir(Barco* barco);

#endif /* __BARCOS_H__ */