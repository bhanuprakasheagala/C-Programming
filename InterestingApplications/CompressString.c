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

/*

Notes on sprintf():

### `sprintf` in C

`sprintf` is a function in the C standard library used to format strings and store the formatted output in a character
array (buffer). Unlike `printf`, which prints the formatted output to the standard output (usually the console), 
`sprintf` writes the formatted data to a string that you provide as a buffer. This makes `sprintf` a useful function for 
constructing strings with specific formatting requirements before using them in your program.

#### Syntax

```c
int sprintf(char *str, const char *format, ...);
```

- **`str`**: A pointer to a character array where the formatted output will be stored.
- **`format`**: A format string containing text to be written to `str`, interspersed with format specifiers 
(like `%d`, `%s`, `%f`).
- **`...`**: A variable number of arguments that are formatted according to the format specifiers in the `format` string.

The function returns the number of characters written to the buffer, excluding the null terminator. 
If an error occurs, a negative value is returned.

#### Key Differences Between `sprintf` and `printf`

- **Output Destination**: 
  - `printf` outputs formatted text to the console (standard output).
  - `sprintf` outputs formatted text to a string (character array).
  
- **Use Cases**: 
  - `printf` is used when you want to display output to the user.
  - `sprintf` is used when you need to prepare a formatted string for further processing, storage, or sending over a network.

#### Examples

1. **Formatting a String with Integer and Float**

```c
#include <stdio.h>

int main() {
    char buffer[50];
    int age = 25;
    float height = 5.9;

    sprintf(buffer, "Age: %d, Height: %.1f", age, height);
    printf("%s\n", buffer);  // Output: Age: 25, Height: 5.9

    return 0;
}
```

In this example, `sprintf` formats the age and height into the `buffer` string. The formatted string is then printed to the console using `printf`.

2. **Building a Complex String**

```c
#include <stdio.h>

int main() {
    char buffer[100];
    char name[] = "Alice";
    int score = 95;

    sprintf(buffer, "Player: %s, Score: %d", name, score);
    printf("%s\n", buffer);  // Output: Player: Alice, Score: 95

    return 0;
}
```

Here, `sprintf` is used to concatenate different types of data (a string and an integer) into a single formatted string.

3. **Creating a Formatted Log Entry**

```c
#include <stdio.h>

int main() {
    char logEntry[100];
    char action[] = "Login";
    char user[] = "john_doe";

    sprintf(logEntry, "[%s] User %s performed %s action.", "2024-08-25 14:30:15", user, action);
    printf("%s\n", logEntry);
    // Output: [2024-08-25 14:30:15] User john_doe performed Login action.

    return 0;
}
```

In this example, `sprintf` is used to create a formatted log entry, combining timestamps, usernames, and actions into a single string. This is especially useful for writing logs or preparing structured data.

#### When to Use `sprintf`

- **Preparing Data for Logging**: Use `sprintf` to format log entries before writing them to a file.
- **Constructing HTTP Headers or Protocol Messages**: When you need to build a protocol message or an HTTP header, `sprintf` allows you to format the required string before sending it over a network.
- **Buffer Management**: If you need to manage output in memory rather than directly printing it, `sprintf` is ideal.
- **Generating Dynamic Strings**: When building dynamic content for a GUI application or creating messages based on user input or program state.
*/