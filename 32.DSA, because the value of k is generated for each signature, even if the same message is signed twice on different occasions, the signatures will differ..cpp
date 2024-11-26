#include <stdio.h>
#include <stdlib.h>
#include <time.h>0
unsigned long rsa_sign(unsigned long message, unsigned long d, unsigned long n) {
    unsigned long signature = 1;
    for (unsigned long i = 0; i < d; i++) {
        signature = (signature * message) % n;  
    }
    return signature;
}

unsigned long dsa_sign(unsigned long message, unsigned long x, unsigned long p, unsigned long q) {
    unsigned long k = rand() % (q - 1) + 1;  
    unsigned long r = (k * message) % p;  
    unsigned long s = (k * r + x) % q;    
    return s;  
}

int main() {
    srand(time(0));

    unsigned long rsa_message = 1234;
    unsigned long rsa_d = 555, rsa_n = 7919;  
    unsigned long dsa_message = 1234;
    unsigned long dsa_x = 123, dsa_p = 7919, dsa_q = 101;  
    unsigned long rsa_signature1 = rsa_sign(rsa_message, rsa_d, rsa_n);
    unsigned long rsa_signature2 = rsa_sign(rsa_message, rsa_d, rsa_n);

    unsigned long dsa_signature1 = dsa_sign(dsa_message, dsa_x, dsa_p, dsa_q);
    unsigned long dsa_signature2 = dsa_sign(dsa_message, dsa_x, dsa_p, dsa_q);

    printf("RSA Signature 1: %lu\n", rsa_signature1);
    printf("RSA Signature 2: %lu\n", rsa_signature2);
    printf("Do RSA signatures match? %s\n", (rsa_signature1 == rsa_signature2) ? "Yes" : "No");

    printf("\nDSA Signature 1: %lu\n", dsa_signature1);
    printf("DSA Signature 2: %lu\n", dsa_signature2);
    printf("Do DSA signatures match? %s\n", (dsa_signature1 == dsa_signature2) ? "Yes" : "No");

    return 0;
}
