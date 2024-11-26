#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2 // Size of the key matrix

// Function to get the determinant of a 2x2 matrix
int determinant(int matrix[SIZE][SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

// Function to get the modular inverse of a number
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // If no modular inverse exists
}

// Function to find the adjugate of a 2x2 matrix
void adjugate(int matrix[SIZE][SIZE], int adj[SIZE][SIZE]) {
    adj[0][0] = matrix[1][1];
    adj[0][1] = -matrix[0][1];
    adj[1][0] = -matrix[1][0];
    adj[1][1] = matrix[0][0];
}

// Function to encrypt the plaintext using the Hill cipher
void encrypt(int key[SIZE][SIZE], char* plaintext, char* ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += SIZE) {
        int block[SIZE] = {0};
        for (int j = 0; j < SIZE; j++) {
            if (i + j < len) {
                block[j] = plaintext[i + j] - 'A'; // Convert char to 0-25
            }
        }

        for (int j = 0; j < SIZE; j++) {
            ciphertext[i / SIZE * SIZE + j] = (key[j][0] * block[0] + key[j][1] * block[1]) % 26 + 'A';
        }
    }
    ciphertext[len] = '\0'; // Null-terminate the ciphertext
}

// Function to decrypt the ciphertext using the Hill cipher
void decrypt(int key[SIZE][SIZE], char* ciphertext, char* plaintext) {
    int det = determinant(key);
    int invDet = modInverse(det, 26);
    
    if (invDet == -1) {
        printf("No modular inverse exists. Cannot decrypt.\n");
        return;
    }

    int adj[SIZE][SIZE];
    adjugate(key, adj);

    int invKey[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            invKey[i][j] = (invDet * adj[i][j]) % 26;
            if (invKey[i][j] < 0) invKey[i][j] += 26; // Ensure positive values
        }
    }

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += SIZE) {
        int block[SIZE] = {0};
        for (int j = 0; j < SIZE; j++) {
            if (i + j < len) {
                block[j] = ciphertext[i + j] - 'A'; // Convert char to 0-25
            }
        }

        for (int j = 0; j < SIZE; j++) {
            plaintext[i / SIZE * SIZE + j] = (invKey[j][0] * block[0] + invKey[j][1] * block[1]) % 26 + 'A';
        }
    }
    plaintext[len] = '\0'; // Null-terminate the plaintext
}

int main() {
    int key[SIZE][SIZE] = {{6, 24}, {1, 13}}; // Example key
    char plaintext[100], ciphertext[100], decrypted[100];

    printf("Enter plaintext (uppercase A-Z): ");
    scanf("%s", plaintext);

    // Encrypt the plaintext
    encrypt(key, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(key, ciphertext, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}