#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <unistd.h>  

void print_string();

int main() {
    int number;
    char first_string[100], second_string[100];
    clock_t start, end;
    double cpu_time_used;

    while (1) {
        
        printf("Introduce un número de impresión: ");
        if (scanf("%d", &number) != 1 || number <= 0) {  
            printf("Por favor pon un número positivo.\n");
            break;  
        }
        
        // Introducir primer string 
        printf("Introduce la primera frase: ");
        scanf(" %[^\n]", first_string);
        
        // Introducir segundo string 
        printf("Introduce la segunda frase: ");
        scanf(" %[^\n]", second_string);
        
        // Se empieza un reloj 
        start = clock();
        
        // Se imprime el primer string de seguido
        print_string(number, first_string);

        // Se imprime el segundo string de seguido
        print_string(number, second_string);
        
        // Se para el reloj y se calcula la diferencia de tiempo para saber cuánto ha tardado.
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        // El timeo de uso de CPU
        printf("\nTiempo que ha tardado en la CPU: %.4f segundos\n", cpu_time_used);

        // Número de CPUs
        printf("Número de núcelos en el sistema: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));

        printf("\n");
    }

    return 0;
};

void print_string(int number, const char *str) {
    for (int i = 1; i <= number; i++) {
        printf("iteración (%d): %s\n", i, str); 

    }
};
