#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Para medir el tiempo.
#include <unistd.h> // Para conseguir información del sistema.
#include <string.h> // Para operaciones con strings.

///
/// Definiciones 
///

#define TAM 3 // Definimos la el tamaño de la matriz.

// Función que ayuda a suar dos componentes y meterlos en una fila.
void sumar_fila(int A[TAM][TAM], int B[TAM][TAM], int result[TAM][TAM], int row);
// Función que nos da la información del sistema del /proc/self/status
void get_memory_usage();

///
/// Main 
///

int main()
{
    // Definimos las variables.
    int A[TAM][TAM], B[TAM][TAM], result[TAM][TAM]; // Tamaño de la matriz.
    clock_t start, end;                                   // Para calcular el tiempo.
    double cpu_time_used;

    // Meter los elementos de la matriz A.
    printf("Teclea los elementos de la matriz A (3x3):\n");
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }
    printf("\n");

    // Meter los elementos para la matriz B.
    printf("Teclea los elementos de la matriz B (3x3):\n");
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }
    printf("\n");

    // Se emepieza a calcular el tiempo.
    start = clock();

    // Se suman cada fila de forma secuencial.
    for (int i = 0; i < TAM; i++)
    {
        sumar_fila(A, B, result, i);
    }

    // Se acaba el tiempo.
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Se imprime la matriz resultante.
    printf("\nResultado de la suma (A + B):\n");
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Se imprime el tiempo de ejecución.
    printf("\nTiempo de ejecución: %.4f segundos.\n", cpu_time_used);

    // Imprimir info de la memoria.
    printf("Memoria usada (RSS):\n");
    get_memory_usage();

    return 0;
};

///
/// Funciones 
///

void sumar_fila(int A[TAM][TAM], int B[TAM][TAM], int result[TAM][TAM], int row)
{
    for (int j = 0; j < TAM; j++)
    {
        result[row][j] = A[row][j] + B[row][j]; 
    }
};

void get_memory_usage()
{
    FILE *file = fopen("/proc/self/status", "r");
    char line[128];
    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "VmRSS:", 6) == 0)
        {
            printf("%s", line); 
            break;
        }
    }
    fclose(file);
    printf("\n");
};