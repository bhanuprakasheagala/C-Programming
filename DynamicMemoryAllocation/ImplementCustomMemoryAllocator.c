#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMORY_POOL_SIZE 1024

char memory_chunk[MEMORY_POOL_SIZE];
bool allocated[MEMORY_POOL_SIZE] = {false};

void* my_malloc(size_t size) {
    for(int i = 0; i < MEMORY_POOL_SIZE - size; i++) {
        bool can_allocate = true;
        for(int j = 0; j < size; ++j) {
            if(allocated[i + j]) {
                can_allocate = false;
                break;
            }
        }
        if(can_allocate) {
            for(int j = 0; j < size; ++j) {
                allocated[i + j] = true;
            }
            return &memory_chunk[i];
        }
    }

    return NULL; // out of memory
}

void my_free(void* ptr, size_t size) {
    int index = (char*)ptr - memory_chunk;
    for(int i = 0; i < size; ++i) {
        allocated[index + i] = false;
    }
}

int main() {
    void* block1 = my_malloc(100);
    void* block2 = my_malloc(200);

    printf("Allocated blocks at %p and %p\n", block1, block2);

    my_free(block1, 100);
    my_free(block2, 200);
    
    return 0;
}