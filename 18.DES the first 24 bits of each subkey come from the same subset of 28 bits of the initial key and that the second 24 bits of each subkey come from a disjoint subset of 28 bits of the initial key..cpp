#include <stdio.h>
#include <stdint.h>
#define NUM_SUBKEYS 16
#define KEY_SIZE 64
#define HALF_KEY_SIZE 28
#define SUBKEY_SIZE 48

const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

const int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

const int shifts[NUM_SUBKEYS] = {1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2};

uint32_t leftShift(uint32_t value, int shift) {
    return ((value << shift) | (value >> (HALF_KEY_SIZE - shift))) & ((1U << HALF_KEY_SIZE) - 1);
}

void generateSubkeys(uint64_t key, uint64_t subkeys[NUM_SUBKEYS]) {
    uint64_t permutedKey = 0;
    for (int i = 0; i < 56; i++) {
        permutedKey |= ((key >> (64 - PC1[i])) & 1) << (55 - i);
    }

    uint32_t C = (permutedKey >> 28) & 0xFFFFFFF; 
    uint32_t D = permutedKey & 0xFFFFFFF;       

    for (int i = 0; i < NUM_SUBKEYS; i++) {
        C = leftShift(C, shifts[i]);
        D = leftShift(D, shifts[i]);

        uint64_t combinedKey = (C << 28) | D;
        subkeys[i] = 0;
        for (int j = 0; j < 48; j++) {
            subkeys[i] |= ((combinedKey >> (56 - PC2[j])) & 1) << (47 - j);
        }
    }
}

void printSubkeys(uint64_t subkeys[NUM_SUBKEYS]) {
    for (int i = 0; i < NUM_SUBKEYS; i++) {
        printf("Subkey %2d: %012llX\n", i + 1, subkeys[i]);
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t subkeys[NUM_SUBKEYS];

    generateSubkeys(key, subkeys);

    printSubkeys(subkeys);

    return 0;
}