#include "../driver/elevio.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#include "orders.h"
#include "door.h"
#include "timer.h"


void elevator_runStartUp();
void elevator_runOrders();

struct elevatorObject{
    int stopped;
    MotorDirection orderDir;
    MotorDirection motorDir;
    int doorOpen;
    int floor;
};