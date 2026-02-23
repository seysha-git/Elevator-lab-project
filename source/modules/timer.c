#include "timer.h"

time_t start, end;
static int timerActive = 0;

int timer_start(){
    /*
    if(!timerActive){
        start = time(NULL);
    }
    timerActive = 1;
    */
    start = time(NULL);
    return start;
}


int timer_elapsedTime(){
    end = time(NULL);
    return end;
}

void timer_displayPassedTime(){
    printf("%.2f", difftime(end, start));
}

