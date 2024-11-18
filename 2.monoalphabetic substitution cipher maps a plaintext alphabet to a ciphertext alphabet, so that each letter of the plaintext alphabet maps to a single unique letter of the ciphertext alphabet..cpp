#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], char key[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            int index = text[i] - base;
            text[i] = islower(text[i]) ? tolower(key[index]) : toupper(key[index]);
        }
    }
}

int main() {
    char plaintext[100];
    char key[] = "QWERTYUIOPLKJHGFDSAZXCVBNM"; 

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    encrypt(plaintext, key);
    printf("Ciphertext: %s\n", plaintext);

    return 0;
}