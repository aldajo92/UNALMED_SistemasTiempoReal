#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

#define MAX_COUNT 2
#define BUF_SIZE 120

void runProgram();

int main(void) {
    int pid_1 = -1;
    int pid_2 = -1;

    pid_1 = fork();
    pid_2 = fork();

    if(pid_1 != 0 || pid_2 != 0) {
        runProgram();
    }

    // printf("%d %d\n", pid_1, pid_2);

    return 0;
}

void runProgram() {
    pid_t pid;
    int i;
    int x = 0;

    char buf[BUF_SIZE];

    pid = getpid();
    for (i = 1; i <= MAX_COUNT; i++){
        x = rand();
        sprintf(
            buf,
            "Esta linea es de pid %d, valor = %d, valor de x es %d\n",
            pid, i, x);
        write(1, buf, strlen(buf));
    }
}