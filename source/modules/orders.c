#include "orders.h"


int g_ordersUp[4] = {0, 0, 0, 0};
int g_ordersDown[4] = {0, 0, 0, 0};
MotorDirection nextDir = DIRN_DOWN;

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

    // Når enden er nådd skal de etasjene som fortsatt er i lista overføres til den andre listen.

    switch (*motorDir){
        case DIRN_DOWN:
            for (int f = currFloor; f >= 0; f--){
                if (g_ordersDown[f]==1){
                    nextFloor = f;
                    break;
                }
            }
            if (nextFloor==currFloor){
                *motorDir = DIRN_UP;
            }
            for (int f = currFloor; f < N_FLOORS; f++){
                if (g_ordersDown[f]==1){
                    g_ordersUp[f] = 1;
                }
            }
        break;
        case DIRN_UP:
            for (int f = currFloor; f < N_FLOORS; f++){
                if (g_ordersUp[f]==1){
                    nextFloor = f;
                    break;
                }
            }
            if (nextFloor==currFloor){
                *motorDir = DIRN_UP;
            }
            for (int f = currFloor; f >= 0; f--){
                if (g_ordersUp[f]==1){
                    g_ordersDown[f] = 1;
                }
            }
        break;
    }
      

    /*
    switch (*motorDir){
        case DIRN_DOWN:
            *motorDir = DIRN_UP;
            for (int f = currFloor; f >=0; f--){
                if (g_ordersDown[f] == 1){
                    nextFloor = f;
                    *motorDir = DIRN_DOWN;
                    break;
                }
            }
        case DIRN_UP:
            *motorDir = DIRN_DOWN;
            for (int f = currFloor; f < N_FLOORS; f++){
                if (g_ordersUp[f] == 1){
                    nextFloor = f;
                    *motorDir = DIRN_UP;
                    break;
                }
            }
            break;
        case DIRN_STOP:
            break;

    }*/
    return nextFloor;
}
