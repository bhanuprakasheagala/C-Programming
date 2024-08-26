# 1. Custom Substring Extraction (`substring`)

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


# 2. Custom String Tokenizer (`customStrtok`)

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

### How It Works Internally

The `strtok` function in C is designed to tokenize a string by breaking it into smaller, manageable pieces called tokens. These tokens are separated by one or more characters known as delimiters. Understanding the internal workings of `strtok` involves delving into how it manages the state between function calls and how it processes the input string.

#### 1. Stateful Function

- **Static Pointer**: The key to `strtok`'s operation is its use of a static pointer, which persists between calls to the function. This static pointer remembers where the last token ended so that the next call to `strtok` can continue from that position.

- **First Call vs. Subsequent Calls**:
  - On the **first call**, `strtok` takes the string to be tokenized as its first argument. It initializes the static pointer to point to the beginning of the string and starts scanning for the first token.
  - On **subsequent calls**, the string argument is passed as `NULL`, which tells `strtok` to continue tokenizing from where it left off (i.e., using the static pointer's current position).

#### 2. Skipping Leading Delimiters

- **strspn Functionality**: `strtok` uses a function like `strspn` internally to skip over any leading characters in the string that match any of the delimiter characters. This ensures that the tokenization starts at the first non-delimiter character.

#### 3. Identifying and Terminating Tokens

- **strcspn Functionality**: Once `strtok` finds the start of a token, it uses a function like `strcspn` to find the next delimiter in the string, marking the end of the token.

- **Null-Termination**:
  - When `strtok` finds a delimiter, it replaces the delimiter with a null terminator (`\0`). This effectively ends the current token and allows the token to be treated as a standalone string.
  - After inserting the null terminator, `strtok` updates the static pointer to the character immediately following the delimiter, ready for the next tokenization call.

#### 4. Returning the Token

- **Return Value**: `strtok` returns a pointer to the start of the current token (i.e., where it began scanning after skipping delimiters). If no more tokens are found, the function returns `NULL`.

#### 5. Edge Cases

- **Consecutive Delimiters**: If delimiters are consecutive (e.g., `,,`), `strtok` will skip over them until it finds a non-delimiter character or reaches the end of the string.
- **End of String**: If `strtok` reaches the end of the string and no more tokens are available, the static pointer is set to `NULL`, and subsequent calls return `NULL` as well.

#### 6. Non-Reentrant Nature

- **Non-Reentrant**: `strtok` is not thread-safe or reentrant because it uses a static variable to maintain state between calls. This means that if `strtok` is used on different strings simultaneously (e.g., in a multi-threaded environment), it will fail to function correctly, as the static pointer will be shared across all calls.

### Example of Internal Process

Consider the string `"Hello, world! This is a test."` with delimiters `", !"`. Here’s how `strtok` would process it internally:

1. **First Call**: 
   - Input: `"Hello, world! This is a test."`, Delimiters: `", !"`
   - Skips leading delimiters (none in this case).
   - Finds "Hello" as the first token, replaces the comma after "Hello" with `\0`, and sets the static pointer to `" world! This is a test."`.
   - Returns `"Hello"`.

2. **Second Call**:
   - Input: `NULL`, Delimiters: `", !"`
   - Continues from `" world! This is a test."`.
   - Skips leading space.
   - Finds "world" as the next token, replaces the exclamation mark after "world" with `\0`, and updates the pointer to `" This is a test."`.
   - Returns `"world"`.

3. **Subsequent Calls**: The process continues until all tokens are extracted or the end of the string is reached, at which point `strtok` returns `NULL`.

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


# 3. String Compression Function

#### Problem Statement

The goal is to implement a function `char* compressString(char* str)` in C that compresses a string by replacing sequences of the same character with the character followed by the count of its repetitions. For example, the string `"aaabbc"` should be compressed to `"a3b2c1"`. However, if the compressed string is not shorter than the original string, the function should return the original string.

### Step-by-Step Implementation

#### 1. Analyze the Input String

- The function needs to traverse the input string to identify sequences of consecutive characters.
- It must count the number of repetitions for each character.

#### 2. Build the Compressed String

- While traversing, the function should build a new string that contains the character followed by its count.
- The length of the new string should be tracked to determine if it is shorter than the original string.

#### 3. Handle Memory Allocation

- Since strings in C are dynamically allocated, you need to ensure enough space for the compressed string. The maximum possible length for the compressed string is roughly twice the length of the original string (if every character is unique and followed by "1").
- Use `malloc` to allocate memory for the compressed string and `free` to release it when no longer needed.

#### 4. Compare Lengths and Return the Result

- If the compressed string is shorter, return it.
- Otherwise, free the allocated memory for the compressed string and return the original string.

### Example Pseudocode

```c
char* compressString(char* str) {
    // Calculate the length of the original string
    int originalLength = strlen(str);
    
    // Allocate memory for the compressed string
    char* compressed = malloc((2 * originalLength + 1) * sizeof(char));
    if (compressed == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int count = 1;
    int index = 0;
    
    // Traverse the string and build the compressed version
    for (int i = 0; i < originalLength; i++) {
        if (str[i] == str[i + 1]) {
            count++;
        } else {
            compressed[index++] = str[i];
            index += sprintf(&compressed[index], "%d", count);
            count = 1;
        }
    }
    
    compressed[index] = '\0';

    // Compare the lengths of the compressed and original strings
    if (strlen(compressed) >= originalLength) {
        free(compressed);
        return str;
    } else {
        return compressed;
    }
}
```

### Edge Cases

- **Single Character Strings**: Input strings like `"a"` or `"bb"` should simply return `"a1"` or `"b2"`, respectively.
- **Empty Strings**: Handle the case where the input string is empty.
- **Memory Allocation Failures**: Always check if `malloc` returns `NULL` and handle this gracefully.

---

### GitHub README for String Compression

Below is a sample README for your `compressString` function.

---

# 3. String Compression in C (`compressString`)

This repository contains an implementation of a string compression function in C, named `compressString`. The function compresses a string by replacing sequences of the same character with the character followed by the count of repetitions. If the compressed string is not shorter than the original, the function returns the original string.

## Table of Contents

- [Introduction](#introduction)
- [Concepts Covered](#concepts-covered)
- [Function Syntax](#function-syntax)
- [How It Works](#how-it-works)
- [Example Usage](#example-usage)
- [Applications](#applications)
  
## Introduction

String compression is a common problem in data processing and compression algorithms. This function provides a simple yet effective way to compress strings by counting repeated characters. The goal is to demonstrate how to manipulate strings, manage memory, and optimize performance in C.

## Concepts Covered

- **String Manipulation**: Techniques for modifying and analyzing strings in C.
- **Memory Management**: Efficient use of `malloc`, `free`, and dynamic memory allocation.
- **Optimization**: Balancing compression effectiveness with performance and memory usage.

## Function Syntax

```c
char* compressString(char* str);
```

- **Parameters**:
  - `str`: The input string to be compressed.

- **Return Value**:
  - The function returns a pointer to the compressed string if it is shorter than the original string. Otherwise, it returns the original string.

## How It Works

The `compressString` function works by:

1. **Counting Repeated Characters**: As the function traverses the string, it counts the occurrences of each character until it encounters a different character.
2. **Building the Compressed String**: For each sequence of repeated characters, the function appends the character and its count to the new string.
3. **Memory Allocation**: The function allocates memory for the compressed string dynamically, ensuring enough space to store the potential output.
4. **Length Comparison**: After building the compressed string, the function compares its length to the original string. If the compressed version is not shorter, the function frees the allocated memory and returns the original string.

### Internal Process Illustration

```text
Original String:  "aaabbc"
Steps:
  1. Count 'a' -> 3 times
  2. Append "a3" to compressed string
  3. Count 'b' -> 2 times
  4. Append "b2" to compressed string
  5. Count 'c' -> 1 time
  6. Append "c1" to compressed string

Final Compressed String: "a3b2c1"
```

## Example Usage

Here are some code snippets demonstrating how to use the `compressString` function:

### Basic Compression

```c
#include <stdio.h>
#include "compressString.h"

int main() {
    char input[] = "aaabbc";
    
    char* compressed = compressString(input);

    if (compressed != NULL) {
        printf("Compressed string: %s\n", compressed);
        if (compressed != input) {
            free(compressed);  // Free the memory if a new string was allocated
        }
    }

    return 0;
}
```

**Output:**

```
Compressed string: a3b2c1
```

### Handling Non-Compressible Strings

```c
#include <stdio.h>
#include "compressString.h"

int main() {
    char input[] = "abcdef";
    
    char* compressed = compressString(input);

    if (compressed != NULL) {
        printf("Compressed string: %s\n", compressed);
        // Since compressed == input, no need to free
    }

    return 0;
}
```

**Output:**

```
Compressed string: abcdef
```

## Applications

The `compressString` function can be applied in:

- **Data Compression**: Reducing the size of repetitive text data.
- **Log File Optimization**: Compressing logs or repetitive textual data to save space.
- **Text Processing**: Preprocessing strings for pattern matching or analysis.
