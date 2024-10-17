#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <unistd.h>  

void print_string(int number, const char *str) {
    for (int i = 1; i <= number; i++) {
        printf("iteration (%d): %s\n", i, str);  
    }
}

int main() {
    int number;
    char first_string[100], second_string[100];
    clock_t start, end;
    double cpu_time_used;

    while (1) {
        // Number and String from the user
        printf("Input a number: ");
        if (scanf("%d", &number) != 1 || number <= 0) {  //Check no negativo or 0 value
            printf("Please enter a valid positive number.\n");
            break;  // Exit loop if invalid input );
        }
        
        // Input 1st string 
        printf("Input first string: ");
        scanf(" %[^\n]", first_string);  // Read characters + spaces
        
        // Input the 2nd string
        printf("Input second string: ");
        scanf(" %[^\n]", second_string);
        
        // Start clock 
        start = clock();
        
        // Print the first string number of times introduced
        print_string(number, first_string);

        // Print the first string number of times introduced
        print_string(number, second_string);
        
        // Stop clock and calculate the total time
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        // print time used 
        printf("\nTime taken to execute: %.4f seconds\n", cpu_time_used);

        // print num of CPUs
        printf("Number of processors available: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));

        printf("\n");
    }

    return 0;
}
