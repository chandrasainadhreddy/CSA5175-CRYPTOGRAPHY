#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char *key, char matrix[SIZE][SIZE]) {
    int alpha[26] = {0}; 
    int k = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; 
        if (isalpha(ch) && alpha[ch - 'A'] == 0) {
            alpha[ch - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; 
        if (alpha[ch - 'A'] == 0) {
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
}

void prepareText(char *text, char *preparedText) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = toupper(text[i]);
        if (isalpha(ch)) {
            if (ch == 'J') ch = 'I'; 
            preparedText[j++] = ch;
            if (j > 0 && j % 2 == 1 && text[i + 1] != '\0' && toupper(text[i + 1]) == ch) {
                preparedText[j++] = 'X'; 
            }
        }
    }
    if (j % 2 != 0) {
        preparedText[j++] = 'X'; 
    }
    preparedText[j] = '\0';
}

void encrypt(char *text, char matrix[SIZE][SIZE], char *cipherText) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        char a = text[i];
        char b = text[i + 1];
        int row1, col1, row2, col2;

        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (matrix[r][c] == a) {
                    row1 = r;
                    col1 = c;
                }
                if (matrix[r][c] == b) {
                    row2 = r;
                    col2 = c;
                }
            }
        }

        if (row1 == row2) {
            cipherText[i] = matrix[row1][(col1 + 1) % SIZE];
            cipherText[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            cipherText[i] = matrix[(row1 + 1) % SIZE][col1]; 
            cipherText[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            cipherText[i] = matrix[row1][col2];
            cipherText[i + 1] = matrix[row2][col1];
        }
    }
    cipherText[len] = '\0'; 
}

int main() {
    char key[100], text[100], preparedText[100], cipherText[100];
    char matrix[SIZE][SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; 

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; 

    createMatrix(key, matrix);
    printf("Playfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
		}

    prepareText(text, preparedText);
    encrypt(preparedText, matrix, cipherText);

    printf("Ciphertext: %s\n", cipherText);
    return 0;
}