#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

// English letter frequency (approximate percentages)
const double englishFreq[ALPHABET_SIZE] = {
    0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002,
    0.005, 0.040, 0.024, 0.067, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091,
    0.028, 0.010, 0.024, 0.001, 0.020, 0.000
};

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

// Function to sort the frequency array and return the sorted indices
void sortFrequencies(int frequency[ALPHABET_SIZE], int sortedIndices[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i; // Initialize sorted indices
    }

    // Simple bubble sort to sort the frequencies and indices
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = 0; j < ALPHABET_SIZE - i - 1; j++) {
            if (frequency[sortedIndices[j]] < frequency[sortedIndices[j + 1]]) {
                // Swap indices
                int temp = sortedIndices[j];
                sortedIndices[j] = sortedIndices[j + 1];
                sortedIndices[j + 1] = temp;
            }
        }
    }
}

// Function to generate possible plaintexts based on frequency analysis
void generatePlaintexts(const char *ciphertext, int sortedIndices[ALPHABET_SIZE], char plaintexts[MAX_PLAINTEXTS][100]) {
    char substitution[ALPHABET_SIZE];
    for (int i = 0; i < MAX_PLAINTEXTS; i++) {
        // Create a substitution mapping based on sorted indices
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            substitution[sortedIndices[j]] = 'A' + j; // Map sorted letter to 'A', 'B', 'C', ...
        }

        // Decrypt the ciphertext using the substitution
        for (int k = 0; ciphertext[k] != '\0'; k++) {
            if (ciphertext[k] >= 'A' && ciphertext[k] <= 'Z') {
                plaintexts[i][k] = substitution[ciphertext[k] - 'A'];
            } else {
                plaintexts[i][k] = ciphertext[k]; // Non-alphabetic characters remain unchanged
            }
        }
        plaintexts[i][strlen(ciphertext)] = '\0'; // Null-terminate the plaintext
    }
}

// Function to display the top N possible plaintexts
void displayTopPlaintexts(const char *ciphertext, int n) {
    int frequency[ALPHABET_SIZE];
    calculateFrequency(ciphertext, frequency);

    int sortedIndices[ALPHABET_SIZE];
    sortFrequencies(frequency, sortedIndices);

    char plaintexts[MAX_PLAINTEXTS][100];
    generatePlaintexts(ciphertext, sortedIndices, plaintexts);

    printf("\nPossible plaintexts based on letter frequency attack:\n");
    for (int i = 0; i < n; i++) {
        printf("Plaintext %d: %s\n", i + 1, plaintexts[i]);
    }
}

int main() {
    char ciphertext[100];
    int topN;

    printf("Enter ciphertext (uppercase A-Z): ");
    scanf("%s", ciphertext);

    // Display the top N possible plaintexts
    printf("How many top plaintexts do you want to see? (max %d): ", MAX_PLAINTEXTS);
    scanf("%d", &topN);
    if (topN > MAX_PLAINTEXTS) {
        topN = MAX_PLAINTEXTS; // Limit to MAX_PLAINTEXTS
    }

    displayTopPlaintexts(ciphertext, topN);

    return 0;
}