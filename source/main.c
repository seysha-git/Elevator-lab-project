#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "driver/elevio.h"
#include "main.h"
#include "./modules/orders.h"

void dox_test_1(){
    printf("Hello world");
}
void dox_test_2(){
    printf("No poles in right half planeeee!");
}

int main(){
    
    elevio_init();
     int defined = 0;
    int elevatorFloor = 0;
    
    while(!defined){
        int floor = elevio_floorSensor();
        if(floor<0){
            elevio_motorDirection(DIRN_DOWN);   
        }
        else {
            elevio_motorDirection(DIRN_STOP);
            defined = 1;
        }
    }

    orders_init();
    while(1){
        int floor = elevio_floorSensor();   
        if(floor >= 0){
            elevatorFloor = floor;
        } 
        for (int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed>0){
                    orders_addOrder(f, elevatorFloor, b);
                }
            }
        }


        if(orders_checkOrder() >= 0){
            int destinationFloor = orders_getDestinationFloor();
            if(elevatorFloor != destinationFloor){
                elevio_motorDirection(orders_getDirection());
            }
            else{
                elevio_motorDirection(DIRN_STOP);
                //orders_resetOrder(destinationFloor);
            }
        }
        else{
            elevio_motorDirection(DIRN_STOP);
            //printf("Waiting on order");
        }

        
        
        

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
   
    return 0;
}
