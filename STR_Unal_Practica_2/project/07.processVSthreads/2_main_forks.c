// Programa que crea procesos para desarrollar cada una de las tareas.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void tarea_A(void);
void tarea_B(void);

int main()
{
    if(fork() == 0) tarea_A();
    else tarea_B();

    return 0;
}

void tarea_A(void){
    printf("Estoy corriendo el proceso A\n");
}

void tarea_B(void){
    printf("Estoy corriendo el proceso B\n");
}