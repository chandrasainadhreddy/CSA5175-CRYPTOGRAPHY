#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(char *key, char *generatedKey, int length) {
    int keyLength = strlen(key);
    for (int i = 0, j = 0; i < length; i++) {
        if (isalpha(generatedKey[i])) {
            generatedKey[i] = toupper(key[j % keyLength]);
            j++;
        } else {
            generatedKey[i] = generatedKey[i]; 
        }
    }
}

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int length = strlen(plaintext);
    char generatedKey[length];
    strcpy(generatedKey, plaintext);
    generateKey(key, generatedKey, length);

    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char p = toupper(plaintext[i]);
            char k = toupper(generatedKey[i]);
            ciphertext[i] = (p + k - 2 * 'A') % 26 + 'A'; 
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0'; 
}

int main() {
    char plaintext[100], key[100], ciphertext[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    encrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}