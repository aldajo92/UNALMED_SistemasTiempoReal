#include "hvac.h"

void setTemperature(int temperature) {
    if (temperature > 10 && temperature < 30) {
        printf("Setting the temperature to %d˚C\n", temperature);
    } else {
        printf("Temperature not allowed\n");
    }
}