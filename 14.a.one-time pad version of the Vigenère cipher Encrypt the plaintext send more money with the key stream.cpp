#include <stdio.h>
#include <string.h>

void encryptVigenere(char *plaintext, int *keyStream, int keyLength, char *ciphertext) {
    int textLength = strlen(plaintext);
    
    for (int i = 0; i < textLength; i++) {
        if (plaintext[i] != ' ') {  
            int p = plaintext[i] - 'a';  
            int k = keyStream[i % keyLength]; 
            int c = (p + k) % 26; 
            ciphertext[i] = c + 'a';  
        } else {
            ciphertext[i] = ' ';  
        }
    }
    ciphertext[textLength] = '\0';  
}

int main() {
    char plaintext[] = "send more money";
    int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int keyLength = sizeof(keyStream) / sizeof(keyStream[0]);
    char ciphertext[strlen(plaintext) + 1];
    
    encryptVigenere(plaintext, keyStream, keyLength, ciphertext);
    
    printf("Encrypted Text: %s\n", ciphertext);
    
    return 0;
}
