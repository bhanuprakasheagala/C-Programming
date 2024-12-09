#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_palindrome(const char *str) {
    const char *left = str;
    const char *right = str + strlen(str) - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isalnum(*left)) left++;
        while (left < right && !isalnum(*right)) right--;

        // Compare characters in lowercase
        if (tolower(*left) != tolower(*right)) {
            return 0; // Not a palindrome
        }

        left++;
        right--;
    }
    return 1; // It's a palindrome
}

int main() {
    char str[] = "A man, a plan, a canal: Panama";

    if (is_palindrome(str)) {
        printf("The string is a palindrome.\n");
    } else {
        printf("The string is NOT a palindrome.\n");
    }

    return 0;
}
