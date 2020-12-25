#include <stdio.h>
#include <stdlib.h>

#define VALUE_SIZE 2 // Motors

union
{
    int value;
    char arr[2];
} left, right, vel;

void process(char *val, int size);

int main()
{   
    char values[] = "m;100;200";
    process(values, 9);

    return 0;
}

void process(char *val, int size){
    char values[VALUE_SIZE][16];
    for(int i = 0; i < VALUE_SIZE; i++){
        memset(values[i], '\0', sizeof(values[i]));
    }
    
    int row = 0;
    int col = 0;
    if (val[0] == 'm')
    {
        char current;
        for(int i = 2; i < size ; i++){
            current = val[i];
            if(current == ';'){
                row++;
                col = 0;
            } else {
                values[row][col] = val[i];
                col++;
            }
        }
        int val1 = atoi(values[0]);
        int val2 = atoi(values[1]);
        printf("value 1: %d\n", val1);
        printf("value 2: %d\n", val2);
        
        // moveM(values[1].toInt(), values[2].toInt());
    }
}
