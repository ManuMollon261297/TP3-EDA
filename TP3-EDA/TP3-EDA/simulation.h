#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Others

double deg2rad(double angulo_deg);

// Robot Managment

robotType * createRobot(unsigned int  count, unsigned int height, unsigned int width); //se asume que se inicializa el seed para el random

void moveRobot(robotType * robots, unsigned int height, unsigned int width); 

void moveRobots(robotType * robots, unsigned int height, unsigned int width, unsigned int robotCount);

posType getRobotPos(robotType * robot);

void destroyRobots(robotType * robot);

// Floor Managment

pisoType * createFloor(unsigned int width, unsigned int height);

bool getTileFromFloor(pisoType * piso, unsigned int fila, unsigned int columna);

void changeTileFromFloor(pisoType * piso, unsigned int fila, unsigned int columna, bool value);

void destroyFloor(pisoType * piso);

// Simulation Managment

simType * createSim(unsigned int robotCount, unsigned int height, unsigned int width);

void destroySim(simType * simulation);

#endif //SIMULATION_H
