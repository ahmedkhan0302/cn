#include <stdio.h>
#include <string.h>

#define MAX 200

// Function to perform XOR
void xorOperation(char *dividend, const char *divisor, int k) {
    for (int i = 1; i < k; i++)
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
}

// Function to compute CRC
void computeCRC(const char *input, const char *poly, int polyLen) {
    char data[MAX], temp[MAX], crc[MAX];
    int i;

    strcpy(data, input);

    // Append zeros to the data
    int dataLen = strlen(data);
    for (i = 0; i < polyLen - 1; i++)
        data[dataLen + i] = '0';
    data[dataLen + i] = '\0';

    strncpy(temp, data, polyLen);
    temp[polyLen] = '\0';

    for (i = polyLen; i <= strlen(data); i++) {
        if (temp[0] == '1')
            xorOperation(temp, poly, polyLen);
        else
            xorOperation(temp, "0000000000000000", polyLen); // zero divisor

        temp[polyLen - 1] = data[i];
    }

    temp[polyLen - 1] = '\0';
    strcpy(crc, temp);

    // Print result
    printf("CRC: %s\n", crc);
    printf("Transmitted Frame: %s%s\n", input, crc);
}

int main() {
    char input[MAX];
    int choice;

    // CRC-12: x^12 + x^11 + x^3 + x^2 + x + 1 → 1100000001111
    // CRC-16: x^16 + x^15 + x^2 + 1 → 11000000000000101

    while (1) {
        printf("\n--- CRC Calculator ---\n");
        printf("Enter binary data: ");
        scanf("%s", input);

        printf("Choose Polynomial:\n");
        printf("1. CRC-12\n");
        printf("2. CRC-16\n");
        printf("3. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            computeCRC(input, "1100000001111", 13);  // CRC-12 (13 bits)
        else if (choice == 2)
            computeCRC(input, "11000000000000101", 17); // CRC-16 (17 bits)
        else if (choice == 3)
            break;
        else
            printf("Invalid choice.\n");
    }

    return 0;
}
