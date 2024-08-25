/*
The goal is to implement a function char* compressString(char* str) in C that compresses a string by replacing sequences of
the same character with the character followed by the count of its repetitions.

For example, the string "aaabbc" should be compressed to "a3b2c1". However, if the compressed string is not shorter
than the original string, the function should return the original string.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* compressString(char* str) {

    // Calculate the length of the original string
    int originalLength = strlen(str);

    // Allocate memory for the compressed string
    char* compressed = malloc((2 * originalLength + 1) * sizeof(char*));
    if(compressed == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int count = 1;
    int index = 0;

    // Traverse the string and build the compressed version
    for(int i=0; i<originalLength; ++i) {
        if(str[i] == str[i+1]) {
            count++;
        }
        else {
            compressed[index++] = str[i];
            index += sprintf(&compressed[index], "%d", count);
            count = 1;
        }
    }

    compressed[index] = '\0';

    // Compare the lengths of the compressed and original strings
    if(strlen(compressed) >= originalLength) {
        free(compressed);
        return str;
    }
    else {
        return compressed;
    }

}

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

    char* compressed = compressString(inputString);

    if(compressed != NULL) {
        printf("%s\n", compressed);
    }

    free(inputString);

    return 0;
}