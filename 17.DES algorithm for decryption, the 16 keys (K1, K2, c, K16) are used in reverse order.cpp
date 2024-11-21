#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define DES_KEY_SIZE 64
#define DES_BLOCK_SIZE 64
#define NUM_ROUNDS 16
void generateKeys(uint64_t key, uint64_t keys[NUM_ROUNDS]);
uint64_t desFunction(uint64_t halfBlock, uint64_t subKey);
uint64_t permute(uint64_t block, const int *permutation, int size);
uint64_t feistel(uint64_t block, uint64_t subKey);
uint64_t desDecrypt(uint64_t ciphertext, uint64_t keys[NUM_ROUNDS]);

void generateKeys(uint64_t key, uint64_t keys[NUM_ROUNDS]) {
uint64_t desFunction(uint64_t halfBlock, uint64_t subKey) {
    return halfBlock; 
}

uint64_t desDecrypt(uint64_t ciphertext, uint64_t keys[NUM_ROUNDS]) {
    uint64_t left = (ciphertext >> 32) & 0xFFFFFFFF;
    uint64_t right = ciphertext & 0xFFFFFFFF;

    for (int i = NUM_ROUNDS - 1; i >= 0; i--) {
        uint64_t temp = right;
        right = left ^ desFunction(right, keys[i]);
        left = temp;
    }

    return (left << 32) | right;
}

int main() {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t ciphertext = 0x0123456789ABCDEF; 
    uint64_t keys[NUM_ROUNDS];

    generateKeys(key, keys);

    uint64_t plaintext = desDecrypt(ciphertext, keys);
    printf("Decrypted plaintext: %016llX\n", plaintext);
    return 0;
}