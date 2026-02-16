
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
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
            timer_end();
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
            timer_start();
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(floor == 1){
            printf("stoppp");
            elevio_motorDirection(DIRN_STOP);
            door_open();
            if(timer_timePassed(3)){
                door_close();
                elevio_motorDirection(DIRN_UP);

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
    timer_displayPassedTime();
    return 0;
}
