#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n = 25;
    int row_col_factor = 5; 
    unsigned long long fact_25 = factorial(n);
    
    unsigned long long fact_5 = factorial(row_col_factor);
    unsigned long long symmetry_reduction = fact_5 * fact_5 * 8; 
    unsigned long long unique_keys = fact_25 / symmetry_reduction;
    
    double log2_all_keys = log2((double)fact_25);
    double log2_unique_keys = log2((double)unique_keys);
    
    printf("Total possible keys (ignoring identical results): 2^%.0f\n", log2_all_keys);
    printf("Effectively unique keys (considering identical results): 2^%.0f\n", log2_unique_keys);
    
    return 0;
}
