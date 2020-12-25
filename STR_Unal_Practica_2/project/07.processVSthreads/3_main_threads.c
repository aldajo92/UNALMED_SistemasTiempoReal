// Programa que realiza las tareas anteriores utilizando procesos ligeros o hilos
// compile with: gcc -std=c99 -D_POSIX_C_SOURCE=200112L -o main_threads 3_main_threads.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

void tarea_A();
void tarea_B();
void createThread(pthread_t *thread, unsigned long long number, void *(*func) (void *));

pthread_t threads[2];

int main() {
    pthread_t thread_0;
    pthread_t thread_1;

    createThread(&thread_0, 0, tarea_A);
    createThread(&thread_1, 1, tarea_B);
    pthread_exit(NULL);
}

void tarea_A(){
    printf("Estoy corriendo el proceso A\n");
    // pthread_exit(NULL);
}

void tarea_B(){
    printf("Estoy corriendo el proceso B\n");
    // pthread_exit(NULL);
}

void createThread(pthread_t *thread, unsigned long long number, void *(*func) (void *)) {
    int r;
    if(r = pthread_create(thread, NULL, func, NULL)){
        char* err_str = strerror(r);
        fprintf(
            stderr, 
            "ERROR: pthread_create() [tid=#%llu]: %s\n",
            number,
            err_str
        );
        exit(EXIT_FAILURE);
    }
}