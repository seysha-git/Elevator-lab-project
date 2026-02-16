#include "orders.h"


int g_ordersUp[4] = {0, 0, 0, 0};
int g_ordersDown[4] = {0, 0, 0, 0};

void orders_addOrder(int floor, int btnType, int motorDir){
    int currFloor = elevio_floorSensor();
    switch (motorDir){
        case 0:
            printf("Down");
            
            //  Legger til bestillingen i riktig liste
            if ((currFloor>floor) && btnType>0){
                g_ordersDown[floor] = 1;
            }
            else {
                g_ordersUp[floor] = 1;
            }
            
            break;
        case 1:
            printf("Up");
            
            if ((currFloor<floor) && (btnType == 0 || btnType ==2)){
                g_ordersUp[floor] = 1;
            }
            else {
                g_ordersDown[floor] = 1;
            }
            break;
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

int orders_nextFloor(int currFloor, int motorDir){
    int nextFloor = currFloor;
    switch (motorDir){
        case 0:
            motorDir = 1;
            for (int f = 0; f < currFloor; f++){
                if (g_ordersDown[f] == 1){
                    nextFloor = f;
                    motorDir = 0;
                    break;
                }
            }
        case 1:
            motorDir = 0;
            for (int f = (N_FLOORS-1); f > currFloor; f--){
                if (g_ordersUp[f] == 1){
                    nextFloor = f;
                    motorDir = 1;
                    break;
                }
            }
    }

    return nextFloor;
}
