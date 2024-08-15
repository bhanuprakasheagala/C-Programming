# Custom String Tokenizer in C (`customStrtok`)

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
