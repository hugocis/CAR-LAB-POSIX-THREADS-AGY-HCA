#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>       // Necesario para obtener información sobre los CPUs
#include <sys/time.h>    // Usamos esto para medir el tiempo que tarda en ejecutarse el código
#include <unistd.h>      // Para leer sobre el uso de memoria y CPU
#include <stdlib.h>      // Manipular memoria (aunque aquí no se usa mucho)
#include <string.h>      // Para trabajar con cadenas
#include <sys/resource.h> // Para medir uso de CPU con getrusage()

// Definimos algunas funciones auxiliares que vamos a usar después
void *sumar_fila(void *arg);  
void print_memory_use();

// Estructura que pasamos a cada thread (hilo)
typedef struct {
    int row;               // Indica la fila que va a sumar
    int (*mat1)[3];        // Matriz 1
    int (*mat2)[3];        // Matriz 2
    int (*result)[3];      // Matriz donde guardamos el resultado
} ThreadData;

int main() {
    int mat1[3][3], mat2[3][3], result[3][3]; // Tres matrices: dos de entrada, una de salida
    pthread_t threads[3];  // Creamos tres hilos (uno por cada fila)
    ThreadData data[3];    // Y un array de datos que pasaremos a cada hilo

    // Medimos el tiempo antes de comenzar a hacer cualquier cosa
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Esto es solo para ver en cuántos CPUs puede correr el proceso
    cpu_set_t set;
    sched_getaffinity(0, sizeof(cpu_set_t), &set);
    int num_cpus_used = CPU_COUNT(&set); // Cuántos CPUs están disponibles
    printf("Número de CPUs disponibles: %d\n", num_cpus_used);

    // Pedimos al usuario los elementos de la primera matriz
    printf("Introduce elementos de la matriz 1 (3x3):\n");
    for (int i = 0; i < 3; i++) { // Recorremos filas
        for (int j = 0; j < 3; j++) { // Recorremos columnas
            scanf("%d", &mat1[i][j]); // Leemos cada valor
        }
    }

    // Lo mismo para la segunda matriz
    printf("Introduce elementos de la matriz 2 (3x3):\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }

    // Aquí creamos los tres hilos, cada uno sumará una fila
    for (int i = 0; i < 3; i++) {
        data[i].row = i;         // Especificamos qué fila le toca a cada hilo
        data[i].mat1 = mat1;     // Pasamos la referencia de la primera matriz
        data[i].mat2 = mat2;     // Y de la segunda matriz
        data[i].result = result; // También le damos la matriz donde guardará el resultado
        pthread_create(&threads[i], NULL, sumar_fila, &data[i]); // Creamos el hilo
    }

    // Esperamos que todos los hilos terminen antes de continuar
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL); // Espera a que el hilo termine
    }

    // Medimos el tiempo al terminar
    gettimeofday(&end, NULL);

    // Imprimimos la matriz final con el resultado
    printf("Matriz resultante:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", result[i][j]); // Mostramos cada valor de la matriz final
        }
        printf("\n"); // Cambiamos de fila
    }

    // Calculamos el tiempo que ha tardado
    long seconds = (end.tv_sec - start.tv_sec);  // Calculamos los segundos
    long micros = ((seconds * 1000000) + end.tv_usec) - start.tv_usec; // Convertimos a microsegundos
    printf("Tiempo de ejecución: %ld microsegundos\n", micros);

    // Imprimimos el uso de memoria
    print_memory_use();

    return 0; // Finalizamos el programa
};

// Función para que cada hilo sume una fila de las matrices
void *sumar_fila(void *arg) {
    ThreadData *data = (ThreadData *)arg;  // Convertimos el argumento a la estructura de datos
    int row = data->row;  // Recuperamos el número de fila que le toca al hilo

    for (int j = 0; j < 3; j++) {
        data->result[row][j] = data->mat1[row][j] + data->mat2[row][j]; // Sumamos los valores de las dos matrices
    }

    return NULL;
};

// Función para imprimir el uso de memoria
void print_memory_use() {
    FILE* file = fopen("/proc/self/status", "r"); // Abrimos el archivo con el estado del proceso
    if (file == NULL) {
        perror("Error al abrir /proc/self/status");
        return;
    }

    char line[256]; // Buffer para leer línea a línea
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {  // Buscamos la línea con el uso de memoria
            printf("Uso de memoria: %s", line); // Imprimimos la línea que contiene la RAM usada
            break;
        }
    }

    fclose(file); // Cerramos el archivo
};
