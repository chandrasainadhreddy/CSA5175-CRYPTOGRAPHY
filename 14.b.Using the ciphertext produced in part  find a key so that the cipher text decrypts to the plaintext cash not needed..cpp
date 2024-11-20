#include <stdio.h>
#include <string.h>

void decryptVigenere(char *ciphertext, int *keyStream, int keyLength, char *plaintext) {
    int textLength = strlen(ciphertext);
    
    for (int i = 0; i < textLength; i++) {
        if (ciphertext[i] != ' ') {  
            int c = ciphertext[i] - 'a'; 
            int k = keyStream[i % keyLength]; 
            int p = (c - k + 26) % 26;  
            plaintext[i] = p + 'a';  
        } else {
            plaintext[i] = ' ';  
        }
    }
    plaintext[textLength] = '\0';  
}

int main() {
    char ciphertext[] = "vdoq dnv tllvw";
    int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int keyLength = sizeof(keyStream) / sizeof(keyStream[0]);
    char plaintext[strlen(ciphertext) + 1];
    
    decryptVigenere(ciphertext, keyStream, keyLength, plaintext);
    
    printf("Decrypted Text: %s\n", plaintext);
    
    return 0;
}
