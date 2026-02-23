#include "orders.h"


static int order_floors[4] =  {0, 0, 0, 0};
struct Order orderUp;
struct Order orderDown;


int orders_checkOrder(){
    if(orderUp.active){return 1;}
    if(orderDown.active){return 0;}
    return -1;
}


void orders_init(){
     orderUp.dir = DIRN_UP;
     orderDown.dir = DIRN_DOWN;
}

void orders_resetOrder(int floor){
    order_floors[floor] = 0;
    if(orders_checkOrder() == 1){
        orderUp.active = 0;
    }
    if(orders_checkOrder() == 0){
        orderDown.active = 0;
    }
}

MotorDirection orders_getDirection(){
    if(orders_checkOrder() == 1){return orderUp.dir;}
    if(orders_checkOrder() == 0){return orderDown.dir;}
}

int orders_getDestinationFloor(){
    if(orders_checkOrder() == 1){return orderUp.destFloorm;}
    if(orders_checkOrder() == 0){return orderDown.destFloorm;}
}

int orders_checkNewOrders(int newElevatorFloor){
    if(orders_checkOrder() == 1 && order_floors[newElevatorFloor] == 1){
        return 1;    
        
    }
    if(orders_checkOrder() == 0 && order_floors[newElevatorFloor] == 0){
            return 1;
    }
    return 0;

}

void orders_addOrder(int currDestFloor, int elevatorFloor, ButtonType btnType){
    orderUp.btnType = btnType;
    orderUp.destFloorm = currDestFloor;

    if(elevatorFloor < currDestFloor && !orderUp.active){
       
        orderUp.active = 1;
        orderDown.active = 0;
        order_floors[currDestFloor] = btnType;

    }
    else if(currDestFloor > orderUp.destFloorm && orderUp.btnType == btnType){
        orderUp.destFloorm = currDestFloor;
    }

    if(elevatorFloor > currDestFloor && !orderDown.active){
        
        orderDown.active = 1;
        orderUp.active = 0;
        order_floors[currDestFloor] = btnType;
    }
    else if(currDestFloor < orderUp.destFloorm && orderDown.btnType == btnType){
        orderDown.destFloorm = currDestFloor;
    }
    
    for(int i = 0; i < 4; i++){
        printf("%d ", order_floors[i]);
    }
    
}

