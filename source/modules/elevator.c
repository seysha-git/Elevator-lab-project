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
    MotorDirection orderDir = DIRN_DOWN;
    MotorDirection motorDir = DIRN_STOP;
    int currFloor = 0;
    int stopped = 0;
    int door = 0;
    int door_finished = 0;


    while(1){
        int floor = elevio_floorSensor();    
        if(floor>=0){
            currFloor = floor;
            elevio_floorIndicator(currFloor);
        }
        
        nextFloor = orders_nextFloor(currFloor, &orderDir);  
        
        if (currFloor == nextFloor && !stopped){
            elevio_motorDirection(DIRN_STOP);
            if (floor==-1 && orders_checkOrders(currFloor)){
                if (motorDir==DIRN_DOWN){
                    currFloor = nextFloor -1;
                }
                else{
                    currFloor = nextFloor + 1;
                }
            }

            if (floor>=0){
                orders_removeOrder(currFloor);
                orders_removeOrderLight(currFloor);
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

        
        if (nextFloor > currFloor){
            elevio_motorDirection(DIRN_UP);
            //door_finished = 0;
            motorDir = DIRN_UP;
        }
        if (nextFloor < currFloor){
            elevio_motorDirection(DIRN_DOWN);
            //door_finished = 0;
            motorDir = DIRN_DOWN;
        }

        orders_buttonUpdates(currFloor, nextFloor);

        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            elevio_stopLamp(1);
            orders_removeAll();
            orders_removeAllOrderLight();
            if (floor>=0){
                elevio_doorOpenLamp(1);
                stopped = 1;
            }
        }
        else if (stopped){

            if(elevio_obstruction()){}
            timer_start(currFloor, stopped);
            while(!timer_elapsedTime()){
                elevio_doorOpenLamp(1);
                orders_buttonUpdates(currFloor,nextFloor);
            }
            elevio_doorOpenLamp(0);
            stopped = 0;
        }
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
}