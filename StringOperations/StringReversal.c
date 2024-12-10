#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverse_string(const char* str) {
    size_t len = strlen(str);
    char* reversed = (char*)malloc((len + 1) * sizeof(char));

    if(!reversed) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    for(size_t i = 0; i < len; i++) {
        reversed[i] = str[len - i - 1];
    }
    reversed[len] = '\0';

    return reversed;
}

int main() {
    const char* original = "Happy world";
    char* reversed = reverse_string(original);

    if(reversed) {
        printf("Original: %s\n", original);
        printf("Reversed: %s\n", reversed);
        free(reversed);
    }
    return 0;
}