#include "utils.h"
#include <time.h>

/* Libera toda la memoria de una matriz de enteros. */
void destruir_matriz(int** matriz, int filas) {
    for (int i = 0; i < filas; i++)
        free(matriz[i]);
    free(matriz);
}

/* Libera toda la memoria de un array de barcos */
void destruir_arreglo_barcos(Barco** barcos, int cantBarcos) {
    for (int i = 0; i < cantBarcos; i++)
        if (barcos[i])
            free(barcos[i]);
    free(barcos);
}

/* Devuelve un numero random en el intervalo [min, max]*/
int random_intervalo(int min, int max) {
    return (rand() % (max + 1 - min)) + min;
}

/* Recibe un nombre de archivo de entrada y devuelve un Board con todos los datos
que el archivo da. */
Board* entrada_board(char* nombreEntrada) {

    // Abrimos el archivo, terminando la ejecucion si hubo un error
    FILE* entrada = fopen(nombreEntrada, "r");
    if (!entrada) {
        printf("No se pudo abrir el archivo de entrada.\n");
        exit(EXIT_FAILURE);
    }

    // Recuperamos el dato de las filas y columnas.
    // Terminando la ejecucion en caso de no ser datos validos.
    int filas, cols;
    fscanf(entrada, "%d %d", &filas, &cols);
    if (filas < 10 || filas > 20 || cols < 10 || cols > 20) {
        printf("Filas o columnas invalidas.\n");
        fclose(entrada);
        exit(EXIT_FAILURE);
    }

    // Metemos todos los barcos en un array de barcos y recuperamos su cantidad.
    int supFila, supCol, orientacion, longitud, cantBarcos = 0, cantValidos = 0;
    Barco** barcos = malloc(sizeof(Barco*) * 50);

    while (fscanf(entrada, "%d %d %d %d", &supFila, &supCol, &orientacion, &longitud) != EOF) {
        
        // si nos vamos a pasar con la cantidad maxima de barcos,
        // liberamos toda la memoria y terminamos la ejecucion
        if (cantBarcos == 50) {
            printf("Cantidad de barcos invalida.\n");
            destruir_arreglo_barcos(barcos, cantBarcos);
            fclose(entrada);
            exit(EXIT_FAILURE);
        }

        Barco* barco = barco_crear(supFila, supCol, orientacion, longitud, filas, cols);
        barcos[cantBarcos++] = barco;
        if (barco != NULL)
            cantValidos++;
            
    
    }

    // Creamos el board del archivo de entrada.
    barcos = realloc(barcos, sizeof(Barco*) * cantBarcos);
    Board* board = board_crear(barcos, cantBarcos, cantValidos, filas, cols);

    fclose(entrada);
    return board;

}

/* Intenta insertar un barco en la matriz que guarda las posiciones ya ocupadas por un barco. 
En caso de no poderlo insentar devuelve NULL.
Si todo salio bien, devuelve el mismo barco pasado como agumento. */
Barco* insertar_barco_matriz(Barco* barco, int** matriz, int filas, int columnas) {

    // Si el barco, ya no era validos por def. devolvemos null.
    if (barco == NULL) 
        return NULL;

    // Si nuestro barco se sale de limites, devolvemos NULL.
    if (barco->orientacion == 0 && barco->supCol > (columnas - barco->longitud + 1)) // Horizontal
        return NULL;
    

    if (barco->orientacion == 1 && barco->supFila > (filas - barco->longitud + 1)) // Vertical
        return NULL;

    // Luego, intentamos introducirlo al "board".
    // Si alguna casilla esta ocupada, devolvemos NULL.
    for (int i = 0; i < barco->longitud; i++) {

        if (barco->orientacion == 0) {
            if (matriz[barco->supFila - 1][barco->supCol + i - 1] == 0) // Horizontal 
                matriz[barco->supFila - 1][barco->supCol + i - 1] = 1;
            
            else
                return NULL;
        }
        if (barco->orientacion == 1) {
            if (matriz[barco->supFila + i - 1][barco->supCol - 1] == 0) // Vertical 
                matriz[barco->supFila + i - 1][barco->supCol - 1] = 1;
            
            else
                return NULL;
        }
    }

    // Si todo salio bien, devolvemos el barco.
    return barco;

}   

/* Recibe el board con los datos del archivo de entrada y selecciona una cantidad random de 
barcos y los escribe en el archivo de salida. */
void salida_board(Board* boardEntrada) {

    FILE* salida = fopen("salida.txt", "w+");
    if (!salida) {
        printf("No se pudo abrir el archivo de salida (salida.txt).\n");
        board_destruir(boardEntrada);
        exit(EXIT_FAILURE);
    }

    // Escribimos la primera lina del archivo de salida.
    fprintf(salida, "%d %d\n", boardEntrada->filas, boardEntrada->columnas);

    // Elegimos la cantidad de barcos random y chequeamos que sea un numero valido.
    srand(time(NULL));
    int randomCant = random_intervalo(boardEntrada->filas / 3, boardEntrada->columnas);

    // Si la cantidad random es mayor a los barcos validos que tenemos
    // Liberamos memoria y terminamos la ejecucion.
    if (randomCant > boardEntrada->cantValidos) {
        printf("Cantidad de barcos validos insuficiente.\n");
        board_destruir(boardEntrada);
        fclose(salida);
        exit(EXIT_FAILURE);
    }
    
    // Creamos las variables de uso y la matriz
    // La matriz contendra cada casilla de nuestro board, con 0 si la casilla
    // no esta ocupada o 1 si esta ocupada.
    int elegidosCant = 0, validosRestantes = boardEntrada->cantValidos;
    int** matriz = malloc(sizeof(int*) * boardEntrada->filas);
    for (int i = 0; i < boardEntrada->filas; i++)
        matriz[i] = calloc(boardEntrada->columnas, sizeof(int));

    // Mientras nos falten barcos por elegir..
    while (elegidosCant != randomCant) {

        int indexElegido = random_intervalo(0, boardEntrada->cantBarcos - 1);
        Barco* barcoElegido = boardEntrada->barcos[indexElegido];
        barcoElegido = insertar_barco_matriz(barcoElegido, matriz, boardEntrada->filas, boardEntrada->columnas);

        // Nos sea de utilidad o no, ese barco ya no lo volveremos a usar.
        validosRestantes--;

        // Si es posible insertar nuestro barco, lo escribimos en el archivo
        if (barcoElegido != NULL) {

            elegidosCant++;

            // Escribimos el barco elegido en el archivo de salida
            fprintf(salida, "%d %d %d %d\n", barcoElegido->supFila, barcoElegido->supCol, 
                barcoElegido->orientacion, barcoElegido->longitud);
            
        }

        // Destruimos y seteamos a NULL el barco elegido
        // independientemento de si nos fue de utilidad o no.
        barco_destruir(boardEntrada->barcos[indexElegido]);
        boardEntrada->barcos[indexElegido] = NULL;

        // Si nos faltan mas barcos de los que tenemos para elegir
        // cortamos le ejecucion.
        if (validosRestantes < (randomCant - elegidosCant)) {
            printf("La eleccion random fallo. Puede intentar de nuevo.\n");
            destruir_matriz(matriz, boardEntrada->filas);
            board_destruir(boardEntrada);
            fclose(salida);
            exit(EXIT_FAILURE);
        }


    } 

    // Liberamos la memoria de la matriz y cerramos el archivo de salida.
    destruir_matriz(matriz, boardEntrada->filas);
    fclose(salida);

}