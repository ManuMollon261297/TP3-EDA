#include <stdio.h>
#include "simulation.h"

#define HEIGHT	30
#define WIDTH	20

typedef struct
{
	unsigned int mode;
	unsigned int width;
	unsigned int height;
}paramsType;

void printf_piso(pisoType * piso, int filas, int columnas);

void init_arr(double * ptr2arr, unsigned int size);

unsigned int simulate_quick(simType * sim);

void print_histograma_bar(double * results, unsigned int r, double height, double width);

clean_floor(simType * sim, unsigned int * floorCleaned);

int main(int argc, char ** argv)
{
	srand((unsigned int)time(NULL));
	paramsType params = {2,100,100};
	if (params.mode == 2)
	{
		bool found = false;
		int r = 0;
		int j = 0;
		unsigned long int suma = 0;
		simType * sim;
		unsigned int time;
		double results[50];
		init_arr(results, 50);
		for (r = 0; (r < 50) && (!found); r++)
		{
			suma = 0;
			for (j = 0; j < 1000; j++)
			{
				sim = createSim(r + 1, params.height, params.width);
				if (sim != NULL)
				{
					time = simulate_quick(sim);
				}
				else
				{
					printf("Error in Simulation Nro %d-%d\n", r, j);
					return 0;
				}
				destroySim(sim);
				suma += time;
			}
			results[r] = suma / 1000.0;
			if ((r>0) && ((results[r-1] - results[r]) < 0.1))
			{
				found = true;
			}
		}
		print_histograma_bar(results,r, params.height, params.width);
	}

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

void init_arr(double * ptr2arr, unsigned int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		ptr2arr[i] = 0;
	}
}

unsigned int simulate_quick(simType * sim)
{
	unsigned int tickCount = 0;
	unsigned int floorCleaned = 0;
	//while (floorCleaned != (sim->height)*(sim->width))
	while (floorCleaned <
	(sim->height)*(sim->width))
	{
		clean_floor(sim,&floorCleaned);
		moveRobots(sim->robots, sim->height, sim->width, sim->robotCount);
		tickCount++;
	}
	return tickCount;
}

clean_floor(simType * sim, unsigned int * floorCleaned) 
{
	int i = 0;
	int fila = 0;
	int columna = 0;
	for (i = 0; i < (sim->robotCount); i++)
	{
		// columna = floor((sim->robots + i)->pos.x) + 1;
		// fila = floor((sim->robots + i)->pos.y) + 1;
		columna = ((int)((sim->robots + i)->pos.x));
		fila = ((int)((sim->robots + i)->pos.y));
		if (!getTileFromFloor(sim->piso,fila,columna))
		{
			changeTileFromFloor(sim->piso, fila, columna, true);
			(*floorCleaned)++;
		}
	}
}

void print_histograma_bar(double * results, unsigned int r, double height, double width)
{
	int i = 0;
	for (i=0;i<r;i++)
	{
		printf("Nro Robots:%d -> PROMEDIO: %f\n", i+1, results[i]);
	}
}















/*

//
int i = 0;

simType * simulation;
simulation = createSim(5, 10, 5);
printf("SIMULATION DATA:\n\n");
printf("	height: %d\n", simulation->height);
printf("	width: %d\n", simulation->width);
printf("	robot count: %d\n", simulation->robotCount);
printf("	tick count: %d\n", simulation->tickCount);
printf("	poiner to floor: %p\n\n", simulation->piso);
for (i = 0; i < 5; i++)
{
printf("ROBOT NRO %d:\n", i);
printf("%f\n", ((simulation->robots) + i)->pos.x);
printf("%f\n", ((simulation->robots) + i)->pos.y);
printf("%f\n", ((simulation->robots) + i)->angulo);
printf("\n");
}
printf_piso(simulation->piso, 10, 5);
destroySim(simulation);
paramsType params = { 2,2,2 };

//
int i = 0;
int j = 0;
srand(time(NULL));

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

//PRUEBA DE FUNCIONAMIENTO DE FLOOR MANAGMENT

pisoType * piso;
piso = createFloor(WIDTH, HEIGHT);
printf_piso(piso,HEIGHT,WIDTH);
changeTileFromFloor(piso, 2, 1, true);
printf_piso(piso,HEIGHT,WIDTH);
destroyFloor(piso);

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