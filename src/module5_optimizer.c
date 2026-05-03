#include <ctype.h>
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
  int n, i, j, k, index, outCount = 0;
  char line[100];
  char left[10], temp_expr[50], clean_left[20], expression[50];
  char output[MAX][50];
  char *p;

  printf("Enter number of TAC lines: ");
  scanf("%d", &n);
  getchar();

  printf("\nEnter TAC lines:\n");

  for (i = 0; i < n; i++) {

    fgets(line, sizeof(line), stdin);

    if (strlen(line) <= 1) {
      i--;
      continue;
    }

    if (sscanf(line, "%[^=]=%[^\n]", left, temp_expr) == 2) {
      p = left + strlen(left) - 1;
      while (p >= left && isspace((unsigned char)*p))
        *p-- = '\0';

      p = left;
      while (*p && isspace((unsigned char)*p))
        p++;

      strcpy(clean_left, p);

      j = 0;
      for (k = 0; temp_expr[k] != '\0'; k++) {
        if (!isspace((unsigned char)temp_expr[k])) {
          expression[j++] = temp_expr[k];
        }
      }
      expression[j] = '\0';

      index = findExpression(expression);

      if (index != -1) {
        sprintf(output[outCount++], "%s = %s", clean_left, result[index]);
      } else {
        strcpy(expr[count], expression);
        strcpy(result[count], clean_left);
        sprintf(output[outCount++], "%s = %s", clean_left, expression);
        count++;
      }
    }
  }

  printf("\nOutput:\n");

  for (i = 0; i < outCount; i++) {
    printf("%s\n", output[i]);
  }

  return 0;
}