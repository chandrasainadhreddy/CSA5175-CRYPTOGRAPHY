#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 1000

void frequencyAnalysis(const char *ciphertext, int freq[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i]) || ispunct(ciphertext[i])) {
            freq[(unsigned char)ciphertext[i]]++;
        }
    }
}
void printFrequency(int freq[]) {
    printf("Character frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i, freq[i]);
        }
    }
}

void substitutionDecode(const char *ciphertext, const char substitution[], char *decoded) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i]) || ispunct(ciphertext[i])) {
            decoded[i] = substitution[(unsigned char)ciphertext[i]];
        } else {
            decoded[i] = ciphertext[i];
        }
    }
    decoded[strlen(ciphertext)] = '\0';  
}

int main() {
     
    const char *ciphertext = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                             "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                             ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
                             "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
 
    char substitution[256];
    for (int i = 0; i < 256; i++) {
        substitution[i] = i; 
    }

    int freq[256] = {0};
    char decoded[MAX_TEXT];
 
    frequencyAnalysis(ciphertext, freq);
    printFrequency(freq);
  
    char ch, replacement;
    printf("\nEnter substitutions (format: original replacement). Enter '0 0' to stop:\n");
    while (1) {
        scanf(" %c %c", &ch, &replacement);
        if (ch == '0' && replacement == '0') break;
        substitution[(unsigned char)ch] = replacement;
    }
 
    substitutionDecode(ciphertext, substitution, decoded);
 
    printf("\nDecoded message:\n%s\n", decoded);

    return 0;
}
