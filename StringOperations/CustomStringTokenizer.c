/*
Problem: Implement a function similar to strtok called char* customStrtok(char* str, const char* delimiters).
The function should split a string into tokens based on the given delimiter characters.

Concepts: Pointers, string parsing, memory manipulation.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* customStrtok(char* str, const char* delimeters) {
    static char* nextToken = NULL;

    // If str not NULL, start tokenizing the new string
    if(str != NULL) {
        nextToken = str;
    }

    // If no string to tokenize, return NULL
    if(nextToken == NULL) {
        return NULL;
    }

    // Skip leading delimeters
    nextToken += strspn(nextToken, delimeters);

    // If we've reached the end of the string, return NULL
    if(*nextToken == '\0') {
        return NULL;
    }

    // Find the end of the current token
    char* tokenStart = nextToken;
    nextToken = tokenStart + strcspn(tokenStart, delimeters);

    // If a delimeter is found, null-terminate the current token
    if(*nextToken != '\0') {
        *nextToken = '\0';
        nextToken++;
    }
    else {
        // If no delimeter is found, set nextToken to NULL
        nextToken = NULL;
    }
    
    return tokenStart;
}

// Function to read the input from user
char* readString() {
    int bufferSize = 10;
    int length = 0;
    char* actualBuffer = malloc(bufferSize * sizeof(char));

    if(actualBuffer == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) {
        if(length >= (bufferSize - 1)) {
            bufferSize *= 2;
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

    actualBuffer[length] = '\0';

    return actualBuffer;

}

int main() {

    printf("Enter a string: ");
    char* inputString = readString();
    const char* delimeters = " ,.!";

    char* token = customStrtok(inputString, delimeters);

    while(token != NULL) {
        printf("Token: %s\n", token);
        token = customStrtok(NULL, delimeters);
    }

    free(inputString);

    return 0;
}