#include "ticket.h"

int ticketPrice = 10000;
int totalTickets = 100;
int ticketsTaken = 0;

void getTicketPrice() {
    printf("Ticket price: $%d\n", ticketPrice);
}

void getTotalTicketPrice(int amount) {
    printf("Total Ticket price: $%d\n", ticketPrice * amount);
}

void getTicketsAmount() {
    printf("Total tickets: %d\n", totalTickets);
}

void getTicketsAvailable() {
    printf("Tickets available: %d\n", totalTickets - ticketsTaken);
}

bool buyTicket(int amount) {
    if (amount < (totalTickets - ticketsTaken)) {
        printf("Tickets purchased: %d\n", amount);
        ticketsTaken += amount;
        return true;
    } else {
        printf("You cannot perform this operation!!!\n");
        return false;
    }
}