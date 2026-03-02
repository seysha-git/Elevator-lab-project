#include "door.h"

int door = 0;

void door_open(struct elevatorObject *currState, int nextFloor){
    switch (currState->doorOpen) {
        case 0:
            break;
        case 1 :
            if(!)

            timer_start(currState->floor, currState->stopped);
            while(!timer_elapsedTime()){
                elevio_doorOpenLamp(1);
                orders_buttonUpdates(currState->floor,nextFloor);
            }
            break;


    }

}