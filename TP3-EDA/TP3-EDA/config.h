//// -------------- ////
//// CONFIG LIBRARY ////
//// -------------- ////
#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct
{
	unsigned int mode;
	unsigned int width;
	unsigned int height;
        unsigned int robots_count;
}paramsType; // Userdata parametros

typedef struct
{
	double x;
	double y;
}posType; // Estructura de coordenadas

typedef struct
{
	posType pos;
	double angulo; // 0 <Angulo < 360
}robotType; // Estructura del robot

typedef bool tileType; // Tipo de dato de baldosa

typedef struct
{
	unsigned int width;
	unsigned int height;
	tileType * baldosas;
}pisoType; // Estructura de piso

typedef struct
{
	robotType * robots;
	unsigned int robotCount;
	pisoType * piso;
	unsigned int width;
	unsigned int height;
	unsigned long int tickCount;
}simType; // Estructura de la simulacion


#endif /* CONFIG_H */

