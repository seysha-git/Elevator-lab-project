#include "../driver/elevio.h"
#include <stdlib.h>
#include <stdio.h>

void orders_addOrder(int floor, ButtonType btnType, int currFloor);
void orders_removeOrder(int floor);
void orders_removeAll();
int orders_nextFloor(int currFloor, MotorDirection *motorDir);

