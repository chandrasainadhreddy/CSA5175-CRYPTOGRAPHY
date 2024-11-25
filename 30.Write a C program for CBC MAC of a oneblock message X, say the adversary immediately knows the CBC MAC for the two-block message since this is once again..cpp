#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16

// Function to calculate CBC MAC
void cbc_mac(unsigned char *key, unsigned char *message, int length, unsigned char *mac) {
    unsigned char block[BLOCK_SIZE];
    unsigned char iv[BLOCK_SIZE] = {0x00};

    // Copy message to block
    memcpy(block, message, length);

    // Pad block if necessary
    for (int i = length; i < BLOCK_SIZE; i++) {
        block[i] = 0x00;
    }

    // Calculate MAC
    for (int i = 0; i < BLOCK_SIZE; i++) {
        mac[i] = block[i] ^ iv[i];
        iv[i] = mac[i];
    }
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                           0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

    unsigned char message[BLOCK_SIZE] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
                                               0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56};

    unsigned char mac[BLOCK_SIZE];

    cbc_mac(key, message, BLOCK_SIZE, mac);

    printf("CBC MAC for message X: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    // Calculate CBC MAC for two-block message X || (X ? T)
    unsigned char two_block_message[2 * BLOCK_SIZE];
    unsigned char xor_result[BLOCK_SIZE];

    // Copy message X to two-block message
    memcpy(two_block_message, message, BLOCK_SIZE);

    // Calculate X ? T
    for (int i = 0; i < BLOCK_SIZE; i++) {
        xor_result[i] = message[i] ^ mac[i];
    }

    // Copy X ? T to two-block message
    memcpy(two_block_message + BLOCK_SIZE, xor_result, BLOCK_SIZE);

    unsigned char two_block_mac[BLOCK_SIZE];
    cbc_mac(key, two_block_message, 2 * BLOCK_SIZE, two_block_mac);

    printf("CBC MAC for two-block message X || (X ? T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", two_block_mac[i]);
    }
    printf("\n");

    return 0;
}
