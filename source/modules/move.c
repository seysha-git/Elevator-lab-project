#include "move.h"

void move_setToDefinedFloor(){
    int defStartFloor = 0;
    while(!defStartFloor){
        int floor = elevio_floorSensor();
        if(floor < 0){
            elevio_motorDirection(DIRN_DOWN);
        }
        else{
            elevio_motorDirection(DIRN_STOP);
            defStartFloor = 1;
        }
    }
}

int move_setToNextFloor(int elFloor, int nextFloor, MotorDirection dir){
    if(elFloor != nextFloor){
        elevio_motorDirection(dir);
        return 0;
    }
    return 1;
}

