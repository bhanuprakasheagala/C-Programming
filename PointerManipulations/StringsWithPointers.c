#include <stdio.h>

int stringLength(const char* str) {
    const char* ptr = str;
    while(*ptr != '\0') {
        ptr++;
    }

    return ptr-str;
}

void stringCopy(char* dest, const char* src) {
    while(*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

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

int stringCompare(const char* str1, const char* str2) {
    while(*str1 && (str1 == str2)) {
        str1++;
        str2++;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

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