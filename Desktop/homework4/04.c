#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

void countWords(char *input[], int numLines);

int main() {
    char *input[MAX_LINES];
    char buffer[MAX_WORD_LENGTH];
    int numLines = 0;

    printf("input multiple lines of English chars（end with END）:\n");

    while (numLines < MAX_LINES) {
        fgets(buffer, MAX_WORD_LENGTH, stdin);
        if (strcmp(buffer, "END\n") == 0) {
            break;
        }
        input[numLines] = malloc(strlen(buffer) + 1);
        strcpy(input[numLines], buffer);
        numLines++;
    }

    countWords(input, numLines);

    for (int i = 0; i < numLines; i++) {
        free(input[i]);
    }

    return 0;
}

void countWords(char *input[], int numLines) {
    char *words[MAX_WORDS];
    int counts[MAX_LINES][MAX_WORDS] = {0};
    int totalCounts[MAX_WORDS] = {0};
    int numWords = 0;

    for (int i = 0; i < numLines; i++) {
        char *token = strtok(input[i], " \t\n");
        while (token != NULL) {
         
            int found = 0;
            for (int j = 0; j < numWords; j++) {
                if (strcmp(words[j], token) == 0) {
                    found = 1;
                    counts[i][j]++;
                    totalCounts[j]++;
                    break;
                }
            }
            if (!found) {
                words[numWords] = malloc(strlen(token) + 1);
                strcpy(words[numWords], token);
                counts[i][numWords]++;
                totalCounts[numWords]++;
                numWords++;
            }
            token = strtok(NULL, " \t\n");
        }
    }

    printf("\nword\tcounts per row\ttotal counts\n");
    for (int i = 0; i < numWords; i++) {
        printf("%s\t", words[i]);
        for (int j = 0; j < numLines; j++) {
            printf("%d\t", counts[j][i]);
        }
        printf("%d\n", totalCounts[i]);
        free(words[i]);
    }
}
