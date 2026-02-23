
#include "main.h"

void dox_test_1(){
    printf("Hello world");
}
void dox_test_2(){
    printf("No poles in right half planeeee!");
}

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the hello stop button on the elevator panel to exit\n");
  
    int defined = 0;
    int ventet = 0;
    int currFloor = 0;
    int nextFloor = 0;

    
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
      
    while(1){
        int floor = elevio_floorSensor();
        if (floor>=0){
            currFloor = floor;
        }
        
        if (currFloor==nextFloor){ 
            int start = timer_start();
            elevio_motorDirection(DIRN_STOP);
            while (difftime(timer_elapsedTime(), start)<3){
                elevio_doorOpenLamp(1);
            }
            elevio_doorOpenLamp(0);
            nextFloor = 1;
            
        }

        if (currFloor<nextFloor){
            elevio_motorDirection(DIRN_UP);
        }
        if (currFloor>nextFloor){
            elevio_motorDirection(DIRN_DOWN);
        }

        /*
        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }
        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }
        if(floor == 2 && ventet == 0){
            door_open();
            while(door_waiting()){
                 elevio_motorDirection(DIRN_STOP);
            }
            door_close();
            elevio_motorDirection(DIRN_UP);
            ventet = 1;
        }
        */
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed>0){
                    nextFloor = f;
                }
                elevio_buttonLamp(f, b, btnPressed);
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
    //timer_displayPassedTime();
    return 0;
}
