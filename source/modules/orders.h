#include "../driver/elevio.h"
#include <stdlib.h>

void orders_addOrder(int floor, int btnType, int motorDir);
void orders_removeOrder(int floor);
void orders_removeAll();
int orders_nextFloor(int currFloor, int motorDir);

