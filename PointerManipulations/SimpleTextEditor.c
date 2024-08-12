#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to display the current text
void displayText(const char* text) {
    printf("Current Text: %s\n", text);
}

// Function to insert text at a specified position
void insertText(char** text, const char* insert, int position) {
    int originalLength = strlen(*text);
    int insertLength = strlen(insert);

    // Allocate memory to hold the modified string
    *text = realloc(*text, originalLength + insertLength + 1);

    // Shift the part of the string after the position to the right
    memmove(*text + position + insertLength, *text + position, originalLength - position + 1);

    // Copy the new string into the specified position
    memcpy(*text + position, insert, insertLength);
}


// Function to delete a portion of the text
void deleteText(char* text, int position, int length) {
    int originalLength = strlen(text);

    // Shift the part of the string after the deleted portion to the left
    memmove(text + position, text + position + length, originalLength - position - length + 1);
}

// Function to search for a word in the text
int searchWord(const char* text, const char* word) {
    char* pos = strstr(text, word);
    if(pos) {
        return pos - text;
    }

    return -1;
}

// Function to replace a word in the text
void replaceWord(char** text, const char* oldWord, const char* newWord) {
    int position = searchWord(*text, oldWord);

    if(position != -1) {
        deleteText(*text, position, strlen(oldWord));
        insertText(text, newWord, position);
    }
}


int main() {

    char* text = malloc(100*sizeof(char));  // Initial allocation
    strcpy(text, "Hello, this is a simple text editor.");

    displayText(text);

    // Insert text
    insertText(&text, " very", 13);
    displayText(text);

    // Delete text
    deleteText(text, 5, 7);
    displayText(text);

    // Search for a word
    int pos = searchWord(text, "text");
    if(pos != -1){
        printf("Word 'text' found at position %d\n", pos);
    }
    else {
        printf("Word 'text' not found!\n");
    }

    // Replace a word
    replaceWord(&text, "simple", "basic");
    displayText(text);

    // Free allocated memory
    free(text);

    return 0;
}