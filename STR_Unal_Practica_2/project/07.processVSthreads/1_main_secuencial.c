// Programa secuencial ejecutado por un único proceso

#include <stdio.h>
#include <stdlib.h>

void tarea_A(void);
void tarea_B(void);

int main()
{
    tarea_A();
    tarea_B();
    return 0;
}

void tarea_A(void){
    printf("Estoy corriendo el proceso A\n");
}

void tarea_B(void){
    printf("Estoy corriendo el proceso B\n");
}