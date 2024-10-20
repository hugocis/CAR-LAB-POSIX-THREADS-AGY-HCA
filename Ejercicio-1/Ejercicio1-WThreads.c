#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *print_string(void *arg);

typedef struct {
    int id;
    char *string;
    int repeat_count;
} ThreadData; // Struct con lo que necesita el hilo

int main() {
    int number;
    char str1[100], str2[100];
    pthread_t thread1, thread2;

    while (1) {
        printf("Introduce un número ");
        scanf("%d", &number);
        getchar(); // Para quitar el /n
        printf("Introduce la primera frase: ");
        fgets(str1, sizeof(str1), stdin);
        printf("Introduce la segunda frase: ");
        fgets(str2, sizeof(str2), stdin);

        // Eliminamos el \n del string.
        str1[strcspn(str1, "\n")] = 0;
        str2[strcspn(str2, "\n")] = 0;

        // Creamos, con el struct creado con anterioridad, dos ejemplos que son lo que vamos a crear.
        ThreadData data1 = {1026, str1, number};
        ThreadData data2 = {2051, str2, number};

        // Creamos los dos hilos que hacen la función de imprimir junto con sus datos del struct.
        pthread_create(&thread1, NULL, print_string, &data1);
        pthread_create(&thread2, NULL, print_string, &data2);

        // Esperar a que los hilos terminen
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        printf("\n");
    }

    return 0;
}

void *print_string(void *arg) 
{
    ThreadData *data = (ThreadData *)arg;

    for (int i = 1; i <= data->repeat_count; ++i) {
        printf("Hilo (%d): %d %s\n", data->id, i, data->string);
        sleep(1); 
    }

    return NULL;
}