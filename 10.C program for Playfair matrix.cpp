#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#define MATRIX_SIZE 5
 
char playfairMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
 
void findPosition(char c, int *row, int *col) {
    if (c == 'J') c = 'I';  
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (playfairMatrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
} 
void preparePlaintext(const char *plaintext, char *processedText) {
    int i = 0, j = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            processedText[j] = toupper(plaintext[i]);
            if (processedText[j] == 'J') processedText[j] = 'I';  
            j++;
        }
        i++;
    }
    processedText[j] = '\0';
 
    int len = strlen(processedText);
    for (i = 0; i < len; i += 2) {
        if (processedText[i] == processedText[i + 1]) {
            memmove(&processedText[i + 1], &processedText[i], len - i + 1);
            processedText[i + 1] = 'X';
            len++;
        }
    }
    if (len % 2 != 0) {
        processedText[len] = 'X';
        processedText[len + 1] = '\0';
    }
}
 
void encryptPlayfair(const char *processedText, char *ciphertext) {
    int r1, c1, r2, c2;
    for (int i = 0; processedText[i] != '\0'; i += 2) {
        findPosition(processedText[i], &r1, &c1);
        findPosition(processedText[i + 1], &r2, &c2);

        if (r1 == r2) { 
            ciphertext[i] = playfairMatrix[r1][(c1 + 1) % MATRIX_SIZE];
            ciphertext[i + 1] = playfairMatrix[r2][(c2 + 1) % MATRIX_SIZE];
        } else if (c1 == c2) { 
            ciphertext[i] = playfairMatrix[(r1 + 1) % MATRIX_SIZE][c1];
            ciphertext[i + 1] = playfairMatrix[(r2 + 1) % MATRIX_SIZE][c2];
        } else {
            
            ciphertext[i] = playfairMatrix[r1][c2];
            ciphertext[i + 1] = playfairMatrix[r2][c1];
        }
    }
    ciphertext[strlen(processedText)] = '\0';  
}

int main() {
    const char *plaintext = "Must see you over Cadogan West. Coming at once.";
    char processedText[100];
    char ciphertext[100];
 
    preparePlaintext(plaintext, processedText);
    printf("Processed Plaintext: %s\n", processedText);
 
    encryptPlayfair(processedText, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
