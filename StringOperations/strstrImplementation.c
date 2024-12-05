#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* my_strstr(const char* haystack, const char* needle) {
    // If needle is an empty string, return the haystack
    if(*needle == '\0') {
        return (char*)haystack;
    }

    // Iterate through the haystack
    while(*haystack != '\0') {
        const char* h = haystack;
        const char* n = needle;

        // Compare the current character of haystack with needle
        while(*h != '\0' && *n != '\0' && *h == *n) {
            h++;
            n++;
        }

        // If we've reached the end of needle, we've found the match 
        if(*n == '\0') {
            return (char*)haystack;
        }

        haystack++;
    }

    return NULL;
}

int main() {
    char* str = "Hello, World!";
    char* sub = "World";

    char* result = my_strstr(str, sub);

    if(result) {
        printf("Substring found at: %s\n", result);
    }
    else {
        printf("Substring not found\n");
    }

    return 0;
}