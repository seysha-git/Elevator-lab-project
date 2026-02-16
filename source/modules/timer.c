#include "timer.h"

static time_t start, end;
static int timerActive = 0;

void timer_start(){
    if(!timerActive){
        start = time(NULL);
    }
    timerActive = 1;
}

void timer_end(){
    if(timerActive){
        end = time(NULL);
    }
    timerActive = 0;
}

int timer_timePassed(int final_time){
    if(difftime(end, start) >= final_time){
        return 1;
    };
    return 0;
}

void timer_displayPassedTime(){
    printf("%.2f", difftime(end, start));
}