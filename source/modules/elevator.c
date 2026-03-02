#include "elevator.h"

int nextFloor = 0;

void elevator_runStartUp(){
    int defined = 0;
    while(!defined){
        int floor = elevio_floorSensor();
        if(floor<0){
            elevio_motorDirection(DIRN_DOWN);   
        }
        else {
            elevio_motorDirection(DIRN_STOP);
            nextFloor = floor;
            defined = 1;
        }
    }
    
}
void elevator_runOrders(){
    struct elevatorObject currState = {
        0, 
        DIRN_DOWN, 
        DIRN_STOP, 
        0, 
        0
    };

    while(1){
        int floor = elevio_floorSensor();    
        if(floor>=0){
            currState.floor = floor;
            elevio_floorIndicator(currState.floor);
        }

        nextFloor = orders_nextFloor(currState.floor, &currState.orderDir);  
        
        if (currState.floor == nextFloor){
            elevio_motorDirection(DIRN_STOP);
            if (floor==-1 && orders_checkOrders(currState.floor)){
                if (currState.motorDir==DIRN_DOWN){
                    currState.floor = nextFloor -1;
                }
                else{
                    currState.floor = nextFloor + 1;
                }
            }
            if (floor>=0){
                door_open(&currState, nextFloor); //Not implemented
                orders_removeOrder(currState.floor);
                orders_removeOrderLight(currState.floor);
                //edoor = 1;
            }



            /*
            if(door && elevio_obstruction() && !door_finished){
                elevio_doorOpenLamp(1);
            }
            else if(door ){
                timer_start(currFloor, stopped);
                while(!timer_elapsedTime()){
                    elevio_doorOpenLamp(1);
                    orders_buttonUpdates(currFloor,nextFloor);
                }
                elevio_doorOpenLamp(0);
                door = 0;
                door_finished = 1;
            }
            */            
        }
        if (nextFloor > currState.floor){
            elevio_motorDirection(DIRN_UP);
            //door_finished = 0;
            currState.motorDir = DIRN_UP;
        }
        if (nextFloor < currState.floor){
            elevio_motorDirection(DIRN_DOWN);
            //door_finished = 0;
            currState.motorDir = DIRN_DOWN;
        }

        orders_buttonUpdates(currState.floor, nextFloor);

        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            elevio_stopLamp(1);
            orders_removeAll();
            if (floor>=0){
                elevio_doorOpenLamp(1);
                currState.stopped = 1;
            }
        }
        else if (currState.stopped){
            door_open(&currState, nextFloor); //Not implemented
            if(elevio_obstruction()){}
           
            elevio_doorOpenLamp(0);
            currState.stopped = 0;
        }
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
}