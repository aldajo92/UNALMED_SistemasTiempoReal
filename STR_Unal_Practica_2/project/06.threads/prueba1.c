#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//Missing header
#include<pthread.h>

#define NUM_THREADS 100

void *print_hello(void* arg) {
    /* dagerous void* can be smaller than unsigned long long) */
    unsigned long long tid = (unsigned long long) arg;
    printf("In thread #%llu: Hello World!\n", tid);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    unsigned long long tid;
    int r;

    for(tid=0; tid<NUM_THREADS; tid++){

        printf("In main: about to create thread %llu\n", tid);

        if (r = pthread_create(&threads[tid], NULL, &print_hello, (void *)tid)) {
            char* err_str = strerror(r);
            fprintf(stderr, "ERROR: pthread_create() [tid=#%llu]: %s\n",
                    tid, err_str);
            exit(EXIT_FAILURE);
        }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
}