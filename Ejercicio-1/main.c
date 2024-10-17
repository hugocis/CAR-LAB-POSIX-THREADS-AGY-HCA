#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

// Declaración de la estructura ThreadData
typedef struct {
    int id;
    char *string;
    int repeat_count;
} ThreadData;

// Prototipos de las funciones
void *print_string(void *arg);
void print_string_sequential(ThreadData *data);
void get_time_diff(struct timespec start, struct timespec end, double *seconds);
void measure_resource_usage();

int main() {
    int number;
    char str1[100], str2[100];
    pthread_t thread1, thread2;

    while (1) {
        // Input number and strings from user
        printf("Input a number: ");
        scanf("%d", &number);
        getchar(); // To consume newline left by scanf
        printf("Input first string: ");
        fgets(str1, sizeof(str1), stdin);
        printf("Input second string: ");
        fgets(str2, sizeof(str2), stdin);

        // Remove newline characters from strings
        str1[strcspn(str1, "\n")] = 0;
        str2[strcspn(str2, "\n")] = 0;

        // Thread data for each thread
        ThreadData data1 = {1, str1, number};
        ThreadData data2 = {2, str2, number};

        printf("\n--- Running with Threads ---\n");
        // Variables to hold the start and end time
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Create two threads
        pthread_create(&thread1, NULL, print_string, &data1);
        pthread_create(&thread2, NULL, print_string, &data2);

        // Wait for both threads to finish
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        // Measure end time and calculate total duration
        clock_gettime(CLOCK_MONOTONIC, &end);
        double total_seconds;
        get_time_diff(start, end, &total_seconds);
        printf("Total execution time with threads: %.6f seconds\n", total_seconds);

        // Measure resource usage (CPU and memory)
        measure_resource_usage();

        printf("\n--- Running Sequentially ---\n");
        // Measure start time for sequential execution
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Run sequentially
        print_string_sequential(&data1);
        print_string_sequential(&data2);

        // Measure end time and calculate total duration
        clock_gettime(CLOCK_MONOTONIC, &end);
        get_time_diff(start, end, &total_seconds);
        printf("Total execution time without threads: %.6f seconds\n", total_seconds);

        // Measure resource usage for sequential run
        measure_resource_usage();

        printf("\n");
    }

    return 0;
}

void *print_string(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = 1; i <= data->repeat_count; ++i) {
        printf("thread (%d): %d %s\n", data->id, i, data->string);
        sleep(1); // Simulate some work
    }

    return NULL;
}

void print_string_sequential(ThreadData *data) {
    for (int i = 1; i <= data->repeat_count; ++i) {
        printf("sequential (%d): %d %s\n", data->id, i, data->string);
        sleep(1); // Simulate some work
    }
}

void get_time_diff(struct timespec start, struct timespec end, double *seconds) {
    *seconds = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void measure_resource_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    // Display CPU usage
    double user_cpu_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1e6;
    double system_cpu_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1e6;
    printf("User CPU time used: %.6f seconds\n", user_cpu_time);
    printf("System CPU time used: %.6f seconds\n", system_cpu_time);

    // Display memory usage (in kilobytes)
    printf("Maximum resident set size (memory): %ld KB\n", usage.ru_maxrss);
}
