#include <stdio.h>

void swap(double x, double y){
    double temp = x;
    x = y;
    y = temp;
    return;
}

int main(void){
    double x = 2.0;
    double y = 3.0;
    swap(x,y);
    printf("%1f    %1f", x, y);
}