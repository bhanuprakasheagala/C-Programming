/*
Write a function char* substring(char* str, int start, int length) that extracts a substring from a given string str.
The function should return a pointer to the extracted substring.
Concepts: Pointers, string manipulation, dynamic memory allocation.
*/

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

char* substring(char* str, int start, int substrLength, int originalStrLength) {
    if((start < 0) || (start >= originalStrLength) || (substrLength <= 0)) {
        printf("Out of range input!!\n");
        return NULL;
    }

    // Ensure we don't go out of bounds
    if((start + substrLength) > originalStrLength) {
        substrLength = originalStrLength - start;
    }

    char* substr = malloc(substrLength * sizeof(char) + 1);
    if(substr == NULL) {
        printf("Memory allocation failed!!\n");
        return NULL;
    }

    for(int i=0; i<substrLength; ++i) {
        substr[i] = str[start + i];
    }
    substr[substrLength] = '\0';

    return substr;
}

int main() {
    printf("Enter a string: ");
    char* inputString = readString();

    if(inputString != NULL) {
        printf("Entered string is: %s\n", inputString);
        int length = strlen(inputString);
        printf("Length of the original string: %d\n", length);

        int start, substrLength;
        printf("Enter substring start position and substring length: ");
        scanf("%d%d", &start, &substrLength);

        char* substr = substring(inputString, start, substrLength, length);

        if(substr != NULL) {
            printf("Substring starting from %d with the length of %d is: %s\n", start, substrLength, substr);
            free(substr);
        }

        if(inputString != NULL) {
            free(inputString);
        }
    }

    return 0;
}