#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

// Function to calculate the frequency of letters in the ciphertext
void calculateFrequency(const char *ciphertext, int frequency[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i] = 0; // Initialize frequency array
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
        }
    }
}

// Function to decrypt the ciphertext using a given shift
void decryptWithShift(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = (ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the plaintext
}

// Function to display the top N possible plaintexts
void displayTopPlaintexts(const char *ciphertext, int n) {
    char plaintext[100]; // Buffer for plaintext
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decryptWithShift(ciphertext, shift, plaintext);
        printf("Shift %2d: %s\n", shift, plaintext);
        if (shift + 1 >= n) {
            break; // Limit to top N
        }
    }
}

int main() {
    char ciphertext[100];
    int frequency[ALPHABET_SIZE];
    int topN;

    printf("Enter ciphertext (uppercase A-Z): ");
    scanf("%s", ciphertext);

    // Calculate letter frequency
    calculateFrequency(ciphertext, frequency);

    // Display the top N possible plaintexts
    printf("How many top plaintexts do you want to see? (max %d): ", MAX_PLAINTEXTS);
    scanf("%d", &topN);
    if (topN > MAX_PLAINTEXTS) {
        topN = MAX_PLAINTEXTS; // Limit to MAX_PLAINTEXTS
    }

    printf("\nPossible plaintexts based on letter frequency attack:\n");
    displayTopPlaintexts(ciphertext, topN);

    return 0;
}