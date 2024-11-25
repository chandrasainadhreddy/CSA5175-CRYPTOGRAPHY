#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8


void key_schedule(uint8_t *key, uint64_t *subkeys) {
}

void feistel_round(uint8_t *left, uint8_t *right, uint64_t subkey) {
}

void des_decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext) {
    uint64_t subkeys[16];
    uint8_t left[BLOCK_SIZE / 2], right[BLOCK_SIZE / 2];
    
    key_schedule(key, subkeys);


    for (int round = 15; round >= 0; round--) { 
        feistel_round(left, right, subkeys[round]);
        
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x13, 0x34, 0x53, 0x79, 0x97, 0xAF, 0x56, 0x3A}; 
    uint8_t ciphertext[BLOCK_SIZE] = {0xD1, 0x9A, 0xF4, 0x1A, 0xD6, 0x65, 0x39, 0x59}; 
    uint8_t plaintext[BLOCK_SIZE];
    
    des_decrypt(ciphertext, key, plaintext);
    
    printf("Decrypted plaintext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    return 0;
}
