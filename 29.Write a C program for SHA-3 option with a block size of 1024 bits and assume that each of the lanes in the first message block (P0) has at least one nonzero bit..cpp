#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define STATE_SIZE 25  
#define LANE_BITS 64    
#define BLOCK_SIZE 1024 
#define RATE 1024       
#define CAPACITY (1600 - RATE) 

int all_capacity_nonzero(uint64_t state[STATE_SIZE], int rate_lanes) {
    for (int i = rate_lanes; i < STATE_SIZE; i++) {
        if (state[i] == 0) return 0; 
    }
    return 1; 
}

void xor_random_block(uint64_t state[STATE_SIZE], int rate_lanes) {
    for (int i = 0; i < rate_lanes; i++) {
        uint64_t random_data = ((uint64_t)rand() << 32) | rand(); 
        state[i] ^= random_data;
    }
}

int main() {
    srand(time(NULL)); 

    uint64_t state[STATE_SIZE] = {0}; 
    int rate_lanes = RATE / LANE_BITS; 
    int iterations = 0;

    printf("Starting simulation...\n");

    while (!all_capacity_nonzero(state, rate_lanes)) {
        xor_random_block(state, rate_lanes);
        iterations++;
    }

    printf("All capacity lanes are nonzero after %d iterations.\n", iterations);

    return 0;
}
