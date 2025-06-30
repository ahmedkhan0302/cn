#include <stdio.h>
#include <string.h>
#define MAX 100
#define FLAG "flag"
#define ESC "esc"

void characterCount() {
    char input[MAX], output[MAX];
    printf("Enter the message (space separated words): ");
    getchar(); // clear newline
    fgets(input, MAX, stdin);

    int len = strlen(input);
    if (input[len - 1] == '\n') input[len - 1] = '\0';

    sprintf(output, "%lu %s", strlen(input), input);
    printf("Character Count Framed Message: %s\n", output);
}

void bitStuffing() {
    char input[MAX], stuffed[MAX];
    int i, j = 0, count = 0;

    printf("Enter the bit stream: ");
    scanf("%s", input);

    for (i = 0; input[i]; i++) {
        stuffed[j++] = input[i];
        if (input[i] == '1') {
            count++;
            if (count == 5) {
                stuffed[j++] = '0'; // insert 0 after five 1's
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    stuffed[j] = '\0';
    printf("Bit Stuffed Message: %s\n", stuffed);
}

void bitDestuffing() {
    char input[MAX], destuffed[MAX];
    int i, j = 0, count = 0;

    printf("Enter the stuffed bit stream: ");
    scanf("%s", input);

    for (i = 0; input[i]; i++) {
        destuffed[j++] = input[i];
        if (input[i] == '1') {
            count++;
            if (count == 5 && input[i + 1] == '0') {
                i++; // skip the stuffed 0
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    destuffed[j] = '\0';
    printf("Bit Destuffed Message: %s\n", destuffed);
}

void byteStuffing() {
    char word[MAX], stuffed[MAX * 2] = "";
    int n;

    printf("Number of words: ");
    scanf("%d", &n);

    strcat(stuffed, FLAG);
    strcat(stuffed, " ");

    printf("Enter the words:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        if (strcmp(word, FLAG) == 0 || strcmp(word, ESC) == 0) {
            strcat(stuffed, ESC);
            strcat(stuffed, " ");
        }
        strcat(stuffed, word);
        strcat(stuffed, " ");
    }

    strcat(stuffed, FLAG);
    printf("Byte Stuffed Message: %s\n", stuffed);
}

void byteDestuffing() {
    char word[MAX], result[MAX * 2] = "";
    int flagCount = 0, escapeNext = 0;

    printf("Enter stuffed input (space separated):\n");
    getchar(); // clear newline

    while (scanf("%s", word) == 1) {
        if (strcmp(word, ESC) == 0 && !escapeNext) {
            escapeNext = 1;
            continue;
        }

        if (strcmp(word, FLAG) == 0 && !escapeNext) {
            flagCount++;
            if (flagCount == 1) continue;
            if (flagCount == 2) break;
        }

        if (strlen(result) > 0) strcat(result, " ");
        strcat(result, word);
        escapeNext = 0;
    }

    printf("Byte Destuffed Message: %s\n", result);
}

int main() {
    int choice;
    while (1) {
        printf("\nFraming Techniques Menu:\n");
        printf("1. Character Count\n");
        printf("2. Bit Stuffing (Transmitter)\n");
        printf("3. Bit Stuffing (Receiver)\n");
        printf("4. Byte Stuffing (Transmitter)\n");
        printf("5. Byte Stuffing (Receiver)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: characterCount(); break;
            case 2: bitStuffing(); break;
            case 3: bitDestuffing(); break;
            case 4: byteStuffing(); break;
            case 5: byteDestuffing(); break;
            case 6: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
