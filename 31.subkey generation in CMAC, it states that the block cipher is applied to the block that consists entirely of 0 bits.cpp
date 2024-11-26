#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE_128 16  // 128-bit block size
#define BLOCK_SIZE_64 8    // 64-bit block size

// Constants for 128-bit and 64-bit block sizes
#define CONSTANT_128 0x87  // 0x87 for 128-bit block size
#define CONSTANT_64  0x1b  // 0x1b for 64-bit block size

// Function to perform a left shift of 1 bit on a block
void left_shift(uint8_t *block, int block_size) {
    uint8_t carry = 0;
    for (int i = 0; i < block_size; i++) {
        uint8_t next_carry = (block[i] & 0x80) ? 1 : 0; // check the MSB
        block[i] = (block[i] << 1) | carry; // shift and add carry bit
        carry = next_carry; // update carry bit
    }
}

// Function to XOR a block with a constant (for CMAC)
void xor_with_constant(uint8_t *block, uint8_t constant, int block_size) {
    for (int i = 0; i < block_size; i++) {
        block[i] ^= constant;
    }
}

// Function to generate the first and second subkeys for CMAC
void generate_subkeys(uint8_t *L, uint8_t *K1, uint8_t *K2, int block_size) {
    // Generate K1 by left shifting L by 1
    left_shift(L, block_size);
    // If the leftmost bit of L was 1, XOR with the constant
    if (L[0] & 0x80) {
        xor_with_constant(L, (block_size == BLOCK_SIZE_128) ? CONSTANT_128 : CONSTANT_64, block_size);
    }
    // K1 is now stored in L
    for (int i = 0; i < block_size; i++) {
        K1[i] = L[i];
    }

    // Generate K2 by left shifting K1 by 1
    left_shift(K1, block_size);
    // If the leftmost bit of K1 was 1, XOR with the constant
    if (K1[0] & 0x80) {
        xor_with_constant(K1, (block_size == BLOCK_SIZE_128) ? CONSTANT_128 : CONSTANT_64, block_size);
    }
    // K2 is now stored in K1
    for (int i = 0; i < block_size; i++) {
        K2[i] = K1[i];
    }
}

// Utility function to print a block (in hexadecimal)
void print_block(const uint8_t *block, int block_size) {
    for (int i = 0; i < block_size; i++) {
        printf("%02x", block[i]);
    }
    printf("\n");
}

int main() {
    uint8_t L[BLOCK_SIZE_128] = {0};  // 128-bit all zero block
    uint8_t K1[BLOCK_SIZE_128] = {0}; // First subkey
    uint8_t K2[BLOCK_SIZE_128] = {0}; // Second subkey

    printf("Generating subkeys for 128-bit block size...\n");

    // Generate the subkeys for 128-bit block size
    generate_subkeys(L, K1, K2, BLOCK_SIZE_128);

    printf("K1 (128-bit): ");
    print_block(K1, BLOCK_SIZE_128);
    printf("K2 (128-bit): ");
    print_block(K2, BLOCK_SIZE_128);

    // Now, repeat the same process for a 64-bit block size
    uint8_t L64[BLOCK_SIZE_64] = {0};   // 64-bit all zero block
    uint8_t K1_64[BLOCK_SIZE_64] = {0}; // First subkey for 64-bit
    uint8_t K2_64[BLOCK_SIZE_64] = {0}; // Second subkey for 64-bit

    printf("\nGenerating subkeys for 64-bit block size...\n");

    // Generate the subkeys for 64-bit block size
    generate_subkeys(L64, K1_64, K2_64, BLOCK_SIZE_64);

    printf("K1 (64-bit): ");
    print_block(K1_64, BLOCK_SIZE_64);
    printf("K2 (64-bit): ");
    print_block(K2_64, BLOCK_SIZE_64);

    return 0;
}
