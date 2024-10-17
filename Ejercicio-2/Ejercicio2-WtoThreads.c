#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // For measuring time
#include <unistd.h>  // For system info
#include <string.h>  // For string operations

#define SIZE 3  // Define the size of the matrix as 3x3

// Function to add two rows of matrices A and B
void add_row(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE], int row) {
    for (int j = 0; j < SIZE; j++) {
        result[row][j] = A[row][j] + B[row][j];  // Add elements of the corresponding row
    }
}

// Function to get memory usage from /proc/self/status
void get_memory_usage() {
    FILE *file = fopen("/proc/self/status", "r");
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            printf("%s", line);  // Print the memory usage line (Resident Set Size)
            break;
        }
    }
    fclose(file);
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], result[SIZE][SIZE];
    clock_t start, end;
    double cpu_time_used;

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

    // Start measuring execution time
    start = clock();

    // Add each row
    for (int i = 0; i < SIZE; i++) {
        add_row(A, B, result, i);  // Call add_row function for each row
    }

    // Stop measuring execution time
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the result matrix
    printf("\nResultant matrix after addition (A + B):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Print execution time
    printf("\nTime taken to execute: %.4f seconds\n", cpu_time_used);

    // Get and print number of CPU cores
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of processors available: %ld\n", num_cores);

    // Get and print memory usage
    printf("Memory usage (RSS):\n");
    get_memory_usage();

    return 0;
}
