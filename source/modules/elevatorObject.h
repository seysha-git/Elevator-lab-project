#include "../driver/elevio.h"
struct elevatorObject{
    int stopped;
    MotorDirection orderDir;
    MotorDirection motorDir;
    int doorOpen;
    int floor;
};