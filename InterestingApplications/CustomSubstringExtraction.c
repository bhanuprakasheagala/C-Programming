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

    char* substr = malloc((substrLength + 1) * sizeof(char));
    if(substr == NULL) {
        printf("Memory allocation failed!!\n");
        return NULL;
    }

    for(int i = 0; i < substrLength; ++i) {
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
        if(scanf("%d%d", &start, &substrLength) != 2) {
            printf("Invalid range inputs!!\n");
            free(inputString);
            return 1;
        }
        
        /* 
        Clear the input buffer to prevent any leftover characters (e.g., '\n') from interfering with subsequent input operations.
        This loop reads and discards all characters in the input buffer until it encounters a newline character '\n'. The newline 
        character is often left behind by scanf() after reading numeric input, and without this step, it could cause the next 
        input function (like getchar() or fgets()) to behave unexpectedly by reading this leftover newline instead of waiting 
        for new input.
        */
        while(getchar() != '\n');

        char* substr = substring(inputString, start, substrLength, length);

        if(substr != NULL) {
            printf("Substring starting from %d with the length of %d is: %s\n", start, substrLength, substr);
            free(substr);
        }

        free(inputString);  // No need to check if inputString is NULL, free(NULL) is safe
    }

    return 0;
}