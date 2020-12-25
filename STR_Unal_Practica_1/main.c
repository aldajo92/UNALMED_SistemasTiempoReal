#include "controllers.h"
#include "managers.h"

bool controlFlag = true;

void printOptions() {
    printf("Please select a valid option:\n");
    printf("\t0. Close Program\n");
    printf("\t1. Go to next station\n");
    printf("\t2. Buy ticket\n");
    printf("\t3. Set temperature\n");
    printf("\t4. Activate Alarm (!)\n");
}

void goNextStation() {
    sleep(1);
    openDoors(false);
    sleep(2);
    setVelocity(30);
    sleep(5);
    setVelocity(0);
    sleep(1);
    activateBrake(true);
    sleep(2);
    openDoors(true);
    sleep(1);
}

void purchaseTickets() {
    int ticketsAmount;
    printf("How many tickets do you want to buy? : ");
    scanf("%d", &ticketsAmount);
    if (buyTicket(ticketsAmount)) {
        getTotalTicketPrice(ticketsAmount);
    }
}

void buyTicketFlow() {
    getTicketPrice();
    getTicketsAmount();
    getTicketsAvailable();
    purchaseTickets();
    sleep(1);
    getTicketsAvailable();
    sleep(3);
}

void configureTemperature() {
    int temperature;
    printf("Enter temperature for your comfort : ");
    scanf("%d", &temperature);
    setTemperature(temperature);
}

void turnOnAlarmSystem(){
    int alarm;
    printf("Are you sure to activate alarm (1: YES, OtherKey: NO) : ");
    scanf("%d", &alarm);
    if(alarm == 1){
        activate_alarm(true);
        sleep(5);
        activate_alarm(false);
    }
}

void optionManager(int option) {
    switch (option) {
        case 0:
            controlFlag = false;
            break;
        case 1:
            goNextStation();
            break;
        case 2:
            buyTicketFlow();
            break;
        case 3:
            configureTemperature();
            break;
        case 4:
            turnOnAlarmSystem();
            break;
        default:
            printf("Add a valid option\n");
    }
}

int main() {
    int option = 0;
    setIllumination(100);
    while (controlFlag) {
        printOptions();
        printf("Enter your option: ");
        scanf("%d", &option);
        optionManager(option);
    }
    setIllumination(0);
}