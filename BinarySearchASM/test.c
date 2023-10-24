#include<stdio.h>

int BSRecursive(int *arr, int low, int high, int target);

int main(void) {

    int a[7] = {1, 50, 60, 70, 90, 180, 255};

    printf("Res: %d\n", BSRecursive(a, 0, 6, 50));

    return 0;
    
}