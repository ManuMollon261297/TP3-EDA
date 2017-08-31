
#include <stdio.h>
#include "sim_graphics.h"
#include "simulation.h"

#define MODULO(a) ( ( (a >= 0)? a : (a * (-1)) ) )


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
        
    if (!al_init_primitives_addon()){
        fprintf(stderr, "failed to initialize primitives addon !\n");
	ret = -1;
    }

    al_init_font_addon();    
    if(!al_init_ttf_addon())
    {
		al_shutdown_primitives_addon();
        fprintf(stderr, "Failed to initialize Font\n");
        ret = -1;
    }

	al_hard->ev_queue = al_create_event_queue();
	if (!(al_hard->ev_queue)) {
		al_shutdown_primitives_addon();
		al_shutdown_font_addon();
		fprintf(stderr, "failed to create event queue!\n");
		ret = -1;
	}

	al_hard->display = al_create_display(DISP_W, DISP_H);
	if (!(al_hard->display)) {
		al_shutdown_primitives_addon();
		al_shutdown_font_addon();
		al_destroy_event_queue(al_hard->ev_queue);
		fprintf(stderr, "failed to create display!\n");
		ret = -1;
	}

	al_register_event_source(al_hard->ev_queue, al_get_display_event_source(al_hard->display));
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

	posType floorStart = calculate_FloorStart(piso->width, piso->height);
	posType baldosaPoint;
	double pixels = calculate_baldosaPixel(piso->width, piso->height);
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

	for (unsigned int i = 0; i < piso->height; i++) {
		for (unsigned int j = 0; j < piso->width; j++) {
			draw_tile(&(sim_graphics->sim_images), piso, i, j);
		}
	}
}

void draw_robot(sim_images_t *sim_images, pisoType *piso, robotType *robot) {

	posType floorStart = calculate_FloorStart(piso->width, piso->height);
	posType robotPoint;
	double pixels = calculate_baldosaPixel(piso->width, piso->height);
	double sw, sh;
	sw = al_get_bitmap_width(sim_images->robotBody);
	sh = sw;

	if ((((piso->width) - (robot->pos.x))*pixels) < (pixels / 4)) {
		robotPoint.x = floorStart.x + (((piso->width) - 0.25)*pixels) - (pixels / 4);
	}
	else if (((robot->pos.x)*pixels) < (pixels / 4)) {
		robotPoint.x = floorStart.x;
	}
	else {
		robotPoint.x = floorStart.x + ((robot->pos.x)*pixels) - (pixels / 4);
	}

	if ((((piso->height) - (robot->pos.y))*pixels) < (pixels / 4)) {
		robotPoint.y = floorStart.y + (((piso->height) - 0.25)*pixels) - (pixels / 4);
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
	al_destroy_event_queue(al_hard->ev_queue);
	al_destroy_display(al_hard->display);
    al_shutdown_primitives_addon();
    al_shutdown_font_addon();
}

void destroy_sim_graphics(sim_graphics_t *sim_graphics) {
	destroy_al_hard(&(sim_graphics->al_hard));
	destroy_images(&(sim_graphics->sim_images));
}


void print_histograma_bar(double * results, ejeCartesiano_t * eje, ALLEGRO_COLOR color1, ALLEGRO_COLOR color2, char * font_type, ALLEGRO_COLOR color_font)
{
    ALLEGRO_FONT * font = al_load_ttf_font(font_type, FONT_SIZE,0);
    
    
    double x = 0.0, y = 0.0;
    bool tolerance_reached = false;
    bool escribir = false;
    
    if(eje->xMax > TOLERANCE_FONT_ROBOT)
    {
          tolerance_reached = true;  
    }
    
    for (int i = 0; i < eje->xMax; i++)
    {
        x = eje->apartamiento_x + (eje->elem_escala_x * (i+1));
        y = eje->apartamiento_y + (eje->elem_escala_y * (eje->yMax - results[i]));
        switch(i & 1)
        {
            case 1: al_draw_filled_rectangle(x-OFFSET_HISTOGRAMA, y, x+OFFSET_HISTOGRAMA, eje->origenY, color1); break;
            case 0: al_draw_filled_rectangle(x-OFFSET_HISTOGRAMA, y, x+OFFSET_HISTOGRAMA, eje->origenY, color2);
        }
        if(tolerance_reached)
        {
            if((i == 0) || (i == 1) || (i == 2) || (i == 3) || ((i + 1) >= eje->xMax))
            {
                escribir = true;
            }
        }
        else
        {
            escribir = true;
        }
        if(escribir)
        {
            al_draw_textf(font, color_font, x - OFFSET_HISTOGRAMA, y - (OFFSET_HISTOGRAMA*2), 0, "%.1f", results[i]);
            escribir = false;
        }
        
    }
    al_flip_display();
    
    al_destroy_font(font);
}

ejeCartesiano_t create_eje_cartesiano(unsigned int anchoTotal, unsigned int altoTotal, double xMax, double yMax, char * varX, char * varY)
{
    ejeCartesiano_t eje;
    eje.xMax = xMax;
    eje.yMax = yMax;
    eje.apartamiento_x = anchoTotal * OFFSET_EJES;
    eje.apartamiento_y = altoTotal * OFFSET_EJES;
    eje.long_eje_x = anchoTotal - (2*eje.apartamiento_x);
    eje.long_eje_y = altoTotal - (2*eje.apartamiento_y);
    eje.variableX = varX;
    eje.variableY = varY;
    eje.elem_escala_x = (eje.long_eje_x)/(MODULO(eje.xMax));
    eje.elem_escala_y = (eje.long_eje_y)/(MODULO(eje.yMax));
    eje.grosor = GROSOR_EJE_PRED;
    eje.numElemX = (eje.long_eje_x / eje.elem_escala_x);
    eje.numElemY = (eje.long_eje_y / eje.elem_escala_y);
    eje.origenX = eje.apartamiento_x;
    eje.origenY = eje.apartamiento_y + eje.long_eje_y;
    return eje;
}

void print_eje_cartesiano(ejeCartesiano_t * eje, ALLEGRO_COLOR color, char * font_type)
{
    ALLEGRO_FONT * font = al_load_ttf_font(font_type, FONT_SIZE,0);
    
    unsigned int x = 0, y = 0;
    al_draw_line(eje->origenX, eje->apartamiento_y, eje->apartamiento_x, eje->origenY, color, eje->grosor);
    al_draw_line(eje->origenX, eje->origenY, eje->long_eje_x + eje->origenX, eje->origenY, color, eje->grosor);
    for (unsigned int i = 1; i <= eje->numElemX; i++)
    {
        al_draw_line( (eje->origenX + (i * eje->elem_escala_x)), eje->origenY + OFFSET_INDICADOR, (eje->origenX + (i * eje->elem_escala_x)), eje->origenY - OFFSET_INDICADOR, color, eje->grosor );
        al_draw_textf(font, color, (eje->origenX + (i * eje->elem_escala_x)), eje->origenY + ((OFFSET_INDICADOR)*2), 0, "%d", i);
    }
    for (unsigned int i = 1; i <= eje->numElemY/SEPARACION_Y; i++)
    {
        al_draw_line(eje->origenX + OFFSET_INDICADOR, (eje->apartamiento_y + (i * eje->elem_escala_y*SEPARACION_Y)), eje->origenX - OFFSET_INDICADOR, (eje->apartamiento_y + (i * eje->elem_escala_y*SEPARACION_Y)), color, eje->grosor);
        
    }
    al_draw_textf(font, color, (eje->apartamiento_x + eje->long_eje_x), eje->origenY + (eje->apartamiento_y/4), 0, "%s", eje->variableX);
    al_draw_textf(font, color, eje->apartamiento_x /2, eje->apartamiento_y, 0, "%s", eje->variableY);
    
    al_destroy_font(font);
}

void print_wait_text(char * font_type, unsigned int alto, unsigned int ancho)
{
	ALLEGRO_FONT * font = al_load_ttf_font(font_type, FONT_SIZE*3, 0);
	ALLEGRO_COLOR  blanco = al_map_rgb(255, 255, 255);
	const char * string1 = "Please Wait...";
	const char * string2 = "Generating Graphic";
	al_draw_textf(font, blanco, ancho / 4, alto / 3, 0, "%s", string1);
	al_draw_textf(font, blanco, ancho / 4, alto / 2, 0, "%s", string2);
	al_flip_display();
	al_destroy_font(font);
}

void clear_display(void)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void print_titulo(unsigned int width_baldosa, unsigned int height_baldosa, unsigned int alto, unsigned int ancho, char * font_type)
{
	ALLEGRO_FONT * font = al_load_ttf_font(font_type, FONT_SIZE * 3, 0);
	ALLEGRO_COLOR  blanco = al_map_rgb(255, 255, 255);
	al_draw_textf(font, blanco, ancho / 4, 10, 0, "Graph for %dx%d floor", width_baldosa,height_baldosa);
	al_flip_display();
	al_destroy_font(font);
}

void print_tick_count(unsigned int tickCount, double height, double width, char * font_type)
{
	ALLEGRO_FONT * font = al_load_ttf_font(font_type, FONT_SIZE * 3, 0);
	ALLEGRO_COLOR  negro = al_map_rgb(0, 0, 0);
	al_draw_textf(font, negro, width /3, height/2, 0, "Total Tick Count: %d", tickCount);
	al_flip_display();
	al_destroy_font(font);
}
