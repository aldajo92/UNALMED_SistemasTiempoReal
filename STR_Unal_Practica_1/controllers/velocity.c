#include "velocity.h"

double currentVelocity = 0;

void setVelocity(int velocity) {
    printf("Setting velocity at %d m/s\n", velocity);
    sleep(1);
    if(velocity > 0){
        for (int i = 0; i < 20; ++i) {
            currentVelocity = (velocity * (1 - exp(-i/2)));
            printf("Current velocity at %2f m/s\n", currentVelocity);
            usleep(500000);
        }
    }
}