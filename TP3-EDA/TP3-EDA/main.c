#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "simulation.h"
#include "sim_graphics.h"
#include "lib.h"    //parseCmd

#define SIZE_LOOKUPTABLE 4
#define AUX_LEN 20
#define TOPE_ANCHO 5
#define TOPE_ALTO 5
#define TOPE_ROBOTS 50
#define EOT '\0'

#define MODE 0
#define ROBOTS 1
#define WIDTH_P 2
#define HEIGHT_P 3
const char * lookUpTable[SIZE_LOOKUPTABLE] = {"mode", "robots", "width", "height"};

int parseCallback(char * key, char * value, void * userData);



int main(int argc, char** argv) 
{
    paramsType params;
    void * userData = &params;
    pCallback p2Callback = parseCallback;
	
    if(parseCmdLine(argc, argv, p2Callback, userData))
    {
        srand((unsigned int)time(NULL));
    
        paramsType params = {1, 20, 20, 1}; ////////////////
    
        sim_graphics_t sim_graphics;
        if(init_sim_graphics(&sim_graphics))
        {    
            if (params.mode == 1)
            {
				unsigned int tickCount = 0;
				unsigned int floorCleaned = 0;
                bool exit = false;
            
                simType * sim;
            
                sim = createSim(params.robots_count, params.height, params.width);
            
                if (sim != NULL)
                {
					draw_floor(&sim_graphics, sim->piso); // First draw
					draw_all_robots(&sim_graphics, sim->robots, sim->piso, sim->robotCount);
					al_flip_display();
                    while((floorCleaned < (sim->height)*(sim->width)) && (!exit))
                    {
                        floorCleaned += simulate(sim,&tickCount);
						draw_floor(&sim_graphics, sim->piso);
						draw_all_robots(&sim_graphics, sim->robots, sim->piso, sim->robotCount);
                        al_rest(0.03);
						al_flip_display();
                    }
					print_tick_count(tickCount, DISP_H, DISP_W,FONT_TYPE);
					al_flip_display();
					al_rest(5.0);
                }
                else
                {
                    printf("error al crear simulacion\n");
                }
                
                destroy_sim_graphics(&sim_graphics);
            
            
            }
            else if (params.mode == 2)
            {
                bool found = false;
                
				int r = 0;
				int j = 0;
				unsigned long int suma = 0;
				unsigned int ticks = 0;
                
				double results[TOPE_ROBOTS];
                
				print_wait_text(FONT_TYPE, DISP_H, DISP_W);

                simType * sim;
                
				init_arr(results, TOPE_ROBOTS);
				for (r = 0; (r < TOPE_ROBOTS) && (!found); r++)
				{
					suma = 0;
					for (j = 0; j < 1000; j++)
					{
						sim = createSim(r + 1, params.height, params.width);
						if (sim != NULL)
						{
							ticks = simulate_quick(sim);
						}
						else
						{
							printf("Error in Simulation Nro %d-%d\n", r, j);
							return 0;
						}
						destroySim(sim);
						suma += ticks;
					}
					results[r] = suma / 1000.0;
					if ((r>0) && ((results[r-1] - results[r]) < 0.1))
					{
						found = true;
					}
				}
				clear_display();
				ejeCartesiano_t eje = create_eje_cartesiano(DISP_W, DISP_H, (double) r, (double) results[0], "robots", "time");
				print_eje_cartesiano(&eje, al_color_name("white"), FONT_TYPE);
				print_titulo(sim->width, sim->height, DISP_H, DISP_W, FONT_TYPE);
				print_histograma_bar(results, &eje, al_color_name("blue"), al_color_name("hotpink"), FONT_TYPE, al_color_name("white"));
				getchar();
			}
		}
		else
		{
			fprintf(stderr, "failed to initialize graphics\n");
		}
    }
	else
    {
        fprintf(stderr, "failed to enter params\n");
    }
	return (EXIT_SUCCESS);
}


int parseCallback(char * key, char * value, void * userData)
{
    paramsType * data = userData;
    int ret = 1, value_int = 0, i = 0;        //inicializo sin error
	char key_aux[AUX_LEN];
    if(key == NULL)
    {
        ret = 0;    //no recibo parametros sin keys, devuelvo error
    }
    else
    {
		for (i = 0; (i < (AUX_LEN - 1)); i++) {
			key_aux[i] = (char)tolower(key[i]); // Pasamos todo a minusculas
			if (key[i] == EOT)
				key_aux[i] = EOT;
		}

        for(i = 0; (i < SIZE_LOOKUPTABLE) && strcmp(lookUpTable[i], key_aux); i++)
        {
           //nada, solo recorro la lookUpTable 
        }

        if(i == MODE)
        {
			value_int = atoi(value);
            if((value_int == 1) || (value_int == 2))
            {
                data->mode = value_int;
            }
            else
            {
                fprintf(stderr, "failed to enter 'mode'\n");
                ret = 0; //error
            }
        }
        else if(i == ROBOTS)
        {
			value_int = atoi(value);
            if((value_int > 0) && (value_int < TOPE_ROBOTS))  //se restringe el numero de robots
            {
                data->robots_count = value_int;
            }
            else
            {
                fprintf(stderr, "failed to enter 'robots'\n");
                ret = 0; //error
            }
        }
        else if(i == WIDTH_P)
        {
			value_int = atoi(value);
            if((value_int > 0) && (value_int < TOPE_ANCHO)) //se restringe el numero de baldosas en ancho
            {
                data->width = value_int;
            }
            else
            {
                fprintf(stderr, "failed to enter 'width'\n");
                ret = 0; //error
            }
        }
        else if(i == HEIGHT_P)
        {
			value_int = atoi(value);
            if((value_int > 0) && (value_int < TOPE_ALTO)) //se restringe el numero de baldosas en alto
            {
                data->height = value_int;
            }
            else
            {
                fprintf(stderr, "failed to enter 'height'\n");
                ret = 0; //error
            }
        }
    }
}




