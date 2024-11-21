#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 8

uint8_t IV[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};

void triple_des_encrypt_block(uint8_t *plaintext, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *ciphertext);
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output, int size);

void cbc_encrypt(uint8_t *plaintext, int plaintext_len, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *ciphertext) {
    uint8_t previous_block[BLOCK_SIZE];
    uint8_t current_block[BLOCK_SIZE];
    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE;

    memcpy(previous_block, IV, BLOCK_SIZE); 
    for (int i = 0; i < num_blocks; i++) {
        memset(current_block, 0, BLOCK_SIZE);
        int block_size = (i == num_blocks - 1) ? (plaintext_len % BLOCK_SIZE) : BLOCK_SIZE;
        memcpy(current_block, plaintext + i * BLOCK_SIZE, block_size);

        xor_blocks(current_block, previous_block, current_block, BLOCK_SIZE);

        triple_des_encrypt_block(current_block, key1, key2, key3, ciphertext + i * BLOCK_SIZE);

        memcpy(previous_block, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

void triple_des_encrypt_block(uint8_t *plaintext, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *ciphertext) {
    printf("Encrypting with 3DES (not implemented fully for brevity)\n");
    memcpy(ciphertext, plaintext, BLOCK_SIZE); 
}

int main() {
    uint8_t plaintext[] = "This is a test message for CBC mode!";
    int plaintext_len = strlen((char *)plaintext);
    uint8_t ciphertext[256]; 
    uint8_t key1[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t key2[BLOCK_SIZE] = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    uint8_t key3[BLOCK_SIZE] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};

    cbc_encrypt(plaintext, plaintext_len, key1, key2, key3, ciphertext);

    printf("Ciphertext:\n");
    for (int i = 0; i < ((plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
