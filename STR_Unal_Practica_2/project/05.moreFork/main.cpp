#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(){
    int p1_pid = -1;
    int p2_pid = -1;
    int p3_pid = -1;
    int p4_pid = -1;

    if((p1_pid = fork()) == 0){
        printf("I am P1 and I am proud of it.\n");
    } else {
        if ((p2_pid = fork()) == 0){
            // fork();
            // de la anterior línea comentada se hizo la siguiente correccion:
            p3_pid = fork();
            printf("I am P3. I like it.\n");
            // fork();
            // de la anterior línea comentada se hizo la siguiente correccion:
            p4_pid = fork();
            printf("I am P4. Get used to it.\n");
        } else
            printf("I am the parent process, obey or die.\n");
    }
}