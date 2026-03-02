#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "objects.h"
#include "orders.h"
#include "../driver/elevio.h"
void door_open(struct elevatorObject *currState, int nextFloor);
void door_startTimer();
int door_elapsedTime();



