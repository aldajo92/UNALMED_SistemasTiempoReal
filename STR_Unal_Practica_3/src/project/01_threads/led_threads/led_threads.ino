#include <Arduino_FreeRTOS.h>

#define LED1 7
#define LED2 8
#define LED3 9

boolean led1_flag = false;
boolean led2_flag = false;
boolean led3_flag = false;

int value = 0;

void setup()
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);

    xTaskCreate(MyTask1, "Task1", 200, NULL, 3, NULL);
    xTaskCreate(MyTask2, "Task2", 200, NULL, 3, NULL);
    xTaskCreate(MyTask3, "Task3", 200, NULL, 3, NULL);
}

void loop() {}

static void MyTask1(void *pvParameters)
{
    while (1)
    {
        led1_flag = !led1_flag;
        digitalWrite(LED1, led1_flag);
        delay(250);
    }
}

static void MyTask2(void *pvParameters)
{
    while (1)
    {
        led2_flag = !led2_flag;
        digitalWrite(LED2, led2_flag);
        delay(500);
    }
}

static void MyTask3(void *pvParameters)
{
    while (1)
    {
        led3_flag = !led3_flag;
        digitalWrite(LED3, led3_flag);
        delay(1000);
    }
}