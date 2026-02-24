#include "../driver/elevio.h"
#include <stdlib.h>
#include <stdio.h>

void orders_addOrder(int floor, ButtonType btnType, int currFloor);
void orders_removeOrder(int floor, int *switched);
void orders_removeAll();
int orders_nextFloor(int currFloor, MotorDirection *motorDir, int *switched);

void orders_addOrderLight(int floor, ButtonType btnType);
void orders_removeOrderLight(int floor);
void orders_removeAllOrderLight();

int orders_checkOrders(int floor);




