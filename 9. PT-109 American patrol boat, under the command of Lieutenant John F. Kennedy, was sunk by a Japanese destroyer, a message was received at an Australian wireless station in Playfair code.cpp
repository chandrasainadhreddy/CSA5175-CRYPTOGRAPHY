#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
void generateMatrix(const char *key, char matrix[5][5]) {
    int used[26] = {0};
    int i, j, k = 0;
 
    for (i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';  
        if (!used[c - 'A']) {
            matrix[k / 5][k % 5] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }
 
    for (i = 0; i < 26; i++) {
        if (i + 'A' == 'J') continue; 
        if (!used[i]) {
            matrix[k / 5][k % 5] = i + 'A';
            used[i] = 1;
            k++;
        }
    }
}
 
void findPosition(char matrix[5][5], char c, int *row, int *col) {
    if (c == 'J') c = 'I'; 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
 
void decryptDigraph(char a, char b, char matrix[5][5], char *out) {
    int r1, c1, r2, c2;
    findPosition(matrix, a, &r1, &c1);
    findPosition(matrix, b, &r2, &c2);

    if (r1 == r2) { 
        out[0] = matrix[r1][(c1 + 4) % 5];
        out[1] = matrix[r2][(c2 + 4) % 5];
    } else if (c1 == c2) { 
        out[0] = matrix[(r1 + 4) % 5][c1];
        out[1] = matrix[(r2 + 4) % 5][c2];
    } else { 
        out[0] = matrix[r1][c2];
        out[1] = matrix[r2][c1];
    }
}
 
void decryptPlayfair(const char *ciphertext, char matrix[5][5], char *plaintext) {
    char digraph[2];
    int len = strlen(ciphertext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        if (ciphertext[i] == ' ') {
            i--;
            continue;  
        }
        digraph[0] = toupper(ciphertext[i]);
        digraph[1] = toupper(ciphertext[i + 1]);
        decryptDigraph(digraph[0], digraph[1], matrix, &plaintext[index]);
        index += 2;
    }
    plaintext[index] = '\0';  
}

int main() { 
    const char *key = "PTBOAT";
    const char *ciphertext = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTU"
                             "OLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSON"
                             "SXBOUYWRHEBAAHYUSEDQ";

    char matrix[5][5];
    char plaintext[1000];
 
    generateMatrix(key, matrix); 
    printf("Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
 
    decryptPlayfair(ciphertext, matrix, plaintext);
 
    printf("\nDecrypted Text:\n%s\n", plaintext);

    return 0;
}
