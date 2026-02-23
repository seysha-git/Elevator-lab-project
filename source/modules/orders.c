#include "orders.h"


int g_ordersUp[4] = {0, 0, 0, 0};
int g_ordersDown[4] = {0, 0, 0, 0};
int switched = 1;

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

void orders_removeOrder(int floor){
    g_ordersDown[floor] = 0;
    g_ordersUp[floor] = 0;
}

void orders_removeAll(){
    for (int i = 0; i < N_FLOORS; i++){
        g_ordersDown[i] = 0;
        g_ordersUp[i] = 0;
    }
}

int orders_nextFloor(int currFloor, MotorDirection *motorDir){
    int nextFloor = currFloor;
    
    /*
    
    if (DIRN_DOWN og akkurat switchet):
        Gå til den øverste etasjen som mulig.
    else if (DIRN_DOWN og ikke akkurat switchet)
        Gå til den nærmeste etasjen under


    */
    
    switch (*motorDir){
        case DIRN_DOWN:
            if (switched){
                for (int f = N_FLOORS-1; f>=0; f--){
                    if (g_ordersDown[f]==1){
                        nextFloor = f;
                        break;
                    }
                }
                switched = 0;
            }
            else{
                for (int f = currFloor; f >=0; f--){
                    if (g_ordersDown[f] == 1){
                        nextFloor = f;
                        break;
                    }
                }
                if(nextFloor==currFloor){
                    *motorDir = DIRN_UP;
                    switched = 1;
                }
            }
            break;
        case DIRN_UP:
            if (switched){
                for (int f = 0; f < N_FLOORS; f++){
                    if (g_ordersUp[f]==1){
                        nextFloor = f;
                        break;
                    }
                }
                switched = 0;
            }
            for (int f = currFloor; f < N_FLOORS; f++){
                if (g_ordersUp[f] == 1){
                    nextFloor = f;
                    break;
                }
            }
            if (nextFloor==currFloor){
                *motorDir = DIRN_DOWN;
                switched = 1;
            }
            break;
        case DIRN_STOP:
            break;

    }
    return nextFloor;
}



//S.S implementasjon

static int floorOrders[4] = {0, 0, 0, 0};
static int floorActive[4] = {0,0,0,0};
void orders_moveElevator(int order_floor, ButtonType btnType, int elevator_floor, MotorDirection *motorDir){
    if(elevator_floor < order_floor){

    }
    else if(elevator_floor > order_floor){

    }
    else







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