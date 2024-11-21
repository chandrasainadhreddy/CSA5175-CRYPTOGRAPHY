#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 8

void encrypt_block(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i]; 
    }
}

void decrypt_block(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i];
    }
}

void ecb_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key, uint8_t *ciphertext) {
    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int i = 0; i < num_blocks; i++) {
        uint8_t block[BLOCK_SIZE] = {0};
        memcpy(block, plaintext + i * BLOCK_SIZE, BLOCK_SIZE);

        encrypt_block(block, key, ciphertext + i * BLOCK_SIZE);
    }
}

void ecb_decrypt(uint8_t *ciphertext, int ciphertext_len, uint8_t *key, uint8_t *plaintext) {
    int num_blocks = (ciphertext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int i = 0; i < num_blocks; i++) {
        uint8_t block[BLOCK_SIZE] = {0};
        memcpy(block, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);

        decrypt_block(block, key, plaintext + i * BLOCK_SIZE);
    }
}

int main() {
    uint8_t plaintext[] = "This is a test message for ECB mode!";
    int plaintext_len = strlen((char *)plaintext);

    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t ciphertext[256] = {0};
    uint8_t decrypted_text[256] = {0};
    ecb_encrypt(plaintext, plaintext_len, key, ciphertext);

    ciphertext[4] ^= 0xFF; 
    ecb_decrypt(ciphertext, plaintext_len, key, decrypted_text);

    printf("Original Plaintext: %s\n", plaintext);
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}
