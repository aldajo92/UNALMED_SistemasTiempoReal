#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef TRAIN_TICKET_H
#define TRAIN_TICKET_H

void getTicketPrice();

void getTotalTicketPrice(int amount);

void getTicketsAmount();

void getTicketsAvailable();

bool buyTicket(int amount);

#endif //TRAIN_TICKET_H
