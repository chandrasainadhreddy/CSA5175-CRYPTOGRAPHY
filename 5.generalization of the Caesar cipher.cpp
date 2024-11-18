#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int isAllowedA(int a) {
    return gcd(a, 26) == 1;
}

char encrypt(char p, int a, int b) {
    if (!isAllowedA(a)) {
        printf("Error: a must be coprime to 26.\n");
        exit(1);
    }
    return (char)((a * (p - 'A') + b) % 26 + 'A');
}

int main() {
    char plaintext[100];
    int a, b;

    printf("Enter the plaintext (uppercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    printf("Enter value for a (must be coprime to 26): ");
    scanf("%d", &a);
    printf("Enter value for b (0 to 25): ");
    scanf("%d", &b);

    if (b < 0 || b > 25) {
        printf("Error: b must be between 0 and 25.\n");
        return 1;
    }

    printf("Ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            char c = encrypt(plaintext[i], a, b);
            printf("%c", c);
        } else {
            printf("%c", plaintext[i]); 
        }
    }
    printf("\n");
    return 0;
}