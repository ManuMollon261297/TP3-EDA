#ifndef SIM_GRAPHICS
#define SIM_GRAPHICS

#include "config.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_color.h>

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

// init_sim_graphics: loads allegro hardware and images, if not returns 0
int init_sim_graphics(sim_graphics_t *sim_graphics);

// destroy_sim_graphics: destroys simulation graphics
void destroy_sim_graphics(sim_graphics_t *sim_graphics);

// draw_floor: draws the actual floor into allegro display
void draw_floor(sim_graphics_t *sim_graphics, pisoType *piso);

// draw_robots: draws all the robots into allegro display
void draw_all_robots(sim_graphics_t *sim_graphics, robotType *robots, pisoType *piso, unsigned int cntRobots);

#endif // !SIM_GRAPHICS
