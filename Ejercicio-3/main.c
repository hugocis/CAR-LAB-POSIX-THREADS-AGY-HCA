#include <stdio.h>
#include <pthread.h>

#define VECTOR_SIZE 20
#define NUM_THREADS 4

int vector[VECTOR_SIZE];
int target_number;
int occurrences[NUM_THREADS] = {0}; 

void *count_occurrences(void *arg);

typedef struct {
    int start;
    int end;
    int thread_id;
} ThreadData;

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData data[NUM_THREADS];
    int total_occurrences = 0;

    printf("Introduce 20 elementos para el array:\n");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        scanf("%d", &vector[i]);
    }

    printf("Introduce el número a buscar: ");
    scanf("%d", &target_number);

    // Cada hilo que se cree es como se dividirá el array, en este caso 4. 
    int partition_size = VECTOR_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].start = i * partition_size;
        data[i].end = (i + 1) * partition_size;
        data[i].thread_id = i;
        pthread_create(&threads[i], NULL, count_occurrences, &data[i]);
    }

    // Se espera a que terminen los hilos.
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_occurrences += occurrences[i];
    }

    // Se imprime el número total de ocurrencias del número en el array
    printf("Se han encontrado %d en el array: %d\n", target_number, total_occurrences);

    return 0;
}

void *count_occurrences(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int count = 0;

    for (int i = data->start; i < data->end; i++) {
        if (vector[i] == target_number) {
            count++;
        }
    }

    occurrences[data->thread_id] = count;
    return NULL;
}
