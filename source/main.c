#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "driver/elevio.h"
#include "main.h"
#include "modules/orders.h"

void dox_test_1(){
    printf("Hello world");
}
void dox_test_2(){
    printf("No poles in right half planeeee!");
}

void main_buttonUpdates(int currFloor, int nextFloor){
    for (int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed>0){
                    orders_addOrder(f, b, currFloor);
                    orders_addOrderLight(f, b);
                    printf("%d \n", nextFloor);
                }
            }
        }
}

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    
    int defined = 0;
    MotorDirection orderDir = DIRN_DOWN;
    MotorDirection motorDir = DIRN_STOP;
    int currFloor = 0;
    int nextFloor = 0;
    int switched = 1;
    int stopped = 0;
    
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

    while(1){
        int floor = elevio_floorSensor();    
        if(floor>=0){
            currFloor = floor;
            elevio_floorIndicator(currFloor);
        }
        
        nextFloor = orders_nextFloor(currFloor, &orderDir, &switched);  
        
        if (currFloor == nextFloor && !stopped){
            elevio_motorDirection(DIRN_STOP);
            timer_start(currFloor, stopped);
            while(!timer_elapsedTime()){
                elevio_doorOpenLamp(1);
                main_buttonUpdates(currFloor,nextFloor);
            }
            elevio_doorOpenLamp(0);
            
            if (floor==-1 && orders_checkOrders(currFloor)){
                if (motorDir==DIRN_DOWN){
                    currFloor = nextFloor -1;
                }
                else{
                    currFloor = nextFloor + 1;
                }
            }
            if (floor>=0){
                orders_removeOrder(currFloor, &switched);
                orders_removeOrderLight(currFloor);
            }
        }

        
        if (nextFloor > currFloor){
            elevio_motorDirection(DIRN_UP);
            motorDir = DIRN_UP;
        }
        if (nextFloor < currFloor){
            elevio_motorDirection(DIRN_DOWN);
            motorDir = DIRN_DOWN;
        }

        main_buttonUpdates(currFloor, nextFloor);

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            orders_removeAll();
            orders_removeAllOrderLight();
            if (floor>=0){
                elevio_doorOpenLamp(1);
                stopped = 1;
            }
        }
        else if (stopped){
            timer_start(currFloor, stopped);
            while(!timer_elapsedTime()){
                elevio_doorOpenLamp(1);
                main_buttonUpdates(currFloor,nextFloor);
            }
            elevio_doorOpenLamp(0);
            stopped = 0;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    //timer_displayPassedTime();
    return 0;
}
