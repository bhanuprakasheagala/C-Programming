/*
Given an array of integers, sort it in such a way that the odd numbers appear first and the even numbers appear later.
The odd numbers should be sorted in descending order and the even numbers should be sorted in ascending order.
*/


#include <stdio.h>
#include <stdlib.h>

int comparator(const void* p, const void* q) {
    // Get the values at the given addresses
    int l = *(const int*)p;
    int r = *(const int*)q;

    // If both odd, put the greater of these two values first
    if((l & 1) && (r & 1)) {
        return (r - l);
    }

    // If both even, put the smaller of two values first
    if(!(l & 1) && !(r & 1)) {
        return (l - r);
    }

    // l is even, put r first
    if(!(l & 1)) {
        return 1;
    }

    // l is odd, put l first
    return -1;
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {

    int arr[] = {1, 6, 5, 2, 3, 9, 4, 7, 8};

    int size = sizeof(arr)/sizeof(arr[0]);
    qsort((void*)arr, size, sizeof(arr[0]), comparator);

    printf("Output Array: \n");
    printArray(arr, size);

    return 0;
}