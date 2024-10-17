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
} ThreadData;

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
        ThreadData data1 = {1026, str1, number};
        ThreadData data2 = {2051, str2, number};

        // Create two threads
        pthread_create(&thread1, NULL, print_string, &data1);
        pthread_create(&thread2, NULL, print_string, &data2);

        // Wait for both threads to finish
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

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