#include <stdio.h>
#include <string.h>

// Function to compute the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to find the modular inverse of 'a' under modulo 26
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  // Return -1 if no modular inverse exists
}

// Function to encrypt using the Affine Caesar Cipher
char encrypt_affine(char p, int a, int b) {
    if (p >= 'a' && p <= 'z') {
        return (char)((a * (p - 'a') + b) % 26 + 'a');
    } else if (p >= 'A' && p <= 'Z') {
        return (char)((a * (p - 'A') + b) % 26 + 'A');
    }
    return p;  // Return the character as-is if it's not alphabetic
}

// Function to decrypt using the Affine Caesar Cipher
char decrypt_affine(char c, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("Error: No modular inverse exists for a = %d\n", a);
        return c;
    }

    if (c >= 'a' && c <= 'z') {
        return (char)((a_inv * ((c - 'a' - b + 26) % 26)) + 'a');
    } else if (c >= 'A' && c <= 'Z') {
        return (char)((a_inv * ((c - 'A' - b + 26) % 26)) + 'A');
    }
    return c;  // Return the character as-is if it's not alphabetic
}

// Function to encrypt a full message
void encrypt_message(char* plaintext, int a, int b, char* ciphertext) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = encrypt_affine(plaintext[i], a, b);
    }
    ciphertext[i] = '\0';  // Null-terminate the ciphertext string
}

// Function to decrypt a full message
void decrypt_message(char* ciphertext, int a, int b, char* plaintext) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        plaintext[i] = decrypt_affine(ciphertext[i], a, b);
    }
    plaintext[i] = '\0';  // Null-terminate the plaintext string
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;

    // Input plaintext and keys a and b
    printf("Enter the plaintext (only alphabetic characters): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character

    printf("Enter the key a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the key b: ");
    scanf("%d", &b);

    // Check if 'a' is coprime with 26
    if (gcd(a, 26) != 1) {
        printf("Error: 'a' must be coprime with 26 for the encryption to be valid.\n");
        return 1;
    }

    // Encrypt the message
    encrypt_message(plaintext, a, b, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    // Decrypt the message
    char decrypted[100];
    decrypt_message(ciphertext, a, b, decrypted);
    printf("Decrypted plaintext: %s\n", decrypted);

    return 0;
}
