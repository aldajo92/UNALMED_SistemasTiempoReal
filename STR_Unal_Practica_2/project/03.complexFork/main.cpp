#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_COUNT 20
char* barras[5] = { "*", "**", "***", "****", "*****"};

void childProcess(void);        //prototipo proceso hijo
void parentProcess(void);       //prototipo proceso padre

int main(void)
{
    pid_t pid;
    
    pid = fork();
    if(pid == 0) childProcess();
    else parentProcess();

    return 0;
}

void childProcess(void){
    int i;
    for(i = MAX_COUNT - 1; i >= 0; i--){
        printf("\t\th-%s\n", barras[i%5]);
        sleep(i % 5);
    }
    printf("     *** fin proceso hijo ***\n");
}

void parentProcess(void){
    int i, h;
    for(i = 0; i < MAX_COUNT; i++){
        printf("\tp-%s\n", barras[i%5]);
        sleep(i % 5);
    }
    printf("*** fin del Padre ***\n");
}