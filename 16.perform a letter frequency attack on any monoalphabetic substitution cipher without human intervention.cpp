#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_SIZE 10000
#define ALPHABET_SIZE 26

const char expected_freq[] = "etaoinshrdlcumwfgypbvkjxqz";

void calculate_frequencies(const char *ciphertext, int *freq) {
    for (int i = 0; i < ALPHABET_SIZE; i++) freq[i] = 0;
    
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            freq[tolower(ciphertext[i]) - 'a']++;
        }
    }
}

void sort_by_frequency(int *freq, char *sorted_letters) {
    int freq_copy[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) freq_copy[i] = freq[i];
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int max_idx = 0;
        for (int j = 1; j < ALPHABET_SIZE; j++) {
            if (freq_copy[j] > freq_copy[max_idx]) {
                max_idx = j;
            }
        }
        sorted_letters[i] = 'a' + max_idx;
        freq_copy[max_idx] = -1; 
    }
}

void generate_plaintext(const char *ciphertext, const char *substitution, char *plaintext) {
    char map[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) map[substitution[i] - 'a'] = expected_freq[i];
    
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = map[tolower(ciphertext[i]) - 'a'] - 'a' + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    int freq[ALPHABET_SIZE];
    char sorted_letters[ALPHABET_SIZE];
    char plaintext[MAX_TEXT_SIZE];
    int num_plaintexts;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("How many top plaintexts would you like to see? ");
    scanf("%d", &num_plaintexts);

    calculate_frequencies(ciphertext, freq);
    sort_by_frequency(freq, sorted_letters);

    printf("\nTop %d possible plaintexts:\n", num_plaintexts);
    for (int i = 0; i < num_plaintexts; i++) {
        generate_plaintext(ciphertext, sorted_letters, plaintext);
        printf("%d: %s\n", i + 1, plaintext);

        if (i < ALPHABET_SIZE - 1) {
            char temp = sorted_letters[i];
            sorted_letters[i] = sorted_letters[i + 1];
            sorted_letters[i + 1] = temp;
        }
    }

    return 0;
}