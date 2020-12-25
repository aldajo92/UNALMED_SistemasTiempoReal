#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t Semaforo;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(MyTask1, "Task1", 100, NULL, 1, NULL);
  if (Semaforo == NULL)
  {
    Semaforo = xSemaphoreCreateCounting(2, 1);
    if (Semaforo != NULL)
      xSemaphoreGive(Semaforo);
  }
}

void loop(){}

static void MyTask1(void *pvParameters)
{
  while (1)
  {
    Serial.println("print something...");
    if (xSemaphoreTake(Semaforo, (TickType_t)5) == pdTRUE)
    {
      xSemaphoreGive(Semaforo);
    }
    delay(500);
  }
}