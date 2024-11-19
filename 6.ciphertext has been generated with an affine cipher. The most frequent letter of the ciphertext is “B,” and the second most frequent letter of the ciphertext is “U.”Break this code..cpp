#include <stdio.h>
#include <ctype.h>
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

void decryptAffineCipher(const char *ciphertext, int a, int b) {
    int m = 26; 
    int a_inverse = modInverse(a, m);

    if (a_inverse == -1) {
        printf("Invalid key: modular inverse of a does not exist.\n");
        return;
    }

    printf("Decrypted text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int y = ciphertext[i] - base;
            int x = (a_inverse * (y - b + m)) % m;
            printf("%c", x + base);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

int main() {
    const char *ciphertext = "BUUBUJTFMP";

    int a = 3; 
    int b = 15; 
    decryptAffineCipher(ciphertext, a, b);

    return 0;
}
