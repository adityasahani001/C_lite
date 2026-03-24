#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 5000

char *keywords[] = {
    "int","float","char","double","void",
    "if","else","switch","case","default",
    "for","while","do","break","continue",
    "return","main",
    "read","print",
    "true","false",
    "const","static",
    "struct","typedef",
    "sizeof",
    "long","short","unsigned","signed",
    "goto","and","or","not",
    NULL
};

int isKeyword(char *word) {
    for (int i = 0; keywords[i] != NULL; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    return 0;
}

int isMultiCharOperator(char *input, int i) {
    if ((input[i]=='=' && input[i+1]=='=') ||
        (input[i]=='!' && input[i+1]=='=') ||
        (input[i]=='<' && input[i+1]=='=') ||
        (input[i]=='>' && input[i+1]=='=') ||
        (input[i]=='+' && input[i+1]=='=') ||
        (input[i]=='-' && input[i+1]=='=') ||
        (input[i]=='&' && input[i+1]=='&') ||
        (input[i]=='|' && input[i+1]=='|'))
        return 1;
    return 0;
}

void lexicalAnalyzer(char *input) {
    int i = 0;
    char buffer[100];

    while (input[i] != '\0') {

        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (input[i]=='/' && input[i+1]=='/') {
            while (input[i]!='\n' && input[i]!='\0')
                i++;
            continue;
        }

        if (isalpha(input[i]) || input[i]=='_') {
            int j = 0;
            while (isalnum(input[i]) || input[i]=='_')
                buffer[j++] = input[i++];
            buffer[j] = '\0';

            if (isKeyword(buffer))
                printf("Token: %s -> KEYWORD\n", buffer);
            else
                printf("Token: %s -> IDENTIFIER\n", buffer);
        }

        else if (isdigit(input[i]) || 
                (input[i]=='-' && isdigit(input[i+1]))) {

            int j = 0;
            if (input[i]=='-')
                buffer[j++] = input[i++];

            int hasDecimal = 0;

            while (isdigit(input[i]) || input[i]=='.') {
                if (input[i]=='.') {
                    if (hasDecimal) break;
                    hasDecimal = 1;
                }
                buffer[j++] = input[i++];
            }

            buffer[j] = '\0';
            printf("Token: %s -> NUMBER\n", buffer);
        }

        else if (isMultiCharOperator(input, i)) {
            printf("Token: %c%c -> OPERATOR\n", input[i], input[i+1]);
            i += 2;
        }

        else {
            printf("Token: %c -> OPERATOR\n", input[i]);
            i++;
        }
    }
}

int main() {
    char input[MAX], fullInput[MAX] = "";

    printf("Enter C-Lite code (Type END to stop):\n");

    while (1) {
        fgets(input, MAX, stdin);
        if (strncmp(input, "END", 3) == 0)
            break;
        strcat(fullInput, input);
    }

    lexicalAnalyzer(fullInput);
    return 0;
}