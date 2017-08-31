
#include "simulation.h"
#include <stdio.h>
#include <math.h>

#define MAX_ANGLE	360
#define PI	3.14159265359	

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
void moveRobot(robotType * robot, unsigned int height, unsigned int width)
{
	posType newpos;
	double angle_deg = robot->angulo;
	double angle_rad = deg2rad(robot->angulo);
	newpos.x = (robot->pos.x) + cos(angle_rad);
	newpos.y = (robot->pos.y) + sin(angle_rad);
	if (((newpos.x) > width) || ((newpos.y) > height)||((newpos.x) < 0)||((newpos.y) < 0))
	{
		do
		{
			angle_deg = (double)(rand()) / ((double)(RAND_MAX / MAX_ANGLE));
			double angle_rad = deg2rad(angle_deg);
			newpos.x = (robot->pos.x) + cos(angle_rad);
			newpos.y = (robot->pos.y) + sin(angle_rad);
		} while (((newpos.x) > width) || ((newpos.y) > height) || ((newpos.x) < 0) || ((newpos.y) < 0));
	}
	robot->angulo = angle_deg;
	robot->pos.x = newpos.x;
	robot->pos.y = newpos.y;
}

void moveRobots(robotType * robots, unsigned int height, unsigned int width, unsigned int robotCount)
{
	int i = 0;
	for (i = 0; i < robotCount; i++)
	{
		moveRobot(robots + i, height, width);
	}
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
	int j = 0;
	piso = malloc(sizeof(pisoType));
	if (piso != NULL)
	{
		piso->height = height;
		piso->width = width;
		piso->baldosas = malloc(sizeof(bool)*width*height);
		if (piso->baldosas != NULL)
		{
			for (i = 0; i < width; i++)
			{
				for (j=0; j < height; j++)
				{
					changeTileFromFloor(piso, j, i, false);
				}
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
		sim->piso = createFloor(width, height); // revisar
		sim->robots = createRobot(robotCount, height, width);  //revisar
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

// Others

double deg2rad(double angulo_deg)
{
	return ((angulo_deg*PI)/180.0);
}

void clean_floor(simType * sim, unsigned int * floorCleaned) 
{
	int i = 0;
	int fila = 0;
	int columna = 0;
	for (i = 0; i < (sim->robotCount); i++)
	{
		columna = ((int)((sim->robots + i)->pos.x));
		fila = ((int)((sim->robots + i)->pos.y));
		if (!getTileFromFloor(sim->piso,fila,columna))
		{
			(*floorCleaned)++;
		}
		changeTileFromFloor(sim->piso, fila, columna, true);
	}
}

void init_arr(double * ptr2arr, unsigned int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		ptr2arr[i] = 0;
	}
}


unsigned int simulate(simType * sim, unsigned int * tickCount)
{
	unsigned int floorCleaned = 0;

	clean_floor(sim,&floorCleaned);
	moveRobots(sim->robots, sim->height, sim->width, sim->robotCount);
    (*tickCount)++;   

	return floorCleaned;
}

unsigned int simulate_quick(simType * sim)
{
	unsigned int tickCount = 0;
	unsigned int floorCleaned = 0;
	while (floorCleaned < (sim->height)*(sim->width))
	{
		clean_floor(sim, &floorCleaned);
		moveRobots(sim->robots, sim->height, sim->width, sim->robotCount);
		tickCount++;
	}
	return tickCount;
}
