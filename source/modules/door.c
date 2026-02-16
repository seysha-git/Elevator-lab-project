#include "door.h"


void door_open(){
    elevio_doorOpenLamp(1);
}


void door_close(){
    elevio_doorOpenLamp(0);
}

