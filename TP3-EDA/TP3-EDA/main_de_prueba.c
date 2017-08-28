#include <stdio.h>
#include "simulation.h"

#define HEIGHT	30
#define WIDTH	20

void printf_piso(pisoType * piso, int filas, int columnas);

int main(int argc, char ** argv)
{
	int i = 0;
	int j = 0;
	srand(time(NULL));
	/* 
	//PRUEBA DE FUNCIONAMIENTO DE ROBOT MANAGMENT
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
	*/
	//PRUEBA DE FUNCIONAMIENTO DE FLOOR MANAGMENT

	pisoType * piso;
	piso = createFloor(WIDTH, HEIGHT);
	printf_piso(piso,HEIGHT,WIDTH);
	changeTileFromFloor(piso, 2, 1, true);
	printf_piso(piso,HEIGHT,WIDTH);
	destroyFloor(piso);
	/*
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

	// PRUEBA DE MOVIMIENTO DE ROBOTS

	robotType * robot;
	robot = createRobot(4, 100, 100);

	(robot + 0)->pos.x = 0.1;
	(robot + 0)->pos.y = 0.1;
	(robot + 0)->angulo = 270;

	(robot + 1)->pos.x = 0.1;
	(robot + 1)->pos.y = 50;
	(robot + 1)->angulo = 135;

	(robot + 2)->pos.x = 50;
	(robot + 2)->pos.y = 99.5;
	(robot + 2)->angulo = 45;

	(robot + 3)->pos.x = 99.9;
	(robot + 3)->pos.y = 50;
	(robot + 3)->angulo = 0;

	for (i = 0; i < 4; i++)
	{
		printf("ROBOT ANTES DE MOVERSE NRO %d:\n", i);
		printf("%f\n", (robot + i)->pos.x);
		printf("%f\n", (robot + i)->pos.y);
		printf("%f\n", (robot + i)->angulo);
		printf("\n");
	}
	moveRobots(robot, 100, 100, 4);
	for (i = 0; i < 4; i++)
	{
		printf("ROBOT DESPUES DE MOVERSE NRO %d:\n", i);
		printf("%f\n", (robot + i)->pos.x);
		printf("%f\n", (robot + i)->pos.y);
		printf("%f\n", (robot + i)->angulo);
		printf("\n");
	}
	*/
	getchar();
	return 0;
}

void printf_piso(pisoType * piso, int filas, int columnas)
{
	int i, j;
	for (i = 0; i < filas; i++)
	{
		for (j = 0; j < columnas; j++)
		{
			printf("%d ", getTileFromFloor(piso, i, j));
		}
		printf("\n");
	}
	printf("\n");
}