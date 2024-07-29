#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void* data;             // Pointer to the array data
    size_t element_size;    // Size of each element
    size_t noOfElements;    // Number of elements in the array
    size_t capacity;        // Capacity of the array
} DynamicArray;

// Initialize the Dynamic Array
DynamicArray* init(size_t element_size, size_t capacity) {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    arr->element_size = element_size;
    arr->noOfElements = 0;
    arr->capacity = capacity;
    arr->data = calloc(element_size, capacity);

    return arr;
}

// Resize the Array
void resize(DynamicArray* arr, size_t newCapacity) {
    void* new_data = realloc(arr->data, (arr->element_size) * newCapacity);
    if(new_data == NULL) {
        printf("Memory allocation failed!!\n");
        exit(1);
    }
    arr->data = new_data;
    arr->capacity = newCapacity;
}

// Add elements to the Array
void addElement(DynamicArray* arr, void* element) {
    if(arr->noOfElements == arr->capacity) {
        resize(arr, (arr->capacity) * 2);
    }
    void* target = (char*)arr->data + (arr->noOfElements * arr->element_size);
    memcpy(target, element, arr->element_size);
    (arr->noOfElements)++;
}

// Remove elements from the Array
void removeElement(DynamicArray* arr, size_t index) {
    if(index >= arr->noOfElements) {
        printf("Index out of bounds\n");
        return;
    }
    void* target = (char*)arr->data + (index * arr->element_size);
    void* next = (char*)target + arr->element_size;
    memmove(target, next, (arr->noOfElements - index - 1) * arr->element_size);
    (arr->noOfElements)--;
}

// Destroy the Array
void destroy(DynamicArray* arr) {
    free(arr->data);
    free(arr);
}

int main() {

    // Initialize a Dynamic array for integers
    DynamicArray *arr = init(sizeof(int), 4);

    // Add elements to the Array
    for(int i=1; i <= 10; ++i) {
        addElement(arr, &i);
    }

    // Print the elements
    printf("Array elements: ");
    for(size_t i=0; i<arr->noOfElements; ++i) {
        printf("%d ", ((int*)arr->data)[i]);
    }
    printf("\n");

    // Remove an element
    removeElement(arr, 2);

    // Print the elements after removal
    printf("Array elements after removal: ");
    for(size_t i=0; i<arr->noOfElements; ++i) {
        printf("%d ", ((int*)arr->data)[i]);
    }
    printf("\n");

    // Destroy the Array
    destroy(arr);

    return 0;
}