#include <stdio.h>
#include <stdlib.h>

int mod26Determinant(int mat[2][2]) {
    return (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) % 26;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void matrixInverse(int key[2][2], int inverse[2][2]) {
    int det = mod26Determinant(key);
    int detInv = modInverse(det, 26);
    
    if (detInv == -1) {
        printf("Inverse does not exist!\n");
        return;
    }
    
    inverse[0][0] = (key[1][1] * detInv) % 26;
    inverse[0][1] = (-key[0][1] * detInv + 26) % 26;
    inverse[1][0] = (-key[1][0] * detInv + 26) % 26;
    inverse[1][1] = (key[0][0] * detInv) % 26;
}

void matrixMultiply(int matrix[2][2], int vector[2], int result[2]) {
    result[0] = (matrix[0][0] * vector[0] + matrix[0][1] * vector[1]) % 26;
    result[1] = (matrix[1][0] * vector[0] + matrix[1][1] * vector[1]) % 26;
}

void breakHillCipher(int P1[2], int C1[2], int P2[2], int C2[2], int key[2][2]) {
  
    int M[2][2] = {{P1[0], P1[1]}, {P2[0], P2[1]}};  
    int C[2][2] = {{C1[0], C1[1]}, {C2[0], C2[1]}};  
    
    int M_inv[2][2];
    matrixInverse(M, M_inv);  
    
    int temp[2];
    matrixMultiply(M_inv, C1, temp);
    key[0][0] = temp[0];
    key[0][1] = temp[1];
    
    matrixMultiply(M_inv, C2, temp);
    key[1][0] = temp[0];
    key[1][1] = temp[1];
}

void printMatrix(int mat[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int P1[2] = {12, 4};  
    int C1[2] = {14, 18}; 

    int P2[2] = {19, 7}; 
    int C2[2] = {0, 18};  

    int key[2][2] = {{0}};

    breakHillCipher(P1, C1, P2, C2, key);

    printf("Key Matrix: \n");
    printMatrix(key);

    return 0;
}
