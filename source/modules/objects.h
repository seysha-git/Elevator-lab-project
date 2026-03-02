#pragma once
#include "../driver/elevio.h"

typedef enum { 
    ORDER_STOP = 0,
    USER_STOP = 1,
} StopType;

struct elevatorObject{
    int stopped;
    int doorOpen;
    int floor;
    MotorDirection orderDir;
    MotorDirection motorDir;
    StopType Stop;
    
};