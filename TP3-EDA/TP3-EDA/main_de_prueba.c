#include <stdio.h>
#include "simulation.h"


int main(int argc, char ** argv)
{
	int i = 0;
	int j = 0;
	/* 
	//PRUEBA DE FUNCIONAMIENTO DE ROBOT MANAGMENT
	srand(time(NULL));
	robotType * robot;
	robot = createRobot(5, 100, 100);
	for (i = 0; i < 5; i++)
	{
		printf("ROBOT NRO %d:\n", i);
		printf("%f\n", (robot+i)->pos.x);
		printf("%f\n", (robot+i)->pos.y);
		printf("%f\n", (robot+i)->angulo);
		printf("\n");
	}
	posType coord;
	coord = getRobotPos(robot);
	printf("x: %f	y: %f", coord.x, coord.y);
	destroyRobots(robot);
	

	//PRUEBA DE FUNCIONAMIENTO DE FLOOR MANAGMENT

	pisoType * piso;
	piso = createFloor(100, 100);
	//NO ESTA INICLIAIZANDO CON FALSE!
	for (i = 0; i < 100 ; i++)
	{
		for (j = 0; j < 100; j++)
		{
			printf("%d	", getTileFromFloor(piso, i, j));
		}
		printf("\n");
	}
	changeTileFromFloor(piso, 0, 0, false);
	printf("%d\n", getTileFromFloor(piso, 0, 0));
	destroyFloor(piso);
	*/

	//PRUEBA DE FUNCIONAMIENTO DEL SIMULATOR MANAGMENT
	simType * simulation;
	simulation = createSim(5, 100, 100);
	printf("SIMULATION DATA:\n\n");
	printf("	height: %d\n", simulation->height);
	printf("	width: %d\n", simulation->width);
	printf("	robot count: %d\n", simulation->robotCount);
	printf("	tick count: %d\n", simulation->tickCount);
	printf("	poiner to floor: %p\n\n", simulation->piso);
	for (i = 0; i < 5; i++)
	{
		printf("ROBOT NRO %d:\n", i);
		printf("%f\n", ((simulation->robots )+ i)->pos.x);
		printf("%f\n", ((simulation->robots) + i)->pos.y);
		printf("%f\n", ((simulation->robots) + i)->angulo);
		printf("\n");
	}
	destroySim(simulation);

	return 0;
}

//ME FALTA:
//MOVEROBOT
//INICILAIZAR BALDOSAS