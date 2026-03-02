#include "main.h"

void dox_test_1(){
    printf("Hello world");
}
void dox_test_2(){
    printf("No poles in right half planeeee!");
}


int main(){
    elevio_init();
    elevator_runStartUp();
    elevator_runOrders();
    return 0;
}