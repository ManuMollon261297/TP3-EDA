#include "simulation.h"
#include <stdio.h>


#define MAX_ANGLE 360

// Simulation Managment

robotType * createRobot(unsigned int  count, unsigned int height, unsigned int width)
{
	robotType * robots = NULL;
	int i = 0;
	robots = malloc(sizeof(robotType)*count);
	if (robots != NULL)
	{
		for (i = 0; i < count; i++)
		{
			(robots[i]).pos.x = (double) (rand()) / ((double) (RAND_MAX / width));
			(robots[i]).pos.y = (double)(rand()) / ((double)(RAND_MAX / height));
			(robots[i]).angulo = (double)(rand()) / ((double)(RAND_MAX / MAX_ANGLE));
		}
	}
	return robots;
}

void moveRobot(robotType * robots, unsigned int height, unsigned int width)
{

}

posType getRobotPos(robotType * robot)
{
	return (robot->pos);
}

void destroyRobots(robotType * robot)
{
	free(robot);
}

// Floor Managment 

pisoType * createFloor(unsigned int width, unsigned int height)
{
	pisoType * piso;
	int i = 0;
	piso = malloc(sizeof(pisoType));
	if (piso != NULL)
	{
		piso->height = height;
		piso->width = width;
		piso->baldosas = malloc(sizeof(bool)*width*height);
		if (piso->baldosas != NULL)
		{
			for (i = 0; i < (width*height); i++);
			{
				*((piso->baldosas)+i) = false;
			}
		}
		else
		{
			free(piso);
			piso = NULL;
		}
	}
	return piso;
}

bool getTileFromFloor(pisoType * piso, unsigned int fila, unsigned int columna)
{
	return *(piso->baldosas + (fila*(piso->width)) + columna);
}

void changeTileFromFloor(pisoType * piso, unsigned int fila, unsigned int columna, bool value)
{
	*(piso->baldosas + (fila*(piso->width)) + columna) = value;
}

void destroyFloor(pisoType * piso)
{
	free(piso);
}

// Simulation Managment

simType * createSim(unsigned int robotCount, unsigned int height, unsigned int width)
{
	simType * sim = NULL;
	sim = malloc(sizeof(simType));
	if (sim != NULL)
	{
		sim->piso = createFloor(height, width);
		sim->robots = createRobot(robotCount, width, height);
		sim->height = height;
		sim->width = width;
		sim->robotCount = robotCount;
		sim->tickCount = 0;
	}
	else
	{
		free(sim);
		sim = NULL;
	}
	if ((sim->piso == NULL)||(sim->robots == NULL))
	{
		free(sim);
		sim = NULL;
	}
	return  sim;
}

void destroySim(simType * simulation)
{
	free(simulation->piso);
	free(simulation->robots);
}