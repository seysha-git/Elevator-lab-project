#include "orders.h"


int g_ordersUp[4] = {0, 0, 0, 0};
int g_ordersDown[4] = {0, 0, 0, 0};
int first_order = 0;

void orders_addOrder(int floor, ButtonType btnType, int currFloor){    
    if(btnType == BUTTON_HALL_UP){
        g_ordersUp[floor] = 1;
    }
    if(btnType == BUTTON_HALL_DOWN){
        g_ordersDown[floor] = 1;
    }
    if(btnType== BUTTON_CAB){
        if(floor>currFloor){
            g_ordersUp[floor] = 1;
        }
        if(floor<currFloor){
            g_ordersDown[floor] = 1;
        }
    }
    for(int i =0; i <4; i++){
        printf("%d ", g_ordersUp[i]);
    }
}

void orders_removeOrder(int floor, int *switched){
    if ((g_ordersDown[floor]!=0) || g_ordersUp[floor]!=0){
        *switched = 0;
    }
    g_ordersDown[floor] = 0;
    g_ordersUp[floor] = 0;
}

void orders_removeAll(){
    for (int i = 0; i < N_FLOORS; i++){
        g_ordersDown[i] = 0;
        g_ordersUp[i] = 0;
    }
}

int orders_checkOrders(int floor){
    if (g_ordersDown[floor]==1 || g_ordersUp[floor]==1){
         return 1;
    }
    return 0;
}

int orders_nextFloor(int currFloor, MotorDirection *motorDir, int *switched){
    int nextFloor = currFloor;
    
    /*
    
    if (DIRN_DOWN og akkurat switchet):
        Gå til den øverste etasjen som mulig.
    else if (DIRN_DOWN og ikke akkurat switchet
        Gå til den nærmeste etasjen under


    */
    
    switch (*motorDir){
        case DIRN_DOWN:
            if (*switched){
                for (int f = N_FLOORS-1; f>=0; f--){
                    if (g_ordersDown[f]==1){
                        nextFloor = f;
                        break;
                    }
                }
            }
            else{
                for (int f = currFloor; f >=0; f--){
                    if (g_ordersDown[f] == 1){
                        nextFloor = f;
                        break;
                    }
                }
            }
            if(nextFloor==currFloor){
                *motorDir = DIRN_UP;
                *switched = 1;
            }
            break;

        case DIRN_UP:
            if (*switched){
                for (int f = 0; f < N_FLOORS; f++){
                    if (g_ordersUp[f]==1){
                        nextFloor = f;
                        break;
                    }
                }
            }
            else{ 
                for (int f = currFloor; f < N_FLOORS; f++){
                    if (g_ordersUp[f] == 1){
                        nextFloor = f;
                        break;
                    }
                }
            }
            if (nextFloor==currFloor){
                *motorDir = DIRN_DOWN;
                *switched = 1;
            }
            break;
        case DIRN_STOP:
            break;

    }
    return nextFloor;
}


void orders_addOrderLight(int floor, ButtonType btnType){
    elevio_buttonLamp(floor, btnType, 1);
}
void orders_removeOrderLight(int floor){
    for(int b = 0; b < N_BUTTONS; b++){
        elevio_buttonLamp(floor, b, 0);  
    }
}

void orders_removeAllOrderLight(){
    for (int b = 0; b < N_BUTTONS; b++){
        for (int f = 0; f < N_FLOORS; f++){
            elevio_buttonLamp(f, b, 0);
        }
    }
}

