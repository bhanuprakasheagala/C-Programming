# 1. Custom Substring Extraction in C (`substring`)

This is an implementation of a custom substring extraction function in C, named `substring`. The purpose of this project is to practice string manipulation, memory management, and pointer arithmetic in C by implementing a function that extracts a portion of a string based on a specified start position and length.

## Table of Contents

- [Introduction](#introduction)
- [Concepts Covered](#concepts-covered)
- [Function Syntax](#function-syntax)
- [How It Works Internally](#how-it-works-internally)
- [Example Usage](#example-usage)
- [Applications](#applications)

## Introduction

String manipulation is a fundamental skill in C programming. Extracting a substring from a given string is a common task, often required in text processing, data parsing, and similar operations. The `substring` function implemented here serves as a practical example of how to work with strings and pointers in C, handling edge cases and ensuring memory safety.

## Concepts Covered

- **String Manipulation**: Techniques for extracting portions of strings.
- **Pointer Arithmetic**: Navigating and manipulating strings using pointers.
- **Memory Management**: Allocating and freeing memory dynamically to store the extracted substring.
- **Error Handling**: Ensuring the function behaves correctly with invalid inputs.

## Function Syntax

```c
char* substring(char* str, int start, int substrLength, int originalStrLength);
```

- **Parameters**:
  - `str`: The input string from which the substring will be extracted.
  - `start`: The starting index of the substring within the original string (0-based index).
  - `substrLength`: The desired length of the substring.
  - `originalStrLength`: The length of the original string to prevent out-of-bounds access.

- **Return Value**:
  - The function returns a dynamically allocated string containing the extracted substring. If the input is invalid (e.g., start index out of bounds), it returns `NULL`.

## How It Works Internally

The `substring` function operates by performing the following steps:

1. **Input Validation**:
   - The function first checks if the `start` index is within the bounds of the original string and whether the `substrLength` is positive.
   - If the input is invalid, the function prints an error message and returns `NULL`.

2. **Boundary Adjustment**:
   - The function ensures that the requested substring length does not exceed the remaining characters in the original string, adjusting `substrLength` if necessary.

3. **Memory Allocation**:
   - The function allocates memory for the substring, including space for the null terminator (`\0`).

4. **Substring Extraction**:
   - Using a loop, the function copies characters from the original string, starting at the `start` index, into the newly allocated substring buffer.

5. **Null-Termination**:
   - The function adds a null terminator at the end of the substring to ensure it is a valid C string.

6. **Return the Substring**:
   - Finally, the function returns the pointer to the newly created substring.

### Internal Process Illustration

```text
Original String:  "Hello, world!"
Start Index:      7
Substring Length: 5

Steps:
  1. Validate input (7 < length of "Hello, world!")
  2. Adjust length if needed (length is within bounds)
  3. Allocate memory for "world\0"
  4. Copy characters "world"
  5. Return substring "world"
```

## Example Usage

Here are a few code snippets demonstrating how to use the `substring` function:

### Basic Substring Extraction

```c
#include <stdio.h>
#include "substring.h"

int main() {
    char input[] = "Hello, world!";
    int start = 7;
    int length = 5;

    char* result = substring(input, start, length, strlen(input));

    if (result != NULL) {
        printf("Extracted substring: %s\n", result);
        free(result);  // Remember to free the allocated memory
    }

    return 0;
}
```

**Output:**

```
Extracted substring: world
```

### Handling Out-of-Bounds Start Index

```c
#include <stdio.h>
#include "substring.h"

int main() {
    char input[] = "Hello, world!";
    int start = 20;  // Out of bounds
    int length = 5;

    char* result = substring(input, start, length, strlen(input));

    if (result == NULL) {
        printf("Invalid input: start index is out of bounds.\n");
    }

    return 0;
}
```

**Output:**

```
Out of range input!!
Invalid input: start index is out of bounds.
```

### Substring Length Adjustment

```c
#include <stdio.h>
#include "substring.h"

int main() {
    char input[] = "Hello, world!";
    int start = 10;
    int length = 10;  // Longer than remaining characters

    char* result = substring(input, start, length, strlen(input));

    if (result != NULL) {
        printf("Adjusted substring: %s\n", result);
        free(result);
    }

    return 0;
}
```

**Output:**

```
Adjusted substring: ld!
```

## Applications

The `substring` function can be used in various scenarios, including:

- **Text Processing**: Extracting specific parts of text based on known positions.
- **Data Parsing**: Handling substrings within structured data formats like CSV, XML, or JSON.
- **String Manipulation**: Implementing custom string processing algorithms.


# 2. Custom String Tokenizer in C (`customStrtok`)

This is an implementation of a custom string tokenizer function in C, named `customStrtok`, which mimics the behavior of the standard `strtok` function. The purpose of this project is to dive into string manipulation, pointer arithmetic, and state management in C.

## Table of Contents

- [Introduction](#introduction)
- [Concepts Covered](#concepts-covered)
- [Function Syntax](#function-syntax)
- [How It Works Internally](#how-it-works-internally)
- [Example Usage](#example-usage)
- [Applications](#applications)

## Introduction

Tokenizing a string is a common operation in many programming tasks, especially when parsing input. The standard `strtok` function in C is a useful tool for this purpose, but it is not reentrant and can be tricky to use in certain contexts. This project implements a similar function, `customStrtok`, to better understand the underlying mechanics and to provide a customizable alternative.

## Concepts Covered

- **String Manipulation**: Understanding how to modify and manage strings in C.
- **Pointer Arithmetic**: Navigating through strings using pointers.
- **State Management**: Retaining the state between function calls to continue processing the string.
- **Memory Safety**: Ensuring that string manipulations do not cause buffer overflows or other memory issues.

## Function Syntax

```c
char* customStrtok(char* str, const char* delimiters);
```

- **Parameters**:
  - `str`: The input string to be tokenized. On the first call, this should be the string to tokenize. On subsequent calls, it should be `NULL`.
  - `delimiters`: A string containing one or more delimiter characters that separate tokens.

- **Return Value**:
  - The function returns a pointer to the next token found in the string. If no more tokens are available, it returns `NULL`.

## How It Works Internally

`customStrtok` operates similarly to the standard `strtok` function but with a few key differences and improvements:

1. **Initial Call**: When `customStrtok` is first called, it initializes a static pointer to keep track of the current position in the string.
2. **Skipping Delimiters**: The function uses `strspn` to skip over any leading delimiters, moving the pointer to the start of the next token.
3. **Token Identification**: `strcspn` is used to locate the next delimiter, marking the end of the current token.
4. **Null-Termination**: The delimiter is replaced with a null terminator (`\0`) to end the current token.
5. **State Update**: The static pointer is updated to point just after the null terminator, ready for the next call to `customStrtok`.
6. **Subsequent Calls**: The function continues tokenizing the string based on the updated pointer until no more tokens are found, at which point it returns `NULL`.

### Internal Process Illustration

```text
Input String:  "Hello, world! This is a test."
Delimiters:    " ,.!?"

Iteration 1:
  Token: "Hello"
  Next Start: "world! This is a test."

Iteration 2:
  Token: "world"
  Next Start: "This is a test."

...

Iteration 5:
  Token: "test"
  Next Start: NULL (No more tokens)
```

## Example Usage

Here are a few code snippets demonstrating how to use `customStrtok`:

### Basic Tokenization

```c
#include <stdio.h>
#include "customStrtok.h"

int main() {
    char input[] = "Hello, world! This is a test.";
    const char* delimiters = " ,.!";

    char* token = customStrtok(input, delimiters);

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = customStrtok(NULL, delimiters);
    }

    return 0;
}
```

**Output:**

```
Token: Hello
Token: world
Token: This
Token: is
Token: a
Token: test
```

### Handling Multiple Delimiters

```c
#include <stdio.h>
#include "customStrtok.h"

int main() {
    char input[] = ";;Hello,world;;";
    const char* delimiters = ";, ";

    char* token = customStrtok(input, delimiters);

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = customStrtok(NULL, delimiters);
    }

    return 0;
}
```

**Output:**

```
Token: Hello
Token: world
```

## Applications

The `customStrtok` function can be used in various scenarios where string parsing is required, such as:

- **Parsing Command-Line Arguments**: Breaking down command-line inputs into individual arguments.
- **CSV Parsing**: Splitting a CSV string into individual fields.
- **Log Processing**: Tokenizing log entries for further analysis.
