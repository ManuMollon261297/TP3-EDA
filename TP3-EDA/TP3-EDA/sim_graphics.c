#include <stdio.h>
#include "sim_graphics.h"
#include "simulation.h"

#define DISP_W 1280
#define DISP_H 720

// init_al_hard: initializes allegro display and addons
int init_al_hard(allegro_hard_t *al_hard);

// load_sim_images: loads images for simulation mode 1
int load_sim_images(sim_images_t *sim_images);

// load_image: loads an image from resources. If not, returns 0
ALLEGRO_BITMAP* load_image(const char *image);

// draw_tile: draws one tile into given position
void draw_tile(sim_images_t *sim_images, pisoType *piso, unsigned int fil, unsigned int col);

// draw_robot: draws one robot in new position
void draw_robot(sim_images_t *sim_images, pisoType *piso, robotType *robot);

// destroy_images: destroy tiles and robot images
void destroy_images(sim_images_t *sim_images);

// destroy_al_hard: destroys allegro hardware used
void destroy_al_hard(allegro_hard_t *al_hard);

posType calculate_FloorStart(unsigned int width, unsigned int height);

double calculate_baldosaPixel(unsigned int width, unsigned int height);

int init_al_hard(allegro_hard_t *al_hard) {
	int ret = 1;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		ret = -1;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize image addon !\n");
		ret = -1;
	}

	al_hard->display = al_create_display(DISP_W, DISP_H);
	if (!(al_hard->display)) {
		fprintf(stderr, "failed to create display!\n");
		ret = -1;
	}

return ret;
}

ALLEGRO_BITMAP* load_image(const char *image) {

	ALLEGRO_BITMAP *image_png = NULL;
	image_png = al_load_bitmap(image);
	if (!image_png) {
		fprintf(stderr, "failed to load image !\n");
		return 0;
	}
	return image_png;
}

int load_sim_images(sim_images_t *sim_images) {

	int ret = 1;
	sim_images->cleanTile = load_image("Images/cleanTile.png");
	if (!(sim_images->cleanTile)) {
		ret = -1;
	}
	sim_images->dirtyTile = load_image("Images/dirtyTile.png");
	if (!(sim_images->dirtyTile)) {
		ret = -1;
	}
	sim_images->robotBody = load_image("Images/robot.png");
	if (!(sim_images->robotBody)) {
		ret = -1;
	}
	return ret;
}

int init_sim_graphics(sim_graphics_t *sim_graphics) {
	int aux = 1;
	aux = init_al_hard(&(sim_graphics->al_hard));
	if (aux == -1) {
		return 0;
	}

	aux = load_sim_images(&(sim_graphics->sim_images));
	if (aux == -1) {
		return 0;
	}
	return aux;
}

double calculate_baldosaPixel(unsigned int width, unsigned int height) {
	double pixels;
	if ((DISP_W / width) >= DISP_H / height) {
		pixels = (DISP_H - 20) / height;
	}
	else {
		pixels = (DISP_W - 20) / width;
	}
	return pixels;
}

posType calculate_FloorStart(unsigned int width, unsigned int height) {
	posType coord_start;
	double baldosa_pixels = calculate_baldosaPixel(width, height);

	coord_start.x = (DISP_W - (baldosa_pixels * width)) / 2;
	coord_start.y = (DISP_H - (baldosa_pixels * height)) / 2;

	return coord_start;
}

void draw_tile(sim_images_t *sim_images, pisoType *piso, unsigned int fila, unsigned int columna) {

	posType floorStart = calculate_FloorStart(piso->height, piso->width);
	posType baldosaPoint;
	double pixels = calculate_baldosaPixel(piso->height, piso->width);
	double sw, sh;
	sw = al_get_bitmap_width(sim_images->dirtyTile); // Its the same original size for both images
	sh = sw;
	bool baldosa_clean = getTileFromFloor(piso, fila, columna);

	baldosaPoint.x = floorStart.x + (columna * pixels);
	baldosaPoint.y = floorStart.y + (fila * pixels);

	if (!baldosa_clean) {
		al_draw_scaled_bitmap(sim_images->dirtyTile, 0, 0, sw, sh, baldosaPoint.x, baldosaPoint.y, pixels, pixels, 0);
	}
	else {
		al_draw_scaled_bitmap(sim_images->cleanTile, 0, 0, sw, sh, baldosaPoint.x, baldosaPoint.y, pixels, pixels, 0);
	}
}

void draw_floor(sim_graphics_t *sim_graphics, pisoType *piso) {

	for (unsigned int i = 0; i < piso->width; i++) {
		for (unsigned int j = 0; j < piso->height; j++) {
			draw_tile(&(sim_graphics->sim_images), piso, i, j);
		}
	}
}

void draw_robot(sim_images_t *sim_images, pisoType *piso, robotType *robot) {

	posType floorStart = calculate_FloorStart(piso->height, piso->width);
	posType robotPoint;
	double pixels = calculate_baldosaPixel(piso->height, piso->width);
	double sw, sh;
	sw = al_get_bitmap_width(sim_images->robotBody);
	sh = sw;

	if ((((piso->height) - (robot->pos.x))*pixels) < (pixels / 4)) {
		robotPoint.x = floorStart.x + (((piso->height) - 0.25)*pixels) - (pixels / 4);
	}
	else if (((robot->pos.x)*pixels) < (pixels / 4)) {
		robotPoint.x = floorStart.x;
	}
	else {
		robotPoint.x = floorStart.x + ((robot->pos.x)*pixels) - (pixels / 4);
	}

	if ((((piso->width) - (robot->pos.y))*pixels) < (pixels / 4)) {
		robotPoint.y = floorStart.y + (((piso->width) - 0.25)*pixels) - (pixels / 4);
	}
	else if (((robot->pos.y)*pixels) < (pixels / 4)) {
		robotPoint.y = floorStart.y;
	}
	else {
		robotPoint.y = floorStart.y + ((robot->pos.y)*pixels) - (pixels / 4);
	}

	al_draw_scaled_bitmap(sim_images->robotBody, 0, 0, sw, sh, robotPoint.x, robotPoint.y, pixels / 2, pixels / 2, 0);
}


void draw_all_robots(sim_graphics_t *sim_graphics, robotType *robots, pisoType *piso, unsigned int cntRobots) {
	for (size_t i = 0; i < cntRobots; i++)
	{
		draw_robot(&(sim_graphics->sim_images), piso, (robots + i));
	}
}

void destroy_images(sim_images_t *sim_images) {
	al_destroy_bitmap(sim_images->cleanTile);
	al_destroy_bitmap(sim_images->dirtyTile);
	al_destroy_bitmap(sim_images->robotBody);
}

void destroy_al_hard(allegro_hard_t *al_hard) {
	al_destroy_display(al_hard->display);
	//al_destroy_event_queue(al_hard->ev_queue);
}

void destroy_sim_graphics(sim_graphics_t *sim_graphics) {
	destroy_al_hard(&(sim_graphics->al_hard));
	destroy_images(&(sim_graphics->sim_images));
}