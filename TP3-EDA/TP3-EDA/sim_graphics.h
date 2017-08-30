/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sim_graphics.h
 * Author: matias
 *
 * Created on August 28, 2017, 8:33 PM
 */

#ifndef SIM_GRAPHICS_H
#define SIM_GRAPHICS_H

#include "config.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define DISP_W 1280
#define DISP_H 720

#define OFFSET_EJES (0.13)
#define GROSOR_EJE_PRED 2
#define OFFSET_INDICADOR 3
#define SEPARACION_Y 4
#define OFFSET_HISTOGRAMA 8
#define FONT_SIZE ((OFFSET_HISTOGRAMA * 3)/2)
#define FONT_TYPE "Raleway-Black.ttf"
#define TOLERANCE_FONT_ROBOT 28


typedef struct {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *ev_queue;
} allegro_hard_t;

typedef struct {
	ALLEGRO_BITMAP *dirtyTile;
	ALLEGRO_BITMAP *cleanTile;
	ALLEGRO_BITMAP *robotBody;
} sim_images_t;

typedef struct {
	allegro_hard_t al_hard;
	sim_images_t sim_images;
} sim_graphics_t;

typedef struct {
    unsigned int apartamiento_x;    //margenes
    unsigned int apartamiento_y;    
    float xMax;                     //valores maximos
    float yMax;
    float elem_escala_x;            //salto de elemento a elemento
    float elem_escala_y;
    unsigned int long_eje_x;        //
    unsigned int long_eje_y;
    unsigned int grosor;            //
    char * variableX;               //nombre de las variables
    char * variableY;
    unsigned int numElemX;          //numero total de elementos
    unsigned int numElemY;
    unsigned int origenX;           //comienzo de los ejes (cruce entre si)
    unsigned int origenY;
}ejeCartesiano_t;

// init_sim_graphics: loads allegro hardware and images, if not returns 0
int init_sim_graphics(sim_graphics_t *sim_graphics);

// destroy_sim_graphics: destroys simulation graphics
void destroy_sim_graphics(sim_graphics_t *sim_graphics);

// draw_floor: draws the actual floor into allegro display
void draw_floor(sim_graphics_t *sim_graphics, pisoType *piso);

// draw_robots: draws all the robots into allegro display
void draw_all_robots(sim_graphics_t *sim_graphics, robotType *robots, pisoType *piso, unsigned int cntRobots);

void print_histograma_bar(double * results, ejeCartesiano_t * eje, ALLEGRO_COLOR color1, ALLEGRO_COLOR color2, char * font_type, ALLEGRO_COLOR color_font);

ejeCartesiano_t create_eje_cartesiano(unsigned int anchoTotal, unsigned int altoTotal, double xMax, double yMax, char * varX, char * varY);

void print_eje_cartesiano(ejeCartesiano_t * eje, ALLEGRO_COLOR color, char * font_type);

void print_wait_text(char * font_type, unsigned int alto, unsigned int ancho);

void clear_display(void);

void print_titulo(unsigned int width_baldosa, unsigned int height_baldosa, unsigned int alto, unsigned int ancho, char * font_type);

#endif /* SIM_GRAPHICS_H */

