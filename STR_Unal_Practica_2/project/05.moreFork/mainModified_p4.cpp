#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(){
    int p1_pid = -1;
    int p2_pid = -1;

    if((p1_pid = fork()) == 0){
        printf("I am P2.\n");
        if ((p2_pid = fork()) == 0){
            printf("I am P3.\n");
        } else {
            printf("I am P4.\n");
        }
    } else {
        printf("I am P1.\n");
    }
}