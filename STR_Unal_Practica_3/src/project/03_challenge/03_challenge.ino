#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define SENSOR1 A0
#define SENSOR2 A1
#define SENSOR3 A2

SemaphoreHandle_t Semaforo;

int sensors[] = {SENSOR1, SENSOR2, SENSOR3};
int rawTemperatures[3];
float temperatures[3];

void setup()
{
  Serial.begin(9600);
  xTaskCreate(MyTask1, "Task1", 100, NULL, 3, NULL);
  xTaskCreate(MyTask2, "Task2", 100, NULL, 3, NULL);
  xTaskCreate(MyTask3, "Task3", 100, NULL, 4, NULL);
  if (Semaforo == NULL)
  {
    Semaforo = xSemaphoreCreateCounting(4, 1);
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
        getAndPrintTemperature(1);
        xSemaphoreGive(Semaforo);
    }
    delay(250);
  }
}

static void MyTask2(void *pvParameters)
{
  while (1)
  {
    if (xSemaphoreTake(Semaforo, (TickType_t)2) == pdTRUE)
    {
        getAndPrintTemperature(2);
        xSemaphoreGive(Semaforo);
    }
    delay(500);
  }
}

static void MyTask3(void *pvParameters)
{
  while (1)
  {
    if (xSemaphoreTake(Semaforo, (TickType_t)2) == pdTRUE)
    {
        getAndPrintTemperature(3);
        xSemaphoreGive(Semaforo);
    }
    delay(1000);
  }
}

float getAndPrintTemperature(int position){
    rawTemperatures[position] = analogRead(sensors[position]);
    temperatures[position] = (rawTemperatures[position] * 5.0)/1024.0;
    Serial.print("Temperature sensor #");
    Serial.print(position);
    Serial.print(": ");
    Serial.print(temperatures[position]);
    Serial.print("\r\n");
}