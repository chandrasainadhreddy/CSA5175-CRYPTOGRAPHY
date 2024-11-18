#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesarCipher(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if (isupper(ch)) {
            text[i] = (ch - 'A' + shift) % 26 + 'A';
        }
        
        else if (islower(ch)) {
            text[i] = (ch - 'a' + shift) % 26 + 'a';
        }
    
    }
}

int main() {
    char text[100];
    int k;

    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    printf("Enter shift value (1-25): ");
    scanf("%d", &k);

    if (k < 1 || k > 25) {
        printf("Shift value must be between 1 and 25.\n");
        return 1;
    }

    caesarCipher(text, k);
    printf("Encrypted text: %s\n", text);

    return 0;
}
