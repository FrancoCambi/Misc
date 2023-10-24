#include<stdio.h>

int suma_divisores(int num);


int main() {

    for (int i = 33550000; i <= 33551000; i++) {
        printf("%d\n", i);
        if (i == suma_divisores(i)) {
            printf("ENCONTRADO! NUM = %d\n", i);
            getchar();
        }
    }

    return 0;
}

int suma_divisores(int num) {


    int resultado = 0;

    for (int i = 1; i < num; i++) {

        if (!(num % i))
            resultado += i;
    }

    return resultado;
}