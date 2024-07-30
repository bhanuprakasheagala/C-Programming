#include <stdio.h>

int compareAsc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int comapreDesc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

void printArray(int arr[], int size) {
    for(int i=0; i<size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {

    int arr[] = {5, 2, 8, 1, 4};
    int size = sizeof(arr)/sizeof(arr[0]);

    printf("Original Array: ");
    printArray(arr, size);

    qsort(arr, size, sizeof(int), compareAsc);
    printf("Sorted Array in Ascending order: ");
    printArray(arr, size);

    qsort(arr, size, sizeof(int), comapreDesc);
    printf("Sorted Array in Descending order: ");
    printArray(arr, size);

    return 0;
}