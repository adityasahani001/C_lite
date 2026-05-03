#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int pos = 0;
int tempCount = 1;

char temps[20][10];   // store all temp variables separately

char* newTemp() {
    sprintf(temps[tempCount], "t%d", tempCount);
    return temps[tempCount++];
}

char* F();
char* T();
char* E();

char* F() {
    char *res = (char*)malloc(10);   // allocate new memory

    if (input[pos] == '(') {
        pos++;
        char* val = E();
        if (input[pos] == ')') pos++;
        return val;
    }

    res[0] = input[pos];
    res[1] = '\0';
    pos++;
    return res;
}

char* T() {
    char* left = F();

    while (input[pos] == '*') {
        pos++;
        char* right = F();

        char* temp = newTemp();
        printf("%s = %s * %s\n", temp, left, right);
        left = temp;
    }

    return left;
}

char* E() {
    char* left = T();

    while (input[pos] == '+') {
        pos++;
        char* right = T();

        char* temp = newTemp();
        printf("%s = %s + %s\n", temp, left, right);
        left = temp;
    }

    return left;
}

int main() {
    printf("Enter expression: ");
    scanf("%s", input);

    printf("\nThree Address Code:\n");
    E();

    return 0;
}