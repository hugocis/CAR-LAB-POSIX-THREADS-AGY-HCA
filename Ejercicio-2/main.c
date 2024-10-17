#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>       // Para obtener el conjunto de CPUs
#include <sys/time.h>    // Para medir el tiempo de ejecución
#include <unistd.h>      // Para leer el uso de memoria y CPU
#include <stdlib.h>      // Para manipular memoria
#include <string.h>      // Para manipular cadenas
#include <sys/resource.h> // Para medir uso de CPU con getrusage()

#define SIZE 3

void *add_row(void *arg);
void print_memory_usage();
void print_cpu_usage();

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

    // Medir tiempo de inicio
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Obtener el número de CPUs en las que el proceso puede ejecutarse
    cpu_set_t set;
    sched_getaffinity(0, sizeof(cpu_set_t), &set);
    int num_cpus_used = CPU_COUNT(&set);
    printf("Number of CPUs available for the process: %d\n", num_cpus_used);

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

    // Crear 3 threads para sumar cada fila
    for (int i = 0; i < SIZE; i++) {
        data[i].row = i;
        data[i].mat1 = mat1;
        data[i].mat2 = mat2;
        data[i].result = result;
        pthread_create(&threads[i], NULL, add_row, &data[i]);
    }

    // Esperar a que todos los threads terminen
    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    // Medir tiempo de fin
    gettimeofday(&end, NULL);

    // Imprimir la matriz resultante
    printf("Resultant matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Calcular y mostrar el tiempo de ejecución en milisegundos
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - start.tv_usec;
    printf("Time of execution: %ld microseconds\n", micros);

    // Imprimir el uso de memoria
    print_memory_usage();

    // Imprimir el uso de CPU (porcentaje de tiempo de CPU utilizada)
    print_cpu_usage();

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

// Función para imprimir el uso de memoria
void print_memory_usage() {
    FILE* file = fopen("/proc/self/status", "r");
    if (file == NULL) {
        perror("Failed to open /proc/self/status");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {  // VmRSS contiene la memoria RAM en uso
            printf("Memory usage: %s", line);
            break;
        }
    }

    fclose(file);
}

// Función para imprimir el uso de CPU (usuario y sistema)
void print_cpu_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    long user_time_sec = usage.ru_utime.tv_sec;
    long user_time_usec = usage.ru_utime.tv_usec;
    long sys_time_sec = usage.ru_stime.tv_sec;
    long sys_time_usec = usage.ru_stime.tv_usec;

    printf("CPU usage (user): %ld seconds and %ld microseconds\n", user_time_sec, user_time_usec);
    printf("CPU usage (system): %ld seconds and %ld microseconds\n", sys_time_sec, sys_time_usec);
}
