#include <Arduino_FreeRTOS.h>

void setup()
{
    xTaskCreate(MyTask1, "Task1", 100, NULL, 1, NULL);
}

void loop() {}

static void MyTask1(void *pvParameters)
{
    while (1)
    {
        //
    }
}