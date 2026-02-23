
#include "main.h"
#include "driver/elevio.h"

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
    printf(" hello");
    elevio_motorDirection(DIRN_DOWN);
  



    int defined = 0;
    int ventet = 0;
    MotorDirection motorDir = DIRN_DOWN;
    int currFloor = 0;


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
        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }
        if(floor == 0){
            printf("0");
            elevio_motorDirection(DIRN_UP);
        }
        /*
         if(floor == 2 && !ventet){
            printf("in story 2 \n ");
            door_open();
            while(door_waiting()){
                 elevio_motorDirection(DIRN_STOP);
            }
            printf("finished waiting \n");
            elevio_motorDirection(DIRN_DOWN);
            door_close();
            ventet = 1;
        }

        */
       
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
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
