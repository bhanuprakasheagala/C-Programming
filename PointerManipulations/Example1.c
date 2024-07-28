#include <stdio.h>
#include <stdlib.h>

void manipulateArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int main() {
    int size = 5;
    int *arr = (int*) malloc(sizeof(int) * size);
    
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    manipulateArray(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}