#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a string is a palindrome
int isPalindrome(char* inputString) {
    int length = strlen(inputString);

    // Allocate memory for a cleaned version of the string
    char* str = malloc((length + 1) * sizeof(char));
    if (str == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    int index = 0;
    // Normalize the input string: remove non-alphanumeric characters and convert to lowercase
    for (int i = 0; i < length; ++i) {
        if (isalnum((unsigned char)inputString[i])) {  // Use inputString here
            str[index++] = tolower((unsigned char)inputString[i]);
        }
    }
    str[index] = '\0';  // Null-terminate the cleaned string

    // Check for palindrome using two-pointer technique
    int left = 0;
    int right = index - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            free(str);  // Free the allocated memory
            return 0;   // Not a palindrome
        }
        left++;
        right--;
    }

    free(str);  // Free the allocated memory
    return 1;   // It's a palindrome
}

// Function to read the input from the user
char* readString() {
    int bufferSize = 10;
    int length = 0;
    char* actualBuffer = malloc(bufferSize * sizeof(char));  // Allocate initial memory

    if (actualBuffer == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length >= (bufferSize - 1)) {
            bufferSize *= 2;  // Double the size of the buffer
            char* newBuffer = realloc(actualBuffer, bufferSize * sizeof(char));
            if (newBuffer == NULL) {
                free(actualBuffer);
                printf("Memory allocation failed!\n");
                return NULL;
            }
            actualBuffer = newBuffer;
        }

        actualBuffer[length++] = ch;
    }

    actualBuffer[length] = '\0';  // Null-terminate the string

    return actualBuffer;
}

int main() {
    printf("Enter a string: ");
    char* inputString = readString();

    if (inputString != NULL) {
        if (isPalindrome(inputString) == 1) {
            printf("\"%s\" is a palindrome\n", inputString);
        } else {
            printf("\"%s\" is not a palindrome\n", inputString);
        }
        free(inputString);  // Free the input string
    } else {
        printf("Failed to read the input string.\n");
    }

    return 0;
}