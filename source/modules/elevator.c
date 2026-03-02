#include "elevator.h"
#include "objects.h"
#include "orders.h"

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
        0,
        0, 
        DIRN_DOWN, 
        DIRN_STOP, 
        ORDER_STOP,
    };

    while(1){
        int floor = elevio_floorSensor();    
        if(floor>=0){
            currState.floor = floor;
            elevio_floorIndicator(currState.floor);
        }

        nextFloor = orders_nextFloor(currState.floor, &currState.orderDir, &currState.motorDir);  
        
        if (currState.floor == nextFloor){
            if (floor==-1 && orders_checkOrders(currState.floor) && currState.orderDir==DIRN_STOP){
                currState.orderDir = DIRN_UP;   //setter denne til noe random
                if (currState.motorDir==DIRN_DOWN){
                    currState.floor = nextFloor - 1;
                }
                else{
                    currState.floor = nextFloor + 1;
                }
            }
            if (floor>=0){
                currState.motorDir = DIRN_STOP;
                elevio_motorDirection(DIRN_STOP);
                if(orders_checkOrders(floor)){
                    currState.Stop = ORDER_STOP;
                    currState.stopped = 1;
                }
                orders_removeOrder(currState.floor);
                orders_removeOrderLight(currState.floor);
            }         
        }

        if (nextFloor > currState.floor){
            elevio_motorDirection(DIRN_UP);
            currState.motorDir = DIRN_UP;
        }
        if (nextFloor < currState.floor){
            elevio_motorDirection(DIRN_DOWN);
            currState.motorDir = DIRN_DOWN;
        }
        
        orders_buttonUpdates(currState.floor, nextFloor);

        if(elevio_obstruction() && currState.doorOpen){
            currState.stopped = 1;
            currState.Stop = USER_STOP;
        }
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            currState.orderDir = DIRN_STOP;
            elevio_stopLamp(1);
            orders_removeAll();
            if (floor>=0){
                currState.stopped = 1;
                currState.Stop = USER_STOP;
            }
        }
        else{
            elevio_stopLamp(0);
        }
        if (currState.stopped){
            currState.doorOpen = 1;
            door_open(&currState, nextFloor); //Not implemented
            currState.stopped = 0;
        }
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
}