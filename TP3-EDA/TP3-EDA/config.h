#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct
{
	double x;
	double y;
}posType; // estructura de coordenadas

typedef struct
{
	posType pos;
	double angulo; // 0<angulo<360
}robotType; //estructura del robot

typedef bool tileType;

typedef struct
{
	unsigned int width;
	unsigned int height;
	tileType * baldosas;
}pisoType;

typedef struct
{
	robotType * robots;
	unsigned int robotCount;
	pisoType * piso;
	unsigned int width;
	unsigned int height;
	unsigned long int tickCount;
}simType; // estructura de la simulacion

#endif //CONFIG_H
