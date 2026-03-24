#include <stdio.h>
#include <ctype.h>

char input[100];
int pos = 0;

int E(), T(), F();

int F() {
    int value;

    if (input[pos] == '(') {
        pos++;
        value = E();
        if (input[pos] == ')')
            pos++;
        return value;
    }

    else if (isdigit(input[pos])) {
        value = input[pos] - '0';
        pos++;
        return value;
    }

    return 0;
}

int T() {
    int value = F();

    while (input[pos] == '*') {
        pos++;
        value = value * F();
    }

    return value;
}

int E() {
    int value = T();

    while (input[pos] == '+') {
        pos++;
        value = value + T();
    }

    return value;
}

int main() {
    printf("Enter expression: ");
    scanf("%s", input);

    int result = E();

    printf("Result: %d\n", result);

    return 0;
}