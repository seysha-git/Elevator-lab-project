#include "door.h"

static int wait = 0;

void door_open(){
    wait = 1;
    elevio_doorOpenLamp(1);
}

int door_waiting(){
    return wait;
}

void door_close(){
    wait = 0;
    elevio_doorOpenLamp(0);
}

