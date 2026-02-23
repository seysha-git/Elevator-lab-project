#include "door.h"
#include "timer.h"

static int waiting = 0;
static int door_time_open = 3;

void door_open(){
    elevio_doorOpenLamp(1);
    timer_start();
    waiting = 1;

}

int door_waiting(){
    if(waiting && !timer_timePassed(door_time_open)){
        return 1;
    }
    return 0;
}

void door_close(){
    elevio_doorOpenLamp(0);
    timer_end();
    waiting = 0;
}

