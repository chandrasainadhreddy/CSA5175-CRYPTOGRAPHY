#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000
double englishFrequencies[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
    0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
    0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01970, 0.00074
};

void calculateFrequencies(char *text, int length, double *frequencies) {
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = 0;
    }
    for (i = 0; i < length; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequencies[text[i] - 'a']++;
        }
    }
    for (i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] /= (double) length;
    }
}
double calculateChiSquare(double *frequencies) {
    int i;
    double chiSquare = 0;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        chiSquare += pow((frequencies[i] - englishFrequencies[i]), 2) / englishFrequencies[i];
    }
    return chiSquare;
}

void decrypt(char *ciphertext, int length, int key, char *plaintext) {
    int i;
    for (i = 0; i < length; i++) {
        plaintext[i] = (ciphertext[i] - key - 'a') % 26 + 'a';
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    char plaintext[MAX_TEXT_LENGTH];
    double frequencies[ALPHABET_SIZE];
    double chiSquares[ALPHABET_SIZE];
    int i, j, key, top;

    printf("Enter ciphertext: ");
    fgets(ciphertext, MAX_TEXT_LENGTH, stdin);
    ciphertext[strlen(ciphertext) - 1] = '\0';  
    calculateFrequencies(ciphertext, strlen(ciphertext), frequencies);

    for (key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, strlen(ciphertext), key, plaintext);
        calculateFrequencies(plaintext, strlen(ciphertext), frequencies);
        chiSquares[key] = calculateChiSquare(frequencies);
    }

    printf("Enter number of top plaintexts to display: ");
    scanf("%d", &top);

    for (i = 0; i < ALPHABET_SIZE; i++) {
        for (j = i + 1; j < ALPHABET_SIZE; j++) {
            if (chiSquares[i] > chiSquares[j]) {
                double temp = chiSquares[i];
                chiSquares[i] = chiSquares[j];
                chiSquares[j] = temp;
                int tempKey = i;
                key = j;
            }
        }
    }

    for (i = 0; i < top; i++) {
        decrypt(ciphertext, strlen(ciphertext), i, plaintext);
        printf("Key %d: Chi-Square = %.2f\nPlaintext: %s\n\n", i, chiSquares[i], plaintext);
    }

    return 0;
}
