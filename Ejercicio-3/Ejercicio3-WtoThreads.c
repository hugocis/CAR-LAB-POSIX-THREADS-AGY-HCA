#include <stdio.h>

#define TAM 20 // Definimos el tamaño del vector como 20
#define PARTES 2 // Definimos el número de partes en las que dividimos el vector
#define OBJETIVO 2 // Número que vamos a buscar en el vector

// Función para contar las ocurrencias del número objetivo en una parte específica del vector
int contar_ocurrencias(int vec[], int inicio, int fin) {
    int cuenta = 0;  // Inicializamos la variable para contar las ocurrencias
    // Recorremos desde la posición de inicio hasta la de fin en el vector
    for (int i = inicio; i < fin; i++) {
        if (vec[i] == OBJETIVO) {  // Si el valor en la posición actual del vector es igual al objetivo
            cuenta++;  // Aumentamos el contador
        }
    }
    return cuenta;  // Devolvemos el número de ocurrencias en esta parte
}

int main() {
    int vec[TAM], i;
    int tam_parte = TAM / PARTES;  // Calculamos el tamaño de cada parte
    int cuenta_total = 0;  // Variable para guardar la suma total de las ocurrencias

    // Pedimos al usuario que introduzca los elementos del vector
    printf("Introduce 20 elementos para el vector:\n");
    for (i = 0; i < TAM; i++) {
        scanf("%d", &vec[i]);  // Leemos cada elemento introducido 
    }

    // Contamos las ocurrencias en cada parte de forma secuencial
    for (i = 0; i < PARTES; i++) {
        int inicio = i * tam_parte;  // Calculamos el índice de inicio de la parte actual
        int fin = inicio + tam_parte;  // Calculamos el índice de fin de la parte actual
        int cuenta_parte = contar_ocurrencias(vec, inicio, fin);  // Llamamos a la función para contar ocurrencias
        // Mostramos el resultado para la parte actual
        printf("Ocurrencias de %d en la parte %d: %d\n", OBJETIVO, i + 1, cuenta_parte);
        cuenta_total += cuenta_parte;  // Sumamos las ocurrencias de esta parte al total
    }

    // Mostramos el número total de ocurrencias del número objetivo en todo el vector
    printf("\nTotal de ocurrencias de %d en el vector: %d\n", OBJETIVO, cuenta_total);

    return 0;  // Fin
}