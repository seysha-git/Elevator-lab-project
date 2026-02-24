#include "timer.h"

time_t start, end;
static int timerActive = 0;
int previousFloor = -1;

void timer_start(int floor, int stopped){
    if( !timerActive && (previousFloor != floor || stopped)){
        start = time(NULL);
        previousFloor = floor;
        timerActive = 1;
    }    
}


int timer_elapsedTime(){
    end = time(NULL);
    if(timerActive){
        if(difftime(end, start) >= 3){
            timerActive = 0;
            return 1;
        }
        return 0;
        
    }
    return 1;
}

void timer_displayPassedTime(){
    printf("%.2f", difftime(end, start));
}

