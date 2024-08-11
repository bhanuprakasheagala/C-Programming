#include <stdio.h>

/*
   - We start with a pointer pointing to the beginning of the string.
   - We iterate through the string until we encounter the null character `'\0'`.
   - The difference between the current pointer and the starting pointer gives us the string length.
*/

int stringLength(const char* str) {
    const char* ptr = str;
    while(*ptr != '\0') {
        ptr++;
    }

    return ptr-str;
}

/*
   - We copy each character from the source string (`src`) to the destination string (`dest`) using pointers.
   - The loop continues until the null character in the source string is reached.
   - Finally, we ensure that the destination string is null-terminated.
*/
void stringCopy(char* dest, const char* src) {
    while(*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

/*
   - First, we move the destination pointer (`dest`) to the end of the first string.
   - Then, we copy each character from the source string (`src`) to the end of the destination string.
   - After copying, we null-terminate the concatenated string.
*/
void stringConcat(char* dest, const char* src) {
    while(*dest != '\0') {
        dest++;
    }
    while(*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

/*
   - We compare the strings character by character using pointers.
   - The loop continues as long as the characters are equal and neither of the strings has ended (`*str1 && (*str1 == *str2)`).
   - If a difference is found, we return the difference between the ASCII values of the first unmatched characters.
*/
int stringCompare(const char* str1, const char* str2) {
    while(*str1 && (str1 == str2)) {
        str1++;
        str2++;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

/*
   - We use two pointers: one at the beginning (`str`) and one at the end (`end`) of the string.
   - We swap the characters at these pointers and move the pointers towards each other until they meet or cross.
   - This effectively reverses the string in place.
*/
void stringReverse(char* str) {
    char* end = str + stringLength(str)-1;
    char temp;

    while(str < end) {
        temp = *str;
        *str = *end;
        *end = temp;

        str++;
        end--;
    }
}

// Main function to demonstrate the string operations
int main() {
    char str1[20] = "Hello";
    char str2[20] = "World";
    char str3[30];

    // String Length
    printf("Length of str1: %d\n", stringLength(str1));

    // String Copy
    stringCopy(str3, str1);
    printf("Copied string: %s\n", str3);

    // String Concatenation
    stringConcat(str1, str2);
    printf("Concatenated string: %s\n", str1);

    // String Comparison
    int cmpResult = stringCompare(str1, str2);
    if(cmpResult == 0) {
        printf("Strings are equal\n");
    }
    else if(cmpResult < 0) {
        printf("%s is less than %s\n", str1, str2);
    }
    else {
        printf("%s is greater than %s\n", str1, str2);
    }

    // String Reverse
    stringReverse(str1);
    printf("Reversed string: %s\n", str1);

    return 0;
}