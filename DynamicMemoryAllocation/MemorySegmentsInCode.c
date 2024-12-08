#include <stdio.h>
#include <stdlib.h>

// Global variable (Data segment - Initialized)
int global_var = 42;

// Global variable (BSS - Uninitialized)
int uinit_global;

void displayMemoryAddresses() {
    static int static_var = 10; // Data segment - Initialized
    int local_var = 20; // Stack
    int* heap_var = (int*)malloc(sizeof(int)); // Heap
    *heap_var = 30;

    printf("Text Segment (Code): %p\n", (void*)displayMemoryAddresses);
    printf("Data Segment (Initialized): %p\n", (void*)&global_var);
    printf("BSS (Uninitialized): %p\n", (void*)&uinit_global);
    printf("Data Segment (Static): %p\n", (void*)&static_var);
    printf("Stack: %p\n", (void*)&local_var);
    printf("Heap: %p\n", (void*)heap_var);

    free(heap_var);
}

int main() {
    displayMemoryAddresses();
    return 0;
}