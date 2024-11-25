#include <stdio.h>
#include <math.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long a = 5;   
    long long q = 23;  

    long long x = 6;   
    long long y = 15;  

    long long A = mod_exp(a, x, q);
    long long B = mod_exp(a, y, q); 

    long long K1 = mod_exp(B, x, q); 
    long long K2 = mod_exp(A, y, q);

    printf("Public parameters: a = %lld, q = %lld\n", a, q);
    printf("Alice's public key: %lld\n", A);
    printf("Bob's public key: %lld\n", B);
    printf("Shared key computed by Alice: %lld\n", K1);
    printf("Shared key computed by Bob: %lld\n", K2);

    if (K1 == K2) {
        printf("Key exchange successful! Shared key: %lld\n", K1);
    } else {
        printf("Key exchange failed.\n");
    }

    return 0;
}
