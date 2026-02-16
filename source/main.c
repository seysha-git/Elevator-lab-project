#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "main.h"
#include "modules/orders.h"

void dox_test_1(){
    printf("Hello world");
}
void dox_test_2(){
    printf("No poles in right half planeeee!");
}

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    
    int defined = 0;
    int motorDir = 0;
    int currFloor = 0;
    while(1){
        int floor = elevio_floorSensor();
        int nextFloor = orders_nextFloor(floor, &motorDir);


        printf("%d Motor dir: ", motorDir);
        printf("\n");
        if((floor<0) && !defined){
            elevio_motorDirection(DIRN_DOWN);   
        }
        else {
            elevio_motorDirection(DIRN_STOP);
            defined = 1;
        }
        
        if(floor>=0){
            currFloor = floor;
            elevio_floorIndicator(currFloor);
        }
        
        if (currFloor == nextFloor){
            elevio_motorDirection(DIRN_STOP);
            orders_removeOrder(currFloor);
        }
        if (nextFloor > currFloor){
            elevio_motorDirection(DIRN_UP);
        }
        if (nextFloor < currFloor){
            elevio_motorDirection(DIRN_DOWN);
        }

        for (int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed>0){
                    orders_addOrder(f, b, currFloor);
                    printf("%d \n", nextFloor);
                }
            }
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
