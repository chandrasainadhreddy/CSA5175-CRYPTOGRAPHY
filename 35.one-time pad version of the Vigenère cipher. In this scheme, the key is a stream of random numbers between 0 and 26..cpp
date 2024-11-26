#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ALPHABET_SIZE 26

// Function to encrypt a character using the one-time pad Vigenère cipher
char encrypt_char(char plaintext_char, int key_value) {
    if (plaintext_char >= 'a' && plaintext_char <= 'z') {
        return (plaintext_char - 'a' + key_value) % ALPHABET_SIZE + 'a';
    } else if (plaintext_char >= 'A' && plaintext_char <= 'Z') {
        return (plaintext_char - 'A' + key_value) % ALPHABET_SIZE + 'A';
    } else {
        // Non-alphabetic characters remain unchanged
        return plaintext_char;
    }
}

// Function to generate a random key stream of a given length
void generate_key(int* key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE;  // Random number between 0 and 25
    }
}

// Function to print the key stream
void print_key(int* key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
}

// Function to encrypt the entire message using the one-time pad Vigenère cipher
void encrypt_message(const char* plaintext, int* key, size_t length, char* ciphertext) {
    for (size_t i = 0; i < length; i++) {
        ciphertext[i] = encrypt_char(plaintext[i], key[i]);
    }
    ciphertext[length] = '\0';  // Null-terminate the ciphertext string
}

int main() {
    // Seed the random number generator for key generation
    srand(time(NULL));

    // Example plaintext message
    char plaintext[] = "Hello, World!";
    size_t length = strlen(plaintext);

    // Generate a key stream of the same length as the plaintext
    int key[length];
    generate_key(key, length);

    // Print the generated key stream
    printf("Generated Key Stream: ");
    print_key(key, length);

    // Encrypt the message using the one-time pad Vigenère cipher
    char ciphertext[length + 1];
    encrypt_message(plaintext, key, length, ciphertext);

    // Print the encrypted ciphertext
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
