#include "door.h"
#include "orders.h"

time_t start, end;
static int timerActive = 0;

void door_open(struct elevatorObject *currState, int nextFloor){
    while (currState->doorOpen){
        elevio_doorOpenLamp(1);

        switch (currState->Stop){
            case ORDER_STOP:
                door_startTimer();
                currState->doorOpen = 0;
                while(!door_elapsedTime()){
                    orders_buttonUpdates(currState->floor);
                    if(elevio_obstruction()||elevio_stopButton()){
                        currState->Stop = USER_STOP;
                        currState->doorOpen = 1;
                        break;
                    }
                }
                break;
            case USER_STOP:
                if(elevio_obstruction()||elevio_stopButton()){

                    if(elevio_stopButton()){
                        elevio_stopLamp(1);
                    }
                    else{
                        orders_buttonUpdates(currState->floor);
                    }
                }
                else{
                    elevio_stopLamp(0);
                    currState->orderDir = DIRN_UP; //   settes random
                    currState->Stop = ORDER_STOP;
                }
                break;
        }
    }
    elevio_doorOpenLamp(0);
    
}


void door_startTimer(){
    start = time(NULL);
    timerActive = 1;
}

int door_elapsedTime(){
    end = time(NULL);
    if(difftime(end, start) >= 3){
        return 1;
    }
    return 0;
        
}