#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_CIPHERTEXT_LENGTH 1000

// English letter frequencies in descending order (from most frequent to least frequent)
const char english_frequency[] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'u', 'c', 'm', 'f', 'p', 'b', 'g', 'y', 'v', 'k', 'j', 'x', 'q', 'z'};

// Function to count the frequency of each letter in the ciphertext
void count_frequencies(const char *ciphertext, int freq[ALPHABET_SIZE]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = tolower(ciphertext[i]);
        if (ch >= 'a' && ch <= 'z') {
            freq[ch - 'a']++;
        }
    }
}

// Function to print the letter frequency table
void print_frequencies(int freq[ALPHABET_SIZE]) {
    printf("Letter frequencies:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", 'a' + i, freq[i]);
        }
    }
}

// Function to sort letters by frequency (in descending order)
void sort_by_frequency(int freq[ALPHABET_SIZE], char sorted_letters[ALPHABET_SIZE]) {
    int sorted_freq[ALPHABET_SIZE];
    memcpy(sorted_freq, freq, ALPHABET_SIZE * sizeof(int));

    // Sorting letters based on frequency
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (sorted_freq[i] < sorted_freq[j]) {
                // Swap frequencies
                int temp_freq = sorted_freq[i];
                sorted_freq[i] = sorted_freq[j];
                sorted_freq[j] = temp_freq;

                // Swap corresponding letters
                char temp_letter = sorted_letters[i];
                sorted_letters[i] = sorted_letters[j];
                sorted_letters[j] = temp_letter;
            }
        }
    }
}

// Function to generate the best candidate plaintext by mapping frequencies
void generate_plaintext(const char *ciphertext, const char sorted_letters[ALPHABET_SIZE], char *plaintext) {
    int mapping[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[sorted_letters[i] - 'a'] = i;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = tolower(ciphertext[i]);
        if (ch >= 'a' && ch <= 'z') {
            plaintext[i] = 'a' + mapping[ch - 'a'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to attempt multiple substitutions and generate possible plaintexts
void attempt_frequency_attack(const char *ciphertext, int top_n) {
    int freq[ALPHABET_SIZE] = {0};
    count_frequencies(ciphertext, freq);

    // Create an array to store letters sorted by frequency
    char sorted_letters[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_letters[i] = 'a' + i;
    }

    // Sort the letters by their frequency in descending order
    sort_by_frequency(freq, sorted_letters);

    // Try to map the most frequent ciphertext letters to the most frequent English letters
    for (int i = 0; i < top_n; i++) {
        char candidate_plaintext[MAX_CIPHERTEXT_LENGTH];
        generate_plaintext(ciphertext, sorted_letters, candidate_plaintext);
        printf("Possible Plaintext %d:\n%s\n\n", i + 1, candidate_plaintext);
    }
}

int main() {
    char ciphertext[MAX_CIPHERTEXT_LENGTH];
    int top_n;

    // Get ciphertext input from user
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    // Get number of top possible plaintexts to display
    printf("Enter the number of top plaintexts to display: ");
    scanf("%d", &top_n);

    // Attempt the frequency attack
    attempt_frequency_attack(ciphertext, top_n);

    return 0;
}
