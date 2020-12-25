#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t Semaforo;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(MyTask1, "Task1", 100, NULL, 3, NULL);
  xTaskCreate(MyTask2, "Task2", 100, NULL, 3, NULL);
  xTaskCreate(MyTask3, "Task3", 100, NULL, 4, NULL);
  if (Semaforo == NULL)
  {
    Semaforo = xSemaphoreCreateCounting(4, 1);
    // Semaforo = xSemaphoreCreateMutex();
    if (Semaforo != NULL)
      xSemaphoreGive(Semaforo);
  }
}

void loop(){}

static void MyTask1(void *pvParameters)
{
  while (1)
  {
    if (xSemaphoreTake(Semaforo, (TickType_t)2) == pdTRUE)
    {
        Serial.println("print something...");
        xSemaphoreGive(Semaforo);
    }
    // Serial.println("print something...");
    delay(200);
  }
}

static void MyTask2(void *pvParameters)
{
  while (1)
  {
    if (xSemaphoreTake(Semaforo, (TickType_t)2) == pdTRUE)
    {
        Serial.println("print other...");
        xSemaphoreGive(Semaforo);
    }
    // Serial.println("print other...");
    delay(200);
  }
}

static void MyTask3(void *pvParameters)
{
  while (1)
  {
    if (xSemaphoreTake(Semaforo, (TickType_t)2) == pdTRUE)
    {
        Serial.println("task 3...");
        xSemaphoreGive(Semaforo);
    }
    // Serial.println("task 3...");
    delay(200);
  }
}