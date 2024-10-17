#include <stdio.h>

#define SIZE 3  // Define the size of the matrix as 3x3

// Function to add two rows of matrices A and B
void add_row(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE], int row) {
    for (int j = 0; j < SIZE; j++) {
        result[row][j] = A[row][j] + B[row][j];  // Add elements of the corresponding row
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], result[SIZE][SIZE];

    // Input elements of matrix A
    printf("Enter elements of matrix A (3x3):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    // Input elements of matrix B
    printf("Enter elements of matrix B (3x3):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    // Add each row
    for (int i = 0; i < SIZE; i++) {
        add_row(A, B, result, i);  // Call add_row function for each row
    }

    // Print the result matrix
    printf("\nResultant matrix after addition (A + B):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
