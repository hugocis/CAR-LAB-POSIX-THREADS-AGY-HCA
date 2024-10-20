#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

typedef struct {
    int id;
    char *string;
    int repeat_count;
} ThreadData; // Struct con los datos a meter para el hilo.

// Funciones a utilizar
void *print_string(void *arg);
void print_string_sequential(ThreadData *data);
void get_time_diff(struct timespec start, struct timespec end, double *seconds);
void RAMCPUTiempo();

int main() {
    int number;
    char str1[100], str2[100];
    pthread_t thread1, thread2;

    while (1) {
        printf("Introduce un número: ");
        scanf("%d", &number);
        getchar(); // Para el /n del scanf
        printf("Introduce primera frase: ");
        fgets(str1, sizeof(str1), stdin);
        printf("Introduce segunda frase: ");
        fgets(str2, sizeof(str2), stdin);

        // Quitar el \n del scanf
        str1[strcspn(str1, "\n")] = 0;
        str2[strcspn(str2, "\n")] = 0;

        // Con el struct, creamos dos estancias para nuestros dos hilos y los llenamos con nuestros hilos.
        ThreadData data1 = {1, str1, number};
        ThreadData data2 = {2, str2, number};

        printf("\n--- Ejecutando con hilos ---\n");
        // Se empieza el reloj
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Se crean los dos hilos con la función y el struc de datos
        pthread_create(&thread1, NULL, print_string, &data1);
        pthread_create(&thread2, NULL, print_string, &data2);

        // Esperamos a que terminen
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        // Medimos la diferencia de tiempo con el reloj
        clock_gettime(CLOCK_MONOTONIC, &end);
        double segundos;
        get_time_diff(start, end, &segundos);
        printf("Total execution time with threads: %.6f seconds\n", segundos);

        // Memoria usada de CPU y RAM
        RAMCPUTiempo();

        printf("\n--- Ejecución Sequencial ---\n");
        // Se empieza el reloj
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Se imprime de forma secuencial
        print_string_sequential(&data1);
        print_string_sequential(&data2);

        // Se calcula ña diferencia de tiempo
        clock_gettime(CLOCK_MONOTONIC, &end);
        get_time_diff(start, end, &segundos);
        printf("Tiempo de ejecución sin hilos: %.6f segundos\n", segundos);

        // Tiempo de CPU y RAM sin hilos.
        RAMCPUTiempo();

        printf("\n");
    }

    return 0;
};

void *print_string(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = 1; i <= data->repeat_count; ++i) {
        printf("Hilo (%d): %d %s\n", data->id, i, data->string);
        sleep(1); // Simulamos tiempo 
    }

    return NULL;
};

void print_string_sequential(ThreadData *data) {
    for (int i = 1; i <= data->repeat_count; ++i) {
        printf("Secuencial (%d): %d %s\n", data->id, i, data->string);
        sleep(1); // Simulamos tiempo
    }
};

void get_time_diff(struct timespec start, struct timespec end, double *seconds) {
    *seconds = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
};

void RAMCPUTiempo() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    // CPU
    double system_cpu_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1e6;
    printf("CPU: %.6f seconds\n", system_cpu_time);

    // RAM
    printf("RAM: %ld KB\n", usage.ru_maxrss);
};
