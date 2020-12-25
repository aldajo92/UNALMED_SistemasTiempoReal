#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#define NUM_THREADS 4
#define BUSY_LOOP_ITERATIONS 10000

/*
 * Function with a long execution time.
 * Receives its thread number.
 * Returns its thread number.
 */
void* busy_work(void* arg) {
    /* dagerous void* can be smaller than unsigned long long) */
    unsigned long long tid = (unsigned long long) arg;
    double result=0.0;

    printf("In thread #%llu: starting busy loop...\n", tid);
    for (int i=0; i<BUSY_LOOP_ITERATIONS; i++) {
        result += i/3 * i * 10;
    }
    printf("In thread #%llu: busy loop finished, result is %e.\n", tid, result);
    pthread_exit((void*) arg);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int r;

    /* Allow joining threads */
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if (errno = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)) {
        perror("pthread_attr_setdetachstate");
        exit(EXIT_FAILURE);
    }

    /* Launch threads */
    unsigned long long tid;
    for(tid=0; tid<NUM_THREADS; tid++) {
        printf("In main: about to create thread #%llu.\n", tid);

        if (r = pthread_create(&threads[tid], &attr, &busy_work, (void *)tid)) {
            char* err_str = strerror(r);
            fprintf(stderr, "ERROR: pthread_create() [tid=#%llu]: %s.\n",
                    tid, err_str);
            exit(EXIT_FAILURE);
        }
    }


    /* Once the threads are launched, we no longer need the attribute */
    pthread_attr_destroy(&attr);

    /* Wait untill all threads finish execution, store their return
     * values */
    void *status;
    for(tid=0; tid<NUM_THREADS; tid++) {
        if (r = pthread_join(threads[tid], &status)) {
            char* err_str = strerror(r);
            fprintf(stderr, "ERROR: pthread_join() [tid=#%llu]: %s.\n",
                    tid, err_str);
            exit(EXIT_FAILURE);
        }
        printf("In main: thread %llu finished, return value was %llu.\n", tid, (unsigned long long) status);
    }

    printf("In main: program finished.\n");
    pthread_exit(NULL);
}