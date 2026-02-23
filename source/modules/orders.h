#include "../driver/elevio.h"
#include <stdlib.h>
#include <stdio.h>


/*
Tom bestilling
Ny bestilling:
    -aktiverer etasjen
    -velger Order struct
    -setter knapp typen til order objekt og destinasjon floor

*/

struct Order{
    int destFloorm;
    MotorDirection dir;
    ButtonType btnType;
    int active;
};


void orders_addOrder(int destFloor, int elevatorFloor, ButtonType btnType);
MotorDirection orders_getDirection();
int orders_getDestinationFloor();
int orders_checkOrder();
int orders_checkNewOrders(int newElevatorFloor);
void orders_init();
void orders_resetOrder(int floor);