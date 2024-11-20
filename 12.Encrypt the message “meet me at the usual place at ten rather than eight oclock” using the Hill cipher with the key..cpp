#include <stdio.h>
#include <string.h>

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
void matrixMultiply(int key[2][2], int pair[2], int result[2]) {
    result[0] = (key[0][0] * pair[0] + key[0][1] * pair[1]) % 26;
    result[1] = (key[1][0] * pair[0] + key[1][1] * pair[1]) % 26;
}

void encrypt(char *plaintext, int key[2][2]) {
    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i += 2) {
        int pair[2] = {plaintext[i] - 'a', plaintext[i + 1] - 'a'};
        int result[2];
        matrixMultiply(key, pair, result);
        printf("%c%c", result[0] + 'a', result[1] + 'a');
    }
    printf("\n");
}

void decrypt(char *ciphertext, int key[2][2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (det < 0) det += 26;

    int detInv = modInverse(det, 26);
    int invKey[2][2] = {
        {(key[1][1] * detInv) % 26, (-key[0][1] * detInv + 26) % 26},
        {(-key[1][0] * detInv + 26) % 26, (key[0][0] * detInv) % 26}
    };

    printf("Decrypted text: ");
    for (int i = 0; i < strlen(ciphertext); i += 2) {
        int pair[2] = {ciphertext[i] - 'a', ciphertext[i + 1] - 'a'};
        int result[2];
        matrixMultiply(invKey, pair, result);
        printf("%c%c", result[0] + 'a', result[1] + 'a');
    }
    printf("\n");
}

int main() {
    char plaintext[] = "meet me at the usual place at ten rather than eight o clock";
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    if (strlen(plaintext) % 2 != 0) {
        strcat(plaintext, "x");
    }

    printf("Plaintext: %s\n", plaintext);
    encrypt(plaintext, key);

    char ciphertext[] = "ciphertext_from_above"; 
    decrypt(ciphertext, key);

    return 0;
}
