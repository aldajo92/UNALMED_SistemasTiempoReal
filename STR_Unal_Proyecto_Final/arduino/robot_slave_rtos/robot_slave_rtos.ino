#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <ZumoMotors.h>
#include <stdlib.h>
#include <Wire.h>
#include <LSM303.h>

#define SENSOR1 A0   // Read Sensors
#define VALUE_SIZE 2 // Motors

SemaphoreHandle_t semaforo;

//////////////////Motors Block//////////////////

ZumoMotors motors;
int sensors[] = {SENSOR1};
int rawTemperatures[1];
float temperatures[1];

//////////////////Serial Block//////////////////

char c;
String command;

//////////////////Sensor Block//////////////////
LSM303 compass;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    compass.init();
    compass.enableDefault();

    xTaskCreate(MyTask1, "Task1", 200, NULL, 3, NULL);
    xTaskCreate(MyTask2, "Task2", 200, NULL, 3, NULL);

    if (semaforo == NULL)
    {
        semaforo = xSemaphoreCreateCounting(4, 1);
        if (semaforo != NULL)
            xSemaphoreGive(semaforo);
    }

    compass.m_min = (LSM303::vector<int16_t>){+3330,  -8009,  -8913};
    compass.m_max = (LSM303::vector<int16_t>){+6805,  -4549,  -4133};
}

void loop() {}

////////////////////// Manage Tasks /////////////////////////////

static void MyTask1(void *pvParameters)
{
    char c;
    char comm[64];
    memset(comm, '\0', sizeof(comm));
    int index = 0;
    while (1)
    {
        if (xSemaphoreTake(semaforo, (TickType_t)2) == pdTRUE)
        {
            while (Serial.available())
            {
                c = Serial.read();
                if (c == '\n')
                {
                    process(comm, (index + 1));
                    memset(comm, '\0', sizeof(comm));
                    index = 0;
                    Serial.flush();
                }
                else
                {
                    comm[index] = c;
                    index++;
                }
            }
            xSemaphoreGive(semaforo);
        }
        // delay(5);
    }
}

static void MyTask2(void *pvParameters){
    float heading;
    while (1)
    {
        if (xSemaphoreTake(semaforo, (TickType_t)2) == pdTRUE)
        {
            compass.read();
            heading = compass.heading();
            Serial.println(heading);
        }
        xSemaphoreGive(semaforo);
        delay(100);
    }
}

////////////////////// Manage Serial Communication /////////////////////////////

void echo(String value)
{
    Serial.print("responding-to-");
    Serial.println(value);
}

union {
    int value;
    char arr[2];
} left, right, vel;


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
        // printf("value 1: %d\n", val1);
        // printf("value 2: %d\n", val2);
        
        moveM(val1, val2);
    }
}

// void parseCommand(char *val, int size)
// {
//     atoi("23");
//     char values[VALUE_SIZE][16];
//     // if (com[0] == "e")
//     // {
//     //     echo(values[1]);
//     // }
//     // else if (values[0] == "f")
//     // {
//     //     forward(values[1].toInt());
//     // }
//     // else
//     int row = 0;
//     int col = 0;
//     if (val[0] == "m")
//     {
//         char current;
//         for(int i = 2; i < size ; i++){
//             current = val[i];
//             if(current == ';'){
//                 row++;
//                 col = 0;
//             } else {
//                 values[row][col] = val[i];
//             }
//         }
//         moveM(values[1].toInt(), values[2].toInt());
//     }
// }

////////////////////// Manage Motors /////////////////////////////

void forward(int value)
{
    motors.setSpeeds(value, value);
}

void moveM(int v, int w)
{
    motors.setSpeeds(v + w, v - w);
}
