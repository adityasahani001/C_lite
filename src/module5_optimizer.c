#include <stdio.h>
#include <string.h>

#define MAX 50

char expr[MAX][50];
char result[MAX][10];
int count = 0;

int findExpression(char *e) {
    for (int i = 0; i < count; i++) {
        if (strcmp(expr[i], e) == 0)
            return i;
    }
    return -1;
}
int main() {
    int n;
    char line[100];
    char left[10], op1[10], op[5], op2[10];

    printf("Enter number of TAC lines: ");
    scanf("%d", &n);
    getchar();

    printf("\nEnter TAC lines:\n");

    char output[MAX][50];
    int outCount = 0;

    for (int i = 0; i < n; i++) {

        fgets(line, sizeof(line), stdin);

        if (strlen(line) <= 1) {
            i--;
            continue;
        }

        sscanf(line, "%s = %s %s %s", left, op1, op, op2);

        char expression[50];
        sprintf(expression, "%s %s %s", op1, op, op2);

        int index = findExpression(expression);

        if (index != -1) {
            sprintf(output[outCount++], "%s = %s", left, result[index]);
        } else {
            strcpy(expr[count], expression);
            strcpy(result[count], left);
            sprintf(output[outCount++], "%s = %s", left, expression);
            count++;
        }
    }

    printf("\nOutput:\n");

    for (int i = 0; i < outCount; i++) {
        printf("%s\n", output[i]);
    }

    return 0;
}