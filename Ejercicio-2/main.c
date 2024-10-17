#include <stdio.h>
#include <pthread.h>

#define SIZE 3

void *add_row(void *arg);

typedef struct {
    int row;
    int (*mat1)[SIZE];
    int (*mat2)[SIZE];
    int (*result)[SIZE];
} ThreadData;

int main() {
    int mat1[SIZE][SIZE], mat2[SIZE][SIZE], result[SIZE][SIZE];
    pthread_t threads[SIZE];
    ThreadData data[SIZE];

    // Input matrix 1
    printf("Enter elements of matrix 1 (3x3):\n");
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            scanf("%d", &mat1[i][j]);

    // Input matrix 2
    printf("Enter elements of matrix 2 (3x3):\n");
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            scanf("%d", &mat2[i][j]);

    // Create 3 threads to add each row
    for (int i = 0; i < SIZE; i++) {
        data[i].row = i;
        data[i].mat1 = mat1;
        data[i].mat2 = mat2;
        data[i].result = result;
        pthread_create(&threads[i], NULL, add_row, &data[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix
    printf("Resultant matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void *add_row(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int row = data->row;

    for (int j = 0; j < SIZE; j++) {
        data->result[row][j] = data->mat1[row][j] + data->mat2[row][j];
    }

    return NULL;
}
