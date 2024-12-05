#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read the input from user
char* readString() {
    int bufferSize = 10;
    int length = 0;
    char* actualBuffer = malloc(bufferSize * sizeof(char));   // Allocate initial memory

    if(actualBuffer == NULL) {
        printf("Memory allocation failed!!\n");
        return NULL;
    }

    int ch;
    while((ch = getchar()) != '\n' && (ch != EOF)) {
        if(length >= (bufferSize - 1)) {
            bufferSize *= 2;        // Double the size of buffer
            char* newBuffer = realloc(actualBuffer, bufferSize * sizeof(char));

            if(newBuffer == NULL) {
                free(actualBuffer);
                printf("Memory allocation failed!\n");
                return NULL;
            }

            actualBuffer = newBuffer;
        }

        actualBuffer[length++] = ch;
    }

    actualBuffer[length] = '\0';        // Null-terminate the string
    
    return actualBuffer;
}

char* my_strstr(const char* haystack, const char* needle) {
    // If needle is an empty string, return the haystack
    if(*needle == '\0') {
        return (char*)haystack;
    }

    // Iterate through the haystack
    while(*haystack != '\0') {
        const char* h = haystack;
        const char* n = needle;

        // Compare the current character of haystack with needle
        while(*h != '\0' && *n != '\0' && *h == *n) {
            h++;
            n++;
        }

        // If we've reached the end of needle, we've found the match 
        if(*n == '\0') {
            return (char*)haystack;
        }

        haystack++;
    }

    return NULL;
}

int main() {
    
    printf("Enter the main string: \n");
    char* str = readString();
    
    printf("Enter the substring that needs to be searched in the main string: \n");
    char* sub = readString();

    char* result = my_strstr(str, sub);

    if(result) {
        printf("Substring found at: %s\n", result);
    }
    else {
        printf("Substring not found\n");
    }

    return 0;
}