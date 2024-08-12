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

/*

### Example

Imagine you have the following text:

```c
char *text = "Hello, World!";
```

You want to insert the word `"beautiful "` at position `7`, so the new text should become `"Hello, beautiful World!"`.

### Initial State

Before the `insertText` function is called, the memory for `text` looks something like this:

```
Memory Address | Content
-------------------------
0x1000         | 'H'
0x1001         | 'e'
0x1002         | 'l'
0x1003         | 'l'
0x1004         | 'o'
0x1005         | ','
0x1006         | ' '
0x1007         | 'W'
0x1008         | 'o'
0x1009         | 'r'
0x100A         | 'l'
0x100B         | 'd'
0x100C         | '!'
0x100D         | '\0' (null terminator)
```

### Step 1: Calculating Lengths

- **Original Text Length**: `13` (including the null terminator `'\0'`)
- **Insert Text Length**: `"beautiful "` is `10` characters long.

### Step 2: Reallocating Memory

To insert `"beautiful "` at position `7`, the `realloc` function increases the size of the memory block to accommodate the new text:

- **New Total Length**: `23` (Original `13` + Insert `10`)

After reallocation, the memory for `text` now has space for the new string, but the content hasn't been fully updated yet:

```
Memory Address | Content
-------------------------
0x1000         | 'H'
0x1001         | 'e'
0x1002         | 'l'
0x1003         | 'l'
0x1004         | 'o'
0x1005         | ','
0x1006         | ' '
0x1007         | (Empty or old content)
...
0x1019         | '\0' (new null terminator)
```

### Step 3: Shifting Existing Text

To make space for `"beautiful "`, the function shifts the text starting from position `7` (where `"World!"` begins) to the right:

```
Memory Address | Content
-------------------------
0x1000         | 'H'
0x1001         | 'e'
0x1002         | 'l'
0x1003         | 'l'
0x1004         | 'o'
0x1005         | ','
0x1006         | ' '
0x1007         | 'W'
0x1008         | 'o'
0x1009         | 'r'
0x100A         | 'l'
0x100B         | 'd'
0x100C         | '!'
0x100D         | '\0'
```

After shifting:

```
Memory Address | Content
-------------------------
0x1000         | 'H'
0x1001         | 'e'
0x1002         | 'l'
0x1003         | 'l'
0x1004         | 'o'
0x1005         | ','
0x1006         | ' '
0x1007         | (Empty space, shifted text begins here)
...
0x1011         | 'W'
0x1012         | 'o'
0x1013         | 'r'
0x1014         | 'l'
0x1015         | 'd'
0x1016         | '!'
0x1017         | '\0'
```

### Step 4: Copying the Insert Text

Now, `"beautiful "` is copied into the space starting from position `7`:

```
Memory Address | Content
-------------------------
0x1000         | 'H'
0x1001         | 'e'
0x1002         | 'l'
0x1003         | 'l'
0x1004         | 'o'
0x1005         | ','
0x1006         | ' '
0x1007         | 'b'
0x1008         | 'e'
0x1009         | 'a'
0x100A         | 'u'
0x100B         | 't'
0x100C         | 'i'
0x100D         | 'f'
0x100E         | 'u'
0x100F         | 'l'
0x1010         | ' '
0x1011         | 'W'
0x1012         | 'o'
0x1013         | 'r'
0x1014         | 'l'
0x1015         | 'd'
0x1016         | '!'
0x1017         | '\0'
```

### Final State

After inserting `"beautiful "` at position `7`, the final string is:

```
"Hello, beautiful World!"
```
*/