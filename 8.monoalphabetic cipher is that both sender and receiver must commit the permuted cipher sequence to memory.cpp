#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
void generateCipherAlphabet(const char *keyword, char cipherAlphabet[]) {
    int i, j = 0;
    int used[26] = {0};  
 
    for (i = 0; i < strlen(keyword); i++) {
        if (isalpha(keyword[i])) {
            char c = toupper(keyword[i]) - 'A';
            if (!used[c]) {
                used[c] = 1;
                cipherAlphabet[j++] = keyword[i];
            }
        }
    }
 
    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            cipherAlphabet[j++] = 'A' + i;
        }
    }
    cipherAlphabet[j] = '\0';  
}
 
void encryptMessage(const char *plaintext, const char *cipherAlphabet, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char c = toupper(plaintext[i]) - 'A';
            ciphertext[i] = cipherAlphabet[c];
        } else {
            ciphertext[i] = plaintext[i];  
        }
    }
    ciphertext[i] = '\0';  
}

int main() {
    const char *keyword = "CIPHER";
    const char *plaintext = "HELLO WORLD";  

    char cipherAlphabet[27];  
    char ciphertext[100];     
 
    generateCipherAlphabet(keyword, cipherAlphabet);

    printf("Cipher Alphabet: %s\n", cipherAlphabet);
 
    encryptMessage(plaintext, cipherAlphabet, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
